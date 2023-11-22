#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "Timers.h"
#include "RGB.h"


void RGB_Init(void)
{
	// initialize Timer 0
	TIMER0_Init(TIMER0_FASTPWM_MODE,TIMER0_SCALER_8);
	TIMER0_OC0Mode(OC0_NON_INVERTING);
	
	// initialize Timer 1
	Timer1_Init(TIMER1_FASTPWM_ICR_TOP_MODE,TIMER1_SCALER_8);
	Timer1_OCRA1Mode(OCRA_NON_INVERTING);
	Timer1_OCRB1Mode(OCRA_NON_INVERTING);
	
	//set TOP Value in ICR Register
	ICR1=255;

}

void RGB_SetColor(ColorName_Types color)
{
	if(color<TOTAL_COLORS)
	{
		RED_PIN=ColorsArray[color][0];
		GREEN_PIN=ColorsArray[color][1];
		BLUE_PIN=ColorsArray[color][2];
	}
}

void RGB_ToggleColors(void)
{
	for (int i = 0; i < TOTAL_COLORS; i++)
	{
		RED_PIN   = ColorsArray[i][0];
		GREEN_PIN = ColorsArray[i][1];
		BLUE_PIN  = ColorsArray[i][2];
		
		_delay_ms(DELAY_TIME);
	}
}