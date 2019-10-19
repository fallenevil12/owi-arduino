#include <Arduino.h>
#include <avr/sleep.h>
#include <Arduino_FreeRTOS.h>
#include <timers.h>
#include "ros.h"
#include "robotjoint.hh"
#include "jointconfig.hh"
#include "SerialHelper.hh"

/////////////////// Prototypes //////////////////

/** Callback for ROS whenever a new command is received. Handle updating target angle */
void cmdCallback(const owi::position_cmd& cmd);
/** Handle ROS communication */
void task_ROS(void *pvParams);
/** Handle serial communication */
void task_Serial(void *pvParams);
/** Handle actuation of joints */
void task_actuate(void *pvParams);

///////////////////// Globals ///////////////////
ROSSERIAL rosserial(&cmdCallback);
volatile bool ROSctrl = false; //TODO: use semaphore instead
//TODO: need to implement thread safe methods
JOINT joint[5] = {JOINT(joint0conf),
                  JOINT(joint1conf),
                  JOINT(joint2conf),
                  JOINT(joint3conf),
                  JOINT(joint4conf) };

///////////////////// Setup //////////////////////
void setup() {
    set_sleep_mode(SLEEP_MODE_IDLE);
    sleep_enable();
    Serial.begin(9600);
    rosserial.init(115200);
    xTaskCreate(&task_ROS, "ROS", 512, NULL, 0, NULL);
    xTaskCreate(&task_Serial, "MENU", 512, NULL, 0, NULL);
    xTaskCreate(&task_actuate, "ACTUATE", 512, NULL, 1, NULL);
}


/////////////////////// Tasks //////////////////////
void cmdCallback(const owi::position_cmd& cmd) {
    if (!ROSctrl) return;

    //Serial.println("Received a command");
    for (int i = 0; i < 5; i++) {
        //Serial.println(cmd.position[i]);
        joint[i].setTarget(cmd.position[i]);
    }
}

void task_ROS(void *pvParams) {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    while(true) {
        rosserial.putMsg("Hello");
        float angle[] = {joint[0].getAngle(),
                         joint[1].getAngle(),
                         joint[2].getAngle(),
                         joint[3].getAngle(),
                         joint[4].getAngle()};
        rosserial.putState(angle, 5);
        rosserial.update();
        vTaskDelayUntil(&xLastWakeTime, 10);
    }
}

void task_Serial(void *pvParams) {
    static char menu[] = "\n=======================================\n" 
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
                Serial.println("Positive direction test PASSED");
            } else {
                Serial.println("Positive direction test FAILED");
            }

            if (joint[i].test_step_neg()) {
                Serial.println("Negative direction test PASSED");
            } else {
                Serial.println("Negative direction test FAILED");
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

void task_actuate(void *pvParams) {
    while(!ROSctrl) {
        vTaskDelay(100);
    }

    TickType_t xLastWakeTime = xTaskGetTickCount();
    while(true) {
        for (int i = 0; i < 4; i++) {
            joint[i].actuate();
        } 
        vTaskDelayUntil(&xLastWakeTime, 5);
    }
}

/** Idle task */
void loop() {
    sleep_cpu();
}