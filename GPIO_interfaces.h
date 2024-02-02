/**********************************************/
/* Author  			: Mahmoud Sayed 	      */
/* Date    			: 1 jan 2024             */
/* Version 			: V02                     */
/* Microcontroller  : STM32F446xx             */
/**********************************************/

#ifndef GPIO_INTERFACING_H_
#define GPIO_INTERFACING_H_

typedef enum
{
	PORTA=0,
	PORTB,
	PORTC,
	PORTD,
	PORTE,
	PORTF,
	PORTG,
	PORTH
}PORT;

typedef enum
{
	PIN0=0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7,
	PIN8,
	PIN9,
	PIN10,
	PIN11,
	PIN12,
	PIN13,
	PIN14,
	PIN15
}PIN;

typedef enum
{
	Input=0,
	output,
	Alternate_function,
	Analog
}MOOD;

typedef enum
{
	Low=0,
	Medium,
	Fast,
	High
}OutputSpeed;

typedef enum
{
	push_pull=0,
	open_drain
}OutputType;

typedef enum
{
	 Nopullup=0,
	 Pullup,
	 Pulldown
} pullupdown;

typedef enum
{
	 PIN_LOW=0,
	 PIN_HIGH
}PinValue;

typedef enum
{
	AF0=0 ,
	AF1   , 
	AF2   , 
	AF3   ,
	AF4   ,
	AF5   ,
	AF6   ,
	AF7   ,
	AF8   ,
	AF9   ,
	AF10  ,
	AF11  ,
	AF12  ,
	AF13  ,
	AF14  ,
	AF15  
}ALTFUN;

typedef struct
{
	PORT port;
	PIN PinNum;
	MOOD Mood;
	OutputSpeed Speed;
	OutputType OutPutType;
	pullupdown PullType;
	ALTFUN AltFunc;
}GPIO_PinConfig;
uint8_t GPIO_PinInit(const GPIO_PinConfig* PinConfig);
uint8_t GPIO_SetPinValue(PORT port,PIN PinNum,PinValue pinvla);
uint8_t GPIO_TogglePinValue(PORT port,PIN PinNum);
uint8_t GPIO_ReadPinValue(PORT port,PIN PinNum,PinValue* pinvla);

#endif 
