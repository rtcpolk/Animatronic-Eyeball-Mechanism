# Animatronic Eyeball Mechanism
An animatronic eyeball mechanism that rotates a sphereical eyeball 360° (or more) around any axis. Developed using ROS2 with microROS for the ESP32.

## Table of Contents

<!--ts-->
   * [About the Project](##About)
   * [Mechatronics](##Mechatronics)
   * [Installation](##Installation)
   * [File Structure](##File)
   * [Acknowledgements](##Acknowledgements)
<!--te-->

## About the Project
This eyeball mechanism is being developed by `Team Blink` at Vanderbilt University for our mechanical engineering senior captstone project. This project is sponsored by [Animax Designs](https://www.animaxdesigns.com/), a global animatronic company based in Nashville, TN. The mechanism is able to rotate a spherical eyeball around any axis and has two operational modes: `Path Following` and `Facial Tracking` (hopefully).

While the code in this repository is specialized for this mechanism, hopefully it can serve as a guide for those looking to integrate `ROS2` and `microROS` into their own robotics projects.

## Mechatronics
This project utilizes the following:
```
Software:
  *Ubuntu 22.04 (run on a VM)
  *ROS2 Humble
  *microRos
Hardware:
  *ESP32 Dev Modules
  *MPU6050 6-Axis IMU
  *DC Motors w/ Encoders
```

## Installation
This section is a guide on how I installed all of the necessary dependencies and setup the project workspaces. This is my first time working with something of this nature, and I had to piece together a few different tutorials online as I couldn't find one that worked out of the gate. Links to those tutorials are at the end of this section. 

If you are unfamiliar with `ROS2` or `microROS`, check out the official [ROS2 Concepts Documentation](https://docs.ros.org/en/humble/Concepts.html) or [microROS Concepts Documentation](https://micro.ros.org/docs/concepts/client_library/introduction/).

### Installing VMWare, Ubuntu, and ROS2
The class I am taking had us install `ROS2` on Ubuntu 22.04. `ROS2` and `microROS` seem to have better support for Ubuntu, but should work with Windows and macOS. If you don't use Ubuntu, the following steps should still apply but the commands will be different.

`VMWare` is now free and can be used to create virtal machines that allow you to run a different OS than what is native to your computer. To install `VMWare` for Windows use this [download](https://vanderbilt365-my.sharepoint.com/:u:/g/personal/hao_yang_vanderbilt_edu/EV_91KZyB4xBiFNZSW5ffjQBcetFDbwrvGudhkRSaf6fvw?e=VUdvoN) and follow this [tutorial](https://shaileshjha.com/how-to-install-vmware-workstation-12-pro-on-windows-10/).

Once `VMWare` is installed, download [Ubuntu 22.04.5 Desktop Image](https://vanderbilt365-my.sharepoint.com/:u:/g/personal/hao_yang_vanderbilt_edu/ESSq4SrNMhBLvuMlTSyhBNoBTE-sshxs2tIUgoP59lGs3Q?e=NeBvae), and follow this [turtorial](https://medium.com/@florenceify74/how-to-download-install-and-run-ubuntu-in-vmware-workstation-ce5f2d4d0438) to set up your VM.

`ROS2` has excellent documentation and tutorials. Follow this [tutorial](https://docs.ros.org/en/humble/Installation/Ubuntu-Install-Debs.html) to download `ROS2` onto your Ubuntu VM. Follow this [tutorial](https://docs.ros.org/en/humble/Tutorials/Beginner-Client-Libraries/Creating-A-Workspace/Creating-A-Workspace.html) to create a workspace in the `ros2_ws` directory. Follow this [tutorial](https://docs.ros.org/en/humble/Tutorials/Beginner-Client-Libraries/Creating-Your-First-ROS2-Package.html) to create `ROS2` packages.

### Installing microROS
To install `microROS` follow the official [tutorial](https://micro.ros.org/docs/tutorials/core/first_application_rtos/freertos/) on creating your first microROS application for FreeRTOS. Follow the steps to install the `microROS` build system into the `microros_ws` directory. This will create a workspace with ready to use shells that enable you to build and flash applications to the ESP32. You can also cross reference this [tutorial](https://medium.com/@markjdsmith/getting-oriented-to-ros2-uros-and-controlling-servos-with-esp32-3b99533ac986) and/or this [tutorial](https://technologiehub.at/project-posts/micro-ros-on-esp32-tutorial/). 

I ran into two problems when following the tutorials. If you do not have permission to access the serial ports see this [fix](https://askubuntu.com/questions/58119/changing-permissions-on-serial-port). Add yourself to the dialout and/or tty groups and restart your computer. If you have issues with an unstable USB serial connection see this [fix](https://askubuntu.com/questions/1403705/dev-ttyusb0-not-present-in-ubuntu-22-04). After following these fixes to get permission and remove brltty I was able to complete the remainder of the tutorial successfully.

The tutorial takes you through the 4 step build process to flash an example app onto the ESP32. Since this project uses an ESP32 with FreeRTOS the `# Create` step command is:
```
ros2 run micro_ros_setup create_firmware_ws.sh freertos esp32
```
Follow the rest of the tutorial to flash the example app. You may need to press the `boot` button on the ESP32 while flashing to get it to register. Once that has been complete, follow the tutorial to setup the agent on the host computer and test that the system is working. Assuming all went well, (and you avoided the painstaking time spent ~~debugging~~ learning the quirks of Ubuntu and how to use the command line all while questioning why you continually put yourself into this situation) you should now have a successful microROS build system as part of your project.

### Flashing a Custom microROS App to the ESP32
`microROS` apps live in the `microros_ws/firmware/freertos_apps/apps` directory and contain the `app.c` and `app-colcon.meta` files. 

Once the custom app has been created, use the 4 steps of the `microROS` build system to flash the app onto the ESP32:
```
Create: Download the required firmware code for your specific microcontroller
Configure: Select which app to compile and eventually flash onto your microcontroller
Build: Build the app and generate project binaries
Flash: Upload the binaries onto your microcontroller
```
The documentation goes more in depth on these steps. The firmware workspace has already been created so this step can be skipped. Configure the workspace for the custom app, build it, and then flash it onto the ESP32. The commands below assume serial communication is being used. Different configurations can be used, see the [documentation](https://micro.ros.org/docs/tutorials/core/first_application_rtos/freertos/).
```
ros2 run micro_ros_setup configure_firmware.sh [app_name] --transport serial
ros2 run micro_ros_setup build_firmware.sh
ros2 run micro_ros_setup flash_firmware.sh
```

## File Structure
This project is structured with the root directory `Animatronic-Eyeball-Mechanism` containing two workspaces - `microros_Ws` and `ros2_ws`. I did this because the `microROS` applications that run on the microcontroller have a different build sequence than the traditional `ros2` packages that run on the host computer. There is likley a way to combine these into a single workspace but I left them separate for simplicity sake. All of the applications that will be flashed onto the ESP32 go into the `microros_ws/firmware/freertos_apps/apps` directory, and all of the `ROS2` packages to be run on the host computer go into the `ros2_ws/src` directory.

## License
This project is under the Apache 2.0 open source license.

## Acknowledgements
This project is still in development and thus there are likely to be errors or bugs that pop up. 

I am an undergraduate mechanical engineer and recently found a passion for mechatronics. I have some academic experience with mechatronics and computer science but most of my knowledge has come from hands on experience through personal projects. I have spent countless hours trying to read through various code libraries, debugging problems, and searching the internet for help. I try to document my projects with the challenges I faced and the solutions I used the best I can to hopefully make it that much easier for the next person that comes along.

If this project / guide inspired or helped you with your own project I'd love to hear about it. I am also willing to hear any feeback or discuss errors / bugs. Contact robert.t.polk@vanderbilt.edu.
