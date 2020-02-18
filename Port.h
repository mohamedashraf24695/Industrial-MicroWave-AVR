
#ifndef PORT_H
#define PORT_H


/*********************************************
 *            H files Included               *
 *********************************************/

#include "common_macros.h"
#include "std_types.h"
#include "micro_config.h"

/******************************************
 *           MACROS DEF                *
 ******************************************/
#define PORT_INITIALIZED   1
#define PORT_NOT_INITIALIZED 0
#define Pins_Total_Num 32


/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/


typedef uint8 Port_PinType ;

typedef enum {
	PORT_PIN_IN ,
	PORT_PIN_OUT
}Port_PinDirectionType;



typedef enum {
	No_PULL ,
	Pull_Up ,
	Pull_Down

}Port_PullingConfig ;

typedef enum{
	Not_Changable,
	Changable
}Port_PinDirectionChange;



typedef struct {
	Port_PinType port;
	Port_PinType pin_num;
    Port_PinDirectionType direction;
    Port_PullingConfig pulling ;
}Port_ConfigTypeParam;



/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/


void SetPortDirection(Port_ConfigTypeParam * Config_Ptr) ;

#endif

