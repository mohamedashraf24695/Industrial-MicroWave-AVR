#include "ISR.h"
#include "OS.h"

uint8 Runtime_Cancel = 0 ;

ISR(INT1_vect)
{

		 if (MAIN_PROCESS_STATE == OS_State_flag){

			 OS_State_flag = CANEL_FINSHING_STATE ;

}
		if ((OS_State_flag >OFF_STATE )&& (OS_State_flag < MAIN_PROCESS_STATE)){
			Runtime_Cancel = 1 ;
			LCD_clearScreen();
			OS_State_flag = CANCEL_TAKING_TIME ;
			LCD_displayString("Press Any number ");
			LCD_goToRowColumn(Second_ROW, First_Char);
			LCD_displayString("From The Keypad ");
			delay_ms_Fuction(FINISHING_MSG_DELAY_TIME);

		}

}


/* External INT1 enable and configuration function */
void INT1_Init(void)
{
	SET_BIT(SREG,7);     // Enable interrupts by setting I-bit
	CLEAR_BIT(DDRD,PD3); // Configure INT1/PD3 as input pin
	SET_BIT(PORTD,PD3); // Enable the internal pull up resistor at PD3 pin
	SET_BIT(GICR,INT1);    // Enable external interrupt pin INT1

	// Trigger INT1 with the falling edge
	SET_BIT(MCUCR,ISC11);
	CLEAR_BIT(MCUCR,ISC10);

}


