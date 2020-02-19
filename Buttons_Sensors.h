#ifndef BUTTONS_SENSORS_H
#define BUTTONS_SENSORS_H

/*******************************************************************************
 *                              Included Files                               *
 *******************************************************************************/

#include "Port.h"
#include "Dio.h"
#include "Gpt.h"

/*******************************************************************************
 *                              MACROS DEFINITION                               *
 *******************************************************************************/

#define DEBOUNCE_CONSTANT_US 1

/*******************************************************************************
 *                           Functions Prototype                            *
 *******************************************************************************/

void buttons_sensorsInit(void);
uint8 readStartButton(void);
uint8 readWeightSensor(void);
uint8 readDoorSensor(void);
uint8 readOnButton(void);
uint8 readOffButton(void);

#endif
