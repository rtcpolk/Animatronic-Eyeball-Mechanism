// Author: Robert Polk
// Last Modified: 01/27/25

#include <chrono>
#include <functional>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/quaternion.hpp"

#include "NimBLEDevice.h"

/*
 * This program is responsible for creating a BLE server that connects with the internal esp. It then processes IMU data and publishes it to a ros2 tipic
 */

using namespace std::chrono_literals;


//====================================================================================================================//


/**
 * A struct to define what to do for client events
 */
struct ClientCallbacks final : public NimBLEClientCallbacks {
    /**
     * Called for connection events
     *
     * @param connectedClient - The client that connected
     */
    void onConnect(NimBLEClient *connectedClient) override
    {
        RCLCPP_INFO(*logger, "Connected to the server");
        connectedClient->updateConnParams(120, 120, 0, 60); //todo figure this out
    }

    /**
     * Called for disconnection events. Starts a new scan
     *
     * @param disconnectedClient - The client that disconnected
     * @param reason - The reason for disconnect
     */
    void onDisconnect(NimBLEClient *disconnectedClient, int reason) override;

    // Member Variables:
    std::shared_ptr<rclcpp::Logger> logger; // A ROS2 logger
};






/**
 * A ROS2 class to publish the IMU data
 */
class IMUPublisher final : public rclcpp::Node
{
public:
    IMUPublisher() : Node("minimal_publisher")
    {
        imu_publisher = this->create_publisher<geometry_msgs::msg::Quaternion>("imu_quaternion", 10);
        imu_timer = this->create_wall_timer(500ms, std::bind(&IMUPublisher::timer_callback, this));
    }

private:
    /**
     * Called whenever the specified time has elapsed.
     */
    void timer_callback()
    {
        auto message = geometry_msgs::msg::Quaternion();
        //RCLCPP_INFO(this->get_logger(), "Publishing: %f", message);
        imu_publisher->publish(message);
    }

    // Member Variables
    rclcpp::TimerBase::SharedPtr imu_timer;
    rclcpp::Publisher<geometry_msgs::msg::Quaternion>::SharedPtr imu_publisher;
};

/**
 * Main program method
 * @param argc - Number of arguments
 * @param argv - Array of arguments
 * @return - Error codes
 */
int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<IMUPublisher>());
    rclcpp::shutdown();
    return 0;
}
