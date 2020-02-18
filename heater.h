#ifndef _HEARTER_H
#define _HEARTER_H

/*********************************************
 *            H files Included               *
 *********************************************/

#include "Port.h"
#include "Dio.h"
#include "Gpt.h"


/******************************************
 *           MACROS DEF                *
 ******************************************/
#define PMW_ENABLE    LOW
#define HEATER_RATE_OF_INCREASING   10
#define DEFAULT_HEATER_DIRECTION    0
#define DEFAULT_HEATER_HEAT_PRECENTAGE      50
#define FULL_HEATER_HEAT_PRECENTAGE  100
#define DEFAULT_HEATER_MODE         1

/******************************************
 *           Decelerations                *
 ******************************************/
extern uint16 g_heating_temperature ;



typedef enum {
	HEATER_OFF, HEATER_ON
} heater_mode;

typedef struct {

	heater_mode mode; /*Motor is on or off*/
	float heat_precentage; /*The speed of the motor*/

} heater_info_holder;

/******************************************
 *            Functions Prototypes                    *
 ******************************************/

void heaterInit(void);
void heaterAction(void);
#if (PMW_ENABLE==HIGH)
void heaterIncHeat(void);
#endif
void heaterStop (void);
void heaterRun (void);



#endif
