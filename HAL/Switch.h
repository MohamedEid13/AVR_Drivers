


#ifndef SWITCH_H_
#define SWITCH_H_

#define SWITCH_PIN  PIND2
typedef enum
{
	PRESSED,
	UNPRESSED
}Button_State;

void Switch_Init();

Button_State Get_Switch(void);






#endif /* SWITCH_H_ */