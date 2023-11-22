


#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

typedef enum
{
	ULTRASONIC_1=PINB1,
	NO_Of_Ultrasoincs=1
}ULTRASONIC_type;

void ULTRASONIC_Init(void);

u16 ULTRASONIC_GetDistance(ULTRASONIC_type Ultrasonic);


#endif /* ULTRASONIC_H_ */