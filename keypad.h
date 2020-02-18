/* MODULE      : KEYPAD
 * file type   : H file
 * AUTHOR      : Mohamed Ashraf Ibrahim
 * Description : A default keypad module for 4x3 or 4x4 module
 * Notes       : Please check your connections and if it is different,
 *               redefine ports to be fit your drive connection
 *
 */

#ifndef _KEY_PAD_H
#define _KEY_PAD_H


                           /*********************************************
                                       H files Included
                           *********************************************/
#include "micro_config.h"
#include "common_macros.h"
#include "std_types.h"


                          /*********************************************
                                      Driver Definitions
                          *********************************************/


       /************************* Define number of Columns and Rows of Keypad ******************/

#define N_col 4
#define N_row 4

/************************* Define number of Columns and Rows of Keypad ******************/

#define KEYPAD_PORT_DIR DDRA
#define KEYPAD_PORT_IN  PINA
#define KEYPAD_PORT_OUT PORTA

                        /*********************************************
                                      Functions prototypes
                        *********************************************/

uint8 KeyPad_getPressedKey(void);

#endif
