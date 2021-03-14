""" This file contains constants variables used to configure the controller script for compatibility with various hardware setups. """

PORT = 'COM7'
BAUD_RATE = 9600
TIMEOUT = 1

# NOTE: These will be removed once the coordinates are taken from the mouse within a window, not the entire monitor.
SCREEN_X = 2560 # Maximum resolution of the monitor for the X-axis
SCREEN_Y = 1440 # Maximum resolution of the monitor for the Y-axis

WRITE_DELAY = 15 # Delay (in milliseconds) of when data can be written to the arduino in 'on_move' function.








