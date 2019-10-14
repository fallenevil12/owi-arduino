#include <Arduino.h>
#include <ros.h>
#include <Arduino_FreeRTOS.h>
#include "owijoint.hh"
#include "jointconfig.hh"
#include "SerialHelper.hh"

void cmdCallback(const trajectory_msgs::JointTrajectoryPoint& cmd);
void taskROS(void *pvParameters);

ROSSERIAL rosserial(&cmdCallback);

JOINT joint[5] = {JOINT(joint0conf),
                  JOINT(joint1conf),
                  JOINT(joint2conf),
                  JOINT(joint3conf),
                  JOINT(joint4conf) };

char menu[] = "\n=======================================\n" 
                         "0 - Peform initial joint direction test\n"
                         "1 - Perform pid movement test\n"
                         "2 - Become a ROS node\n";

void setup() {
    adnoserial.begin(9600);
    rosserial.init(115200);
}

void loop() {

    int choice = displayMenu(String(menu), 3);
    switch (choice) {

    case 0: //initial step test
        {
          int i = displayMenu(String("\nEnter joint index\n"),5);
          if (joint[i].test_step_pos()) {
              adnoserial.println("Positive direction test PASSED");
          } else {
              adnoserial.println("Positive direction test FAILED");
          }

          if (joint[i].test_step_neg()) {
              adnoserial.println("negative direction test PASSED");
          } else {
              adnoserial.println("negative direction test FAILED");
          }
        }
        break;

    case 1: //PID test
        {
        int i = displayMenu(String("\nEnter joint index\n"), 5);
        joint[i].pid_test();
        }
        break;

    case 2: //start ros node mode, spin forever
        adnoserial.println("\nTo start the node run command:\n"
                        "rosrun rosserial_python serial_node.py /dev/ttyACM0");
        while(true) {
            float angle[] = {joint[0].getAngle(),
                              joint[1].getAngle(),
                              joint[2].getAngle(),
                              joint[3].getAngle(),
                              joint[4].getAngle()};
            rosserial.pushState(angle, 5);
            rosserial.update();
            delay(10);
        }
        break;

    default:
        break;
    }
}




void cmdCallback(const trajectory_msgs::JointTrajectoryPoint& cmd) {
    adnoserial.println("Received command");
    for (int i = 0; i < cmd.positions_length; i++) {
        joint[i].driveTo(cmd.positions[i]);
    }
}