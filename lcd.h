
#ifndef _LCD_H_
#define _LCD_H_


                           /*********************************************
                                       H files Included
                           *********************************************/
#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"
#include "stdlib.h"
             /*******************************************************************************
              *                      Preprocessor Macros                                    *
              *******************************************************************************/

                         /* LCD Data bits mode configuration */


#define DATA_BITS_MODE 4

/* Use higher 4 bits in the data port */
#if (DATA_BITS_MODE == 4)
#define UPPER_PORT_PINS
#endif

/* LCD HW Pins */
#define RS PC0
#define RW PC1
#define E  PC2
#define LCD_CTRL_PORT PORTC
#define LCD_CTRL_PORT_DIR DDRC

#define LCD_DATA_PORT PORTD
#define LCD_DATA_PORT_DIR DDRD

/* LCD Commands */
#define CLEAR_COMMAND 0x01
#define FOUR_BITS_DATA_MODE 0x02
#define TWO_LINE_LCD_Four_BIT_MODE 0x28
#define TWO_LINE_LCD_Eight_BIT_MODE 0x38
#define CURSOR_OFF 0x0C
#define CURSOR_ON 0x0E
#define SET_CURSOR_LOCATION 0x80

/* LCD Parameters */
#define First_ROW 0
#define Second_ROW 1
#define Third_ROW 2
#define Fourth_ROW 3

#define First_Char 0
#define Second_Char 1
#define Third_Char 2
#define Fourth_Char 3
#define Fifth_Char 4
#define Sixth_Char 5
#define Seventh_Char 6
#define Eighth_Char 7
#define Ninth_Char 8
#define Tenth_Char 9


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void LCD_sendCommand(uint8 command);
void LCD_displayCharacter(uint8 data);
void LCD_displayString(const char *Str);
void LCD_init(void);
void LCD_clearScreen(void);
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str);
void LCD_goToRowColumn(uint8 row,uint8 col);
void LCD_intgerToString(int data);

#endif /* LCD_H_ */

