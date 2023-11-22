
#ifndef ULTRASONIC2_H_
#define ULTRASONIC2_H_



#define ULTRASONIC_TRIG_PIN     PINB0   // Replace X with the actual trigger pin
#define ULTRASONIC_ECHO_PIN     PINB1   // Replace Y with the actual echo pin

typedef struct {
	u32 distance_cm;
	u32 distance_inches;
} UltrasonicData;

void Ultrasonic_Init(void);

u8 Ultrasonic_GetDistance(UltrasonicData *data);


#endif /* ULTRASONIC2_H_ */