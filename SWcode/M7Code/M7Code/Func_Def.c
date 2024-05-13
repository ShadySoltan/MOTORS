/*
* Func_Def.c
*
* Created: 5/13/2024 12:22:24 AM
*  Author: shady
*/
#include "Func_Dec.h"

volatile int MOTOR_STATUS = 0;

void MCU_INIT(void)
{
	//Initialize the MCU PINs Directions
	//Init the buttons to input
	ClearBit(BUTTONS_DDR_REG,ENGINE_ON_BUTTON_PIN);
	ClearBit(BUTTONS_DDR_REG,ENGINE_INCREASE_SPEED_PIN);
	ClearBit(BUTTONS_DDR_REG,ENGINE_DECREASE_SPEED_PIN);
	ClearBit(BUTTONS_DDR_REG,ENGINE_OFF_BUTTON_PIN);
	ClearBit(BUTTONS_DDR_REG,TURBO_ON_OFF_BUTTON_PIN);
	
	//Init LEDs Directions
	SetBit(LEDS_DDR_REG,GREEN_LED_PIN);
	SetBit(LEDS_DDR_REG,RED_LED_PIN);
	SetBit(LEDS_DDR_REG,YELLOW_LED_PIN);
	SetBit(LEDS_DDR_REG,AQUA_LED_PIN);
	
	//Init MOTOR Directions
	SetBit(MOTOR_DDR_REG,MOTOR_DIR_RIGHT_PIN);
	SetBit(MOTOR_DDR_REG,MOTOR_DIR_LEFT_PIN);
	SetBit(MOTOR_DDR_REG,MOTOR_EN_PIN);
	
	//Init TURBO Directions
	SetBit(TURBO_DDR_REG,TURBO_DIR_RIGHT_PIN);
	SetBit(TURBO_DDR_REG,TURBO_DIR_LEFT_PIN);
	SetBit(TURBO_DDR_REG,TURBO_EN_PIN);
	
	//At Rest Red Led Is Lit
	SetBit(LEDS_PORT_REG,RED_LED_PIN);
	
	//AirDynamics Directions
	SetBit(AIR_DYNAMIC_DDR_REG,AIR1_DIR_RIGHT_PIN);
	SetBit(AIR_DYNAMIC_DDR_REG,AIR1_DIR_LEFT_PIN);
	SetBit(AIR_DYNAMIC_DDR_REG,AIR1_EN_PIN);

	SetBit(AIR_DYNAMIC_DDR_REG,AIR2_DIR_RIGHT_PIN);
	SetBit(AIR_DYNAMIC_DDR_REG,AIR2_DIR_LEFT_PIN);
	SetBit(AIR_DYNAMIC_DDR_REG,AIR2_EN_PIN);
}

void MOTOR_START_BUTTON(MOTOR_DIR_Types direction)
{
	while(MOTOR_STATUS == 0)
	{
		if(GetBit(BUTTONS_PIN_REG,ENGINE_ON_BUTTON_PIN) == 1)
		{
			while(GetBit(BUTTONS_PIN_REG,ENGINE_ON_BUTTON_PIN) == 1);
			MOTOR_STATUS = 1;
			MOTOR_START(direction);
		}
	}
}

void MOTOR_START(MOTOR_DIR_Types direction)
{
	//Set The Direction of the Motor to ready state and turn on yellow led as indicator for ready!
	if(direction == MOTOR_DIR_RIGHT)
	{
		SetBit(MOTOR_PORT_REG,MOTOR_DIR_RIGHT_PIN);
		ClearBit(MOTOR_PORT_REG,MOTOR_DIR_LEFT_PIN);
	}
	else if(direction == MOTOR_DIR_LEFT)
	{
		ClearBit(MOTOR_PORT_REG,MOTOR_DIR_RIGHT_PIN);
		SetBit(MOTOR_PORT_REG,MOTOR_DIR_LEFT_PIN);
	}
	else
	{
		//Do Nothing
	}
	
	//Initialize the PWM and make the motor be at rest "Not rotating"
	SetBit(TCCR1A,7);
	ClearBit(TCCR1A,6); //Clear on Compare-match Reset at OCR1A Non Inverting Mode
	
	ClearBit(TCCR1A,1);
	SetBit(TCCR1A,0);
	SetBit(TCCR1B,3);
	ClearBit(TCCR1B,4); //Choosing 8bit FAST PWM mode
	
	SetBit(TCCR1B,0);
	SetBit(TCCR1B,1);
	ClearBit(TCCR1B,2); //Prescale 64
	
	OCR1A = 0;
	
	//MOTOR is Ready!
	SetBit(LEDS_PORT_REG,YELLOW_LED_PIN);
	ClearBit(LEDS_PORT_REG,RED_LED_PIN);
}

