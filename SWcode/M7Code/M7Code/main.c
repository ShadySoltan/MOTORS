/*
 * M7Code.c
 *
 * Created: 5/12/2024 3:17:49 AM
 * Author : shady
 */ 

#include "Clock.h"
#include "BitMath.h"
#include "Design_Namings.h"
#include "Func_Dec.h"

int main(){
	MCU_INIT();
	MOTOR_START_BUTTON(MOTOR_DIR_RIGHT);
	while(1){ACTION();}
}