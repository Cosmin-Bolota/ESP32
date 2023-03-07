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

#include "SRVL/SCHEDULER/scheduler.h"

#include "BSW/MCAL/ADC/adc.h"
#include "BSW/MCAL/GPIO/gpio.h"
#include "BSW/MCAL/PWM/pwm.h"
#include "BSW/MCAL/WIFI/wifi.h"

#include "RTE/rte.h"
#include "BSW/HAL/Shift_Register/shift_register.h"
#include "BSW\HAL\DC_Motor\dc_motor.h"
#include "BSW/HAL/Buzzer/buzzer.h"
#include "BSW/HAL/Servo_Motor/servo_motor.h"
#include "BSW/HAL/Temp_Sensor/temp_sensor.h"

/* #include "BSW/HAL/Com/com.h" */

#include "nvs_flash.h"

static const char *TAG = "SRVL SCHEDULER";

static httpd_handle_t server = NULL;

void SYSTEM_vInit(void)
{
    /* Call these functions only when specific HW parts are connected */
    
	//Initialize NVS
	esp_err_t ret = nvs_flash_init();
	if (ret == ESP_ERR_NVS_NO_FREE_PAGES)
	{
		ESP_ERROR_CHECK(nvs_flash_erase());
		ret = nvs_flash_init();
	}
	ESP_ERROR_CHECK(ret);

	ADC_vInit();

	GPIO_vInit();

	PWM_vInit();

  	GPIO_vSetDirection(SN74HC595N_DS_PIN,DIR_OUTPUT);
	GPIO_vSetDirection(SN74HC595N_SH_CP_PIN,DIR_OUTPUT);
	GPIO_vSetDirection(SN74HC595N_ST_CP_PIN,DIR_OUTPUT);
	WIFI_vInit(&server);

	DHT11_vRequest();
	uint8_t x = DHT11_i8Response();
}

void vTask100ms(void)
{
	/* COM_vTaskProcessServer(); */

	// SHIFTREG_vOutput8Bits(0b00000000);
	// vTaskDelay(200);
	// SHIFTREG_vOutput8Bits(0b11111111);
	// vTaskDelay(200);

	//RTE_vSetAmbientalLightState(true);
	//vTaskDelay(800);

	
	// DCMOT_vChangeSpeed(DC_MOTOR_LOW_SPEED);
	// vTaskDelay(100);
	// DCMOT_vChangeSpeed(DC_MOTOR_STOP);
	// vTaskDelay(1000);
	// DCMOT_vChangeSpeed(DC_MOTOR_MEDIUM_SPEED);
	// vTaskDelay(1000);
	// DCMOT_vChangeSpeed(DC_MOTOR_FULL_SPEED);
	// vTaskDelay(1000);
	// DCMOT_vChangeSpeed(DC_MOTOR_STOP);
	
	//buzzer
	// BUZZER_vChangeDutyCycle(10000);
	// SERVO_vChangeAngle(4);
	// vTaskDelay(500);
	// BUZZER_vChangeDutyCycle(0);
	// vTaskDelay(500);

	//servo
	SERVO_vChangeAngle(1);
	vTaskDelay(300);
	SERVO_vChangeAngle(2);
	vTaskDelay(300);

	//ASW_vTaskHeadLightsControl(14);
}

void SYSTEM_vTaskScheduler(void)
{
	uint16_t u16TickCount = 0;

	while (1)
	{
		if (u16TickCount % TASK_100MS == 0)
		{
			vTask100ms();
		}

		u16TickCount++;
		if (u16TickCount >= TASK_5000MS)
		{
			u16TickCount = 0;
		}

		vTaskDelay(100);
	}
}
