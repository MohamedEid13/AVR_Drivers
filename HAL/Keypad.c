#include "StdTypes.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "Kaypad_Cfg.h"
#include "Kaypad_Interface.h"


void KEYPAD_Init(void)
{
	DIO_WritePin(FIRST_OUTPUT,HIGH);
	DIO_WritePin(FIRST_OUTPUT+1,HIGH);
	DIO_WritePin(FIRST_OUTPUT+2,HIGH);
	DIO_WritePin(FIRST_OUTPUT+3,HIGH);
	
	DIO_InitPin2(PD,FIRST_INPUT,INPULL);
	DIO_InitPin2(PD,FIRST_INPUT+1,INPULL);
	DIO_InitPin2(PD,FIRST_INPUT+2,INPULL);
	DIO_InitPin2(PD,FIRST_INPUT+3,INPULL);
	
}

u8 KEYPAD_GetKey(void)
{
	u8 r,c,key=NO_KEY;
	for(r=0;r<ROWS;r++)
	{
		DIO_WritePin(FIRST_OUTPUT+r,LOW);
		for(c=0;c<COLS;c++)
		{
			if(DIO_ReadPin(FIRST_INPUT+c)==LOW)
			{
				key=KeysArray[r][c];
				while(DIO_ReadPin(FIRST_INPUT+c)==LOW);
				
			}
		}
		DIO_WritePin(FIRST_OUTPUT+r,HIGH);
	}
	return key;
}