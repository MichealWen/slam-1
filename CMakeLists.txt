cmake_minimum_required(VERSION 2.8.3)
project(part2)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
)
find_package(PCL REQUIRED
  common io
)
find_package(OpenCV REQUIRED)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES part2
#  CATKIN_DEPENDS roscpp rospy std_msgs
#  DEPENDS system_lib
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)
include_directories(${PCL_INCLUDE_DIRS})
link_directories($(PCL_LIBRARY_DIRS))
add_definitions(${PCL_DEFINITIONS})


add_executable(part2 src/gen_pt_cloud.cpp)
target_link_libraries(part2 ${catkin_LIBRARIES})
target_link_libraries(part2 ${PCL_LIBRARIES} ${OpenCV_LIBS})

set(CMAKE_BUILD_TYPE Debug)
set(executable_output_path bin)

