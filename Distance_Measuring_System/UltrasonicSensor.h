/**************************************************************************************************************
 * File Name: UltrasonicSensor.h
 * Date: 20/8/2023
 * Driver: Ultrasonic Sensor Driver Header File
 * Author: Youssef Zaki
 *************************************************************************************************************/
#include "Standard_Types.h"

#ifndef ULTRASONICSENSOR_H_
#define ULTRASONICSENSOR_H_

/****************************************************************************************
 *                                      Macros Definition                               *
 ****************************************************************************************/
#define VELOCITY_SOUND                    34000
#define ULTRASONIC_VOLTAGE_SRC            5

#define ULTRASONIC_TRIGGER_PORT_ID        PORTB_ID
#define ULTRASONIC_TRIGGER_PIN_ID         PIN5_ID

#define ULTRASONIC_ECHO_PORT_ID           PORTD_ID
#define ULTRASONIC_ECHO_PIN_ID            PIN6_ID

/****************************************************************************************
 *                                      Functions Prototypes                            *
 ****************************************************************************************/

/*
 * Description:
 * 1. Let the MCU pin which is responsible for triggering the ultrasonic sensor as output pin.
 * 2. Make sure that trigger pin is low at the beginning of the application.
 * 3. Set the Call back function pointer in the ICU driver.
 */
void Ultrasonic_Init(void);

/*
 * Description:
 * Activate the MCU pin which is responsible for triggering Ultrasonic 10us then deactivate it.
 */
void Ultrasonic_Trigger(void);

/*
 * Description:
 * 1. Trigger the TRIG pin of Ultrasonic Sensor and wait for rising edge on ECHO pin.
 * 2. Calculate the distance in terms of sound velocity and measured time of the echo pulse.
 */
uint16 Ultrasonic_ReadDistance(void);

/*
 * Description:
 *** Call Back function to calculate the time for the ultrasonic pulse.
 * 1. Clear timer at the beginning to start timer at Rising Edge on the ECHO Pin and wait for falling edge.
 * 2. Capture the Falling Edge on the ECHO pin.
 * 3. Wait until the ECHO pin goes low.
 * 4. Store the value of ICR1 in Timer_Value.
 * 5. Set the Rising edge again to start the timer and wait for another falling edge.
 */
void Ultrasonic_EdgeProcessing(void);

#endif /* ULTRASONICSENSOR_H_ */
