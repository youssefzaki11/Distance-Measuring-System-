/**************************************************************************************************************
 * File Name: ICU.c
 * Date: 21/7/2023
 * Driver: ATmega32 Input Capture Unit (ICU) Driver Source File
 * Author: Youssef Zaki
 *************************************************************************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Common_Macros.h"
#include "GPIO.h"
#include "ICU.h"

/***************************************************************************************
 *                                      Global Variables                               *
 ***************************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_CallBackPtr)(void) = NULL_PTR;

/***************************************************************************************
 *                                  Interrupt Service Routines                         *
 ***************************************************************************************/
ISR(TIMER1_CAPT_vect)
{
	if ((g_CallBackPtr) != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_CallBackPtr)();
	}
}

/****************************************************************************************
 *                                     Functions Definitions                            *
 ****************************************************************************************/

/*
 * Description:
 * 1. Activate FOC1A and FOC1B bits in TCCR1A Registers if it specifies non-PWM mode.
 * 2. Let TCNT1 Register = ZERO to start counting from ZERO & Let ICR1 = 0 .
 * 3. Make ICP1 pin (PD6) in PORTD Register as input pin.
 * 4. From clock select (CS12:0) bits in TCCR1B Register, choose the required Pre-scalar.
 * 5. Configure the ICES1 (bit 6) bit in TCCR1B Register according to edge (falling = 0, rising = 1).
 * 6. Activate TICIE1 bit in TIMSK Register to enable Input Capture Interrupt.
 */
void ICU_Init(const ICU_ConfigType *Config_Ptr)
{
	SET_BIT(TCCR1A, FOC1A);
	SET_BIT(TCCR1A, FOC1B);

	TCNT1 = 0;
	ICR1 = 0;

	GPIO_SetupPinDirection(PORTD_ID, PIN6_ID, INPUT_PIN);

	TCCR1B = (TCCR1B & 0xF8) | (Config_Ptr -> ICU_Prescalar);
	TCCR1B = (TCCR1B & 0xBF) | ((Config_Ptr -> ICU_Edge) << ICES1);

	SET_BIT(TIMSK, TICIE1);
}

/*
 * Description:
 * Set Call Back Function Address
 */
void ICU_SetCallBack(void(*a_ptr)(void))
{
	g_CallBackPtr = a_ptr;
}

/*
 * Description:
 * Set the required edge detection
 */
void ICU_SetEdgeDetectionType(const ICU_EgdeDetection Edge)
{
	TCCR1B = (TCCR1B & 0xBF) | (Edge << ICES1);
}

/*
 * Description:
 * Return the value of ICR1, as the timer value is stored in this register
 */
uint16 ICU_GetInputCaptureValue(void)
{
	return ICR1;
}

/*
 * Description:
 * Clear the timer value and start counting from ZERO
 */
void ICU_ClearTimerValue(void)
{
	TCNT1 = 0;
}

/*
 * Description:
 * Disable the timer1 and Input Capture Unit
 */
void ICU_DeInit(void)
{
	TCNT1 = 0;
	ICR1 = 0;
	TCCR1A = 0;
	TCCR1B = 0;
	CLEAR_BIT(TIMSK, TICIE1);
}

