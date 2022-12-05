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
#ifndef COMPONENTS_VITAL_RTE_H
#define COMPONENTS_VITAL_RTE_H
#include "global.h"
typedef enum
{
	LOCK_GREEN = (uint8_t)(1 << 1),
	LOCK_RED = (uint8_t)(1 << 2),
	RGB_RED_POS = (uint8_t)(1 << 4),
	RGB_GREEN_POS = (uint8_t)(1 << 5),
	RGB_BLUE_POS = (uint8_t)(1 << 3),
	HEAD_LIGHTS_POS = (uint8_t)((1 << 6) | (1 << 7))
} shift_register_positions_t;

void RTE_vSetAmbientalLightState(bool bState);
void RTE_vSetHeadlightsState(uint8_t LEDS,bool bState);
void RTE_vSetShiftRegisterOutput(shift_register_positions_t u8ComponentMask,
bool bLevel);

#define LOW false
#define HIGH true

#endif