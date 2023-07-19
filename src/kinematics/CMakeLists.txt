cmake_minimum_required(VERSION 2.8.3)
project(kinematics)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp std_msgs message_generation REQUIRED)
add_message_files(DIRECTORY msg FILES wheels_rpm.msg)

generate_messages(
   DEPENDENCIES
   std_msgs
 )
## Declare a catkin package
catkin_package()


include_directories(msg ${catkin_INCLUDE_DIRS})

add_executable(kinematics_node src/kinematicsMain.cpp src/kinematicsNode.cpp)
add_dependencies(kinematics_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(kinematics_node ${catkin_LIBRARIES})
