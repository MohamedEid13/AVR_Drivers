#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "UART.h"
	

static void(*UART_RX_Fptr)(void)=NULLPTR;
static void(*UART_TX_Fptr)(void)=NULLPTR;


void UART_Init(void)
{
	/* Set baud rate 9600 */
	UBRRL=51;
	/* Normal Speed */
	CLEAR_BIT(UCSRA,U2X);
	/* Frame no parity 1 stop bit  8 data */
	
	/* Enable */
	SET_BIT(UCSRB,TXEN);
	SET_BIT(UCSRB,RXEN);
}


void UART_Send(u8 data)
{
	while(!READ_BIT(UCSRA,UDRE));
	UDR=data;
}

u8 UART_Receive(void)
{
	while(!READ_BIT(UCSRA,RXC));
	return UDR;
}

u8 UART_ReceivePerodic(u8 *pdata)
{
	if(READ_BIT(UCSRA,RXC))
	{
		*pdata=UDR;
		return 1;
	}
	return 0;
}

void UART_RX_InterruptEnable(void)
{
	SET_BIT(UCSRB,RXCIE);
}

void UART_RX_InterruptDisable(void)
{
	CLEAR_BIT(UCSRB,RXCIE);
}

void UART_TX_InterruptEnable(void)
{
	SET_BIT(UCSRB,TXCIE);
}

void UART_TX_InterruptDisable(void)
{
	CLEAR_BIT(UCSRB,TXCIE);
}

void UART_RX_SetCallBack(void (*LocalFptr)(void))
{
	UART_RX_Fptr = LocalFptr;
}

void UART_TX_SetCallBack(void (*LocalFptr)(void))
{
	UART_TX_Fptr = LocalFptr;
}


ISR(UART_RX_vect)
{
	if (UART_RX_Fptr!=NULLPTR)
	{
		UART_RX_Fptr();
	}
}

ISR(UART_TX_vect)
{
	if (UART_TX_Fptr!=NULLPTR)
	{
		UART_TX_Fptr();
	}
}

void UART_SendNoBlock(u8 data)
{
	UDR=data;
}
u8 UART_ReceiveNoBlock(void)
{
	return UDR;
}


// Asynchronos Function
static void TX_Func(void);
static u8 *TXstr;

void UART_SendStringAsynch(u8 *str)
{
	UART_SendNoBlock(str[0]);
	UART_TX_InterruptEnable();
	UART_TX_SetCallBack(TX_Func);
	TXstr=str;
}

void TX_Func(void)
{
	static u8 i=1;
	if (TXstr!=0)
	{
		UART_SendNoBlock(TXstr[i]);
		i++;
	}
	else{i=1;}
}

