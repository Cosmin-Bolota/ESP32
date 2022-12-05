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

#include "RTE/rte.h"

#include "BSW/HAL/Buzzer/buzzer.h"
#include "BSW/HAL/Com/com.h"
#include "BSW/HAL/DC_Motor/dc_motor.h"
#include "BSW/HAL/Proximity_Sensor/proximity_sensor.h"
#include "BSW/HAL/Servo_Motor/servo_motor.h"
#include "BSW/HAL/Shift_Register/shift_register.h"

static const char *TAG = "RTE";


void RTE_vSetAmbientalLightState(bool bState)
{
	//static uint8_t s_u8ColorState = STATE_RED;
	static uint8_t s_u8ColorState = 0;
	switch (s_u8ColorState)
	{
	case 0:
		SHIFTREG_vOutput8Bits(0b00100000);
		s_u8ColorState++;
		break;
	case 1:
		SHIFTREG_vOutput8Bits(0b00010000);
		s_u8ColorState++;
		break;
	case 2:
		SHIFTREG_vOutput8Bits(0b00001000);
		s_u8ColorState++;
		break;
	case 3:
		SHIFTREG_vOutput8Bits(0b00110000);
		s_u8ColorState = 0;
		break;
	default:
		break;
	}

}

void RTE_vSetHeadlightsState(uint8_t LEDS,bool bState)
{
	RTE_vSetShiftRegisterOutput(LEDS, bState);
}

void RTE_vSetShiftRegisterOutput(shift_register_positions_t u8ComponentMask,
bool bLevel)
{
	static uint8_t s_u8CurrentData = 0;

	if (bLevel == HIGH)
	{
		s_u8CurrentData |= u8ComponentMask;
	}
	else if (bLevel == LOW)
	{
		s_u8CurrentData &= ~(u8ComponentMask);
	}
	else
	{
		ESP_LOGI(TAG, "Invalid level for shift register");
	}
 
	SHIFTREG_vOutput8Bits(s_u8CurrentData);
}
