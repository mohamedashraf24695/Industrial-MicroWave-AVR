#include "App.h"


/***************************************************
 * Name: initApp
 * Parameters (in):void
 * Return value: void
 * Description: Function to Initialize The used Modules
 *********************************************************/


void initApp(void) {

	Dio_Init(&Dio_Configuration);
	buttons_sensorsInit();
	ledsInit();
	motorInit();
	INT1_Init();
	LCD_init();
	GptInit();
	heaterInit();

}


/***************************************************
 * Name: check_OnButton
 * Parameters (in):void
 * Return value: uint8
 * Description: Function is used to check if the on button is pressed or not
 * if the button pressed , the function will return high , else , it will return low
 *********************************************************/

uint8 check_OnButton(void) {
	if (HIGH == readOnButton()) {
		writeONLamp(HIGH);
		return HIGH;
	} else {
		writeONLamp(LOW);
		return LOW;

	}
}


/***************************************************
 * Name: check_Door_Weight
 * Parameters (in):void
 * Return value: uint8
 * Description: Function is used to check if the door is closed and their is a weight in the Microwave
 * if the Two sensors reads HIGH , the function will return high , else , it will return LOW
 *********************************************************/

uint8 check_Door_Weight(void) {

	if ((HIGH == readWeightSensor()) && (HIGH == readDoorSensor())) {
		return HIGH;
	} else {
		return LOW;
	}
}

/***************************************************
 * Name: check_StartButton
 * Parameters (in):void
 * Return value: uint8
 * Description: Function is used to check if the start button is pressed or not
 * if the button pressed , the function will return high , else , it will return low
 *********************************************************/


uint8 check_StartButton(void) {
	if (HIGH == readStartButton()) {
		return HIGH;

	} else {
		return LOW;

	}
}

/***************************************************
 * Name: requestTime
 * Parameters (in):void
 * Return value: void
 * Description: Function is used to get time from the user.
 * The Function Algorithm is as following :
 * 1) it stop the counting flag from counting
 * 2) make the time equals zero as if there is a previous time value from the first usage
 * 3) Display On LCD
 * 4) Takes the time number by number
 * 5) Convert numbers to Time
 * 6) Checks if the time is a proper one or not , for example , if the
 * user enters the minutes 99 and seconds as 65 so it no a proper time
 * 7) Makes the user to re-enter the time until reach proper time
 * 8) Pass the time to the GPT ( General Purpose Timers )
 *********************************************************/


void requestTime(void) {
	timeStop();
	timeRest();
	uint8 entered_hours_tens = 0;
	uint8 entered_hours_uints = 0;
	uint8 entered_min_tens = 0;
	uint8 entered_min_units = 0;
	uint8 entered_sec_tens = 0;
	uint8 entered_sec_uints = 0;

	uint8 entered_hours = 0;
	uint8 entered_min = 0;
	uint8 entered_sec = 0;

	do {
		LCD_clearScreen();
		LCD_displayString("Timer Settings");
		LCD_goToRowColumn(Second_ROW, First_Char);
		LCD_displayString("HH:MM:SS");
		LCD_goToRowColumn(Third_ROW, First_Char);
		LCD_displayString("__:__:__");
		LCD_goToRowColumn(Third_ROW, First_Char);

		entered_hours_tens = requestNumberFromKeypad();
		entered_hours_uints = requestNumberFromKeypad();

		LCD_goToRowColumn(Third_ROW, Fourth_Char);
		entered_min_tens = requestNumberFromKeypad();
		entered_min_units = requestNumberFromKeypad();

		LCD_goToRowColumn(Third_ROW, Seventh_Char);

		entered_sec_tens = requestNumberFromKeypad();
		entered_sec_uints = requestNumberFromKeypad();

		LCD_goToRowColumn(Third_ROW, Tenth_Char);

		entered_hours = (entered_hours_tens * 10) + entered_hours_uints;
		entered_min = (entered_min_tens * 10) + entered_min_units;
		entered_sec = (entered_sec_tens * 10) + entered_sec_uints;

		if ((entered_min > 59) || (entered_sec > 59)) {
			LCD_clearScreen();
			LCD_displayString("Please Enter");
			LCD_goToRowColumn(Second_ROW, First_Char);
			LCD_displayString("Proper Time");
			delay_ms_Fuction(300);

		}

	} while ((entered_min > 59) || (entered_sec > 59));

	timeSet(entered_hours, entered_min, entered_sec);

}


/***************************************************
 * Name: displayTime
 * Parameters (in):void
 * Return value: void
 * Description: Function is used to display time to the user on screen
 * The Function Algorithm is as following :
 * 1) it start the counting flag to counting
 * 2) Displaying time on the screen
 *********************************************************/

