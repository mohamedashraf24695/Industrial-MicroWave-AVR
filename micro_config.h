

#ifndef MICRO_CONFIG_H_
#define MICRO_CONFIG_H_

#ifndef F_CPU
#define F_CPU 1000000UL //1MHz Clock frequency
#endif  


/*
 * This define The microcontroller used to use this #define in the entire code
 * The goal from this to make code portable as possible to more than one controller
 *
  */
#define MICRO_CONTROLLER_USED_ATMEGA_16




#ifdef MICRO_CONTROLLER_USED_ATMEGA_16

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#endif



#endif /* MICRO_CONFIG_H_ */


