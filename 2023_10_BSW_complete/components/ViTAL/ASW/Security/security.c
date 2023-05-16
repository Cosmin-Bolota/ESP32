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

#include "ASW/Security/security.h"

#include "RTE/rte.h"
#include "BSW/HAL/Buzzer/buzzer.h"
#include "BSW/HAL/Com/com.h"

extern COM_POST_struct g_POST_DataStructure;

static const char *TAG = "ASW SECURITY";
int flagFindMyCar = 0;
void ASW_vTaskFindMyCar()
{
    flagFindMyCar = RTE_bGet_ButtonFindMyCarStatus();
    if(flagFindMyCar)
    {
        RTE_vSetBuzzerOn();
        BUZZER_vChangeDutyCycle(BUZZER_PWM_LVL5);
        
        RTE_vSetHeadlightsState(ON);
        RTE_vSetShiftRegisterOutput(ALL_COLORS, HIGH);
        ESP_LOGI(TAG, "Security: ON");
        ets_delay_us(8000);
    }
    else
    {
        if(!RTE_bGetBuzzerStatusSecurity())
        {
            BUZZER_vChangeDutyCycle(BUZZER_PWM_STOP);
            RTE_vSetBuzzerOff();
        }

        RTE_vSetHeadlightsState(OFF);
        if(!RTE_bGet_ButtonAmbientalLightsStatus())
        {
            RTE_vSetShiftRegisterOutput(ALL_COLORS, LOW);
        }
        ESP_LOGI(TAG, "Security: OFF");
    }
}

void ASW_vTaskCheckDriver()
{
    RTE_vSet_Occupied(RTE_u16GetSavedDistance() < DISTANCE_THRESHOLD);
    if(RTE_bGet_IsOccupied() && RTE_bGet_IsLocked())
    {
        RTE_vSetBuzzerOnSecurity();
        BUZZER_vChangeDutyCycle(BUZZER_PWM_LVL5);
        RTE_vSetHeadlightsState(ON);
        RTE_vSetShiftRegisterOutput(ALL_COLORS, HIGH);
    }
    else if(!RTE_bGet_IsLocked())
    {
        if(!RTE_bGetBuzzerStatus())
        {
            BUZZER_vChangeDutyCycle(BUZZER_PWM_STOP);
        }

        RTE_vSetBuzzerOffSecurity();
        RTE_vSetHeadlightsState(OFF);
        if(!RTE_bGet_ButtonAmbientalLightsStatus())
        {
            RTE_vSetShiftRegisterOutput(ALL_COLORS, LOW);
        }
    }
}
