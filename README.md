# Animatronic Eyeball Mechanism
An animatronic eyeball mechanism that rotates a sphereical eyeball 360° (or more) around any axis. Developed using ROS2 with microROS for the ESP32.

## Table of Contents

<!--ts-->
   * [About the Project](##About)
   * [Project Hardware and Software](##Hardware)
   * [Installation](#Installation)
<!--te-->

## About the Project
This eyeball mechanism is being developed by `Team Blink` at Vanderbilt University for our mechanical engineering senior captstone project. This project is sponsored by [Animax Designs](https://www.animaxdesigns.com/), a global animatronic company based in Nashville, TN. The mechanism is able to rotate a spherical eyeball around any axis, allowing any point on the sphere to be front facing. It has two operational modes: `Path Following` and `Facial Tracking` (hopefully).

While the code in this repository is specialized for this mechanism, hopefully it can serve as a guide for those looking to integrate `ROS2` and `microROS` into their own robotics projects.

## Project Hardware and Software
This project utilizes the following:
```
ESP32 Dev Modules
Ubuntu 22.04 (run on a VM)
ROS2 Humble
MicroRos
```

## Installation
This section is a guide on how I installed all of the necessary dependencies and setup the project workspaces. I pieced together a few different tutorials online as I couldn't find one that worked out of the gate. Links to those tutorials are at the end of this section. 

If you are unfamiliar with `ROS2` or `microROS`, check out the official [ROS2 Concepts Documentation](https://docs.ros.org/en/humble/Concepts.html) or [microROS Concepts Documentation](https://micro.ros.org/docs/concepts/client_library/introduction/).

### Structure
The project is structured to have a root directory `Animatronic-Eyeball-Mechanism`, with two workspaces - `microros_Ws` and `ros2_ws`. I did this because the `microROS` applications that run on the microcontroller have a different build sequence than the traditional `ros2` packages that run on the host computer. There is likley a way to combine these into a single workspace but I left them separate for simplicity sake. 

### Installing Ubuntu on a Virutal Machine
instructions

### Installing ROS2 Humble
instructions

### Installing MicroROS
To install `microROS` follow the official [tutorial](https://micro.ros.org/docs/tutorials/core/first_application_rtos/freertos/) on creating your first microROS application for FreeRTOS. Since this project uses the ESP32 Dev Modules that run freeRTOS, the `# Create step` command is:

`ros2 run micro_ros_setup create_firmware_ws.sh freertos esp32`

If you are using a different microcontroller with a different RTOS the `# Create step` command will be different.
