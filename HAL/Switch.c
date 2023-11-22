#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "Switch.h"


void Switch_Init()
{
	DIO_Init();
}

Button_State Get_Switch(void)
{
	Button_State local_State=UNPRESSED;
	if (DIO_ReadPin(SWITCH_PIN)==LOW)
	{
		local_State = PRESSED;
	}
	else 
	{
		local_State=UNPRESSED;
	}
	return local_State;
}