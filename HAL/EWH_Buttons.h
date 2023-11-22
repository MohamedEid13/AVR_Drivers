

#ifndef EWH_BUTTONS_H_
#define EWH_BUTTONS_H_



typedef enum
{
	OFF_S,
	ON_S,
	UP_S,
	DOWN_S
}state_type;

typedef enum
{
	ON_OFF_B,
	UP_B,
	DOWN_B,
	No_Button_Pressed
}transitions_type;

typedef enum
{
	SetTemperature_Mode=0,
	Operating_Mode
	
}DeviceMode_t;

void OFF(void);
void ON(void);
void UP(void);
void DOWN(void);
void Button_Init(void);


#endif /* EWH_BUTTONS_H_ */