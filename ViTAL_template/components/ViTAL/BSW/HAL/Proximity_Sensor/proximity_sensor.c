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

#include "BSW/HAL/Proximity_Sensor/proximity_sensor.h"
#include "BSW/MCAL/GPIO/gpio.h"
#include "BSW/HAL/Com/com.h"

static const char *TAG = "HAL PROXIMITY SENSOR";

extern COM_GET_struct g_GET_DataStructure;

void PROX_vRequest(void)
{
    GPIO_vSetDirection(HC_SR04_TRIGGER_PIN, DIR_OUTPUT);
    /* L-H-L of at least 10us */
    GPIO_vSetLevel(HC_SR04_TRIGGER_PIN, LOW_LEVEL);
	GPIO_vSetLevel(HC_SR04_TRIGGER_PIN, HIGH_LEVEL);
    ets_delay_us(10);
    GPIO_vSetLevel(HC_SR04_TRIGGER_PIN, LOW_LEVEL);
}

uint16_t PROX_u16Read(void)
{
    PROX_vRequest();

	while (GPIO_iGetLevel(HC_SR04_ECHO_PIN) == 0)
		;

	int64_t echo_start = esp_timer_get_time();

	while (GPIO_iGetLevel(HC_SR04_ECHO_PIN))
		;

    uint16_t distanceCM = (uint16_t) (((esp_timer_get_time() - echo_start) * 0.0343) / 2);
    g_GET_DataStructure.u16Distance = distanceCM;

	return distanceCM;
}