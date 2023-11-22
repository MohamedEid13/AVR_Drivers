#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "DIO_Private.h"
#include "DIO_Interface.h"

void DIO_InitPin2(DIO_Port_t port,u8 pin_num,DIO_PinStatus_t status){
	
	switch(status){
		case OUTPUT:
		switch(port){
			case PA:
			SET_BIT(DDRA,pin_num);
			CLEAR_BIT(PORTA,pin_num);
			break;
			case PB:
			SET_BIT(DDRB,pin_num);
			CLEAR_BIT(PORTB,pin_num);
			break;
			case PC:
			SET_BIT(DDRC,pin_num);
			CLEAR_BIT(PORTC,pin_num);
			break;
			case PD:
			SET_BIT(DDRD,pin_num);
			CLEAR_BIT(PORTD,pin_num);
			break;
		}
		break;
		case INFREE:
		switch(port){
			case PA:
			CLEAR_BIT(DDRA,pin_num);
			CLEAR_BIT(PORTA,pin_num);
			break;
			case PB:
			CLEAR_BIT(DDRB,pin_num);
			CLEAR_BIT(PORTB,pin_num);
			break;
			case PC:
			CLEAR_BIT(DDRC,pin_num);
			CLEAR_BIT(PORTC,pin_num);
			break;
			case PD:
			CLEAR_BIT(DDRD,pin_num);
			CLEAR_BIT(PORTD,pin_num);
			break;
		}
		break;
		case INPULL:
		switch(port){
			case PA:
			CLEAR_BIT(DDRA,pin_num);
			SET_BIT(PORTA,pin_num);
			break;
			case PB:
			CLEAR_BIT(DDRB,pin_num);
			SET_BIT(PORTB,pin_num);
			break;
			case PC:
			CLEAR_BIT(DDRC,pin_num);
			SET_BIT(PORTC,pin_num);
			break;
			case PD:
			CLEAR_BIT(DDRD,pin_num);
			SET_BIT(PORTD,pin_num);
			break;
		}
		break;
	}
	
}


void DIO_WritePin2(DIO_Port_t port,u8 pin_num,DIO_PinVoltage_t volt){
	if(volt==HIGH){
		switch(port){
			case PA:
			SET_BIT(PORTA,pin_num);
			break;
			case PB:
			SET_BIT(PORTB,pin_num);
			break;
			case PC:
			SET_BIT(PORTC,pin_num);
			break;
			case PD:
			SET_BIT(PORTD,pin_num);
			break;
		}
		

	}
	else if(volt==LOW){
		switch(port){
			case PA:
			CLEAR_BIT(PORTA,pin_num);
			break;
			case PB:
			CLEAR_BIT(PORTB,pin_num);
			break;
			case PC:
			CLEAR_BIT(PORTC,pin_num);
			break;
			case PD:
			CLEAR_BIT(PORTD,pin_num);
			break;
		}
		
	}
	else{/* Do Nothing */}
}

DIO_PinVoltage_t DIO_ReadPin2(DIO_Port_t port,u8 pin_num){
	DIO_PinVoltage_t volt=LOW;
	switch(port){
		case PA:
		volt=READ_BIT(PINA,pin_num);
		break;
		case PB:
		volt=READ_BIT(PINB,pin_num);
		break;
		case PC:
		volt=READ_BIT(PINC,pin_num);
		break;
		case PD:
		volt=READ_BIT(PIND,pin_num);
		break;
	}
	return volt;
}
/*
Error_t DIO_ReadPin(DIO_Port_t port,u8 pin_num,DIO_PinVoltage_t *pvolt){
	if(pvolt==NULLPTR){
		return NULL_PTR_ERROR;
	}
	else if((port>PD) || (pin_num>7)){
		return OUT_OF_RANGE;
	}
	else{
		switch(port){
			case PA:
			*pvolt=READ_BIT(PINA,pin_num);
			break;
			case PB:
			*pvolt=READ_BIT(PINB,pin_num);
			break;
			case PC:
			*pvolt=READ_BIT(PINC,pin_num);
			break;
			case PD:
			*pvolt=READ_BIT(PIND,pin_num);
			break;
		}
		return OK;
		
	}
}
*/

