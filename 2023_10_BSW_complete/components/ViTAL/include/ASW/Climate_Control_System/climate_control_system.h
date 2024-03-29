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

#ifndef COMPONENTS_VITAL_ASW_CLIMATE_CONTROL_SYSTEM_H
#define COMPONENTS_VITAL_ASW_CLIMATE_CONTROL_SYSTEM_H

#include "global.h"

uint8_t u8CalculateComfort(uint8_t u8Temp, uint8_t u8Hum);

void ASW_vTaskDCMsTest(void);
void ASW_vTaskDCMdTest(void);
void ASW_vTaskFanTempTreshold();

#endif
