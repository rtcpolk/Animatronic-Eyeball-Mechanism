# Project info
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
cmake_minimum_required(VERSION 3.8)
project(sensors)

# Fetch content
include(FetchContent)
FetchContent_Declare(
        nimble
        GIT_REPOSITORY https://github.com/h2zero/NimBLE-Arduino.git
        GIT_TAG master
)
FetchContent_MakeAvailable(nimble)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)

# Include NimBLE-Arduino headers
include_directories(${nimble_SOURCE_DIR}/src)

# Add executables
add_executable(talker src/publisher_member_function.cpp)
add_executable(listener src/subscriber_member_function.cpp)
add_executable(imu_publisher src/imu_publisher.cpp)

# Ament targets
ament_target_dependencies(talker rclcpp std_msgs)
ament_target_dependencies(listener rclcpp std_msgs)
ament_target_dependencies(imu_publisher rclcpp geometry_msgs)

# Install targets
install(TARGETS
        talker
        listener
        imu_publisher
        DESTINATION lib/${PROJECT_NAME})

ament_package()
