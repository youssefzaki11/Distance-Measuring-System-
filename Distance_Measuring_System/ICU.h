/**************************************************************************************************************
 * File Name: ICU.h
 * Date: 21/7/2023
 * Driver: ATmega32 Input Capture Unit (ICU) Driver Header File
 * Author: Youssef Zaki
 *************************************************************************************************************/
#include "Standard_Types.h"

#ifndef ICU_H_
#define ICU_H_

/****************************************************************************************
 *                                      Types Declaration                               *
 ****************************************************************************************/
typedef enum
{
	No_Clock, CLK_1, CLK_8, CLK_64, CLK_256, CLK_1024
}ICU_ClockSelect;

typedef enum
{
	FALLING, RISING
}ICU_EgdeDetection;

typedef struct
{
	ICU_ClockSelect ICU_Prescalar;
	ICU_EgdeDetection ICU_Edge;
}ICU_ConfigType;

/****************************************************************************************
 *                                      Functions Prototypes                            *
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
void ICU_Init(const ICU_ConfigType *Conig_Ptr);

/*
 * Description:
 * Set Call Back Function Address
 */
void ICU_SetCallBack(void(*a_ptr)(void));

/*
 * Description:
 * Set the required edge detection
 */
void ICU_SetEdgeDetectionType(const ICU_EgdeDetection Edge);

/*
 * Description:
 * Return the value of ICR1, as the timer value is stored in this register
 */
uint16 ICU_GetInputCaptureValue(void);

/*
 * Description:
 * Clear the timer value and start counting from ZERO
 */
void ICU_ClearTimerValue(void);

/*
 * Description:
 * Disable the timer1 and Input Capture Unit
 */
void ICU_DeInit(void);

#endif /* ICU_H_ */
