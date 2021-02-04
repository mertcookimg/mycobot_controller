# mycobot_controller
unofficial mycobot controller package

## Environment
|  |  |
|---|---|
| ROS | melodic |
| m5 atom | v2.4 |
| pymycobot| v2.1.2|
| pyserial| v3.5|

## Setup
```
cd your_ws/src
git clone https://github.com/mertcookimg/mycobot_ros.git
git clone https://github.com/mertcookimg/mycobot_controller.git
catkin build
```

## Moveit RealRobot
```
sudo chmod 666 /dev/ttyUSB0
roslaunch mycobot_controller demo_mycobot.launch
```

![moveit](https://user-images.githubusercontent.com/58113372/106903946-f40b9d80-673d-11eb-9303-1e4c55f885af.png)

![rqt_](https://user-images.githubusercontent.com/58113372/106903957-f66df780-673d-11eb-9693-461db503f767.png)

## Official Repositories
    * https://github.com/elephantrobotics/myCobot
    * https://github.com/elephantrobotics/myCobotROS
    * https://github.com/elephantrobotics/pymycobot


## License
This repository is licensed under the MIT license, see [LICENSE](./LICENSE).  
Unless attributed otherwise, everything in this repository is licensed under the MIT license.

### Acknowledgements

* [elephantrobotics/myCobotROS](https://github.com/elephantrobotics/myCobotROS)
    * `Copyright (c) 2020, Elephant Robotics`
    * [BSD-2-Clause](https://github.com/elephantrobotics/myCobotROS/blob/cc9c7151b60709c445e1d2bdf500b9fbad91f841/LICENSE)

* [ros-planning/moveit](https://github.com/ros-planning/moveit)
    * `Copyright (c) 2008-2013, Willow Garage, Inc.`
    * [BSD-3-Clause](https://github.com/ros-planning/moveit/blob/664ae01803abf5e0b4649063102357262de9e05c/LICENSE.txt)
    
* [nisshan-x/mycobot_moveit](https://github.com/mertcookimg/mycobot_moveit)
    * [MIT](https://github.com/nisshan-x/mycobot_moveit/blob/main/LICENSE)

* [Tiryoh/mycobot_ros](https://github.com/Tiryoh/mycobot_ros)
    * [MIT](https://github.com/Tiryoh/mycobot_ros/blob/main/LICENSE)