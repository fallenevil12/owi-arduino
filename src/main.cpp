#include <Arduino.h>
#include <ros.h>
#include "owijoint.hh"
#include "jointconfig.hh"
#include "SerialHelper.hh"

void cmdCallback(const trajectory_msgs::JointTrajectoryPoint &cmd) {
    for (int i = 0; i < cmd.positions_length; i++) {
        adnoserial.Serial.println(cmd.positions[i]);
    }
}

ADNOSERIAL adnoserial(Serial1);
ROSSERIAL rosserial(&cmdCallback);

/** dummy, not used */
void setup() {}

/** used as main(), actual loop inside */
void loop() {
    adnoserial.Serial.println("Yo coming");
    
    JOINT joint[5] = {JOINT(joint0conf),
                      JOINT(joint1conf),
                      JOINT(joint2conf),
                      JOINT(joint3conf),
                      JOINT(joint4conf) };

    char menu[] = "\n=======================================\n" 
                               "0 - Peform initial joint direction test\n"
                               "1 - Perform pid movement test\n"
                               "2 - Become a ROS node\n"
                               "ENTER A NUMBER\n";

    // Actual loop
    while (true) {
        int choice = adnoserial.displayMenu(String(menu), 3);
        switch (choice) {
          case 0: //initial step test
            init_step_test(joint);
            break;

          case 1: //PID test
            {
            int i = adnoserial.displayMenu(String("\nEnter joint index\n"), 5);
            joint[i].pid_test();
            }
            break;

          case 2:
            {
            adnoserial.Serial.println("\nTo start the node run command:\n"
                           "rosrun rosserial_python serial_node.py /dev/ttyACM0");

            rosserial.print("Hello");
            while(true) {
                adnoserial.Serial.println("Yo Im here");
                rosserial.print("Hello");
                // float angle[] = {joint[0].getAngle(),
                //                  joint[1].getAngle(),
                //                  joint[2].getAngle(),
                //                  joint[3].getAngle(),
                //                  joint[4].getAngle()};
                // rosserial.sendState(angle, 5);
                delay(1000);
            }
            adnoserial.Serial.println("Yo I'm outta here");
            }
            break;

          default:
            break;
        }

        delay(1000);
    }

}
