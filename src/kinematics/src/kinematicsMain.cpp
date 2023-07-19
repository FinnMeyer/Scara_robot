#include <ros/ros.h>
#include <cstdlib>
#include "kinematicsNode.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "kinematics");
    kinematicsNode kinematics;
    ros::spin();
    return EXIT_SUCCESS;
}
