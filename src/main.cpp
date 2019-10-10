#include <Arduino.h>
#include <ros.h>
#include <std_msgs/String.h>
#include "owijoint.hh"
#include "jointconfig.hh"
#include "SerialHelper.hh"

/** not using, setup in loop() */
void setup() {
    // not using, setup in loop()
}

/** used as main(), actual loop inside */
void loop() {
    static JOINT joint[5] = { JOINT(joint0conf),
                              JOINT(joint1conf),
                              JOINT(joint2conf),
                              JOINT(joint3conf),
                              JOINT(joint4conf) };

    static String menu("\n=======================================\n" 
                       "0 - Peform initial joint direction test\n"
                       "1 - Perform pid movement test\n"
                       "2 - Become a ROS node\n"
                       "ENTER A NUMBER\n");

    static ros::NodeHandle node;
    static std_msgs::String msg;
    static ros::Publisher publisher("message", &msg);

    // Actual loop forever
    while (true) {
        Serial.begin(9600);

        int choice = displayMenu(menu, 3);
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
            node.initNode();
            node.advertise(publisher);
            msg.data = "Hello";
            publisher.publish(&msg);
            node.spinOnce();
            break;

          default:
            break;
        }

        delay(1000);
    }

}
