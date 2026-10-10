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

## Setup vcan (Setting up can bus without the actual car)
1. Load the module: sudo modprobe vcan
2. Create the interface: sudo ip link add dev vcan0 type vcan
3. Bring it up: sudo ip link set up vcan0
4. Check it: ip link show vcan0 should show UP.

## Setup
Install libsub 1.0 binaries to be able to use the pyusb library, store dll in System32 folder

## Test run for CAN communication

1. Ensure that Arduino IDE is running sample CAN test code
2. In WSL terminal, run the following:
- Get CAN to start listening at 500 kbit/s: sudo ip link set can0 up type can bitrate 500000
- Send messages: candump can0
