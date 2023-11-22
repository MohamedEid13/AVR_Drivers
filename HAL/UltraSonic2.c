#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "Timers.h"
#include "UltraSonic2.h"

static volatile u8 ultrasonic_flag = 0;
static volatile u32 ultrasonic_duration = 0;

static void Ultrasonic_F(void);


void Ultrasonic_Init(void)
{
	// Set TRIG pin as output and ECHO pin as input
	DIO_InitPin2(PB,0, OUTPUT);
	DIO_InitPin2(PB,1, INPULL);

	// Initialize Timer1 for capturing the echo pulse duration
	Timer1_Init(TIMER1_NORMAL_MODE, TIMER1_SCALER_8);
	Timer1_ICU_SetCallBack(Ultrasonic_F);
	Timer1_InputCaptureEdge(RISING);
	Timer1_ICU_InterruptEnable();
}

u8 Ultrasonic_GetDistance(UltrasonicData *data)
{
	// Send ultrasonic pulse
	DIO_WritePin(ULTRASONIC_TRIG_PIN, HIGH);
	_delay_us(10);
	DIO_WritePin(ULTRASONIC_TRIG_PIN, LOW);

	// Wait for the echo pulse to be captured
	while (ultrasonic_flag == 0);

	// Calculate distance in cm and inches
	data->distance_cm = (ultrasonic_duration * 0.017);    // Speed of sound = 343 meters/second = 0.0343 cm/microsecond
	data->distance_inches = (ultrasonic_duration * 0.00067);    // Speed of sound = 13503 inches/second = 0.00067 inches/microsecond

	// Reset the flag and duration for the next measurement
	ultrasonic_flag = 0;
	ultrasonic_duration = 0;

	return 1; // Measurement successful
}

void Ultrasonic_F(void)
{
	static u32 start_time = 0;

	if (ultrasonic_flag == 0)
	{
		// Rising edge detected, start the timer
		start_time = ICR1;
		Timer1_InputCaptureEdge(FALLING);
		ultrasonic_flag = 1;
	}
	else
	{
		// Falling edge detected, stop the timer and calculate the duration
		ultrasonic_duration = ICR1 - start_time;
		Timer1_InputCaptureEdge(RISING);
		ultrasonic_flag = 0;
	}
}
