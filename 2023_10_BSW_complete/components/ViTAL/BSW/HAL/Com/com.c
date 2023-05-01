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

#include "BSW/HAL/Com/com.h"

#include "BSW/MCAL/WIFI/wifi.h"

static const char *TAG = "HAL COM";

extern char g_cGETBuffer[100];
extern char g_cPOSTBuffer[100];

extern bool g_bGETRequestInProcess;
extern bool g_bPOSTRequestInProcess;

/* Assign some default values to GET buffer */
COM_GET_struct g_GET_DataStructure =
{ .u8Temperature = 27, .u8Humidity = 50, .u8Comfort = 24, .bIsLocked = true,
		.bIsOccupied = false, .u8Distance = 0 };

/* Assign some default values to POST buffer */
COM_POST_struct g_POST_DataStructure =
{ .bButtonFan = false, .bButtonTrunk = false, .bButtonHeadlights = false,
		.bButtonAmbientalLights = false, .bButtonFindMyCar = false,
		.bButtonHonk = false, .bButtonSecurity = false, .bButtonDoorLock = false,
		.u8UserTemperature = 27, 
		.bButtonShiftReg = false, .bButtonRLed = false, .bButtonGLed = false, .bButtonBLed = false, .u8UserdataDCMs = 0, .u8UserdataDCMd = 0,
		.u8UserdataBuzzer = 0, .u8UserdataServomotor = 0};

/*******************************************************************************
 *  Function name    : COM_vProcessGetRequest
 *
 *  Description      : Update the GET buffer
 *
 *  List of arguments: -
 *
 *  Return value     : -
 *
 *******************************************************************************/
void COM_vProcessGetRequest(void)
{
	if (g_bGETRequestInProcess)
	{
		char dataBuffer[7];

		sprintf(dataBuffer, "%d", g_GET_DataStructure.u8Temperature);
		/* First string to be copied to buffer */
		strcpy(g_cGETBuffer, dataBuffer);
		strcat(g_cGETBuffer, "\n");

		sprintf(dataBuffer, "%d", g_GET_DataStructure.u8Humidity);
		strcat(g_cGETBuffer, dataBuffer);
		strcat(g_cGETBuffer, "\n");

		sprintf(dataBuffer, "%d", g_GET_DataStructure.u8Comfort);
		strcat(g_cGETBuffer, dataBuffer);
		strcat(g_cGETBuffer, "\n");

		sprintf(dataBuffer, "%d", g_GET_DataStructure.u16PhotoRes);
		strcat(g_cGETBuffer, dataBuffer);
		strcat(g_cGETBuffer, "\n");

		if (g_GET_DataStructure.bIsLocked)
		{
			strcat(g_cGETBuffer, "locked\n");
		}
		else
		{
			strcat(g_cGETBuffer, "unlocked\n");
		}

		if (g_GET_DataStructure.bIsOccupied)
		{
			strcat(g_cGETBuffer, "occupied\n");
		}
		else
		{
			strcat(g_cGETBuffer, "unoccupied\n");
		}

		sprintf(dataBuffer, "%d", g_GET_DataStructure.u8Distance);
		strcat(g_cGETBuffer, dataBuffer);
		strcat(g_cGETBuffer, "\n");

		g_bGETRequestInProcess = false;
	}
}

/*******************************************************************************
 *  Function name    : COM_vProcessPostRequest
 *
 *  Description      : Process the POST buffer
 *
 *  List of arguments: -
 *
 *  Return value     : -
 *
 *******************************************************************************/
