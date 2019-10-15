#include <Arduino.h>
#include <ros.h>
#include <Arduino_FreeRTOS.h>
#include "owijoint.hh"
#include "jointconfig.hh"
#include "SerialHelper.hh"

void cmdCallback(const trajectory_msgs::JointTrajectoryPoint& cmd);
void task_ROS(void *pvParameters);
void task_Serial(void *pvParameters);

ROSSERIAL rosserial(&cmdCallback);

JOINT joint[5] = {JOINT(joint0conf),
                  JOINT(joint1conf),
                  JOINT(joint2conf),
                  JOINT(joint3conf),
                  JOINT(joint4conf) };

void setup() {
    adnoserial.begin(9600);
    rosserial.init(115200);
    xTaskCreate(&task_ROS, "ROS", 512, NULL, 2, NULL);
    xTaskCreate(&task_Serial, "MENU", 512, NULL, 0, NULL);
}

// Callback for ROS whenever a new command is received
void cmdCallback(const trajectory_msgs::JointTrajectoryPoint& cmd) {
    adnoserial.println("Received command");
    for (int i = 0; i < cmd.positions_length; i++) {
        joint[i].driveTo(cmd.positions[i]);
    }
}

// Handle ROS communication periodically
void task_ROS(void *pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    while(true) {
        rosserial.pushMsg("Hello");
        float angle[] = {joint[0].getAngle(),
                         joint[1].getAngle(),
                         joint[2].getAngle(),
                         joint[3].getAngle(),
                         joint[4].getAngle()};
        rosserial.pushState(angle, 5);
        rosserial.update();

        vTaskDelayUntil(&xLastWakeTime, 100/portTICK_PERIOD_MS);
    }
}

void task_Serial(void *pvParameters) {
    static char menu[] = "\n=======================================\n" 
                         "0 - Peform initial joint direction test\n"
                         "1 - Perform pid movement test\n"
                         "2 - Become a ROS node\n";
    
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
            adnoserial.println( "\nTo start the node run command:\n"
                                "rosrun rosserial_python serial_node.py /dev/ttyACM0");
            
            break;

        default:
            break;
        }
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}

// Not used for RTOS
void loop() {}