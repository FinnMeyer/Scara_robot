#include <ros/ros.h>
#include "ImuNode.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "egn_slip_control");
    ImuNode Imu;
    ros::spin();
    return EXIT_SUCCESS;
}
