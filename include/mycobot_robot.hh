#ifndef _MYCOBOT_ROBOT_HH_
#define _MYCOBOT_ROBOT_HH_

#include <ros/ros.h>
#include <hardware_interface/joint_command_interface.h>
#include <hardware_interface/joint_state_interface.h>
#include <hardware_interface/robot_hw.h>
#include "mycobot_common.hh"
#include <map>
#include <string>
#include <vector>
#include <std_msgs/Float32MultiArray.h>

namespace mycobot_controller
{
    class MycobotHW : public hardware_interface::RobotHW
    {
    public:
        MycobotHW();
        virtual ~MycobotHW();
        ros::Time getTime() const;
        ros::Duration getPeriod() const;
        void read();
        void write();
    private:
        ros::NodeHandle nh_;
        ros::NodeHandle private_nh_;
        ros::Publisher joint_cmd_pub_;
        ros::Subscriber joint_res_sub_;
        hardware_interface::JointStateInterface joint_state_interface_;
        hardware_interface::PositionJointInterface joint_position_interface_;
        double cmd_[NUM_JOINT] = {};
        double pos_[NUM_JOINT] = {};
        double vel_[NUM_JOINT] = {};
        double eff_[NUM_JOINT] = {};
        void jointCallback(const std_msgs::Float32MultiArray::ConstPtr &msg);
    };
};

#endif // _MYCOBOT_ROBOT_HW
