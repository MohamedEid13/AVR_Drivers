#include "StdTypes.h"
#include "Motors_Interface.h"
#include "Motor_Private.h"
#ifndef MOTOR_CFG_H_
#define MOTOR_CFG_H_
/*
typedef struct{
	DIO_Pin_types IN1;
	DIO_Pin_types IN2;
	DIO_Pin_types EN;
}MOTOR_Pins_type;

*/

/********* H-Bridge pin Configuration *****************/

#define   M1_IN1   PIND0
#define   M1_IN2   PIND1
#define   M1_EN    PIND2

#define   M2_IN1   PIND6
#define   M2_IN2   PIND7
#define   M2_EN	   PIND4

#define   M3_IN1   PINA0
#define   M3_IN2   PINA5
#define   M3_EN    PINB0

#define   M4_IN1   PINC4
#define   M4_IN2   PINC7
#define   M4_EN    PINC1

#ifdef  MOTOR_PROG

DIO_Pin_types MotorPinsArray[NUMBER_MOTORS][MOTOR_PIN_NUMBERS]={
				/* IN1   IN2     EN  */
	/* motor 1*/{ M1_IN1,M1_IN2,M1_EN},
	/* motor 2*/{ M2_IN1,M2_IN2,M2_EN},
	/* motor 3*/{ M1_IN1,M1_IN2,M1_EN},
	/* motor 4*/{ M1_IN1,M1_IN2,M1_EN},
};


/* Using struct to replace motorpinsarray */


// MOTOR_Pins_type MotorPinsArray2[NUMBER_MOTORS]={
// 				/* IN1   IN2     EN  */
// 	/* motor 1*/{ M1_IN1,M1_IN2,M1_EN},
// 	/* motor 2*/{ M2_IN1,M2_IN2,M2_EN},
// 	/* motor 3*/{ M1_IN1,M1_IN2,M1_EN},
// 	/* motor 4*/{ M1_IN1,M1_IN2,M1_EN},
// 	
// };


#endif





#endif /* MOTOR_CFG_H_ */