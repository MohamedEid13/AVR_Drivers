#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "Servo.h"


void SERVO_Init(void)
{
	/*set timer 1 prescaler to 8to get 1us tick time
	use fast mode with top value at OCRA reg to set the freq of servo
	diconnect OC1A PIN ,and generate the PWM on OC1B PIN with nin inverting mode to use OCR1B reg as the ton value*/

	Timer1_Init(TIMER1_FASTPWM_ICR_TOP_MODE,TIMER1_SCALER_8);
	Timer1_OCRA1Mode(OCRA_NON_INVERTING);
	ICR1=19999;
	OCR1A=750;//20000us to get 50hz 
	
}

void SERVO_SetAngle(u16 angle)
{
	OCR1A=angle;
	//OCR1B=(((u32)angle*1000)/180)+999;
}

