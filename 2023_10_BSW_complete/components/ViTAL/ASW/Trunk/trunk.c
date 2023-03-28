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

#include "ASW/Trunk/trunk.h"

#include "RTE/rte.h"

static const char *TAG = "ASW TRUNK";

int flagTrunk=0; 
int flagServoTest=0; 
int p0=0, p90=0, p180=0;


void ASW_vTaskServoTest(void)
{
    uint8_t p = RTE_u8Get_UserServo();
	if (!RTE_bGet_ButtonTrunkStatus())
	{
        if(p==90 && p90==0) //if p is equal to 90 (degrees)
        {
            p0=0; p90=1; p180=0;
            flagServoTest=1; //servomotor is taken by ASW_vTaskServoTest
            RTE_vSetServoPosition(SERVO_MOTOR_90_DEG); //set the duty cycle corresponding to 90 deg
        }
        else if(p==180 && p180==0) //if p is equal to 180 (degrees)
        {
            p0=0; p90=0; p180=1;
            flagServoTest=1; //servomotor is taken by ASW_vTaskServoTest
            RTE_vSetServoPosition(SERVO_MOTOR_180_DEG); //set the duty cycle corresponding to 180 deg
        }
        else if(p==0 && p0==0) //if p is equal to 0 (degrees)
        {
            p0=1; p90=0; p180=0;
            flagServoTest=0; //servomotor is released by ASW_vTaskServoTest
            RTE_vSetServoPosition(SERVO_MOTOR_0_DEG); //set the duty cycle corresponding to 0 deg 
	    }
    }
}