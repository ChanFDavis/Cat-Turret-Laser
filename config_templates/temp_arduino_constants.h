/**
 * NOTE: This is a template file. Please do the following:
 *    - copy this file into the same directory as the Cat_Laser_Turret.ino Arduino file
 *    - rename the file to remove the "temp_" at the beginning
 *    - update the definitions below with values that work with your setup
 *
 * This file contains constants variables used to configure the arduino code for compatibility with various hardware setups.
 */

/* Minimum angle of the servo shaft in microseconds.  */
#define MIN_SERVO_US 500

/* Maximum angle of the servo shaft in microseconds.  */
#define MAX_SERVO_US 2500

/* BAUD rate for serial communication. */
#define BAUD_RATE    9600

/* Pin that the X-axis servo is attached to. */
#define SERVO_PIN_X  8

/* Pin that the Y-axis servo is attached to. */
#define SERVO_PIN_Y  7

/* Pint that the laser light is attached to. */
#define LASER_PIN    12