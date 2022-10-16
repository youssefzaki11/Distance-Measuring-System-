/************************************************************************************************************
 * Module: LCD
 * File Name: lcd.h
 * Description: LCD driver Header File
 * Author: Youssef Ahmed Zaki
 ***********************************************************************************************************/

#ifndef LCD_H_
#define LCD_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
/* LCD Data bits mode configuration, its value should be 4 or 8*/
#define LCD_DATA_BITS_MODE 8

#if ( (LCD_DATA_BITS_MODE != 4) && (LCD_DATA_BITS_MODE != 8) )

#error "Number of Data bits should be equal to 4 or 8"

#endif


#define LCD_RS_PORT_ID                 PORTB_ID
#define LCD_RS_PIN_ID                  PIN0_ID

#define LCD_E_PORT_ID                  PORTB_ID
#define LCD_E_PIN_ID                   PIN2_ID

#define LCD_RW_PORT_ID                 PORTB_ID
#define LCD_RW_PIN_ID                  PIN1_ID

#define LCD_DATA_PORT_ID               PORTA_ID

#if (LCD_DATA_BITS_MODE == 4)

#define LCD_DB4_PIN_ID                 PIN3_ID
#define LCD_DB5_PIN_ID                 PIN4_ID
#define LCD_DB6_PIN_ID                 PIN5_ID
#define LCD_DB7_PIN_ID                 PIN6_ID

#endif

#define LCD_CLEAR_COMMAND                    0x01
#define LCD_GO_TO_HOME                       0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE        0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE         0x28
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1   0x33    /* for initialize last 4 bits */
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2   0x32    /* for initialize first 4 bits */
#define LCD_CURSOR_OFF                       0x0C
#define LCD_CURSOR_ON                        0x0E
#define LCD_SET_CURSOR_LOCATION              0x80

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description:
 * 1. Setup the LCD pins directions by GPIO Driver
 * 2. Setup the LCD Data Mode 8 bits
 */
void LCD_init(void);

/*
 * Description:
 * Send Command to LCD
 */
void LCD_sendCommand(uint8 command);

/*
 * Description:
 * Send Data to LCD to Display it
 */
void LCD_displayCharacter(uint8 data);

/*
 * Description:
 * Displaying a String on LCD
 */
void LCD_displayString(const char *Str);

/*
 * Description :
 * Move the cursor to a specified row and column index on the screen
 */

void LCD_moveCursor(uint8 row, uint8 col);

/*
 * Description:
 * Display the required string in a specified row and column index on the screen
 */
void LCD_displayStringRowColumn(uint8 row, uint8 col, const char *Str);

/*
 * Description:
 * Send the clear screen command
 */
void LCD_clearScreen(void);

/*
 * Description:
 * Display the required decimal value on the screen
 */
void LCD_intgerToString(int data);


#endif /* LCD_H_ */
