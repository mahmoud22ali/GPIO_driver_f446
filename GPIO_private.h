/**********************************************/
/* Author  			: Mahmoud Sayed 	      */
/* Date    			: 28 DES 2023             */
/* Version 			: V02                     */
/* Microcontroller  : STM32F103xx             */
/**********************************************/

#ifndef GPIO_PRIVATE_H_
#define GPIO_PRIVATE_H_

#define GPIO_PERIPHERAL_NUM 	8u

#define MOODER_MASK				0b11
#define MOODER_PIN_ACCESS		2u

#define PUPDR_MASK				0b11
#define PUPDR_PIN_ACCESS		2u

#define OTYPER_MASK				0b1

#define OSPEEDR_MASK			0b11
#define OSPEEDR_PIN_ACCESS		2u

#define AFR_MASK				0b1111
#define AFR_PIN_ACCESS			4u
#define AFR_PIN_SHIFTING		8u


#endif

