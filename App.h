
#ifndef APP_H
#define APP_H

/*********************************************
 *            H files Included               *
 *********************************************/


#include "Dio.h"
#include "Gpt.h"
#include "lED.h"
#include "Buttons_Sensors.h"
#include "motor.h"
#include "lcd.h"
#include "keypad.h"
#include "heater.h"
#include "ISR.h"


/******************************************
 *           MACROS DEF                *
 ******************************************/

#define FINISHING_MSG_DELAY_TIME 500
#define KEYPAD_ACCEPTING_DELAY_TIME 250



/******************************************
 *           Decelerations                *
 ******************************************/





/******************************************
 *            Functions Prototypes                    *
 ******************************************/
void initApp(void);
uint8 check_OnButton(void) ;
uint8 check_Door_Weight(void);

uint8 check_StartButton(void);

void requestTime(void) ;
void displayTime(void) ;
void requestHeat(void);
void runHeater(void);
void restTimer(void);
void timeIsFinished(void);
uint8 requestNumberFromKeypad(void);
void turnOffHeater(void);
uint8 checkTimeOut (void) ;
void processIsCanceled(void) ;

#endif
