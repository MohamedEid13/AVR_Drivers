

#ifndef STEPPER_INTERFACE_H_
#define STEPPER_INTERFACE_H_

void Stepper_Init(void);
void Stepper_Bipolar_CW(void);
void Stepper_Bipolar_CCW(void);

void Stepper_Unipolar_CW(void);
void Stepper_Unipolar_CCW(void);

void Stepper_Unipolar_CW_HS(void);
void Stepper_Unipolar_CCW_HS(void);

#endif /* STEPPER_INTERFACE_H_ */