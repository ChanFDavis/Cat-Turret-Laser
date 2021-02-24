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

   /* While data is present in the RX buffer, transfer it to the TX buffer byte by byte. */
   while (Serial.available()) {
      read_byte = Serial.read();

      Serial.println(read_byte, DEC);
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
