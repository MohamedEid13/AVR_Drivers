


#ifndef ADC_PRIVATE_MODIFED_H_
#define ADC_PRIVATE_MODIFED_H_



/****** ADC Saved DATA Registers */
#define ADCLOW (*(volatile unsigned char * )0x24)
#define ADCHIGH (*(volatile unsigned char * )0x25)
#define ADCDATA (*(volatile unsigned short * )0x24)

/*************************************/
typedef struct
{
	u8 MUX:5;
	u8 ADLAR:1;
	u8 REFS:2;
}ADMUX;

#define  ADMUX_REG ((volatile ADMUX*)0X27)
/****************************************/

typedef struct
{
	u8 ADPS:3;
	u8 ADIE:1;
	u8 ADIF:1;
	u8 ADATE:1;
	u8 ADSC:1;
	u8 ADEN:1;
}ADCSRA;

#define  ADCSRA_REG ((volatile ADCSRA*)0x26)


/******************************************/
typedef struct 
{
	u8          : 5;
	u8 ADTS : 3;
} SFIOR;

#define SFIOR_reg		((volatile SFIOR *) 0x50)

#endif /* ADC_PRIVATE_MODIFED_H_ */