/*************************************************************************************************************
 * [File]: DistanceMeasuringSystemProject.c
 * [Date]: 20/8/2023
 * [Objective]: Developing a system that measure the distance and display it on LCD.
 * [Drivers]: GPIO - ICU - ADC - Ultrasonic Sensor - LCD
 * [Author]: Youssef Ahmed Zaki
 *************************************************************************************************************/
#include <avr/io.h>
#include <util/delay.h>

/* MCAL Layer */
#include "GPIO.h"
#include "ICU.h"

/* HAL Layer */
#include "LCD.h"
#include "UltrasonicSensor.h"

int main(void)
{
	uint16 Read_Distance = 0;

	/*
	 * ICU Configuration:
	 * 1. Set the pre-scaler to be F_CPU/8 as mentioned in the requirements
	 * 2. Set the rising edge to be detected first.
	 */
	ICU_ConfigType ICU_Config = {CLK_8, RISING};

	/* MCAL Drivers Initialization */
	ICU_Init(&ICU_Config);

	/* HAL Drivers Initialization */
	LCD_Init();
	Ultrasonic_Init();

	/* Always Display this message on the LCD Screen */
	LCD_DisplayString("Distance =    cm");

	/* Enable Global Interrupt I-Bit */
	SREG |= (1<<7);

	while (1)
	{
		/* Get the read distance from Ultrasonic Sensor measurement */
		Read_Distance = Ultrasonic_ReadDistance();

		/* Move the cursor to this position to write the actual distance based on measurements of US Sensor */
		LCD_MoveCursor(0, 11);

		/* Display the reading on the LCD Screen */
		if (Read_Distance >= 100)
		{
			LCD_IntegerToString(Read_Distance);
		}
		else
		{
			LCD_IntegerToString(Read_Distance);

			/* Put space in next place when the number is one or two digits to prevent noises on LCD */
			LCD_DisplayCharacter(' ');
		}
	}

}
