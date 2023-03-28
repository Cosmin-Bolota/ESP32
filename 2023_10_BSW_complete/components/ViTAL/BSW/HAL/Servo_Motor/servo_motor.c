/*******************************************************************************
 * COPYRIGHT (C) VITESCO TECHNOLOGIES
 * ALL RIGHTS RESERVED.
 *
 * The reproduction, transmission or use of this document or its
 * contents is not permitted without express written authority.
 * Offenders will be liable for damages. All rights, including rights
 * created by patent grant or registration of a utility model or design,
 * are reserved.
 *******************************************************************************/

#include "BSW/HAL/Servo_Motor/servo_motor.h"

#include "BSW/MCAL/PWM/pwm.h"
uint16_t contor = 0;
int lastangle=0;
static const char *TAG = "HAL SERVO MOTOR";

/*******************************************************************************
 *  Function name    : SERVO_vChangeAngle
 *
 *  Description      : Change the Servo Motor angle
 *
 *  List of arguments: u32ServoAngle -> PWM duty cycle for this angle
 *
 *  Return value     : -
 *
 *******************************************************************************/
void SERVO_vChangeAngle(uint32_t u32ServoAngle)
{
	if (u32ServoAngle == SERVO_MOTOR_0_DEG) //if the parameter is equal to 0 degrees
	{	if(lastangle == 90)
		{
		//set the fill factor so that the servomotor moves counter-clockwise with 90 degrees
        PWM_vSetDutyCycle(SERVO_MOTOR_PWM_CHANNEL, SERVO_MOTOR_180_DEG);
		ets_delay_us(176000);
		PWM_vSetDutyCycle(SERVO_MOTOR_PWM_CHANNEL, SERVO_MOTOR_90_DEG);
		lastangle=0;
		}
	}

	else if (u32ServoAngle == SERVO_MOTOR_90_DEG)
	{	if(lastangle == 0)
		{
			//set the fill factor so that the servomotor moves clockwise with 90 degrees
			PWM_vSetDutyCycle(SERVO_MOTOR_PWM_CHANNEL, SERVO_MOTOR_0_DEG);
			ets_delay_us(176000);
			PWM_vSetDutyCycle(SERVO_MOTOR_PWM_CHANNEL, SERVO_MOTOR_90_DEG);
		}
		else if (lastangle == 180){
			//set the fill factor so that the servomotor moves counter-clockwise with 90 degrees
			PWM_vSetDutyCycle(SERVO_MOTOR_PWM_CHANNEL, SERVO_MOTOR_180_DEG);
			ets_delay_us(176000);
			PWM_vSetDutyCycle(SERVO_MOTOR_PWM_CHANNEL, SERVO_MOTOR_90_DEG);
		}
		lastangle=90;
	}

	else if (u32ServoAngle == SERVO_MOTOR_180_DEG)
	{
			//set the fill factor so that the servomotor moves clockwise with 90 degrees
			PWM_vSetDutyCycle(SERVO_MOTOR_PWM_CHANNEL, SERVO_MOTOR_0_DEG);
			ets_delay_us(176000);
			PWM_vSetDutyCycle(SERVO_MOTOR_PWM_CHANNEL, SERVO_MOTOR_90_DEG);
			lastangle=180;
	}

	else
	{
		ESP_LOGI(TAG, "Invalid value");
	}
}