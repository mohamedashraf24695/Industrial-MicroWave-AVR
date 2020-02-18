
#include "heater.h"


heater_info_holder  heater_information_1;
heater_info_holder *holder_ptr;
static Port_ConfigTypeParam Heater_Config_1;

uint16 g_heating_temperature ;


static void heaterConfigurations(void){

	Heater_Config_1.port = DioConf_HEATER_PORT_NUM;
	Heater_Config_1.pin_num = DioConf_HEATER_CHANNEL_1_NUM;
	Heater_Config_1.direction = PORT_PIN_OUT;
	Heater_Config_1.pulling = No_PULL;


	heater_information_1.mode= DEFAULT_HEATER_MODE;

#if (PMW_ENABLE == HIGH)
	heater_information_1.heat_precentage =DEFAULT_HEATER_HEAT_PRECENTAGE ;
#else
	heater_information_1.heat_precentage =FULL_HEATER_HEAT_PRECENTAGE ;
#endif

}
void heaterInit(void) {

	heaterConfigurations();
	SetPortDirection(&Heater_Config_1);
	holder_ptr = &heater_information_1 ;
}

void heaterAction(void) {
	holder_ptr->heat_precentage = (float32)g_heating_temperature/1000.0 ;

	if (holder_ptr->mode == HEATER_OFF) {
		Dio_WriteChannel(DioConf_HEATER_ID_INDEX_1_NUM, LOW);

	} else if (holder_ptr->mode == HEATER_ON) {
		Dio_WriteChannel(DioConf_HEATER_ID_INDEX_1_NUM, HIGH);
	}
#if (PMW_ENABLE==HIGH)
		if (holder_ptr->heat_precentage >= 0
				&& holder_ptr->heat_precentage <= 100) {

			PWM_Timer0_Init(
					(holder_ptr->heat_precentage / 100.0)
							* MAX_PWM_REGISTER_NUMBER);

		} else {

			PWM_Timer0_Init(MAX_PWM_REGISTER_NUMBER);
		}

	} else {
		/*No Code*/

	}
#endif
}





#if (PMW_ENABLE == HIGH)
void heaterIncHeat(void) {
	holder_ptr->heat_precentage += HEATER_RATE_OF_INCREASING;

	if (holder_ptr->heat_precentage >= 0
			&&holder_ptr->heat_precentage <= 100) {

		PWM_Timer0_Init(
				(holder_ptr->heat_precentage / 100.0) * MAX_PWM_REGISTER_NUMBER);

	} else {

		PWM_Timer0_Init(MAX_PWM_REGISTER_NUMBER);
	}

}

#endif


void heaterStop (void){
	holder_ptr->mode = HEATER_OFF ;
	heaterAction();
}
void heaterRun (void){
	holder_ptr->mode = HEATER_ON ;
	heaterAction();
}


