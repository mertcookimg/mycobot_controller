#include <ros/ros.h>
#include "mycobot_robot.hh"
#include "mycobot_common.hh"
#include <hardware_interface/joint_command_interface.h>
#include <hardware_interface/joint_state_interface.h>
#include <hardware_interface/robot_hw.h>
#include <map>
#include <string>
#include <vector>
#include <std_msgs/Float32MultiArray.h>
using namespace mycobot_controller;

MycobotHW::MycobotHW() : nh_(""), private_nh_("~")
{
  hardware_interface::JointStateHandle state_handle_1("joint1", &pos_[0], &vel_[0], &eff_[0]);
  joint_state_interface_.registerHandle(state_handle_1);
  hardware_interface::JointStateHandle state_handle_2("joint2", &pos_[1], &vel_[1], &eff_[1]);
  joint_state_interface_.registerHandle(state_handle_2);
  hardware_interface::JointStateHandle state_handle_3("joint3", &pos_[2], &vel_[2], &eff_[2]);
  joint_state_interface_.registerHandle(state_handle_3);
  hardware_interface::JointStateHandle state_handle_4("joint4", &pos_[3], &vel_[3], &eff_[3]);
  joint_state_interface_.registerHandle(state_handle_4);
  hardware_interface::JointStateHandle state_handle_5("joint5", &pos_[4], &vel_[4], &eff_[4]);
  joint_state_interface_.registerHandle(state_handle_5);
  hardware_interface::JointStateHandle state_handle_6("joint6", &pos_[5], &vel_[5], &eff_[5]);
  joint_state_interface_.registerHandle(state_handle_6);
  registerInterface(&joint_state_interface_);

  hardware_interface::JointHandle eff_handle_1(joint_state_interface_.getHandle("joint1"), &cmd_[0]);
  joint_position_interface_.registerHandle(eff_handle_1);
  hardware_interface::JointHandle eff_handle_2(joint_state_interface_.getHandle("joint2"), &cmd_[1]);
  joint_position_interface_.registerHandle(eff_handle_2);
  hardware_interface::JointHandle eff_handle_3(joint_state_interface_.getHandle("joint3"), &cmd_[2]);
  joint_position_interface_.registerHandle(eff_handle_3);
  hardware_interface::JointHandle eff_handle_4(joint_state_interface_.getHandle("joint4"), &cmd_[3]);
  joint_position_interface_.registerHandle(eff_handle_4);
  hardware_interface::JointHandle eff_handle_5(joint_state_interface_.getHandle("joint5"), &cmd_[4]);
  joint_position_interface_.registerHandle(eff_handle_5);
  hardware_interface::JointHandle eff_handle_6(joint_state_interface_.getHandle("joint6"), &cmd_[5]);
  joint_position_interface_.registerHandle(eff_handle_6);
  registerInterface(&joint_position_interface_);
  joint_res_sub_ = nh_.subscribe("/joint_res_", 10, &MycobotHW::jointCallback, this);
  joint_cmd_pub_ = nh_.advertise<std_msgs::Float32MultiArray>("/joint_cmd_", 10);
}


MycobotHW::~MycobotHW()
{
}

ros::Time
MycobotHW::getTime() const
{
    return ros::Time::now();
}

ros::Duration
MycobotHW::getPeriod() const
{
    return ros::Duration(TIME_PERIOD);
}

void 
MycobotHW::jointCallback(const std_msgs::Float32MultiArray::ConstPtr &msg){
  for(int i=0; i<NUM_JOINT; i++){
    pos_[i] = msg->data[i];
  }
}

void
MycobotHW::read()
{
//   joint_res_sub_ = nh_.subscribe("/joint_res_", 10, &MycobotHW::jointCallback, this);
  for(int i=0; i<NUM_JOINT; i++){
    vel_[i] = 0;
    eff_[i] = 0;
  }
}

void
MycobotHW::write()
{
  std_msgs::Float32MultiArray joint_commands;
  joint_commands.data.resize(NUM_JOINT);
  for(int i=0; i<NUM_JOINT; i++){
    joint_commands.data[i] = cmd_[i];
  }
  joint_cmd_pub_.publish(joint_commands);
}