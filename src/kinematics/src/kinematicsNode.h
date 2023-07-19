#ifndef KINEMATICS_NODE_H_
#define KINEMATICS_NODE_H_

#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
# include "sensor_msgs/JointState.h"
# include "geometry_msgs/TwistStamped.h"
class kinematicsNode
{
private:
    ros::NodeHandle n_;
    ros::NodeHandle nPriv_;
    ros::Subscriber wheelDataSubscriber;
    ros::Subscriber CmdSubscriber;
    ros::Publisher Pub_;
    ros::Publisher PubRPM_;
    void wheelDataCallback(sensor_msgs::JointState msg);
    void Publish();
    void PublishRPM();
    void calculateRobot();
    void calculateInverseRobot(geometry_msgs::TwistStamped msg);
    double R = 0.07;
    double l = 0.2;
    double w = 0.169;
    ros::Time time;
    bool ticks = true;
    double oldStamp = 0;
    double velocity[4];
    double oldposition[4] = {0, 0, 0, 0};
    double states[3];
    double vwheel[4];
    double VCog[3];
    double rpm[4];
    double N;
    


public:
    kinematicsNode();
    ~kinematicsNode();
    bool start = false;
};


#endif  // KINEMATICS_NODE_H_
