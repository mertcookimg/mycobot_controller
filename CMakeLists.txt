cmake_minimum_required(VERSION 3.0.2)
project(mycobot_controller)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  tf
  moveit_ros_planning_interface
  hardware_interface
  transmission_interface
  controller_manager
)

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS roscpp hardware_interface transmission_interface controller_manager
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(mycobot_controller src/mycobot_hw_interface_node.cc src/mycobot_robot.cc)
add_dependencies(mycobot_controller ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(mycobot_controller
  ${catkin_LIBRARIES}
)

install(DIRECTORY launch DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
  PATTERN "setup_assistant.launch" EXCLUDE)
install(DIRECTORY config DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})

catkin_install_python(PROGRAMS
  scripts/mycobot_bridge.py
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)