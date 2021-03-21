"""
NOTE: This is a template file. Please do the following:
   - copy this file into the same directory as the controller.py Python file
   - rename the file to remove the "temp_" at the beginning
   - update the variables below with values that work with your setup

This file contains constants variables used to configure the controller script for compatibility with various hardware setups.
"""

# Arduino connection configuration
PORT        = 'COM7' # COM port that the arduino is connected to.
BAUD_RATE   = 9600   # Baud rate for serial communication with the arduino.
TIMEOUT     = 1      # Timeout (in seconds) used when writing data to the output buffer going to the arduino.

# Controller configuration
# NOTE: These will be removed once the coordinates are taken from the mouse within a window, not the entire monitor.
SCREEN_X = 2160 # Maximum resolution of the monitor for the X-axis
SCREEN_Y = 1440 # Maximum resolution of the monitor for the Y-axis

WRITE_DELAY = 15 # Delay (in milliseconds) of when data can be written to the arduino in 'on_move' function.

# Arduino hardware configuration
MIN_SERVO_ROT_US = 500  # Minimum shaft angle for the servos in microseconds.
MAX_SERVO_ROT_US = 2500 # Maximum shaft angle for the servos in microseconds.
