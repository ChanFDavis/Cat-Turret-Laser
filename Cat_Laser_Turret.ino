#include <Servo.h>

Servo x_servo;
Servo y_servo;
bool string_ready;
String serial_str = "";
char char_arr[2];

int pos = 0;

void setup() {
   // put your setup code here, to run once:
   x_servo.attach(8);
   y_servo.attach(7);
   pinMode(5, OUTPUT);

   Serial.begin(9600); /* Set the bod rate. */
   Serial.println("Serial connection established.");

   while (!Serial) {
      // wait for serial port to connect. Needed for native USB
   }

}

void loop() {

   if (string_ready) {
      Serial.println(serial_str);
      serial_str = "";
      string_ready = false;
   }

   /* Print any output that a Serial Event may have created. */
   // TODO:
}

/*
   Handle input from the PC and get control commands.

   SerialEvent occurs whenever a new data comes in the hardware serial RX. This
   routine is run between each time loop() runs, so using delay inside loop can
   delay response. Multiple bytes of data may be available.

   Credits: The SerialEvent.io example file from the Arduino IDE.
*/
void serialEvent() {
   int is_int = false;
   int y_index = -1;
   
   int x = 0;
   int y = 0;

   int rot_x = 0;
   int rot_y = 0;

   int read_byte = 0; /* The signed byte read from the RX buffer. */

   // bool control_byte = true; /* Is this a control byte? (The next byte will be a value byte). */
   bool send_x = true; /* If true, send the next byte's value to the x-axis servo; otherwise, send it to the y-axis servo. */
   // bool control

   /* While data is present in the RX buffer, transfer it to the TX buffer byte by byte. */
   while (Serial.available()) {
      read_byte = Serial.read();

      /* Check if something was actually read. */
      if (read_byte >= 0)
      {
         // if (control_byte)
         // {
         // }

         if (send_x) {
            x_servo.write(read_byte);
         } else {
            y_servo.write(read_byte);
         }

         send_x = !send_x; /* Switch the servo to write the next byte to. */
         // control_byte = !control_byte; /* Toggle the control byte flag. */
      }

      // Serial.println(read_byte);

      // delay(15);
      // Serial.write(read_byte);
   }
}

/**
 * Ideas:
 *
 * Control with mouse and click to activate laser.
 *
 *
 * Sweaty Ideas:
 * Multiple control types
 *
 */