static void DIO_InitPin(DIO_Pin_types pin,DIO_PinStatus_t status){
	u8 Pin_Num=pin%8;
	
	switch(status){
		case OUTPUT:
		if(pin<=PINA7){
			SET_BIT(DDRA,Pin_Num);
			CLEAR_BIT(PORTA,Pin_Num);
		}
		else if(pin>=PINB0 && pin<=PINB7){
			SET_BIT(DDRB,Pin_Num);
			CLEAR_BIT(PORTB,Pin_Num);
		}
		else if(pin>=PINC0 && pin<=PINC7){
			SET_BIT(DDRC,Pin_Num);
			CLEAR_BIT(PORTC,Pin_Num);
		}
		else if(pin>=PIND0 && pin<=PIND7){
			SET_BIT(DDRD,Pin_Num);
			CLEAR_BIT(PORTD,Pin_Num);
		}
		else {/* Do Nothing */}
		break;
		case INFREE:
		if(pin<=PINA7){
			CLEAR_BIT(DDRA,Pin_Num);
			CLEAR_BIT(PORTA,Pin_Num);
		}
		else if(pin>=PINB0 && pin<=PINB7){
			CLEAR_BIT(DDRB,Pin_Num);
			CLEAR_BIT(PORTB,Pin_Num);
		}
		else if(pin>=PINC0 && pin<=PINC7){
			CLEAR_BIT(DDRC,Pin_Num);
			CLEAR_BIT(PORTC,Pin_Num);
		}
		else if(pin>=PIND0 && pin<=PIND7){
			CLEAR_BIT(DDRD,Pin_Num);
			CLEAR_BIT(PORTD,Pin_Num);
		}
		else{/* DO Nothing */}
		break;
		case INPULL:
		if(pin<=PINA7){
			CLEAR_BIT(DDRA,Pin_Num);
			SET_BIT(PORTA,Pin_Num);
		}
		else if(pin>=PINB0 && pin<=PINB7){
			CLEAR_BIT(DDRB,Pin_Num);
			SET_BIT(PORTB,Pin_Num);
		}
		else if(pin>=PINC0 && pin<=PINC7){
			CLEAR_BIT(DDRC,Pin_Num);
			SET_BIT(PORTC,Pin_Num);
		}
		else if(pin>=PIND0 && pin<=PIND7) {
			CLEAR_BIT(DDRD,Pin_Num);
			SET_BIT(PORTD,Pin_Num);
		}
		else{/* DO Nothing */}
		break;
		case INPUT:
		if(pin<=PINA7){
			CLEAR_BIT(DDRA,Pin_Num);
			
		}
		else if(pin>=PINB0 && pin<=PINB7){
			CLEAR_BIT(DDRB,Pin_Num);
			
		}
		else if(pin>=PINC0 && pin<=PINC7){
			CLEAR_BIT(DDRC,Pin_Num);
			
		}
		else if(pin>=PIND0 && pin<=PIND7){
			CLEAR_BIT(DDRD,Pin_Num);
			
		}
		else{/* DO Nothing */}
		break;
	}
}


void DIO_WritePin(DIO_Pin_types pin,DIO_PinVoltage_t volt){
	u8 Pin_Num=pin%8;
	if(volt==HIGH){
		if(pin<=PINA7){
			SET_BIT(PORTA,Pin_Num);
		}
		else if(pin>=PINB0 && pin<=PINB7){
			SET_BIT(PORTB,Pin_Num);
		}
		else if(pin>=PINC0 && pin<=PINC7){
			SET_BIT(PORTC,Pin_Num);
		}
		else if(pin>=PIND0 && pin<=PIND7){
			SET_BIT(PORTD,Pin_Num);
		}
		else{/* Do Nothing */}
		
	}
	else if(volt==LOW){
		if(pin<=PINA7){
			CLEAR_BIT(PORTA,Pin_Num);
		}
		else if(pin>=PINB0 && pin<=PINB7){
			CLEAR_BIT(PORTB,Pin_Num);
		}
		else if(pin>=PINC0 && pin<=PINC7){
			CLEAR_BIT(PORTC,Pin_Num);
		}
		else if(pin>=PIND0 && pin<=PIND7){
			CLEAR_BIT(PORTD,Pin_Num);
		}
		else{/* Do Nothing */}
		
	}
	else{/* Do Nothing */}
}

DIO_PinVoltage_t DIO_ReadPin(DIO_Pin_types pin){
	u8 Pin_Num=pin%8;
	DIO_PinVoltage_t volt=LOW;
	if(pin<=PINA7){
		volt=READ_BIT(PINA,Pin_Num);

	}
	else if(pin>=PINB0 && pin<=PINB7){
		volt=READ_BIT(PINB,Pin_Num);
	}
	else if(pin>=PINC0 && pin<=PINC7){
		volt=READ_BIT(PINC,Pin_Num);
	}
	else if(pin>=PIND0 && pin<=PIND7){
		volt=READ_BIT(PIND,Pin_Num);
	}
	else {/* Do Nothing */}
	
	return volt;
}

void DIO_WritePort(DIO_Port_t port, u8 value)
{
	switch (port) {
		case PA:
		PORTA = value;
		break;
		case PB:
		PORTB = value;
		break;
		case PC:
		PORTC = value;
		break;
		case PD:
		PORTD = value;
		break;
		default:
		// Do Nothing
		break;
	}
}

u8 DIO_ReadPort(DIO_Port_t port){
	u8 value=0;
	if(port==PA){
		value=PINA;
	}
	else if(port==PB){
		value=PINB;
	}
	else if(port==PC){
		value=PINC;
	}
	else if(port==PD){
		value=PIND;
	}
	else{
		/*Do Nothing*/
	}
	return value;
}

void DIO_TogglePin(DIO_Pin_types pin){
	u8 Pin_Num=pin%8;
	if(pin<=PINA7){
		TOGGLE_BIT(PORTA,Pin_Num);
			}
	else if(pin>=PINB0 && pin<=PINB7){
		TOGGLE_BIT(PORTB,Pin_Num);
		}
	else if(pin>=PINC0 && pin<=PINC7){
		TOGGLE_BIT(PORTC,Pin_Num);
			}
	else if(pin>=PIND0 && pin<=PIND7){
		TOGGLE_BIT(PORTD,Pin_Num);
			}
	else{/* Do Nothing */}
	
}

void DIO_Init(void){
	DIO_Pin_types i;
	for(i=PINA0;i<TOTAL_PINS;i++){
	DIO_InitPin(i,PinsStatusArray[i]);
	}
}


	
	
	
	
