#include "Dio.h"
#include "Dio_Regs.h"

const Dio_ConfigType Dio_Configuration = {

DioConf_ON_LAMP_PORT_NUM, DioConf_ON_LAMP_CHANNEL_NUM,
DioConf_START_BUTTON_PORT_NUM, DioConf_START_BUTTON_CHANNEL_NUM,
DioConf_WEIGHT_SENSOR_PORT_NUM, DioConf_WEIGHT_SENSOR_CHANNEL_NUM,
DioConf_DOOR_SENSOR_PORT_NUM, DioConf_DOOR_SENSOR_CHANNEL_NUM,
DioConf_MOTOR_PORT_NUM, DioConf_MOTOR_CHANNEL_1_NUM,
DioConf_MOTOR_PORT_NUM, DioConf_MOTOR_CHANNEL_2_NUM,
DioConf_HEATER_PORT_NUM, DioConf_HEATER_CHANNEL_1_NUM,
DioConf_PAUSE_LAMP_PORT_NUM, DioConf_PAUSE_LAMP_CHANNEL_NUM,
DioConf_HEATER_LAMP_PORT_NUM, DioConf_HEATER_LAMP_CHANNEL_NUM,
DioConf_ON_BUTTON_PORT_NUM, DioConf_ON_BUTTON_CHANNEL_NUM,
DioConf_OFF_BUTTON_PORT_NUM, DioConf_OFF_BUTTON_CHANNEL_NUM

};

Dio_ConfigChannel * Dio_PortChannels = NULL;
Dio_StateType Dio_Status = DIO_NOT_INITIALIZED;

/***************************************************
 * Name: Dio_Init
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in): ConfigPtr -Pointer to post-build configuration data
 * Return value: None
 * Description: Function to Initialize the Dio module.
 *********************************************************/

void Dio_Init(const Dio_ConfigType * ConfigPtr) {

	Dio_Status = DIO_INITIALIZED;
	Dio_PortChannels = ConfigPtr->Channels;

}

/************************************************************************************
 * Name: Dio_WriteChannel
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): ChannelId - ID of DIO channel.
 *                  Level - Value to be written.
 * Return value: None
 * Description: Function to write a channel's level.
 ************************************************************************************/

void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level) {
	volatile Dio_PortType * Port_Ptr = NULL;
	if (Dio_Status == DIO_INITIALIZED) {

		switch (Dio_PortChannels[ChannelId].Port_Num) {
		case 0:
			Port_Ptr = &PORTA_REG;
			break;
		case 1:
			Port_Ptr = &PORTB_REG;
			break;
		case 2:
			Port_Ptr = &PORTC_REG;
			break;
		case 3:
			Port_Ptr = &PORTD_REG;
			break;
		}

		if (Level == HIGH) {
			/* Write Logic High */
			SET_BIT(*Port_Ptr, Dio_PortChannels[ChannelId].Ch_Num);
		} else if (Level == LOW) {
			/* Write Logic Low */
			CLEAR_BIT(*Port_Ptr, Dio_PortChannels[ChannelId].Ch_Num);
		}

	} else {

		/*No Code*/
		/*If I Were using Complete AUTOSAR MODULES , HERE The code
		 * will use the DET Module to report ERROR*/
	}

}

/************************************************************************************
 * Name: Dio_ReadChannel
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): ChannelId - ID of DIO channel.
 * Return value: Dio_LevelType
 * Description: Function to return the value of the specified DIO channel.
 ************************************************************************************/
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId) {
	volatile Dio_PortType * PIN_Ptr = NULL;
	Dio_LevelType output = LOW;

	if (Dio_Status == DIO_INITIALIZED) {

		switch (Dio_PortChannels[ChannelId].Port_Num) {
		case 0:
			PIN_Ptr = &PINA_REG;
			break;
		case 1:
			PIN_Ptr = &PINB_REG;
			break;
		case 2:
			PIN_Ptr = &PINC_REG;
			break;
		case 3:
			PIN_Ptr = &PIND_REG;
			break;
		}
		if (BIT_IS_SET(*PIN_Ptr, Dio_PortChannels[ChannelId].Ch_Num)) {
			output = HIGH;
		} else {
			output = LOW;
		}

	}

	else {

		/*No Code*/
		/*No Code*/
		/*If I Were using Complete AUTOSAR MODULES , HERE The code
		 * will use the DET Module to report ERROR*/
	}
	return output;

}
