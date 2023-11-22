#define  MOTOR_PROG 1
#include "StdTypes.h"
#include "DIO_Interface.h"
#include "Motors_Interface.h"
#include "Motor_Cfg.h"
#include "Motor_Private.h"

void Motor_Init(void)
{
	
}

void Motor_CW(Motor_type Motor)
{
	switch(Motor){
		case M1:
		DIO_WritePin(MotorPinsArray[Motor][IN1],HIGH);
		DIO_WritePin(MotorPinsArray[Motor][IN2],LOW);
		break;
		case M2:
		DIO_WritePin(MotorPinsArray[Motor][IN1],HIGH);
		DIO_WritePin(MotorPinsArray[Motor][IN2],LOW);
		break;
		case M3:
		DIO_WritePin(MotorPinsArray[Motor][IN1],HIGH);
		DIO_WritePin(MotorPinsArray[Motor][IN2],LOW);
		break;
		case M4:
		DIO_WritePin(MotorPinsArray[Motor][IN1],HIGH);
		DIO_WritePin(MotorPinsArray[Motor][IN2],LOW);
		break;
		
	}
}

void Motor_CCW(Motor_type Motor)
{
	switch(Motor){
		case M1:
		DIO_WritePin(MotorPinsArray[Motor][IN1],LOW);
		DIO_WritePin(MotorPinsArray[Motor][IN2],HIGH);
		break;
		case M2:
		DIO_WritePin(MotorPinsArray[Motor][IN1],LOW);
		DIO_WritePin(MotorPinsArray[Motor][IN2],HIGH);
		break;
		case M3:
		DIO_WritePin(MotorPinsArray[Motor][IN1],LOW);
		DIO_WritePin(MotorPinsArray[Motor][IN2],HIGH);
		break;
		case M4:
		DIO_WritePin(MotorPinsArray[Motor][IN1],LOW);
		DIO_WritePin(MotorPinsArray[Motor][IN2],HIGH);
		break;
		
	}
	
}

void Motor_Stop(Motor_type Motor)
{
	
	DIO_WritePin(MotorPinsArray[Motor][IN1],LOW);
	DIO_WritePin(MotorPinsArray[Motor][IN2],LOW);
}