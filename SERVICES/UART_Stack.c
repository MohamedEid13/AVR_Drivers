#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "EX_Interrupt.h"
#include "UART.h"
#include "UART_Service.h"
#include "UART_Stack.h"
#include "LCD_Interface.h"


u8 stack[STACK_SIZE];
static volatile u8 StackPointer=0;
void UART_StackInit(void)
{
	// Set the callback function to fill the stack during UART RX interrupt
	UART_RX_SetCallBack(UART_RX_ISR);
	// Enable UART RX interrupt
	UART_RX_InterruptEnable();
	// Set the trigger edge of external interrupt for button press
	EXI_TriggerEdge(BUTTON_PRESS_INT,INT_TRIGGER_EDGE);
	// Set the callback function for the external interrupt to handle button press
	EXI_SetCallBack(BUTTON_PRESS_INT,ButtonPress_ISR);
	// Enable the external interrupt for button press
	EXI_Enable(BUTTON_PRESS_INT);
}

/****************************ISR Function ****************************************/

void UART_RX_ISR(void)
{
	u8 data=UART_ReceiveNoBlock();
	u8 stackstatue=UART_StackPush(data);
	if(stackstatue==STACK_FULL)
	{
		// Print a message indicating that the stack is full
		UART_SendString("Stack Full");
		/* We read a byte from UART to reset the RX interrupt flag, but we do not save this data because the stack is full. */
		UART_ReceiveNoBlock();
	}
}

STACK_Status_Type UART_StackPush(u8 data)
{
	if (StackPointer==(STACK_SIZE-1))
	{
		return STACK_FULL;
	}
	else 
	{
		/* Fill the stack with the new data received from UART*/
		stack[StackPointer]=data;
		/* increment the pointer to the next available location */
		StackPointer++;
		return STACK_DONE;
	}
}


STACK_Status_Type UART_StackPop(u8 *pdata)
{
	if(StackPointer==0)
	{
		return STACK_EMPTY;
	}
	else{
		StackPointer--;
		*pdata=stack[StackPointer];
		return STACK_DONE;
	}
}

/************************************** ButtonPress Function ******************************************/

 /*
 This code is a interrupt handler which is called when a button is pressed. 
 1 - It is used to control a LCD display.
 2 - When the interrupt is called, data is popped from the UART stack.
 3 - If the stack is empty then the LCD display is updated to show the message "Stack Empty".
 4 - If the stack is not empty, the data is written to the LCD at the position set by LCD_Curser, 
     and then LCD_Curser is incremented. 
 5 - If the LCD had previously been empty, then it is cleared first.
 */
 
u8 data=0;            //  variable to hold received data
u8 stackState=0;      //  variable to hold the state of the UART stack
u8 LCD_Curser=0;      //  variable to hold the current position of the LCD cursor
u8 isLCDEmpty=0;      //  variable to check if the LCD is empty

void ButtonPress_ISR(void)
{
	stackState=UART_StackPop(&data);  // pop the data from the UART stack and get the state of the stack
	if (stackState==STACK_EMPTY)
	{
		LCD_SetCursor(0,1);
		LCD_WriteString("Stack Empty");
		isLCDEmpty=1;
	}
	else if (stackState==STACK_EMPTY)
	{
		if (isLCDEmpty == 1) // if the LCD is empty
		{
			LCD_Clear(); // clear the LCD
			isLCDEmpty = 0; // set the LCD empty flag to 0
			LCD_Curser = 0; // reset the LCD cursor position
		}
		LCD_SetCursor(1,LCD_Curser); // write the received data to the LCD
		LCD_WriteChar(data);
		LCD_Curser++; // move the LCD cursor to the next position
	}
}
