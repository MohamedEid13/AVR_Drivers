

#ifndef LCD_CFG_H_
#define LCD_CFG_H_

#define EN  PINA2
#define RS	PINA1

#define _4_BIT   0
#define _8_BIT   1

/* _4_BIT OR _8_BIT*/
#define  LCD_MODE  _4_BIT

#define  D7   PINA6
#define  D6   PINA5
#define  D5   PINA4
#define  D4   PINA3

#define LCD_PORT PA

/* 8 bit initialization */

#define SETFUNCTION 0X38  // SET 5*7 & 2 line LCD
#define DISPLAY_ON_OFF_CONTROL 0x0c //0x0e , 0x0f
#define DISPLAY_CLEAR 0X01 //Clear LCD
#define ENTRY_MODE_SET 0x06 // Increment DDRAM ,No Shift
#endif /* LCD_CFG_H_ */