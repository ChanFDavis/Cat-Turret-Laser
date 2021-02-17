# Cat Laser Turret

## Goal / Summary
The goal of this project is to create a device that enables the user to play with their cat(s) (or other laser light enthusiasts) remotely. This device changes the direction that the laser is emitted via two servo motors that rotate on the X and Y axes.

The device will be controlled via a program on the user's PC. This program displays a window that tracks the X and Y coordinates of the user's mouse when it is hovering within the bounds of the window. These coordinates are translated to angles for the device's X and Y rotation, which are then sent to the device. On the device end, upon receiving a signal from the PC, the device parses the incoming rotation data and performs the appropriate rotation. The laser will initially be off until the user clicks their mouse within the PC program's window - at which point the laser will turn on.

## Feature Goals
* Commands over Bluetooth


* Get the dang thing workin'