void COM_vProcessPostRequest(void)
{
	if (g_bPOSTRequestInProcess)
	{
		if (strcmp(g_cPOSTBuffer, "button=Fan+On") == 0)
		{
			g_POST_DataStructure.bButtonFan = true;
		}
		else if (strcmp(g_cPOSTBuffer, "button=Fan+Off") == 0)
		{
			g_POST_DataStructure.bButtonFan = false;
		}

		else if (strcmp(g_cPOSTBuffer, "button=Open+Trunk") == 0)
		{
			g_POST_DataStructure.bButtonTrunk = true;
		}
		else if (strcmp(g_cPOSTBuffer, "button=Close+Trunk") == 0)
		{
			g_POST_DataStructure.bButtonTrunk = false;
		}

		else if (strcmp(g_cPOSTBuffer, "button=Head+Lights+On") == 0)
		{
			g_POST_DataStructure.bButtonHeadlights = true;
		}
		else if (strcmp(g_cPOSTBuffer, "button=Head+Lights+Off") == 0)
		{
			g_POST_DataStructure.bButtonHeadlights = false;
		}

		else if (strcmp(g_cPOSTBuffer, "button=Ambiental+Lights+On") == 0)
		{
			g_POST_DataStructure.bButtonAmbientalLights = true;
		}
		
		else if (strcmp(g_cPOSTBuffer, "button=Ambiental+Lights+Off") == 0)
		{
			g_POST_DataStructure.bButtonAmbientalLights = false;
		}

		else if (strcmp(g_cPOSTBuffer, "button=Find+My+Car") == 0)
		{
			g_POST_DataStructure.bButtonFindMyCar = true;
		}

		else if (strcmp(g_cPOSTBuffer, "button=Stop+Find+My+Car") == 0)
		{
			g_POST_DataStructure.bButtonFindMyCar = false;
		}

		else if (strcmp(g_cPOSTBuffer, "button=Stop+Find+My+Car") == 0)
		{
			g_POST_DataStructure.bButtonFindMyCar = false;
		}

		else if (strcmp(g_cPOSTBuffer, "button=Honk+On") == 0)
		{
			g_POST_DataStructure.bButtonHonk = true;
		}

		else if (strcmp(g_cPOSTBuffer, "button=Honk+Off") == 0)
		{
			g_POST_DataStructure.bButtonHonk = false;
		}

		else if (strcmp(g_cPOSTBuffer, "button=Security+On") == 0)
		{
			g_POST_DataStructure.bButtonSecurity = true;
		}
		else if (strcmp(g_cPOSTBuffer, "button=Security+Off") == 0)
		{
			g_POST_DataStructure.bButtonSecurity = false;
		}

		else if (strcmp(g_cPOSTBuffer, "button=Unlock+Door") == 0)
		{
			g_POST_DataStructure.bButtonDoorLock = false;
		}
		else if (strcmp(g_cPOSTBuffer, "button=Lock+Door") == 0)
		{
			g_POST_DataStructure.bButtonDoorLock = true;
		}

		else if (strstr(g_cPOSTBuffer, "user-temp=") != NULL)
		{
			g_POST_DataStructure.u8UserTemperature = (g_cPOSTBuffer[10] - '0') * 10;
			g_POST_DataStructure.u8UserTemperature += g_cPOSTBuffer[11] - '0';
		}

		else if (strstr(g_cPOSTBuffer, "dcmii=") != NULL)
		{
			if((int)(g_cPOSTBuffer[6] - '0') == 0) {
				g_POST_DataStructure.u8UserdataDCMd=0;
			}
			else {
			g_POST_DataStructure.u8UserdataDCMd = (int)(g_cPOSTBuffer[6] - '0') * 10;
			g_POST_DataStructure.u8UserdataDCMd += (int)(g_cPOSTBuffer[7] - '0');
			}
			
			if((int)(g_POST_DataStructure.u8UserdataDCMd)==10) {
					g_POST_DataStructure.u8UserdataDCMd=100;
				}
		}

		else if (strstr(g_cPOSTBuffer, "dcmi=") != NULL)
		{
			if((int)(g_cPOSTBuffer[5] - '0') == 0) {
				g_POST_DataStructure.u8UserdataDCMs=0;
			}
			else {
			g_POST_DataStructure.u8UserdataDCMs = (int)(g_cPOSTBuffer[5] - '0') * 10;
			g_POST_DataStructure.u8UserdataDCMs += (int)(g_cPOSTBuffer[6] - '0');
			}
				if((int)(g_POST_DataStructure.u8UserdataDCMs)==10) {
					g_POST_DataStructure.u8UserdataDCMs=100;
				}
		}
		
		else if (strstr(g_cPOSTBuffer, "buzzer=") != NULL)
		{
			g_POST_DataStructure.u8UserdataBuzzer = (int)(g_cPOSTBuffer[7] - '0') * 10;
			g_POST_DataStructure.u8UserdataBuzzer += (int)(g_cPOSTBuffer[8] - '0');
			if((int)(g_POST_DataStructure.u8UserdataBuzzer)==10) {
				g_POST_DataStructure.u8UserdataBuzzer=100;
			}
		}

		else if (strstr(g_cPOSTBuffer, "servomotor=") != NULL)
		{
			if((int)(g_cPOSTBuffer[11] - '0') == 0) {
				g_POST_DataStructure.u8UserdataServomotor=0;
			}
			else {
				g_POST_DataStructure.u8UserdataServomotor = (int)(g_cPOSTBuffer[11] - '0') * 10;
				g_POST_DataStructure.u8UserdataServomotor += (int)(g_cPOSTBuffer[12] - '0');	
			}
			if((int)(g_POST_DataStructure.u8UserdataServomotor)==18) 
			{
				g_POST_DataStructure.u8UserdataServomotor=180;
			}
			
		}

		else if (strcmp(g_cPOSTBuffer, "button=Shift+Register+On") == 0)
		{
			g_POST_DataStructure.bButtonShiftReg = true;
		}
		else if (strcmp(g_cPOSTBuffer, "button=Shift+Register+Off") == 0)
		{
			g_POST_DataStructure.bButtonShiftReg = false;
		}

		else if (strcmp(g_cPOSTBuffer, "button=R+Led+On") == 0)
		{
			g_POST_DataStructure.bButtonRLed = true;
		}
		else if (strcmp(g_cPOSTBuffer, "button=R+Led+Off") == 0)
		{
			g_POST_DataStructure.bButtonRLed = false;
		}
		else if (strcmp(g_cPOSTBuffer, "button=G+Led+On") == 0)
		{
			g_POST_DataStructure.bButtonGLed = true;
		}
		else if (strcmp(g_cPOSTBuffer, "button=G+Led+Off") == 0)
		{
			g_POST_DataStructure.bButtonGLed = false;
		}
		else if (strcmp(g_cPOSTBuffer, "button=B+Led+On") == 0)
		{
			g_POST_DataStructure.bButtonBLed = true;
		}
		else if (strcmp(g_cPOSTBuffer, "button=B+Led+Off") == 0)
		{
			g_POST_DataStructure.bButtonBLed = false;
		}
		else
		{
			ESP_LOGI(TAG, "Not known");
		}

		g_bPOSTRequestInProcess = false;
	}
}

/*******************************************************************************
 *  Function name    : COM_vTaskProcessServer
 *
 *  Description      : Process POST/GET requests
 *
 *  List of arguments: -
 *
 *  Return value     : -
 *
 *******************************************************************************/
void COM_vTaskProcessServer(void)
{
	COM_vProcessGetRequest();
	COM_vProcessPostRequest();
}
