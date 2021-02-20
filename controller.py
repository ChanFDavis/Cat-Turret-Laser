""" Pynput docs: https://pynput.readthedocs.io/en/latest/ """
from pynput import mouse, keyboard
import serial


# The 'with' keyword is cool! https://www.geeksforgeeks.org/with-statement-in-python/

"""
TODO: 
   Add error checking
"""

ser = serial.Serial('COM5', baudrate=9600)  # open serial port
print(ser.name)         # check which port was really used


# TODO: Add a key listener and add a kill hotkey
def on_press(key):
   try:
      print(f'key pressed {key}')
      if key == keyboard.Key.tab:
         return False
   except AttributeError:
      print(f'special key pressed {key}')

def on_release(key):
   if key == keyboard.Key.space:
      mouse_listener.stop()
      ser.close()             # close port
      return False

def on_move(x, y):
   print(ser.read())
   

   # ser.write(b'$X')     # write a string
   ser.write(x + y)

def on_click(x):
   print(f"clicked {f}")

# Create a non-blocking mouse listener and start it.
mouse_listener = mouse.Listener(on_move=on_move, on_click=on_click)
mouse_listener.start()

# Run a loop for a key listener
with keyboard.Listener(on_press=on_press, on_release=on_release) as key_listener:
   key_listener.join()

