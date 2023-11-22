#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "Timers.h"
#include "UltraSonic.h"


/*
 * t1 , t2 are used to store the time stamps for the start and end of the ultrasonic pulse.
 * The flag variable is used to keep track of the current state of the pulse.
*/
static volatile u16 t1,t2;
static volatile u8 flag=0;


/*
 * This function initializes the ultrasonic sensor.
 * It initialize the timer1 
 * It sets the timer1 input capture interrupt and enables the interrupt.
 */

static void calculate_UltrasonicTiming_ICU(void)
{
	// If the flag is 0, then this is the first edge of the pulse.
	if (flag==0)
	{
		t1=ICR1;  // Capture time of first edge
		Timer1_InputCaptureEdge(FALLING);
		//DIO_WritePin(PINC1,HIGH); // Trigger the ultrasonic sensor by setting a pin high
		flag=1;
	}
	// If the flag is 1, then this is the second edge of the pulse.
	else if(flag==1)
	{
		//DIO_WritePin(PINC0,LOW); // Stop triggering the sensor by setting the pin low
		t2=ICR1;  // Capture time of second edge
		flag=2;
	}
}

void ULTRASONIC_Init(void)
{
	Timer1_Init(TIMER1_NORMAL_MODE,TIMER1_SCALER_8);
	Timer1_ICU_SetCallBack(calculate_UltrasonicTiming_ICU);
	Timer1_ICU_InterruptEnable();
}


/*
 * This function gets the distance to an object from the ultrasonic sensor.
 * It sends a pulse to the sensor and measures the time it takes for the echo to return.
 */

u16 ULTRASONIC_GetDistance(ULTRASONIC_type Ultrasonic)
{
	u16 time,distance;
	
	TCNT1=0;
	flag=0;
	Timer1_InputCaptureEdge(RISING);
	
	// Trigger the ultrasonic sensor by setting a pin high and low
	DIO_WritePin(Ultrasonic,HIGH);
	_delay_us(10);
	DIO_WritePin(Ultrasonic,LOW);
	
	// Wait until both t1 and t2 are captured in ISR
	while(flag<2);
	
	time=t2-t1;   // Calculate time difference
	distance=time/58;    // this equation in data sheet
	return distance;  // Return the calculated distance
}

