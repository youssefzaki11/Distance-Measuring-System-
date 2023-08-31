/**************************************************************************************************************
 * File Name: UltrasonicSensor.c
 * Date: 20/8/2023
 * Driver: Ultrasonic Sensor Driver Source File
 * Author: Youssef Zaki
 *************************************************************************************************************/
#include <util/delay.h>
#include "GPIO.h"
#include "ICU.h"
#include "UltrasonicSensor.h"

/****************************************************************************************
 *                                    Global Variables                                  *
 ****************************************************************************************/

uint16 Timer_Value;

/****************************************************************************************
 *                                     Functions Definitions                            *
 ****************************************************************************************/

/*
 * Description:
 * 1. Let the MCU pin which is responsible for triggering the ultrasonic sensor as output pin.
 * 2. Make sure that trigger pin is low at the beginning of the application.
 * 3. Set the Call back function pointer in the ICU driver.
 */
void Ultrasonic_Init(void)
{
	GPIO_SetupPinDirection(ULTRASONIC_TRIGGER_PORT_ID, ULTRASONIC_TRIGGER_PIN_ID, OUTPUT_PIN);
	GPIO_WritePin(ULTRASONIC_TRIGGER_PORT_ID, ULTRASONIC_TRIGGER_PIN_ID, LOGIC_LOW);

	/* Set the Call back function pointer in the ICU driver */
	ICU_SetCallBack(Ultrasonic_EdgeProcessing);
}

/*
 * Description:
 * Activate the MCU pin which is responsible for sending 10us pulse to trigger Ultrasonic then deactivate it.
 */
void Ultrasonic_Trigger(void)
{
	GPIO_WritePin(ULTRASONIC_TRIGGER_PORT_ID, ULTRASONIC_TRIGGER_PIN_ID, LOGIC_HIGH);
	_delay_us(10);
	GPIO_WritePin(ULTRASONIC_TRIGGER_PORT_ID, ULTRASONIC_TRIGGER_PIN_ID, LOGIC_LOW);
}

/*
 * Description:
 * 1. Trigger the TRIG pin of Ultrasonic Sensor and wait for rising edge on ECHO pin (start measurements).
 * 2. Calculate the distance in terms of sound velocity and measured time of the echo pulse.
 */
uint16 Ultrasonic_ReadDistance(void)
{
	/* Trigger the TRIG pin of Ultrasonic Sensor and wait for rising edge on ECHO pin (start measurements). */
	Ultrasonic_Trigger();

	/* ((34000 * Timer_value * 10^(-6)) / 2) */
	return ( 1 + (Timer_Value/58));
}

/*
 * Description:
 *** Call Back function to calculate the time for the ultrasonic pulse.
 * 1. Clear timer at the beginning to start timer at Rising Edge on the ECHO Pin and wait for falling edge.
 * 2. Capture the Falling Edge on the ECHO pin.
 * 3. Wait until the ECHO pin goes low.
 * 4. Store the value of ICR1 in Timer_Value.
 * 5. Set the Rising edge again to start the timer and wait for another falling edge.
 */
void Ultrasonic_EdgeProcessing(void)
{
	/* Clear timer at the beginning to start timer at Rising Edge on the ECHO Pin and wait for falling edge */
	ICU_ClearTimerValue();

	/* Capture the Falling Edge on the ECHO pin */
	ICU_SetEdgeDetectionType(FALLING);

	/* Wait until the ECHO pin goes low & ICU measures the pulse in the ECHO pin */
	while (GPIO_ReadPin(ULTRASONIC_ECHO_PORT_ID, ULTRASONIC_ECHO_PIN_ID) == LOGIC_HIGH);

	/* Store the value of ICR1 in Timer_Value*/
	Timer_Value = ICU_GetInputCaptureValue();

	/* Set the Rising edge again to start the timer and wait for another falling edge  */
	ICU_SetEdgeDetectionType(RISING);
}
