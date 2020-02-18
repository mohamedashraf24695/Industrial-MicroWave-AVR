#ifndef OS_H
#define OS_H
/*********************************************
 *            H files Included               *
 *********************************************/

#include "Dio.h"
#include "Gpt.h"
#include "ISR.h"
#include "App.h"


/******************************************
 *           MACROS DEF                *
 ******************************************/

#define OFF_STATE  0
#define REQUEST_TIME_STATE 1
#define DOOR_WEIGHT_SENSORS_STATE 2
#define START_BUTTON_STATE 3
#define MAIN_PROCESS_STATE 4
#define NORMAL_FINISHING_STATE 5
#define CANEL_FINSHING_STATE 6
#define CANCEL_TAKING_TIME 7


/******************************************
 *           Decelerations                *
 ******************************************/
extern uint8 OS_State_flag ;



/******************************************
 *            Functions Prototypes                    *
 ******************************************/


void OS_Init (void);
void OS_Schedular (void );




#endif
