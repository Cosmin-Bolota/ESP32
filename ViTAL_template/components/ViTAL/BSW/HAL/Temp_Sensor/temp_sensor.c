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
    //GPIO_vSetLevel(DHT11_PIN, HIGH_LEVEL);
    GPIO_vSetDirection(DHT11_PIN, DIR_INPUT); //when we set pin as input then pull-up resistor activates and pin goes to high level
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
	int count = 0;
	while (GPIO_iGetLevel(DHT11_PIN))
	{
		if (count >= DHT11_RESPONSE_START_US)
		{
            ESP_LOGI(TAG, "No Response(1)!");
			return DHT11_TIMEOUT;
		}
		count++;
		ets_delay_us(1);
	}

	count = 0;
	while (GPIO_iGetLevel(DHT11_PIN) == 0)
	{
		if (count >= DHT11_RESPONSE_LOW_US)
		{
            ESP_LOGI(TAG, "No Response(2)!");
			return DHT11_TIMEOUT;
		}
		count++;
		ets_delay_us(1);
	}

	count = 0;
	while (GPIO_iGetLevel(DHT11_PIN))
	{
		if (count >= DHT11_RESPONSE_HIGH_US)
		{
            ESP_LOGI(TAG, "No Response(3)!");
			return DHT11_TIMEOUT;
		}
		count++;
		ets_delay_us(1);
	}

    ESP_LOGI(TAG, "Response received!");
	return DHT11_OK;
}

/*******************************************************************************
 *  Function name    : DHT11_i8Receive
 *
 *  Description      : Get 8 bits of data from the sensor
 *
 *  List of arguments: -
 *
 *  Return value     : int8_t -> Data received; -1 for TIMEOUT
 *
 *******************************************************************************/
int8_t DHT11_i8Receive(void)
{
    int count = 0;
    uint8_t u8Index = 0;
	/* Sensor measures data in the range of 0-50 degrees and 0-100(max) humidity
	 * so it is safe to type cast uint to int or int to uint */
	uint8_t u8Data = 0;

    for (u8Index = 0; u8Index < 8; u8Index++)
    {
        //common 0 level
        while (GPIO_iGetLevel(DHT11_PIN) == 0)
        {
            if (counter >= DHT11_BIT_START_US)
            {
                return DHT11_TIMEOUT;
            }
            count++;
            ets_delay_us(1);
        }
        //receive the bit
        count = 0;
        while (GPIO_iGetLevel(DHT11_PIN))
        {
            /* Max time of bit */
            if (u8Counter >= DHT11_BIT_1_US)
            {
                {
                    return DHT11_TIMEOUT;
                }
            }
            u8Counter++;
            ets_delay_us(1);
        }
        // Time is greater than a 0 so it must be a one 
        if (count > DHT11_BIT_0_US)
        {
            u8Data = (u8Data << 1) | (0x01);
        }
        else
        {
            u8Data = (u8Data << 1);
        }
	}

	return (int8_t) u8Data;
}
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