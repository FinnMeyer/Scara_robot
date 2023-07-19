#include <ros/ros.h>
#include "ImuNode.h"


/**
 * @brief Constructor for the ImuNode class
 */
ImuNode::ImuNode()
        : n()
        , odometrySub(n.subscribe("/cog_position", 1, &ImuNode::odometryCallback, this, ros::TransportHints().tcpNoDelay()))
{
}


void ImuNode::odometryCallback(nav_msgs::Odometry msg){
    vCog = {msg.twist.twist.linear.x, msg.twist.twist.linear.y};
    yawRate = msg.twist.twist.angular.z;
    publishTorque();
}


void ImuNode::publishTorque(){
    egn_messages::ControlOutput RecommendedSlipControllerTorque;
    RecommendedSlipControllerTorque.header.frame_id = "car_base";
    RecommendedSlipControllerTorque.header.stamp = ros::Time::now();

    RecommendedSlipControllerTorque.TorqueOutputFL = finalTorque[0];
    RecommendedSlipControllerTorque.TorqueOutputFR = finalTorque[1];
    RecommendedSlipControllerTorque.TorqueOutputRL = finalTorque[2];
    RecommendedSlipControllerTorque.TorqueOutputRR = finalTorque[3];

    controlPub.publish(RecommendedSlipControllerTorque);
}
