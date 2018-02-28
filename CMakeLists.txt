cmake_minimum_required(VERSION 2.8.3)
project(joystick_repeater)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  mavros_msgs
)

catkin_package()


include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(joystick_repeater src/main.cpp)
add_executable(attitude_repeater src/attitude_control.cpp)


target_link_libraries(joystick_repeater ${catkin_LIBRARIES})
target_link_libraries(attitude_repeater ${catkin_LIBRARIES})