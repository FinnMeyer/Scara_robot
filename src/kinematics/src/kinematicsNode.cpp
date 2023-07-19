# include <ros/ros.h>
# include <nav_msgs/Odometry.h>
# include "kinematicsNode.h"
# include "sensor_msgs/JointState.h"
# include "geometry_msgs/TwistStamped.h"
#include <kinematics/wheels_rpm.h>
# include <math.h>
/****************************
 * Public Functions
 ****************************/

/*
 */

/**
 * @brief Constructor for the kinematicsNode class
 */
kinematicsNode::kinematicsNode()
        : n_                       ()
        , nPriv_                   ("~")
        , Pub_(n_.advertise<geometry_msgs::TwistStamped>("/cmd_vel", 1000))
        , PubRPM_(n_.advertise<kinematics::wheels_rpm>("/wheels_rpm", 1000))
        , wheelDataSubscriber(n_.subscribe("/wheel_states", 1, &kinematicsNode::wheelDataCallback, this))
        , CmdSubscriber(n_.subscribe("/cmd_vel", 1, &kinematicsNode::calculateInverseRobot, this))

{
    n_.getParam("/kinematics/R", R);
    n_.getParam("/kinematics/N", N);
    n_.getParam("/kinematics/l", l);
    n_.getParam("/kinematics/w", w);
    n_.getParam("/kinematics/ticks", ticks);
}

kinematicsNode::~kinematicsNode(){
};
/****************************
 * Private Functions
 * General information: Notes regarding the variables can be found at the declaration in the kinematicsNode.h file
 ****************************/
void kinematicsNode::wheelDataCallback(sensor_msgs::JointState msg){
    if(ticks == true){
        velocity[0] = (msg.position[0] - oldposition[0]) * 2 * M_PI / 5 / N * R / ((msg.header.stamp.toSec() - oldStamp));
        velocity[1] = (msg.position[1] - oldposition[1]) * 2 * M_PI / 5 / N * R / ((msg.header.stamp.toSec() - oldStamp));
        velocity[2] = (msg.position[2] - oldposition[2]) * 2 * M_PI / 5 / N * R / ((msg.header.stamp.toSec() - oldStamp));
        velocity[3] = (msg.position[3] - oldposition[3]) * 2 * M_PI / 5 / N * R / ((msg.header.stamp.toSec() - oldStamp));
        if(start == false){
            for(int i = 0; i < 4; i++){
                velocity[i] = 0;
            }   
        }
        for(int i = 0; i < 4; i++){
            oldposition[i] = msg.position[i];
        }   
        oldStamp = msg.header.stamp.toSec();
        start = true;
    }
    else{
        velocity[0] = msg.velocity[0] * R / 60 / 5;
        velocity[1] = msg.velocity[1] * R / 60 / 5;
        velocity[2] = msg.velocity[2] * R / 60 / 5;
        velocity[3] = msg.velocity[3] * R / 60 / 5;
    }
    time = msg.header.stamp;
    calculateRobot();
    Publish();    
}

void kinematicsNode::calculateRobot(){
    double A [3][4] =  {{1, 1, 1, 1},
                        {-1, 1, 1, -1},
                        {-1/(l + w), 1/(l + w), -1/(l + w), 1/(l + w)}};
    for(int i = 0; i < 3; i++){
        states[i] = 0;
        for(int j = 0; j < 4; j++){
            states[i] += 0.25 * A[i][j] * velocity[j];
        }
    }
}

void kinematicsNode::calculateInverseRobot(geometry_msgs::TwistStamped msg){
    double Ainverse [4][3] =  {{1, -1, -1/(l + w)},
                                {1, 1, 1/(l + w)},
                                {1, 1, -1/(l + w)},
                                {1, -1, 1/(l + w)}};
    VCog[0] = msg.twist.linear.x;
    VCog[1] = msg.twist.linear.y;
    VCog[2] = msg.twist.angular.z;
    for(int i = 0; i < 4; i++){
        vwheel[i] = 0;
        for(int j = 0; j < 3; j++){
            vwheel[i] += Ainverse[i][j] * VCog[j];
        }
        rpm[i] = vwheel[i] / R * 60 * 5;
    }
    PublishRPM();
}

void kinematicsNode::Publish(){
    geometry_msgs::TwistStamped Kinematics;
     
    Kinematics.header.frame_id = "base_link";
    Kinematics.header.stamp = time;
    Kinematics.twist.linear.x = states[0];
    Kinematics.twist.linear.y = states[1];
    Kinematics.twist.linear.z = 0;
    Kinematics.twist.angular.x = 0;
    Kinematics.twist.angular.y = 0;
    Kinematics.twist.angular.z = states[2];
    Pub_.publish(Kinematics);  
}

void kinematicsNode::PublishRPM(){
    kinematics::wheels_rpm Rpm;
     
    Rpm.header.frame_id = "base_link";
    Rpm.rpm_fl = rpm[0];
    Rpm.rpm_fr = rpm[1];
    Rpm.rpm_rl = rpm[2];
    Rpm.rpm_rr = rpm[3];
    PubRPM_.publish(Rpm);  
}
 