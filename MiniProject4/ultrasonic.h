/************************************************************************************************************
 * Module: Ultrasonic Sensor
 * File Name: ultrasonic.h
 * Description: Ultrasonic Sensor driver Header File
 * Author: Youssef Ahmed Zaki
 ************************************************************************************************************/


#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* Definition of Sound Velocity at F_CPU = 8 MHz and Pre-scalar = 8 */
#define SOUND_VELOCITY_FREQ_OVER_PRESCALAR               0.017       /* (34000/2) * 1 * 10^(-6) cm/s */

/* Definition of Trigger PORT & Pin */
#define TRIGGER_PORT_ID              PORTB_ID
#define TRIGGER_PIN_ID               PIN5_ID

/* Definition of ECHO PORT & Pin */
#define ECHO_PORT_ID                 PORTD_ID
#define ECHO_PIN_ID                  PIN6_ID

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * DESCRIPTION:
 * 1. Initialize the ICU driver as required.
 * 2. Setup the ICU call back function.
 * 3. Setup the direction for the trigger pin as output pin through the GPIO driver.
 */
void Ultrasonic_init(void);

/*
 * DESCRIPTION:
 * Send the Trigger pulse to the ultrasonic.
 */
void Ultrasonic_Trigger(void);

/*
 * DESCRIPTION:
 * 1. Send the trigger pulse by using Ultrasonic_Trigger function.
 * 2. Start the measurements by the ICU from this moment.
 * 3. Return The measured distance in Centimeter.
 */
uint16 Ultrasonic_readDistance(void);

/*
 * DESCRIPTION:
 * This is the call back function called by the ICU driver.
 * This is used to calculate the high time (pulse time) generated by the ultrasonic sensor.
 */
void Ultrasonic_edgeProcessing(void);


#endif /* ULTRASONIC_H_ */
