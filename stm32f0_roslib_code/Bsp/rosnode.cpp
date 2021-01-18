// #include "rosnode.h"
// #include "brushandVuuc.h"
// #include "wheel.h"
// #include "string.h"
// #include <stdlib.h>


// rosnode::rosnode(const char* n1,const char *n2, const char* n3,uint8_t CmdVelLenth_,uint8_t FbVelLenth_):
//             mnCmdVelLenth(CmdVelLenth_),mnFbVelLenth(FbVelLenth_)
                
// {

//     nh.initNode();

//     while (!nh.connected()) {
//         nh.spinOnce();
//     }
//     nh.loginfo("ros is connect");

//     ros::Publisher tmp(n1,&mnVelFeedBack);
//      *mnvelfeedbackpub = tmp;
//      //ros::Subscriber<std_msgs::Int32MultiArray> tmp1(n2,CmdVelCallBack);
//     //*mrcmdvelsub = tmp1;

//     // mnvelfeedbackpub.topic_ = n1;
//     // mnvelfeedbackpub.msg_ = &mnVelFeedBack;
//     // mnvelfeedbackpub.endpoint_ = rosserial_msgs::TopicInfo::ID_PUBLISHER;
//      nh.advertise(*mnvelfeedbackpub);

    
//     // mrcmdvelsub.topic_ = n2;
//     // mrcmdvelsub.cb_ = &mnCmdVel;
//     // mrcmdvelsub.endpoint_ = rosserial_msgs::TopicInfo::ID_SUBSCRIBER;
//     nh.subscribe(*mrcmdvelsub);
//     // mrodompub.topic_ = n1;
//     // mrodompub.msg_ = &mnVelFeedBack;
//     // mrodompub.endpoint = rosserial_msgs::TopicInfo::ID_PUBLISHER;
//     // nh.advertise(*mrodompub);


// }
// void rosnode::CmdVelCallBack(const std_msgs::Int32MultiArray& cmdvel)
// {

//     // int32_t tmp[mnCmdVelLenth];
//     // memcpy(cmdvel.data,tmp,mnCmdVelLenth);
//     // int i =0;
//     // for( ;i<5;i++){
//     //     SetBruAndVuucExpVel(i,tmp[i]);
//     // }
//     // SetWheelGeometry((float)tmp[i],(float)tmp[i+1]);    

// }




// void rosnode::PubVelFeedBack(int32_t* fbvel,uint8_t lenth)
// {
//     mnVelFeedBack.data_length = lenth;
//     mnVelFeedBack.data = fbvel;
//     mnvelfeedbackpub->publish(&mnVelFeedBack);
// }