void MOTOR_TURN_OFF(void)
{
	ClearBit(TCCR1A,7);
	ClearBit(MOTOR_PORT_REG,MOTOR_DIR_LEFT_PIN);
	ClearBit(MOTOR_PORT_REG,MOTOR_DIR_RIGHT_PIN);
	ClearBit(TURBO_PORT_REG,TURBO_DIR_RIGHT_PIN);
	ClearBit(TURBO_PORT_REG,TURBO_DIR_LEFT_PIN);
	ClearBit(TURBO_PORT_REG,TURBO_EN_PIN);
	SetBit(LEDS_PORT_REG,RED_LED_PIN);
	ClearBit(LEDS_PORT_REG,GREEN_LED_PIN);
	ClearBit(LEDS_PORT_REG,YELLOW_LED_PIN);
	ClearBit(LEDS_PORT_REG,AQUA_LED_PIN);
	MOTOR_STATUS = 0;
	OCR1A = 0;
	AIR_DYN_ON_OFF();
	MOTOR_START_BUTTON(MOTOR_DIR_RIGHT);
}

void TURBO_BUTTON(void)
{
	if(OCR1A > 0)
	{
	while(GetBit(BUTTONS_PIN_REG,TURBO_ON_OFF_BUTTON_PIN) == 1);
	ToggleBit(TURBO_PORT_REG,TURBO_EN_PIN);
	ToggleBit(TURBO_PORT_REG,TURBO_DIR_RIGHT_PIN);
	}
	else
	{
		//Do Nothing
	}
}

void ACTION(void)
{
	volatile int TURN_OFF = 0;
	while(TURN_OFF == 0)
	{
		if(OCR1A == 0)
		{
			ClearBit(LEDS_PORT_REG,GREEN_LED_PIN);
			ClearBit(TURBO_PORT_REG,TURBO_EN_PIN);
			ClearBit(TURBO_PORT_REG,TURBO_DIR_RIGHT_PIN);
			ClearBit(TURBO_PORT_REG,TURBO_DIR_LEFT_PIN);
		}
		else
		{
			SetBit(LEDS_PORT_REG,GREEN_LED_PIN);
		}
		
		AIR_DYN_ON_OFF();
		
		if(GetBit(TURBO_PORT_REG,TURBO_EN_PIN) == 1)
		{
			SetBit(LEDS_PORT_REG,AQUA_LED_PIN);
		}
		else
		{
			ClearBit(LEDS_PORT_REG,AQUA_LED_PIN);
		}
		
		if(GetBit(BUTTONS_PIN_REG,ENGINE_OFF_BUTTON_PIN) == 1)
		{
			while(GetBit(BUTTONS_PIN_REG,ENGINE_OFF_BUTTON_PIN) == 1);
			TURN_OFF = 1;
			MOTOR_TURN_OFF();
		}
		else if(GetBit(BUTTONS_PIN_REG,ENGINE_INCREASE_SPEED_PIN) == 1)
		{
			while(GetBit(BUTTONS_PIN_REG,ENGINE_INCREASE_SPEED_PIN) == 1);
			if(OCR1A < 255)
			{
				OCR1A += 51;
			}
			else
			{
				//Do nothing
			}
		}
		else if(GetBit(BUTTONS_PIN_REG,ENGINE_DECREASE_SPEED_PIN) == 1)
		{
			while(GetBit(BUTTONS_PIN_REG,ENGINE_DECREASE_SPEED_PIN) == 1);
			if(OCR1A > 0)
			{
				OCR1A -= 51;
			}
			else
			{
				//Do nothing
			}
		}
		else if(GetBit(BUTTONS_PIN_REG,TURBO_ON_OFF_BUTTON_PIN) == 1)
		{
			TURBO_BUTTON();
		}
		else
		{
			//Do Nothing
		}
	}
}

void AIR_DYN_ON_OFF()
{
	if(OCR1A > 0)
	{
		SetBit(AIR_DYNAMIC_PORT_REG,AIR1_DIR_RIGHT_PIN);
		ClearBit(AIR_DYNAMIC_PORT_REG,AIR1_DIR_LEFT_PIN);
		SetBit(AIR_DYNAMIC_PORT_REG,AIR1_EN_PIN);
		
		SetBit(AIR_DYNAMIC_PORT_REG,AIR2_DIR_RIGHT_PIN);
		ClearBit(AIR_DYNAMIC_PORT_REG,AIR2_DIR_LEFT_PIN);
		SetBit(AIR_DYNAMIC_PORT_REG,AIR2_EN_PIN);
	}
	else if(OCR1A == 0)
	{
		ClearBit(AIR_DYNAMIC_PORT_REG,AIR1_DIR_RIGHT_PIN);
		ClearBit(AIR_DYNAMIC_PORT_REG,AIR1_DIR_LEFT_PIN);
		ClearBit(AIR_DYNAMIC_PORT_REG,AIR1_EN_PIN);
		
		ClearBit(AIR_DYNAMIC_PORT_REG,AIR2_DIR_RIGHT_PIN);
		ClearBit(AIR_DYNAMIC_PORT_REG,AIR2_DIR_LEFT_PIN);
		ClearBit(AIR_DYNAMIC_PORT_REG,AIR2_EN_PIN);
	}
	else
	{
		//Do Nothing
	}
}