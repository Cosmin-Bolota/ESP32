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

#include "BSW/HAL/Temp_Sensor/temp_sensor.h"
#include "BSW/MCAL/GPIO/gpio.h"
static const char *TAG = "HAL TEMP SENSOR";
/*******************************************************************************
 *  Function name    : DHT11_vRequest
 *
 *  Description      : Send pulse to activate the sensor
 *
 *  List of arguments: -
 *
 *  Return value     : -
 *
 *******************************************************************************/
void DHT11_vRequest(void)
{
    GPIO_vSetDirection(DHT11_PIN, DIR_OUTPUT);
    GPIO_vSetLevel(DHT11_PIN, HIGH_LEVEL);
    GPIO_vSetLevel(DHT11_PIN, LOW_LEVEL);
    ets_delay_us(20);
    GPIO_vSetLevel(DHT11_PIN, HIGH_LEVEL);
    ESP_LOGI(TAG, "Request completed!");
}

/*******************************************************************************
 *  Function name    : DHT11_i8Response
 *
 *  Description      : See if the sensor got the pulse
 *
 *  List of arguments: -
 *
 *  Return value     : int8_t -> 0 - OK; -1 for TIMEOUT
 *
 *******************************************************************************/
int8_t DHT11_i8Response(void)
{
    int x,y;
    GPIO_vSetDirection(DHT11_PIN, DIR_INPUT);
    ets_delay_us(50);
    x = GPIO_iGetLevel(DHT11_PIN);
    ets_delay_us(80);
    y = GPIO_iGetLevel(DHT11_PIN);

    if(x==0 && y == 1)
    {
        ESP_LOGI(TAG, "Response received!");
        return 1;
    }
    else 
    {
        ESP_LOGI(TAG, "Response failed!");
        return 0;
    }
}

// /*******************************************************************************
//  *  Function name    : DHT11_i8Receive
//  *
//  *  Description      : Get 8 bits of data from the sensor
//  *
//  *  List of arguments: -
//  *
//  *  Return value     : int8_t -> Data received; -1 for TIMEOUT
//  *
//  *******************************************************************************/
// int8_t DHT11_i8Receive(void)
// {

// }

// /*******************************************************************************
//  *  Function name    : DHT11_dht11Read
//  *
//  *  Description      : Make a full operation on the sensor
//  *
//  *  List of arguments: -
//  *
//  *  Return value     : DHT11_t -> Data from sensor
//  *
//  *******************************************************************************/
// DHT11_struct DHT11_dht11Read(void)
// {

// }

// /*******************************************************************************
//  *  Function name    : DHT11_vTaskTempAndHumCalculate
//  *
//  *  Description      : Calculate and update temp and hum
//  *
//  *  List of arguments: -
//  *
//  *  Return value     : -
//  *
//  *******************************************************************************/
// void DHT11_vTaskTempAndHumCalculate(void)
// {

// }