
#ifndef LED_H
#define LED_H

/*******************************************************************************
 *                              Included Files                               *
 *******************************************************************************/

#include "Port.h"
#include "Dio.h"
#include "Gpt.h"

/*******************************************************************************
 *                           Functions Prototype                            *
 *******************************************************************************/

void ledsInit(void);
void writeONLamp(uint8 LEVEL);
void writePauseLamp(uint8 LEVEL);
void writeHeaterLamp(uint8 LEVEL);
#endif

