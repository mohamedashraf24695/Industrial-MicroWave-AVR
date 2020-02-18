#ifndef DIO_H
#define DIO_H
/*******************************************************************************
 *                              Included Files                               *
 *******************************************************************************/

#include "common_macros.h"
#include "std_types.h"
#include "micro_config.h"

/*******************************************************************************
 *                              Macros Define                               *
 *******************************************************************************/
#define DIO_CONFIGURED_CHANNLES 11
#define DIO_NOT_INITIALIZED  0
#define DIO_INITIALIZED  1

/* DIO Configured Port ID's  */

#define DioConf_ON_LAMP_PORT_NUM                      (Dio_PortType)3
#define DioConf_PAUSE_LAMP_PORT_NUM                    (Dio_PortType)2
#define DioConf_HEATER_LAMP_PORT_NUM                     (Dio_PortType)3


#define DioConf_START_BUTTON_PORT_NUM                      (Dio_PortType)1
#define DioConf_WEIGHT_SENSOR_PORT_NUM                    (Dio_PortType)1
#define DioConf_DOOR_SENSOR_PORT_NUM                       (Dio_PortType)1

#define DioConf_ON_BUTTON_PORT_NUM                      (Dio_PortType)1
#define DioConf_OFF_BUTTON_PORT_NUM                      (Dio_PortType)0

#define DioConf_MOTOR_PORT_NUM                            (Dio_PortType)2
#define DioConf_HEATER_PORT_NUM                            (Dio_PortType)2





/* DIO Configured Channel ID's */
#define DioConf_ON_LAMP_CHANNEL_NUM          (Dio_ChannelType)1
#define DioConf_PAUSE_LAMP_CHANNEL_NUM             (Dio_ChannelType)3
#define DioConf_HEATER_LAMP_CHANNEL_NUM            (Dio_ChannelType)0


#define DioConf_START_BUTTON_CHANNEL_NUM          (Dio_ChannelType)1
#define DioConf_WEIGHT_SENSOR_CHANNEL_NUM         (Dio_ChannelType)5
#define DioConf_DOOR_SENSOR_CHANNEL_NUM           (Dio_ChannelType)4

#define DioConf_ON_BUTTON_CHANNEL_NUM          (Dio_ChannelType)0
#define DioConf_OFF_BUTTON_CHANNEL_NUM           (Dio_ChannelType)7


#define DioConf_MOTOR_CHANNEL_1_NUM               (Dio_ChannelType)6
#define DioConf_MOTOR_CHANNEL_2_NUM               (Dio_ChannelType)7
#define DioConf_HEATER_CHANNEL_1_NUM               (Dio_ChannelType)4


/* Channel Index in the array of structure*/
#define DioConf_ON_LAMP_ID_INDEX             (uint8)0x00
#define DioConf_START_BUTTON_ID_INDEX             (uint8)0x01
#define DioConf_WEIGHT_SENSOR_ID_INDEX            (uint8)0x02
#define DioConf_DOOR_SENSOR_ID_INDEX              (uint8)0x03
#define DioConf_MOTOR_ID_INDEX_1_NUM              (uint8)0x04
#define DioConf_MOTOR_ID_INDEX_2_NUM              (uint8)0x05
#define DioConf_HEATER_ID_INDEX_1_NUM             (uint8)0x06
#define DioConf_PAUSE_LAMP_ID_INDEX               (uint8)0x07
#define DioConf_HEATER_LAMP_ID_INDEX              (uint8)0x08
#define DioConf_ON_BUTTON_ID_INDEX                (uint8)0x09
#define DioConf_OFF_BUTTON_ID_INDEX               (uint8)0x10

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

/* Type definition for Dio_ChannelType used by the DIO APIs */
typedef uint8 Dio_ChannelType;

/* Type definition for Dio_PortType used by the DIO APIs */
typedef uint8 Dio_PortType;

/* Type definition for Dio_LevelType used by the DIO APIs */
typedef uint8 Dio_LevelType;

typedef uint8 Dio_StateType;

typedef struct {
	/* Member contains the ID of the Port that this channel belongs to */
	Dio_PortType Port_Num;
	/* Member contains the ID of the Channel*/
	Dio_ChannelType Ch_Num;
} Dio_ConfigChannel;

/* Data Structure required for initializing the Dio Driver */
typedef struct {
	Dio_ConfigChannel Channels[DIO_CONFIGURED_CHANNLES];
} Dio_ConfigType;


/******************************************
 *           Decelerations                *
 ******************************************/

extern const Dio_ConfigType Dio_Configuration;

/*******************************************************************************
 *                           Functions Prototype                            *
 *******************************************************************************/

void Dio_Init(const Dio_ConfigType * ConfigPtr);
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level);
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId);



#endif
