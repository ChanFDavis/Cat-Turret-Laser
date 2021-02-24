from pynput import mouse, keyboard
import serial


# Note to self: the 'with' keyword is cool! https://www.geeksforgeeks.org/with-statement-in-python/

"""
TODO: 
   Add error checking
   Add serial monitoring (print output sent from device)
"""
# Output that the controller script is started.
print('Laser turret controller started.')

ser = serial.Serial('COM5', baudrate=9600, timeout=1)  # open serial port
print(f'Communicating through serial port {ser.name}')         # check which port was really used

send_coords  = False # Should mouse coordinates be sent to the arduino?
print_coords = False # Should mouse coordinates be output on move?

def on_press(key):
   try:
      print(f'key pressed {key}')
   except AttributeError:
      print(f'special key pressed {key}')

def on_release(key):
   global send_coords
   global print_coords

   # If escape key is hit, stop listeners, close serial ports, and end this program.
   if key == keyboard.Key.esc:
      mouse_listener.stop() # Stop the mouse listener.
      ser.close() # Close the serial port.
      return False # Return false to end the key listener loop, which ends the program.

   # Get input and output buffer information.
   if key == keyboard.KeyCode().from_char('b'):
      print(f'in-buffer bytes: {ser.in_waiting}\nout-buffer bytes: {ser.out_waiting}')

   # Print all bytes in the input buffer, if any.
   if key == keyboard.KeyCode().from_char('f'):
      if ser.in_waiting > 0:
         print(ser.read(ser.in_waiting))

   # Place mouse coordinates (currently, just X) in the output buffer.
   if key == keyboard.Key.space:
      send_coords = True

   # Toggle output of mouse coordinates to console window.
   if key == keyboard.KeyCode.from_char('t'):
      print_coords = not print_coords
      

def on_move(x, y):
   global send_coords
   global print_coords

   if print_coords:
      print(f'{x}, {y}')

   if send_coords:
      print(f'sending: {x}, {y}')
      ser.write(x)
      send_coords = False

def on_click(x, y, button, pressed):
   pass

# Create a non-blocking mouse listener and start it.
mouse_listener = mouse.Listener(on_move=on_move, on_click=on_click)
mouse_listener.start()

# Run a loop for a key listener
with keyboard.Listener(on_press=on_press, on_release=on_release, suppress=True) as key_listener:
   key_listener.join()

print('Laser turret controller ended.')