#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "_7_Segment_Interface.h"

void MLX_segment_display(unsigned char n){
	unsigned char d0,d1,SegmetArr[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
	static char x=0;
	d0=n%10;
	d1=n/10;
	SEGMENT_PORT=SegmetArr[d0]<<1;
	SET_BIT(PORTC,6);
	CLEAR_BIT(PORTC,7);
	_delay_ms(500);
	SEGMENT_PORT=SegmetArr[d1]<<1;
	SET_BIT(PORTC,7);
	CLEAR_BIT(PORTC,6);
	LEDS_PORT=x;
	x++;
	_delay_ms(500);
	
}

void segment_dis_LookUpTable(u8 n)
{
	u8 arr[] = {
		0b00111111, // 0
		0b00000110, // 1
		0b01011011, // 2
		0b01001111, // 3
		0b01100110, // 4
		0b01101101, // 5
		0b01111101, // 6
		0b00000111, // 7
		0b01111111, // 8
		0b01101111  // 9
	};
	
	DIO_WritePin(PINC7,HIGH);
	DIO_WritePin(PINC6,HIGH);
	SEGMENT_PORT=arr[n]<<1;
	//PORTB=n;
}

void Traffic_lights(u8 Traffic_Counter)
{
	char original_value=Traffic_Counter;
	SET_BIT(TRAFFIC_PORT,RED_LED);
	while(Traffic_Counter!=0)
	{
		MLX_segment_display(Traffic_Counter);
		Traffic_Counter--;
		_delay_ms(200);
	}
	
	CLEAR_BIT(TRAFFIC_PORT,RED_LED);
	SET_BIT(TRAFFIC_PORT,BLUE_LED);
	Traffic_Counter=5;
	
	while(Traffic_Counter!=0)
	{
		MLX_segment_display(Traffic_Counter);
		Traffic_Counter--;
		_delay_ms(200);
	}
	
	CLEAR_BIT(TRAFFIC_PORT,BLUE_LED);
	SET_BIT(TRAFFIC_PORT,GREEN_LED);
	Traffic_Counter=original_value;
	
	while(Traffic_Counter!=0)
	{
		MLX_segment_display(Traffic_Counter);
		Traffic_Counter--;
		_delay_ms(200);
	}
	CLEAR_BIT(TRAFFIC_PORT,GREEN_LED);
}