void displayTime(void) {
	timeStart();
	LCD_goToRowColumn(Third_ROW, First_Char);
	LCD_intgerToString(g_Remaining_hours / 10);
	LCD_intgerToString(g_Remaining_hours % 10);

	LCD_displayCharacter(':');
	LCD_intgerToString(g_Remaining_minutes / 10);
	LCD_intgerToString(g_Remaining_minutes % 10);

	LCD_displayCharacter(':');
	LCD_intgerToString(g_Remaining_seconds / 10);
	LCD_intgerToString(g_Remaining_seconds % 10);
}




/***************************************************
 * Name: runHeater
 * Parameters (in):void
 * Return value: void
 * Description: Function is used to
 * 1) Run the Heater Pin
 * 2) making the motor inside the microwave to run
 * 3) Turn on Heating indication lamp
 *********************************************************/

void runHeater(void) {
	heaterRun();
	motorRun();
	writeHeaterLamp(HIGH);
}

/***************************************************
 * Name: restTimer
 * Parameters (in):void
 * Return value: void
 * Description: Function is used to pass a reset to the timer
 *********************************************************/

void restTimer(void) {
	timeRest();

}

/***************************************************
 * Name: turnOffHeater
 * Parameters (in):void
 * Return value: void
 * Description: Function is used to
 * 1) Turn off the Heater Pin
 * 2) Making the motor inside the microwave to stop
 * 3) Turn off Heating indication lamp
 *********************************************************/
void turnOffHeater(void) {
	heaterStop();
	motorStop();
	writeHeaterLamp(LOW);
}

/***************************************************
 * Name: requestNumberFromKeypad
 * Parameters (in):void
 * Return value: uint8
 * Description: Takes a single number from the user
 * 1) Request a number from the user using polling technique
 * 2)Checks the number if it is between 0 to 9 or not
 * 3)If not , discard the number as it is never been pressed
 * 4)If it is , return it .
 * 5)display it to the screen
 *
 * The variable " Runtime_Cancel " has the following role :
 * 1) if Cancel button is pressed before start button , The program has
 * to clear the timer
 * 2) A part of the algorithm , is not accepting a new number from the user
 * 3) If the Interrupt comes at the point when the OS request the number , it will
 * prevent showing it on the screen
 * 4) The interrupt will show to the user (Press Any key) to make us go out from the function and
 * go to the clearing function and begin to request from the beginning
 *
 * It will be clean when reading the whole process in OS file
 *********************************************************/


uint8 requestNumberFromKeypad(void) {

	uint8 result = 0;
	uint8 Key;
	if (Runtime_Cancel == 0) {

		do{
			Key = KeyPad_getPressedKey();
			result = Key;
			delay_ms_Fuction(KEYPAD_ACCEPTING_DELAY_TIME);
		}
		while (!(Key >= 0 && Key <= 9));

			if (Runtime_Cancel == 0) {

				LCD_intgerToString(result);
			}
	}
	return result;
}

/***************************************************
 * Name: checkTimeOut
 * Parameters (in):void
 * Return value: uint8
 * Description: If the the time comes to zero , return HIGH
 *********************************************************/


uint8 checkTimeOut(void) {

	if ((g_Remaining_hours == 0) && (g_Remaining_minutes == 0)
			&& (g_Remaining_seconds == 0)) {
		return HIGH;
	} else {
		return LOW;
	}

}


/***************************************************
 * Name: checkTimeOut
 * Parameters (in):void
 * Return value: void
 * Description: If the time is finished without any cancellation ,
 * That's means the process is completed successfully
 *
 * 1) It makes the counting flag to stop
 * 2) Setting the time to be zero , as a preparing for the next process
 * 3) Display to the user that the time is finished with out cancellation
 *********************************************************/

void timeIsFinished(void) {
	LCD_clearScreen();
	timeStop();
	timeRest();
	LCD_displayString("Your Food is ");
	LCD_goToRowColumn(Second_ROW, First_Char);
	LCD_displayString("READY !");
	delay_ms_Fuction(FINISHING_MSG_DELAY_TIME);
}

/***************************************************
 * Name: processIsCanceled
 * Parameters (in):void
 * Return value: void
 * Description: If the time is finished as result of cancellation ,
 *
 * 1) It makes the counting flag to stop
 * 2) Setting the time to be zero , as a preparing for the next process
 * 3) Display to the user that the time is finished as result of cancellation
 *********************************************************/

void processIsCanceled(void) {
	LCD_clearScreen();
	timeStop();
	timeRest();
	LCD_displayString("You Cancel ");
	LCD_goToRowColumn(Second_ROW, First_Char);
	LCD_displayString("The Process !");
	delay_ms_Fuction(FINISHING_MSG_DELAY_TIME);

}
