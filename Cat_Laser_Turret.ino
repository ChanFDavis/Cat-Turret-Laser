#include <Servo.h>

Servo x_servo; /* Servo motor that rotates along the X-axis. */
Servo y_servo; /* Servo motor that rotates along the Y-axis. */

bool send_x = true; /* If true, send the next byte's value to the x-axis servo; otherwise, send it to the y-axis servo. */

void setup() {
   x_servo.attach(8); 
   y_servo.attach(7);

   /* Set the mode of the laser diode pin and turn on the laser. */
   pinMode(12, OUTPUT);
   digitalWrite(12, HIGH);

   Serial.begin(9600); /* Set the baud rate. */

   Serial.println("Serial connection established."); /* Send a success message. */

   while (!Serial) { /* Wait for serial port to connect. Needed for native USB. */ }
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
   size_t bytes_read = 0;     /* The number of bytes read from the RX buffer. */
   byte byte_arr[4] = {0};    /* Byte array containing the x-axis and y-axis rotation values read from the RX buffer. */

   while (Serial.available()) {
      /* Read the rotation data from the RX buffer. */
      bytes_read = Serial.readBytes(byte_arr, 4);

      /* Check if something was actually read. */
      if (bytes_read >= 4) {

         /* If bytes were successfully read, write the first and second bytes to the x-axis servo, and the third and fourth bytes to the y-axis servo. */

         // x_servo.writeMicroseconds(MAX_SERVO_MS - ((byte_arr[1] << 8) | byte_arr[0])); /* Account for reverse rotation direction. */
         x_servo.writeMicroseconds(3000 - ((byte_arr[1] << 8) | byte_arr[0])); /* Account for reverse rotation direction. */
         y_servo.writeMicroseconds(((byte_arr[3] << 8) | byte_arr[2]));
      }
   }
}
