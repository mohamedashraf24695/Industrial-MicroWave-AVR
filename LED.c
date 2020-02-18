#include "LED.h"



static Port_ConfigTypeParam ON_Lamp_Config;
static Port_ConfigTypeParam Pause_Lamp_Config;
static Port_ConfigTypeParam Heater_Lamp_Config;




static void ledsConfigurations(void) {

	ON_Lamp_Config.port = DioConf_ON_LAMP_PORT_NUM;
	ON_Lamp_Config.pin_num = DioConf_ON_LAMP_CHANNEL_NUM;
	ON_Lamp_Config.direction = PORT_PIN_OUT;
	ON_Lamp_Config.pulling = Pull_Down;

	Pause_Lamp_Config.port = DioConf_PAUSE_LAMP_PORT_NUM;
	Pause_Lamp_Config.pin_num = DioConf_PAUSE_LAMP_CHANNEL_NUM;
	Pause_Lamp_Config.direction = PORT_PIN_OUT;
	Pause_Lamp_Config.pulling = Pull_Down;

	Heater_Lamp_Config.port = DioConf_HEATER_LAMP_PORT_NUM;
	Heater_Lamp_Config.pin_num = DioConf_HEATER_LAMP_CHANNEL_NUM;
	Heater_Lamp_Config.direction = PORT_PIN_OUT;
	Heater_Lamp_Config.pulling = Pull_Down;

}
void ledsInit(void) {
	ledsConfigurations();
	SetPortDirection(&ON_Lamp_Config);
	SetPortDirection(&Pause_Lamp_Config);
	SetPortDirection(&Heater_Lamp_Config);
}


static void writeLed(Port_ConfigTypeParam *Config_ptr,
		uint8 INDEX_ID , uint8 Level) {
uint8 state = Level ;

		if (state == HIGH) {

			if (Config_ptr->pulling == Pull_Down) {
				Dio_WriteChannel(INDEX_ID,HIGH);
			} else if (Config_ptr->pulling == Pull_Up) {
				Dio_WriteChannel(INDEX_ID,LOW);
			}
		}



	else if (state == LOW) {


			if (Config_ptr->pulling == Pull_Down) {
				Dio_WriteChannel(INDEX_ID,LOW);
			} else if (Config_ptr->pulling == Pull_Up) {
				Dio_WriteChannel(INDEX_ID,HIGH);

		}
	}

	else {
		/*NO CODE*/
	}

}

void writeONLamp(uint8 LEVEL) {

	writeLed(&ON_Lamp_Config,
			DioConf_ON_LAMP_ID_INDEX , LEVEL) ;
}


void writePauseLamp(uint8 LEVEL) {

	writeLed(&Pause_Lamp_Config,
			DioConf_PAUSE_LAMP_ID_INDEX , LEVEL) ;
}


void writeHeaterLamp(uint8 LEVEL) {

	writeLed(&Heater_Lamp_Config,
			DioConf_HEATER_LAMP_ID_INDEX , LEVEL) ;
}

