
#include <geometry_msgs/Vector3.h>
#include <math.h>
#include <ros.h>
#include <ros/time.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Int8.h>
#include <std_msgs/Int32MultiArray.h>
#include <std_msgs/String.h>
#include <stdio.h>

#include "battery.h"
#include "geometry_msgs/Transform.h"
#include "geometry_msgs/Twist.h"
#include "hardwareserial.h"
#include "nav_msgs/Odometry.h"
#include "periph.h"
#include "sensor_msgs/ChannelFloat32.h"
#include "sensor_msgs/Imu.h"
#include "stm32f0xx.h"
#include "timer.h"
#include "wheel.h"
#include "string.h"
void delay(int n) {
  for (int j = 0; j < n; j++) {
    for (int i = 0; i < 65536; i++)
      ;
  }
}
#define mnCmdVelLenth 7
void CmdVelCallBack(const geometry_msgs::Transform& cmdvel) {
  float tmp[mnCmdVelLenth];
  tmp[0] = cmdvel.rotation.x;
  tmp[1] = cmdvel.rotation.y;
  tmp[2] = cmdvel.rotation.z;

  tmp[3] = cmdvel.rotation.w;
  tmp[4] = cmdvel.translation.x;

  tmp[5] = cmdvel.translation.y;
  tmp[6] = cmdvel.translation.z;

  SetWheelGeometry(tmp[5], tmp[6]);
}

int main(void) {
  TimerInit();
  
  PeriphInit();
  WheelInit();
   
  ros::NodeHandle nh;
  initialise();
  nh.initNode();

  while (!nh.connected()) {
    // nh.loginfo("ros is not connect\r\n");
    nh.spinOnce();
  }
  nh.loginfo("ros is connect\r\n");
  // rosnode RosNode("VelFb_","VelCmd_","odom_",7,7);
  delay(100);
  uint16_t timer20mscnt = 0;
  float fbVel[7] = {0}; 

  sensor_msgs::ChannelFloat32 VelFeedBack;
  sensor_msgs::ChannelFloat32 VelLog;
  std_msgs::Int8 VelBumperFeedBack;

  ros::Publisher velfeedbackpub("VelFb_", &VelFeedBack);
  ros::Subscriber<geometry_msgs::Transform> cmdvelsub("VelCmd_",CmdVelCallBack);

  nh.advertise(velfeedbackpub);
  nh.subscribe(cmdvelsub);
  nh.spinOnce();
  // delay(100);
  // nh.loginfo("main thread start");

  while (1) {



    if (GetTimer1msFlag()) {
      SetTImerImsFlag(0);
      timer20mscnt++;


      if (timer20mscnt >= 20) {
        timer20mscnt = 0;
        ControlServo();
        GetWheelVel(&fbVel[5], &fbVel[6]);
   

        VelFeedBack.name = "lyn_test";
        VelFeedBack.values = fbVel;
        VelFeedBack.values_length = 7;
        velfeedbackpub.publish(&VelFeedBack);



      }
      nh.spinOnce();
    }
  }
}
