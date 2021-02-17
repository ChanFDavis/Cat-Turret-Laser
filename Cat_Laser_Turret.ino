#include <Servo.h>

Servo x_servo;
Servo y_servo;
bool string_ready;
String serial_str = "";

int pos = 0;

void setup() {
   // put your setup code here, to run once:
   x_servo.attach(8);
   y_servo.attach(7);
   pinMode(5, OUTPUT);

   Serial.begin(9600); /* Set the bod rate. */
   Serial.print("Serial connection established.");

   while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB
   }

}

void loop() {
   // // put your main code here, to run repeatedly:
   // digitalWrite(5, HIGH);
   // for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
   //    // in steps of 1 degree
   //    x_servo.write(pos); // tell servo to go to position in variable 'pos'
   //    y_servo.write(pos); // tell servo to go to position in variable 'pos'
   //    delay(15); // waits 15ms for the servo to reach the position
   // }

   // digitalWrite(5, LOW);
   // for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
   //    x_servo.write(pos); // tell servo to go to position in variable 'pos'
   //    y_servo.write(pos); // tell servo to go to position in variable 'pos'
   //    delay(15); // waits 15ms for the servo to reach the position
   // }

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
   int y = 0;
   int x = 0;
   int rot_x = 0;
   int rot_y = 0;


   while (Serial.available()) {

      // get the new byte:
      char charmeleon = (char) Serial.read();


      // add it to the inputString:
      serial_str += charmeleon;

      // if the incoming character is a newline, set a flag so the main loop can
      // do something about it:
      if (charmeleon == '\n') {
         string_ready = true;
      }
   }


   if (!Serial.available())
   {
      /* Parse 'X<int>Y<int>'. Each <int> is three digits. */
      if (serial_str.startsWith("$")) {
         y_index = serial_str.indexOf("Y");
         
         if (y_index > 0)
         {
            
            x = serial_str.substring(2, y_index).toInt();
            y = serial_str.substring(y_index+1).toInt();

            x_servo.write(x);
            y_servo.write(y);x
            
            Serial.print("X:");
            Serial.print(x);
            Serial.print(", Y:");
            Serial.println(y);
         }
      }
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
