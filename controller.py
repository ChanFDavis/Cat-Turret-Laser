# TODO: Add shebang

from pynput import mouse, keyboard # Used to get control data from the mouse and keyboard.

import serial     # Used to communicate with the arduino.
import struct     # Used to pack and unpack binary data.
import time       # Used to delay the sending of data to the arduino.

# NOTE: This is a local file that defines variables referenced in this file that are used for configuration (port, baudrate, etc.).
import constants

"""
TODO:
   Add error checking
   Add serial monitoring (print output sent from device)
   Create GUI window and have controls be obtain via the mouse coords w.r.t. the window's bounds
   Hook up a camera to the turret and get the feed to the GUI
   Add controlling over bluetooth connection
   Add sending of control bytes to allow toggling of flags via commands from the controller script.

   Structure this source code file better (AFTER the basic writing of control data functionality is implemented and BEFORE implementing the GUI stuff)
"""

# Output that the controller script is started.
print('Laser turret controller started.')

ser = serial.Serial(constants.PORT, baudrate=constants.BAUD_RATE, timeout=constants.TIMEOUT)  # open serial port
print(f'Communicating through serial port {ser.name}')         # check which port was really used

# Global variables
send_coords  = False # Should mouse coordinates be sent to the arduino?
print_coords = False # Should mouse coordinates be output on move?

# Used for delays when sending data to the arduino.
curr_time    = time.time_ns()
last_time    = curr_time

def mouse_coord_to_servo_angle(coord, max_coord):
   # TODO: Add docstring

   # Translate the given mouse coordinate (between 0 and max_coord) to value between the minimum and maximum servo shaft angle, in microseconds.
   # FIXME: This can get real strange and get mouse coordinates outside of the screen bounds if you swipe the mouse quick enough.
   # This won't be an issue once we move to using a GUI/window versus the entire monitor to track mouse movement.

   return (round((coord * (constants.MAX_SERVO_ROT_US - constants.MIN_SERVO_ROT_US)) / max_coord) + constants.MIN_SERVO_ROT_US)

def on_press(key):
   # TODO: Add docstring

   try:
      print(f'DEBUG: key pressed {key}')
   except AttributeError:
      print(f'DEBUG: special key pressed {key}')

def on_release(key):
   # TODO: Add docstring

   global send_coords
   global print_coords

   # If escape key is hit, stop listeners, close serial ports, and end this program.
   if key == keyboard.Key.esc:
      mouse_listener.stop() # Stop the mouse listener.
      ser.close() # Close the serial port.
      return False # Return false to end the key listener loop, which ends the program.

   # Get input and output buffer information.
   if key == keyboard.KeyCode().from_char('b'):
      print(f'DEBUG: in-buffer bytes: {ser.in_waiting}\nout-buffer bytes: {ser.out_waiting}')

   # TODO: Have another thread that prints any data as it comes.
   # Print all bytes in the input buffer, if any.
   if key == keyboard.KeyCode().from_char('f') and ser.in_waiting > 0:
         print(ser.read(ser.in_waiting))

   # Toggle flag to place mouse coordinates in the output buffer to the arduino.
   if key == keyboard.Key.space:
      send_coords = not send_coords

   # Toggle flag to output mouse coordinates to console window.
   if key == keyboard.KeyCode.from_char('t'):
      print_coords = not print_coords


def on_move(x, y):
   # TODO: Add docstring

   # Global flags
   global send_coords
   global print_coords

   # Timer used for delays
   global last_time
   global curr_time

   # Update the current time.
   curr_time = time.time_ns()

   num_bytes_written = 0 # DEBUG: The number of bytes written to the arduino.
   byte_pack = bytes() # The 'bytes' object containing the packed coordinates sent to the arduino.

   # Convert the X and Y coordinates w.r.t to the container (currently the monitor) into servo shaft angles, in milliseconds.
   x_angle = mouse_coord_to_servo_angle(x, constants.SCREEN_X)
   y_angle = mouse_coord_to_servo_angle(y, constants.SCREEN_Y)

   # Output the mouse's X and Y coordinates if flag is enabled.
   if print_coords:
      print(f'({x}, {y}) -> ({x_angle}, {y_angle})')

   # Send the mouse's X and Y coordinates to the arduino if flag is enabled and the specified delay time has been hit.
   if send_coords and ((curr_time - last_time) >= (constants.WRITE_DELAY * 1000000)):

      # Pack the converted X/Y coordinate data into a byte array of two unsigned shorts.
      byte_pack = struct.pack('HH', x_angle, y_angle)

      # TODO: Add runtime arguments/flags to enable/disable debug messages.
      # DEBUG: Write some debug output.
      # print(f'X int = {x}; X angle = {x_angle}; packed bytes object = {byte_pack}')
      # print(f'unpacked object = {struct.unpack("cB", byte_pack)}')

      # Write the packed bytes to the output buffer.
      num_bytes_written = ser.write(byte_pack)

      # Output the number of bytes written to confirm if the bytes were sent as expected.
      if num_bytes_written > 0:
         print(f"DEBUG: Bytes written: {num_bytes_written}")
      else:
         print("DEBUG: No bytes written")

      last_time = time.time_ns() # Save time of function exit.

def on_click(x, y, button, pressed):
   # TODO: Add docstring or remove if not used in the end.
   pass

# Create a non-blocking keyboard listener and start it.
key_listener = keyboard.Listener(on_press=on_press, on_release=on_release, suppress=True)
key_listener.start()

# Run a loop for a mouse listener.
with mouse.Listener(on_move=on_move, on_click=on_click) as mouse_listener:
   mouse_listener.join()

# Let the user know the controller script has ended.
print('Laser turret controller ended.')