#ifndef GPT_H
#define GPT_H

#include "common_macros.h"
#include "std_types.h"
#include "micro_config.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

#define PMW_TIMER0_DDR DDRB
#define PMW_TIMER0_BIT PB3
#define MAX_PWM_REGISTER_NUMBER 255


/******************************************
 *           Decelerations                *
 ******************************************/


extern uint8 g_Remaining_seconds;
extern uint8 g_Remaining_minutes;
extern uint8 g_Remaining_hours;

extern uint8 g_Set_seconds;
extern uint8 g_Set_minutes;
extern uint8 g_Set_hours;




/*********************************************
 Functions prototypes
 *********************************************/

void PWM_Timer0_Init(uint8 set_duty_cycle);
void GptInit(void);
void delay_us_Fuction(uint16 delay_time);
void delay_ms_Fuction(uint16 delay_time);

void timer0_init_CTC_mode(void);
void timeEstablished(void);
void timeRemaining(void);
void timeSet(uint8 input_hours , uint8 input_minutes , uint8 input_seconds) ;
void timeRest(void);
void timeStop (void);
void timeStart (void);

#endif
