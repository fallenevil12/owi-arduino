#include <Arduino.h>
#include <ros.h>
#include "owijoint.hh"
#include "jointconfig.hh"
#include "SerialHelper.hh"



/** not using, setup in loop() */
void setup() {
}

/** used as main(), actual loop inside */
void loop() {
    static JOINT joint[5] = { JOINT(joint0conf),
                              JOINT(joint1conf),
                              JOINT(joint2conf),
                              JOINT(joint3conf),
                              JOINT(joint4conf) };

    static const char menu[] = "\n=======================================\n" 
                               "0 - Peform initial joint direction test\n"
                               "1 - Perform pid movement test\n"
                               "2 - Become a ROS node\n"
                               "ENTER A NUMBER\n";
    

    Serial1.begin(9600);

    // Actual loop
    while (true) {
        int choice = displayMenu(String(menu), 3);
        switch (choice) {
          case 0:
            init_step_test(joint);
            break;

          case 1:
            {
            int i = displayMenu(String("\nEnter joint index\n"), 5);
            joint[i].pid_test(); 
            }
            break;

          case 2:
            Serial1.println("Please close the serial monitor\n"
                           "Then enter:\n"
                           "rosrun rosserial_python serial_node.py /dev/ttyACM0");
            delay(5000);
            {
            ROSSERIAL rosserial;
            rosserial.print("Hello");
            while(true) {
                float angle[] = {joint[0].getAngle(),
                                 joint[1].getAngle(),
                                 joint[2].getAngle(),
                                 joint[3].getAngle(),
                                 joint[4].getAngle()};
                rosserial.sendState(angle, 5);
                delay(1000);
            }
            }
            break;

          default:
            break;
        }

        delay(1000);
    }

}
