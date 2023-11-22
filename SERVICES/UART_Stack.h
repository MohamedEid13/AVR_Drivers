

#ifndef UART_STACK_H_
#define UART_STACK_H_

/**************************************************************************/
#define BUTTON_PRESS_INT       EX_INT0
#define INT_TRIGGER_EDGE       FALLING_EDGE
#define BUTTON_PRESS_FUNCTION  BUTTONPRESS_ISR

#define  STACK_SIZE  5
/**************************************************************************/

typedef enum {
	STACK_FULL,
	STACK_EMPTY=0,
	STACK_DONE
	}STACK_Status_Type;


void UART_StackInit(void);
STACK_Status_Type UART_StackPush(u8 data);
STACK_Status_Type UART_StackPop(u8 *pdata);

void UART_RX_ISR(void);
void ButtonPress_ISR(void);

#endif /* UART_STACK_H_ */