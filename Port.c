#include "Port.h"
#include "Dio_Regs.h"

/*Important Note
 * PORT driver in normal has more functions , but I minimize the functions due to the project
 *
 *  */


/***************************************************
 * Name: SetPortDirection
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in): ConfigPtr -Pointer to data
 * Return value: None
 * Description: Function to Set the direction.
 *********************************************************/
void SetPortDirection(Port_ConfigTypeParam * Config_Ptr) {

	 volatile Port_PinType* Port_Ptr = NULL;

	switch (Config_Ptr->port) {
	case 0:
		 Port_Ptr = &DDRA_REG;
		break;
	case 1:
		Port_Ptr = &DDRB_REG;
		break;
	case 2:
		Port_Ptr = &DDRC_REG;
		break;
	case 3:
		Port_Ptr = &DDRD_REG;
		break;

	}

	if (Config_Ptr->direction == PORT_PIN_OUT) {

		SET_BIT(*Port_Ptr, Config_Ptr->pin_num);

	} else if (Config_Ptr->direction == PORT_PIN_IN) {

		CLEAR_BIT(*Port_Ptr, Config_Ptr->pin_num);

	} else {

	}
}
