#pragma once

#include <fstream>
#include <ros/ros.h>

#include <nav_msgs/Imu.h>


class ImuNode
{
private:
    ros::NodeHandle n;
    ros::Subscriber ImuSub;
    ros::Publisher ImuPub;

    double yawRate; ///< measured yaw rate in rad/s
    double steerAngle; ///< measured steering angle at the wheels in rad


    void odometryCallback(nav_msgs::Odometry msg);
    void publishTorque();
    
public:
    ImuNode();
    ImuNode(const ImuNode&) = delete;
    ImuNode& operator=(const ImuNode&) = delete;
    ImuNode(ImuNode&&) = delete;
    ImuNode& operator=(ImuNode&&) = delete;
};
