#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <ros.h>
#include <timers.h>
#include "robotjoint.hh"
#include "jointconfig.hh"
#include "SerialHelper.hh"

/** Prototypes */
void cmdCallback(const trajectory_msgs::JointTrajectoryPoint& cmd);
void task_ROS(void *pvParams);
void task_Serial(void *pvParams);
void task_actuate(void *pvParams);

/** Globals */
ROSSERIAL rosserial(&cmdCallback);
volatile bool ROSctrl = false; //TODO: use semaphore
JOINT joint[5] = {JOINT(joint0conf),
                  JOINT(joint1conf),
                  JOINT(joint2conf),
                  JOINT(joint3conf),
                  JOINT(joint4conf) };

/** Setup */
void setup() {
    adnoserial.begin(9600);
    rosserial.init(115200);
    xTaskCreate(&task_ROS, "ROS", 512, NULL, 2, NULL);
    xTaskCreate(&task_Serial, "MENU", 512, NULL, 0, NULL);
    xTaskCreate(&task_actuate, "ACTUATE", 512, NULL, 0, NULL);
}

// Callback for ROS whenever a new command is received
// Update joints target angles
void cmdCallback(const trajectory_msgs::JointTrajectoryPoint& cmd) {
    if (!ROSctrl) return;

    adnoserial.println("Received a command");
    for (int i = 0; i < cmd.positions_length; i++) {
        adnoserial.println(cmd.positions[i]);
        joint[i].setTarget(cmd.positions[i]);
    }
}

/**
 * Handle ROS communication
 * the suscriber requires this task to use a high frequency to not miss receving message
 */
void task_ROS(void *pvParams) {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    TickType_t elapsed = 0;
    while(true) {
        elapsed++;
        if (elapsed == 10) {
            elapsed = 0;
            rosserial.pushMsg("Hello");
            float angle[] = {joint[0].getAngle(),
                            joint[1].getAngle(),
                            joint[2].getAngle(),
                            joint[3].getAngle(),
                            joint[4].getAngle()};
            rosserial.pushState(angle, 5);
        }
        rosserial.update();
        vTaskDelayUntil(&xLastWakeTime, 1);
    }
}

// Handle serial communication
void task_Serial(void *pvParams) {
    static char menu[] = "\nTo start the ROS node open a terminal and run command:\n"
                         "rosrun rosserial_python serial_node.py /dev/ttyACM0"
                         "\n=======================================\n" 
                         "0 - Peform initial joint direction test\n"
                         "1 - Perform pid movement test\n"
                         "2 - Pass control to ROS\n";

    while(true) {
        int choice = displayMenu(menu, 3);
        switch (choice) {

        case 0: //initial step test
            {
            int i = displayMenu("\nEnter joint index\n",5);
            if (joint[i].test_step_pos()) {
                adnoserial.println("Positive direction test PASSED");
            } else {
                adnoserial.println("Positive direction test FAILED");
            }

            if (joint[i].test_step_neg()) {
                adnoserial.println("Negative direction test PASSED");
            } else {
                adnoserial.println("Negative direction test FAILED");
            }
            }
            break;

        case 1: //PID test
            {
            int i = displayMenu("\nEnter joint index\n", 5);
            joint[i].pid_test();
            }
            break;

        case 2: //start ros node mode
            ROSctrl = true;
            vTaskSuspend(NULL);
            break;

        default:
            break;
        }
    }
}


// Handle actuation of joints
void task_actuate(void *pvParams) {
    while(true) {
        if (!ROSctrl) continue;
        for (int i = 0; i < 4; i++) {
            //joint[i].actuate();
        } 
        vTaskDelay(0);
    }
}

// Not used for RTOS
void loop() {}