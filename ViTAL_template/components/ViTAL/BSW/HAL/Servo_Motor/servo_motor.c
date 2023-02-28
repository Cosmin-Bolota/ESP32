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

static const char *TAG = "HAL SERVO MOTOR";

void SERVO_vChangeAngle(uint32_t ServoAngle)
{
    uint32_t u32DutyCycle;

    if(ServoAngle == 0)
    {
        u32DutyCycle = 0;
        PWM_vSetDutyCycle(SERVO_MOTOR_PWM_CHANNEL, u32DutyCycle);
        ESP_LOGI(TAG, "ServoAngle == 0");
    }
        
    else if(ServoAngle == 1)
    {
        u32DutyCycle = 500;
        PWM_vSetDutyCycle(SERVO_MOTOR_PWM_CHANNEL, u32DutyCycle);
        vTaskDelay(11);
        PWM_vSetDutyCycle(SERVO_MOTOR_PWM_CHANNEL, 0);
        ESP_LOGI(TAG, "ServoAngle == 1 (90)");
    }
    else if(ServoAngle == 2)
    {
        u32DutyCycle = 2500;
        PWM_vSetDutyCycle(SERVO_MOTOR_PWM_CHANNEL, u32DutyCycle);
        vTaskDelay(25);
        PWM_vSetDutyCycle(SERVO_MOTOR_PWM_CHANNEL, 0);
        ESP_LOGI(TAG, "ServoAngle == 2 (180)");
    }
    else
        ESP_LOGI(TAG, "Invalid value");

}