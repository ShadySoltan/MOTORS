/*
 * Design_Namings.h
 *
 * Created: 5/13/2024 12:19:58 AM
 *  Author: shady
 */ 

#ifndef DESIGN_NAMINGS_H_
#define DESIGN_NAMINGS_H_

#include <avr/io.h>

//Buttons
#define BUTTONS_PORT_REG							PORTB
#define BUTTONS_PIN_REG								PINB
#define BUTTONS_DDR_REG								DDRB
#define ENGINE_ON_BUTTON_PIN						PB0
#define ENGINE_INCREASE_SPEED_PIN					PB1
#define ENGINE_DECREASE_SPEED_PIN					PB2
#define ENGINE_OFF_BUTTON_PIN						PB3
#define TURBO_ON_OFF_BUTTON_PIN						PB7

//LEDS
#define LEDS_PORT_REG								PORTC
#define LEDS_DDR_REG								DDRC
#define GREEN_LED_PIN								PC0
#define RED_LED_PIN									PC1
#define YELLOW_LED_PIN								PC2
#define AQUA_LED_PIN								PC3

//MOTOR
#define MOTOR_PORT_REG								PORTD
#define MOTOR_DDR_REG								DDRD
#define MOTOR_DIR_RIGHT_PIN							PD0
#define MOTOR_DIR_LEFT_PIN							PD1
#define MOTOR_EN_PIN								PD5

//TURBO
#define TURBO_PORT_REG								PORTD
#define TURBO_DDR_REG								DDRD
#define TURBO_DIR_RIGHT_PIN							PD2
#define TURBO_DIR_LEFT_PIN							PD3
#define TURBO_EN_PIN								PD4

//AirDynamic
#define AIR_DYNAMIC_PORT_REG						PORTA
#define AIR_DYNAMIC_DDR_REG							DDRA
#define AIR1_DIR_RIGHT_PIN							PA0
#define AIR1_DIR_LEFT_PIN							PA1
#define AIR1_EN_PIN									PA2
#define AIR2_DIR_RIGHT_PIN							PA3
#define AIR2_DIR_LEFT_PIN							PA4
#define AIR2_EN_PIN									PA5
	
//Directions 
typedef enum{
	MOTOR_DIR_RIGHT = 0,
	MOTOR_DIR_LEFT
}MOTOR_DIR_Types;

#endif /* DESIGN_NAMINGS_H_ */