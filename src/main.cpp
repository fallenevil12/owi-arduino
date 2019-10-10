#include <Arduino.h>
#include "owijoint.hh"
#include "jointconfig.hh"
#include "SerialHelper.hh"

/** put your setup code here, to run once */
void setup() {
    Serial.begin(9600);
}

/** put your main code here, to run repeatedly */
void loop() {
    static JOINT joint[5] = { JOINT(joint0conf),
                              JOINT(joint1conf),
                              JOINT(joint2conf),
                              JOINT(joint3conf),
                              JOINT(joint4conf) };

    static String menu("/n=======================================/n \
                        0 - Peform initial joint direction test/n \
                        1 - Perform pid movement test/n \
                        2 - Become a ROS node \
                        ENTER A NUMBER/n");

    while (1) {
        int choice = displayMenu(menu, 3);

        switch (choice) {
          case 0:
            init_step_test(joint);
            break;

          case 1:
            {
            int i = displayMenu(String("/nEnter joint index/n"), 5);
            joint[i].pid_test(); 
            }
            break;

          case 2:

            break;

          default:
            break;
        }

    }

}
