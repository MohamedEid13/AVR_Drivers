#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "ADC_Interface.h"
#include "EX_Interrupt.h"
#include "EWH_Buttons.h"


void Button_Init(void)
{
	DIO_Init();
	ADC_Init(VREF_VCC,ADC_SCALER_64);
	EXI_Init();
	
	EXI_Enable(EX_INT0);
	EXI_Enable(EX_INT1);
	EXI_Enable(EX_INT2);
	
}
void OFF(void)
{
	DIO_WritePin(PINC2,LOW);
	DIO_WritePin(PINC1,LOW);
	DIO_WritePin(PINC0,LOW);
	
}

void ON(void)
{
	DIO_WritePin(PINC2,HIGH);
}

void UP(void)
{
	DIO_WritePin(PINC0,HIGH);
	DIO_WritePin(PINC1,LOW);
}

void DOWN(void)
{
	DIO_WritePin(PINC0,LOW);
	DIO_WritePin(PINC1,HIGH);
	
}
