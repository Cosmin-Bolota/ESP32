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

#include "ASW/Headlights/headlights.h"

#include "RTE/rte.h"

static const char *TAG = "ASW HL";

void ASW_vTaskHeadLightControl()
{
    uint16_t luminance = RTE_u16Get_PhotoRes();
    if(luminance < 25)
    {
        RTE_vSetHeadlightsState(1);
        ESP_LOGI(TAG, "HeadLight: ON ( < 25%% )");
    }
    else{
        RTE_vSetHeadlightsState(0);
        ESP_LOGI(TAG, "HeadLight: OFF ( > 25%% )");
    }
}