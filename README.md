# fsai-test-car

## WSL Setup
In order for canable to communicate to ROS nodes within WSL, the following setup needs to be done:

1. Open Windows Powershell with Administrator
- winget install usbipd
- usbipd list
- usbipd bind --busid {check the bus id within the list, e.g. 1-4}
- usbipd attach --wsl --busid {again same bus id} --auto-attach

2. Open WSL
- lsusb
- sudo modprobe gs_usb

## Setup
Install libsub 1.0 binaries to be able to use the pyusb library, store dll in System32 folder

