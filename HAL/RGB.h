


#ifndef RGB_H_
#define RGB_H_

#include "StdTypes.h"
#include "MemMap.h"

u16 ColorsArray[][3];


/*********************** PIN MAPPING OF THE RGB LED ******************************/
#define  RED_PIN  OCR0
#define	 GREEN_PIN OCR1A
#define	 BLUE_PIN OCR1B

#define LED_TYPE COMMAN_CATHOD
/*********************************************************************************************/
#define  DELAY_TIME 500


typedef enum {
	RED,
	GREEN,
	BLUE,
	BLACK,
	MAGENTA,
	CYAN,
	MAROON,
	OLIVE,
	NAVY,
	YELLOW_GREEN,
	PURPLE,
	TEAL,
	GRAY,
	DARK_GRAY,
	WHITE,
	TOTAL_COLORS
	}ColorName_Types;

/************************************ RGB APIs *************************/
/*
 * Initialization Function
 */
void RGB_Init(void);

void RGB_SetColor(ColorName_Types color);

/*
*	Function iterate through all the colors in the array
*/
void RGB_ToggleColors(void);

#endif /* RGB_H_ */