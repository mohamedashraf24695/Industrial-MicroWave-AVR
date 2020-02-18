#include "Gpt.h"


uint8 g_Remaining_seconds;
uint8 g_Remaining_minutes;
uint8 g_Remaining_hours;

uint8 g_Set_seconds;
uint8 g_Set_minutes;
uint8 g_Set_hours;

uint8 g_tick;
uint8 stop_flag = 1;

void delay_us_Fuction(uint16 delay_time) {

	_delay_us(delay_time);
}

void delay_ms_Fuction(uint16 delay_time) {

	_delay_ms(delay_time);
}


void PWM_Timer0_Init(uint8 set_duty_cycle) {
	CLEAR_REG(TCNT0); //initial timer value

	SET_REG(OCR0, set_duty_cycle);

	SET_BIT(PMW_TIMER0_DDR, PMW_TIMER0_BIT); //set OC0 as output pin --> pin where the PWM signal is generated from MC.

	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */
	SET_BIT(TCCR0, WGM00);
	SET_BIT(TCCR0, WGM01);
	SET_BIT(TCCR0, COM01);
	SET_BIT(TCCR0, CS01);

}
void GptInit(void){
	timer0_init_CTC_mode();
}

void timer0_init_CTC_mode(void) {
	SET_BIT(SREG, 7);
	TCNT0 = 0; //timer initial value
	OCR0 = 250; //compare value
	//enable compare interrupt
	/* Configure timer0 control register
	 * 1. Non PWM mode FOC0=1
	 * 2. CTC Mode WGM01=1 & WGM00=0
	 * 3. No need for OC0 in this example so COM00=0 & COM01=0
	 * 4. clock = F_CPU/1024 CS00=1 CS01=0 CS02=1
	 */
	SET_BIT(TIMSK, OCIE0);
	SET_BIT(TCCR0, FOC0);
	SET_BIT(TCCR0, WGM01);
	SET_BIT(TCCR0, CS02);
	SET_BIT(TCCR0, CS00);
}

ISR(TIMER0_COMP_vect) {
	if (stop_flag == 0){
	g_tick++;

	timeRemaining();
	}
}

void timeRemaining(void) {

	if (g_tick == 4) {
		g_tick = 0;
		if (g_Remaining_seconds > 0) {

			g_Remaining_seconds--;
		} else {

			if (g_Remaining_minutes > 0) {
				g_Remaining_seconds = 59;
				g_Remaining_minutes--;

			}

			else {
				if (g_Remaining_hours > 0) {
					g_Remaining_seconds = 59;
					g_Remaining_minutes = 59;
					g_Remaining_hours--;

				}

				else {
					/*No Code*/
				}

			}

		}

	}

}


void timeSet(uint8 input_hours, uint8 input_minutes, uint8 input_seconds) {
	g_Set_seconds = input_seconds;
	g_Set_minutes = input_minutes;
	g_Set_hours = input_hours;

	g_Remaining_seconds = input_seconds;
	g_Remaining_minutes = input_minutes;
	g_Remaining_hours = input_hours;

}

void timeRest(void){
	 g_Remaining_seconds = 0;
	 g_Remaining_minutes=0 ;
	 g_Remaining_hours=0;
	 g_tick = 0 ;
}

void timeStop (void){
	stop_flag = 1 ;
}
void timeStart (void){
	stop_flag = 0 ;
}

