#include "App.h"
#include "OS.h"
uint8 OS_State_flag = OFF_STATE;


void OS_Init(void) {

	initApp();

}


void OS_Schedular(void) {

	if (OS_State_flag == OFF_STATE) {

		if (HIGH == check_OnButton()) {

			OS_State_flag = REQUEST_TIME_STATE;
		} else {

		}
	}

	if (OS_State_flag == REQUEST_TIME_STATE) {

		requestTime();

		if (OS_State_flag == REQUEST_TIME_STATE){
		OS_State_flag = DOOR_WEIGHT_SENSORS_STATE;
		}

	}

	if (OS_State_flag == DOOR_WEIGHT_SENSORS_STATE) {

		if (HIGH == check_Door_Weight()) {

			OS_State_flag = START_BUTTON_STATE;

		}

	}

	if (OS_State_flag == START_BUTTON_STATE) {

		if (HIGH == check_StartButton())

		{
			OS_State_flag = MAIN_PROCESS_STATE;
		}

	}

	if (OS_State_flag == MAIN_PROCESS_STATE) {

		displayTime();
		runHeater();

		if (HIGH == checkTimeOut())

		{
			if (OS_State_flag == CANEL_FINSHING_STATE){
/* If the Interrupt is enabled , it will make time out in the ISR code
 * When the Function checks the time , it will find it out also
 * but if the time is outed by interrupt , it will make the flag = 6
 * so the code is prevented to make the flag = 5 due to normal time out
 * operation */

			}
			else {
				OS_State_flag = NORMAL_FINISHING_STATE;
			}


		}
	}

	if (OS_State_flag == NORMAL_FINISHING_STATE) {
		turnOffHeater();
		timeIsFinished();
		OS_State_flag = 1;

	}

	if (OS_State_flag == CANEL_FINSHING_STATE){
		 turnOffHeater();
		 processIsCanceled();
		 OS_State_flag = REQUEST_TIME_STATE;
	}

	if (OS_State_flag == CANCEL_TAKING_TIME){

		OS_State_flag = 1;
		Runtime_Cancel = 0 ;
		}



}
