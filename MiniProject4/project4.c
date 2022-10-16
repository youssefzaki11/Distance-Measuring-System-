/*************************************************************************************************************
 * File Name: project4.c
 * Description: Project 4 main file
 * Author: Youssef Zaki
 ************************************************************************************************************/

#include "ultrasonic.h"
#include "lcd.h"
#include <avr/io.h>
#include "gpio.h"

int main(void)
{
	uint16 ultrasonic_distance = 0;

	/* Initialization of the LCD */
	LCD_init();

	/* Initialization of the Ultra-sonic Sensor */
	Ultrasonic_init();

	/* Enable Global Interrupt I-Bit */
	SREG |= (1<<7);

	/* Display "Distance" on LCD, then move Cursor */
	LCD_displayString("Distance =    cm");

	while(1)
	{
		ultrasonic_distance = Ultrasonic_readDistance(); /* calculating the distance W.R.T Timer1 ICU mode */
		LCD_moveCursor(0,11);

		if (ultrasonic_distance>99)
		{
			LCD_intgerToString(ultrasonic_distance);
		}
		else {
			LCD_intgerToString(ultrasonic_distance);
			LCD_displayCharacter(' ');
		}
	}
}
