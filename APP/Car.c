
#include "StdTypes.h"
#include "DIO_Interface.h"
#include "Motors_Interface.h"
#include "Car.h"
#define B_F   PIND0
#define B_B   PIND1
#define B_R   PIND2
#define B_L   PIND3


void CAR_Init(void)
{
	/* DO Nothing*/
	
}


void CAR_Runnable(void)
{
	if (DIO_ReadPin(B_F)==LOW)
	{
		MoveForward();
	}
}

static void MoveForward(void)
{
	Motor_CW(M1);
	Motor_CW(M2);
	Motor_CW(M3);
	Motor_CW(M4);
}

static void MoveBackward(void)
{
	Motor_CCW(M1);
	Motor_CCW(M2);
	Motor_CCW(M3);
	Motor_CCW(M4);
}

static void MoveRight(void)
{
	Motor_CW(M1);
	Motor_CW(M3);
	Motor_CCW(M2);
	Motor_CCW(M4);
}

static void MoveLeft(void)
{
	Motor_CCW(M1);
	Motor_CCW(M3);
	Motor_CW(M2);
	Motor_CW(M4);
}

