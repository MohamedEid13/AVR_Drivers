

#ifndef MOTORS_INTERFACE_H_
#define MOTORS_INTERFACE_H_

typedef enum{
	M1,
	M2,
	M3,
	M4,
	NUMBER_MOTORS
	}Motor_type;
	
	
	
void Motor_Init(void);
void Motor_CW(Motor_type Motor);
void Motor_CCW(Motor_type Motor);
void Motor_Stop(Motor_type Motor);


#endif /* MOTORS_INTERFACE_H_ */