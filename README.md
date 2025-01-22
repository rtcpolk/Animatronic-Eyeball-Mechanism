# Animatronic Eyeball Mechanism
An animatronic eyeball mechanism that rotates a sphereical eyeball 360° (or more) around any axis. Developed using ROS2 with microROS for the ESP32.

## Table of Contents

<!--ts-->
   * [About the Project](##About)
   * [Project Hardware and Software](##Hardware)
   * [Installation](#Installation)
<!--te-->

## About the Project
This eyeball mechanism is being developed by `Team Blink` at Vanderbilt University for our mechanical engineering senior captstone project. This project is sponsored by [Animax Designs](https://www.animaxdesigns.com/), a global animatronic company based in Nashville, TN. The mechanism is able to rotate a spherical eyeball around any axis and has two operational modes: `Path Following` and `Facial Tracking` (hopefully).

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
This section is a guide on how I installed all of the necessary dependencies and setup the project workspaces. This is my first time working with something of this nature, and I had to piece together a few different tutorials online as I couldn't find one that worked out of the gate. Links to those tutorials are at the end of this section. 

If you are unfamiliar with `ROS2` or `microROS`, check out the official [ROS2 Concepts Documentation](https://docs.ros.org/en/humble/Concepts.html) or [microROS Concepts Documentation](https://micro.ros.org/docs/concepts/client_library/introduction/).

### Installing Ubuntu on a Windows Virutal Machine
The class I am taking had us install `ROS2` on Ubuntu 22.04. `ROS2` and `microROS` seem to have better support for Ubuntu, but should work with Windows and macOS. If you don't use Ubuntu, the following steps should still apply but the commands will be different.

`VMWare` is now free and can be used to create virtal machines that allow you to run other OS than what is native to your computer. To install `VMWare` for Windows use this [download](https://vanderbilt365-my.sharepoint.com/:u:/g/personal/hao_yang_vanderbilt_edu/EV_91KZyB4xBiFNZSW5ffjQBcetFDbwrvGudhkRSaf6fvw?e=VUdvoN) and follow this [tutorial](https://shaileshjha.com/how-to-install-vmware-workstation-12-pro-on-windows-10/).

Once `VMWare` is installed, download [Ubuntu 22.04.5 Desktop Image](https://vanderbilt365-my.sharepoint.com/:u:/g/personal/hao_yang_vanderbilt_edu/ESSq4SrNMhBLvuMlTSyhBNoBTE-sshxs2tIUgoP59lGs3Q?e=NeBvae), and follow this [turtorial](https://medium.com/@florenceify74/how-to-download-install-and-run-ubuntu-in-vmware-workstation-ce5f2d4d0438) to set up your VM.

### Installing ROS2 Humble
instructions

### Installing MicroROS
To install `microROS` follow the official [tutorial](https://micro.ros.org/docs/tutorials/core/first_application_rtos/freertos/) on creating your first microROS application for FreeRTOS. Follow the steps to install the `microROS` build system into the `microros_ws` directory. This will create a workspace with ready to use shells that enable you to build and flash applications to the ESP32. 



Since this project uses the ESP32 Dev Modules that run freeRTOS, the `# Create step` command is:
```
ros2 run micro_ros_setup create_firmware_ws.sh freertos esp32
```
If you are using a different microcontroller with a different RTOS the `# Create step` command will be different.

## Usage
### Structure
This project is structured with the root directory `Animatronic-Eyeball-Mechanism` containing two workspaces - `microros_Ws` and `ros2_ws`. I did this because the `microROS` applications that run on the microcontroller have a different build sequence than the traditional `ros2` packages that run on the host computer. There is likley a way to combine these into a single workspace but I left them separate for simplicity sake. All of the applications that will be flashed onto the ESP32 go into the `microros_ws/...` directory, and all of the normal `ROS2` nodes / packages go into the 
