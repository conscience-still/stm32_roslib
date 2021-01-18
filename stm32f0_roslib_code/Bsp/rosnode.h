// #ifndef _ROSNODE_H
// #define _ROSNODE_H


// #include "stm32f0xx.h"
// #include <ros.h>
// #include <ros/time.h>
// #include <std_msgs/Int32MultiArray.h>
// #include <ros/time.h>
// #include <std_msgs/Float64.h>
// #include <std_msgs/Int16.h>
// #include <std_msgs/String.h>
// #include <geometry_msgs/Vector3.h>
// #include "geometry_msgs/Twist.h"
// #include "nav_msgs/Odometry.h"
// #include "sensor_msgs/Imu.h"

// class rosnode
// {
//     public:
//         rosnode(const char* n1, const char* n2, const char* n3, uint8_t CmdVelLenth_, uint8_t FbVelLenth_);
//         void PubVelFeedBack(int32_t* fbvel, uint8_t lenth);
//         void CmdVelCallBack(const std_msgs::Int32MultiArray& cmdvel);

//     private:
//         //
//         ros::NodeHandle nh;
//         uint8_t mnCmdVelLenth;
//         uint8_t mnFbVelLenth;
// //
//        // int32_t mnVelFeedBackData[mnFbVelLenth];
//         std_msgs::Int32MultiArray mnVelFeedBack;
//         std_msgs::Int32MultiArray mnCmdVel;


//          ros::Publisher*  mnvelfeedbackpub;
//          ros::Subscriber<std_msgs::Int32MultiArray>* mrcmdvelsub;
//       //  ros::Publisher  mrodompub;
// //

//         nav_msgs::Odometry odom_data;
//         sensor_msgs::Imu imu_data;

// };



// #endif