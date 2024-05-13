/*
 * Func_Dec.h
 *
 * Created: 5/13/2024 12:22:13 AM
 *  Author: shady
 */ 


#ifndef FUNC_DEC_H_
#define FUNC_DEC_H_

#include "BitMath.h"
#include "Design_Namings.h"

void MCU_INIT(void);
void MOTOR_START_BUTTON(MOTOR_DIR_Types direction);
void MOTOR_TURN_OFF(void);
void MOTOR_START(MOTOR_DIR_Types direction);
void TURBO_BUTTON(void);
void ACTION(void);
void AIR_DYN_ON_OFF(void);

#endif /* FUNC_DEC_H_ */