#include <Servo.h>

Servo x_servo; /* Servo motor that rotates along the X-axis. */
Servo y_servo; /* Servo motor that rotates along the Y-axis. */

bool send_x = true; /* If true, send the next byte's value to the x-axis servo; otherwise, send it to the y-axis servo. */

void setup() {
   x_servo.attach(8); 
   y_servo.attach(7);

   pinMode(5, OUTPUT);

   Serial.begin(9600); /* Set the baud rate. */
   Serial.println("Serial connection established.");

   while (!Serial) {
      /* Wait for serial port to connect. Needed for native USB. */
   }
}

void loop() { /* Do nothing. */ }

/*
   Handle input from the PC and get control commands.

   SerialEvent occurs whenever a new data comes in the hardware serial RX. This
   routine is run between each time loop() runs, so using delay inside loop can
   delay response. Multiple bytes of data may be available.

   Credits: The SerialEvent.io example file from the Arduino IDE.
*/
void serialEvent() {
   int read_byte = 0; /* The unsigned byte read from the RX buffer. */


   // bool control_byte = true; /* Is this a control byte? (The next byte will be a value byte). */
   bool send_x = true; /* If true, send the next byte's value to the x-axis servo; otherwise, send it to the y-axis servo. */
   // bool control

   /* While data is present in the RX buffer, transfer it to the TX buffer byte by byte. */
   while (Serial.available()) {
      read_byte = Serial.read();

      /* Check if something was actually read. */
      if (read_byte >= 0)
      {
         /* If byte was successfully read, write it to either the X or Y servo. */
         if (send_x) {
            x_servo.write(read_byte);
         } else {
            y_servo.write(read_byte);
         }

         send_x = !send_x; /* Switch which servo the next byte will be written to. */
         Serial.println(send_x);
      }

      /* TODO: Add reading of control bytes to allow toggling of flags via commands from the controller script. */
      Serial.println(read_byte);
   }
}
