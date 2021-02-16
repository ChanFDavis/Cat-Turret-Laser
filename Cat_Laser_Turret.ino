#include <SPI.h>

#include <Servo.h>

Servo x_servo;
Servo y_servo;

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
   // put your main code here, to run repeatedly:
   digitalWrite(5, HIGH);
   for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      x_servo.write(pos); // tell servo to go to position in variable 'pos'
      y_servo.write(pos); // tell servo to go to position in variable 'pos'
      delay(15); // waits 15ms for the servo to reach the position
   }

   digitalWrite(5, LOW);
   for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      x_servo.write(pos); // tell servo to go to position in variable 'pos'
      y_servo.write(pos); // tell servo to go to position in variable 'pos'
      delay(15); // waits 15ms for the servo to reach the position
   }

   /* Print any output that a Serial Event may have created. */
   // TODO:
}

/* Handle input from the PC and get control commands. */
void serialEvent() {

as


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