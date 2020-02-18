
/* Important Note :
 * When I designed this module , I targeted to make it more general for motors
 * Some Applications use the motor in constant speed ,
 * So , Putting code in PMW is useless in this case , so I made Preprocessing
 * by #define the mode , to make the module depending on your usage , if you want to
 * use speed , enable PMW from the motor.h file
 *
 * By : Mohamed Ashraf Ibrahim
 *
 * */
#include "motor.h"

motor_info_holder motor_information_1;
motor_info_holder *holder_ptr;
static Port_ConfigTypeParam motor_Config_1;
static Port_ConfigTypeParam motor_Config_2;



/***************************************************
 * Name: motorConfigurations  (STATIC FUNCTION)
 * Parameters (in):void
 * Return value: void
 * Description:
 * 1) Motor Configurations : It makes define the port , pin , direction and pulling mode
 * for each pin of the two motor's pin
 *
 * 2) The motor informations , include mode , speed and direction .
 * This information will be read from the other module's function and according to it
 * it will act
 *
 *********************************************************/


static void motorConfigurations(void) {
	motor_Config_1.port = DioConf_MOTOR_PORT_NUM;
	motor_Config_1.pin_num = DioConf_MOTOR_CHANNEL_1_NUM;
	motor_Config_1.direction = PORT_PIN_OUT;
	motor_Config_1.pulling = No_PULL;

	motor_Config_2.port = DioConf_MOTOR_PORT_NUM;
	motor_Config_2.pin_num = DioConf_MOTOR_CHANNEL_2_NUM;
	motor_Config_2.direction = PORT_PIN_OUT;
	motor_Config_2.pulling = No_PULL;

	motor_information_1.mode = DEFAULT_MOTOR_MODE;
	motor_information_1.direction = DEFAULT_MOTOR_DIRECTION;
	motor_information_1.speed_precentage = FULL_MOTOR_SPEED;

}

/***************************************************
 * Name: motorInit
 * Parameters (in):void
 * Return value: void
 * Description:
 * 1) Run the motorconfiguration function (Read its description)
 * 2) Set the directiom of the two motor's pin
 * 3) assign a pointer to read from the motor's information
 *
 *Note : I wrote motor_information_1 to make it possible in other applications to use more than
 *one motor
 *********************************************************/
void motorInit(void) {

	motorConfigurations();
	SetPortDirection(&motor_Config_1);
	SetPortDirection(&motor_Config_2);
	holder_ptr = &motor_information_1;
}

/***************************************************
 * Name: motorAction
 * Parameters (in):void
 * Return value: void
 * Description:
 * 1) Write the motor's pins acccording to its configuration (ON ,OFF)
 * 2) If is it is off , both of the pins will be in LOW state
 * 3) Puts HIGH or LOW on the motor's pin according to it direction if it is ON
 * 4) If PMW enabled , send the speed to the Gpt (General Purpose Timer module )
 * to send PMW signal to the motor's enable pin

 *********************************************************/

void motorAction(void) {

	if (holder_ptr->mode == MOTOR_OFF) {
		Dio_WriteChannel(DioConf_MOTOR_ID_INDEX_1_NUM, LOW);
		Dio_WriteChannel(DioConf_MOTOR_ID_INDEX_2_NUM, LOW);

	}
	else if (holder_ptr->mode == MOTOR_ON) {

		if (holder_ptr->direction == clock_wise) {

			Dio_WriteChannel(DioConf_MOTOR_ID_INDEX_1_NUM, HIGH);
			Dio_WriteChannel(DioConf_MOTOR_ID_INDEX_2_NUM, LOW);

		} else if (holder_ptr->direction == anti_clock_wise) {

			Dio_WriteChannel(DioConf_MOTOR_ID_INDEX_1_NUM, LOW);
			Dio_WriteChannel(DioConf_MOTOR_ID_INDEX_2_NUM, HIGH);

		} else {
			/*No Code*/
		}

#if (PMW_MOTOR_MODE==HIGH)
		if (holder_ptr->speed_precentage >= 0
				&& holder_ptr->speed_precentage <= 100) {

			PWM_Timer0_Init(
					(holder_ptr->speed_precentage / 100.0)
							* MAX_PWM_REGISTER_NUMBER);

		} else {

			PWM_Timer0_Init(MAX_PWM_REGISTER_NUMBER);
		}

#endif


	} else {
		/*No Code*/
	}

}

void motorReverseDirection(void) {
	if (holder_ptr->direction == clock_wise) {

		holder_ptr->direction = anti_clock_wise;
		Dio_WriteChannel(DioConf_MOTOR_ID_INDEX_1_NUM, LOW);
		Dio_WriteChannel(DioConf_MOTOR_ID_INDEX_2_NUM, HIGH);

	} else if (holder_ptr->direction == anti_clock_wise) {
		holder_ptr->direction = clock_wise;
		Dio_WriteChannel(DioConf_MOTOR_ID_INDEX_1_NUM, HIGH);
		Dio_WriteChannel(DioConf_MOTOR_ID_INDEX_2_NUM, LOW);

	} else {
		/*No Code*/
	}

}

void motorStop(void) {
	holder_ptr->mode = MOTOR_OFF;
	motorAction();

}

void motorRun(void) {
	holder_ptr->mode = MOTOR_ON;
	motorAction();
}


#if (PMW_MOTOR_MODE==HIGH)





void motorIncSpeed(void) {
	holder_ptr->speed_precentage = holder_ptr->speed_precentage
			+ ((float32) MOTORSPEED_RATE_OF_INCREASING);

	if (holder_ptr->speed_precentage >= 0.0
			&& holder_ptr->speed_precentage <= 100.0) {

		PWM_Timer0_Init(
				(holder_ptr->speed_precentage / 100.0) * MAX_PWM_REGISTER_NUMBER);
	}

	else if (holder_ptr->speed_precentage < 0.0) {
		holder_ptr->speed_precentage = 0;
		PWM_Timer0_Init(
				(holder_ptr->speed_precentage / 100.0) * MAX_PWM_REGISTER_NUMBER);
	} else if (holder_ptr->speed_precentage > 100.0) {
		holder_ptr->speed_precentage = 100;
		PWM_Timer0_Init(
				(holder_ptr->speed_precentage / 100.0) * MAX_PWM_REGISTER_NUMBER);
	}

}

void motorDecSpeed(void) {

	holder_ptr->speed_precentage = holder_ptr->speed_precentage
			- ((float32) MOTORSPEED_RATE_OF_INCREASING);
	if (holder_ptr->speed_precentage >= 0.0
			&& holder_ptr->speed_precentage <= 100.0) {

		PWM_Timer0_Init(
				(holder_ptr->speed_precentage / 100.0) * MAX_PWM_REGISTER_NUMBER);
	}

	else if (holder_ptr->speed_precentage < 0.0) {
		holder_ptr->speed_precentage = 0;
		PWM_Timer0_Init(
				(holder_ptr->speed_precentage / 100.0) * MAX_PWM_REGISTER_NUMBER);
	} else if (holder_ptr->speed_precentage > 100.0) {
		holder_ptr->speed_precentage = 100;
		PWM_Timer0_Init(
				(holder_ptr->speed_precentage / 100.0) * MAX_PWM_REGISTER_NUMBER);
	}

}


#endif
