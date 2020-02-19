#include "Buttons_Sensors.h"

static Port_ConfigTypeParam Start_Button_Config;
static Port_ConfigTypeParam ON_Button_Config;
static Port_ConfigTypeParam OFF_Button_Config;
static Port_ConfigTypeParam Weight_Sensor_Config;
static Port_ConfigTypeParam Door_Sensor_Config;

static void buttonConfigurations(void) {

	Start_Button_Config.port = DioConf_START_BUTTON_PORT_NUM;
	Start_Button_Config.pin_num = DioConf_START_BUTTON_CHANNEL_NUM;
	Start_Button_Config.direction = PORT_PIN_IN;
	Start_Button_Config.pulling = Pull_Down;

	Weight_Sensor_Config.port = DioConf_WEIGHT_SENSOR_PORT_NUM;
	Weight_Sensor_Config.pin_num = DioConf_WEIGHT_SENSOR_CHANNEL_NUM;
	Weight_Sensor_Config.direction = PORT_PIN_IN;
	Weight_Sensor_Config.pulling = Pull_Down;

	Door_Sensor_Config.port = DioConf_DOOR_SENSOR_PORT_NUM;
	Door_Sensor_Config.pin_num = DioConf_DOOR_SENSOR_CHANNEL_NUM;
	Door_Sensor_Config.direction = PORT_PIN_IN;
	Door_Sensor_Config.pulling = Pull_Down;

	ON_Button_Config.port = DioConf_ON_BUTTON_PORT_NUM;
	ON_Button_Config.pin_num = DioConf_ON_BUTTON_CHANNEL_NUM ;
	ON_Button_Config.direction = PORT_PIN_IN;
	ON_Button_Config.pulling = Pull_Down;

	OFF_Button_Config.port = DioConf_OFF_BUTTON_PORT_NUM;
	OFF_Button_Config.pin_num = DioConf_OFF_BUTTON_CHANNEL_NUM;
	OFF_Button_Config.direction = PORT_PIN_IN;
	OFF_Button_Config.pulling = Pull_Down;


}

void buttons_sensorsInit(void) {
	buttonConfigurations();
	SetPortDirection(&Start_Button_Config);
	SetPortDirection(&Weight_Sensor_Config);
	SetPortDirection(&Door_Sensor_Config);
	SetPortDirection(&ON_Button_Config);
	SetPortDirection(&OFF_Button_Config);

}

static uint8 Read_sensor_button(Port_ConfigTypeParam *Config_ptr,
		uint8 INDEX_ID) {
	uint8 state = LOW;
	uint8 DioReading = Dio_ReadChannel(INDEX_ID);

	if (DioReading == HIGH) {

		if (Config_ptr->pulling == Pull_Down) {
			state = HIGH;
		} else if (Config_ptr->pulling == Pull_Up) {
			state = LOW;
		}

	}

	else if (DioReading == LOW) {
		if (Config_ptr->pulling == Pull_Down) {
			state = LOW;
		} else if (Config_ptr->pulling == Pull_Up) {
			state = HIGH;
		}

	}

	else {
		/*NO CODE*/
	}
	return state;
}

uint8 readStartButton(void) {
	uint8 state;
	state = Read_sensor_button(&Start_Button_Config,
	DioConf_START_BUTTON_ID_INDEX);
	return state;
}

uint8 readWeightSensor(void) {
	uint8 state;
	state = Read_sensor_button(&Weight_Sensor_Config,
	DioConf_WEIGHT_SENSOR_ID_INDEX);
	return state;
}
uint8 readDoorSensor(void) {
	uint8 state;
	state = Read_sensor_button(&Door_Sensor_Config,
	DioConf_DOOR_SENSOR_ID_INDEX);
	return state;
}

uint8 readOnButton(void) {
	uint8 state;
	state = Read_sensor_button(&ON_Button_Config,
			DioConf_ON_BUTTON_ID_INDEX);
	return state;
}

uint8 readOffButton(void) {
	uint8 state;
	state = Read_sensor_button(&OFF_Button_Config,
			DioConf_OFF_BUTTON_ID_INDEX);
	return state;
}



