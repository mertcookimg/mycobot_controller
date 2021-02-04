
#include "mycobot_robot.hh"
#include <ros/ros.h>
#include <controller_manager/controller_manager.h>

using namespace mycobot_controller;

int
main(int argc, char* argv[])
{
    ros::init(argc, argv, "mycobot_controller");

    MycobotHW robot = MycobotHW();
    controller_manager::ControllerManager manager(&robot);

    ros::Rate rate(1.0 / robot.getPeriod().toSec());
    ros::AsyncSpinner spinner(1);
    spinner.start();
    while (ros::ok())
    {
        robot.read();
        manager.update(robot.getTime(), robot.getPeriod());
        robot.write();
        rate.sleep();
    }
    return 0;
}