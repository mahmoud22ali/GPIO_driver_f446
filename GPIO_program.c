/**********************************************/
/* Author  			: Mahmoud Sayed 	      */
/* Date    			: 1 jan 2024             */
/* Version 			: V02                     */
/* Microcontroller  : STM32F446xx             */
/**********************************************/

#include <stdint.h>
#include "STM32F446xx.h"
#include "ERRTYPE.h"
#include "GPIO_interfaces.h"
#include "GPIO_private.h"

static GPIO_RegDif* GPIOPORT[GPIO_PERIPHERAL_NUM]={GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF,GPIOG,GPIOF};

/**********************************************/
/* @fn GPIO_PinInit
/* @brif the function initialize the GPIO PIN according to the input parameters
/* @param[in] PinConfig : the initilization vlaues of the pin
/* @retval Error State
/**********************************************/
uint8_t GPIO_PinInit(const GPIO_PinConfig* PinConfig)
{
	uint8_t Local_ErrorState =OK;
	if(PinConfig!=NULL)
	{
		if((PinConfig->port<=PORTH) && (PinConfig->PinNum<=PIN15))
		{
			/*select GPIO mood*/
			(GPIOPORT[PinConfig->port]->MODER)&=~(MOODER_MASK<<((PinConfig->PinNum)*MOODER_PIN_ACCESS));//clear moods bit
			(GPIOPORT[PinConfig->port]->MODER)|=(PinConfig->Mood)<<((PinConfig->PinNum)*MOODER_PIN_ACCESS);//put value moods bit
			/*select GPIO pull state*/
			(GPIOPORT[PinConfig->port]->PUPDR)&=~(PUPDR_MASK<<((PinConfig->PinNum)*PUPDR_PIN_ACCESS));//clear moods bit
			(GPIOPORT[PinConfig->port]->PUPDR)|=(PinConfig->PullType)<<((PinConfig->PinNum)*PUPDR_PIN_ACCESS);
			/*select OUTPUT type & output speed in case General purpose output mode or Alternate function mode*/
			if((PinConfig->Mood==output) || (PinConfig->Mood==Alternate_function))
			{
				/*select OUTPUT type*/
				(GPIOPORT[PinConfig->port]->OTYPER)&=~(OTYPER_MASK<<(PinConfig->PinNum));//clear moods bit
				(GPIOPORT[PinConfig->port]->OTYPER)|=(PinConfig->OutPutType)<<((PinConfig->PinNum));//put value moods bit
				/*select OUTPUT speed*/
				(GPIOPORT[PinConfig->port]->OSPEEDER)&=~(OSPEEDR_MASK<<((PinConfig->PinNum)*OSPEEDR_PIN_ACCESS));//clear moods bit
				(GPIOPORT[PinConfig->port]->OSPEEDER)|=(PinConfig->Speed)<<((PinConfig->PinNum)*OSPEEDR_PIN_ACCESS);//put value moods bit
				/*select the pin Alternate function*/
				if(PinConfig->Mood==Alternate_function)
				{
					uint8_t local_regnum=(PinConfig->PinNum)/AFR_PIN_SHIFTING;
					uint8_t local_bitnum=(PinConfig->PinNum)%AFR_PIN_SHIFTING;

					(GPIOPORT[PinConfig->port]->AFR[local_regnum])&=~(AFR_MASK<<((local_bitnum)*AFR_PIN_ACCESS));//clear moods bit
					(GPIOPORT[PinConfig->port]->AFR[local_regnum])|=((PinConfig->AltFunc)<<(local_bitnum*AFR_PIN_ACCESS));//put value moods bit
				}
			}

		}
		else
		{
			Local_ErrorState=NULL_PTR_ERR;
		}
	}
	else
	{
		Local_ErrorState=NULL_PTR_ERR;
	}
	return Local_ErrorState;
}

uint8_t GPIO_SetPinValue(PORT port,PIN PinNum,PinValue pinval)
{
	uint8_t Local_ErrorState =OK;
			if((port<=PORTH) && (PinNum<=PIN15))
			{
				if(pinval==PIN_LOW)
				{
					(GPIOPORT[port]->ODR)&=~(1<<PinNum);
					//GPIOPORT[port]->BSRR=1<<(16+PinNum)
				}
				else if(pinval== PIN_HIGH)
				{
					(GPIOPORT[port]->ODR)|=(1<<PinNum);
					//GPIOPORT[port]->BSRR=1<<PinNum;
				}
				else
				{
					Local_ErrorState=NOK;
				}
			}
			else
			{
				Local_ErrorState=NOK;
			}
		return Local_ErrorState;
}

uint8_t GPIO_TogglePinValue(PORT port,PIN PinNum)
{
	uint8_t Local_ErrorState =OK;
		if((port<=PORTH) && (PinNum<=PIN15))
		{
			TOGGLE_BIT(GPIOPORT[port]->ODR, PinNum);
		}
		else
		{
			Local_ErrorState=NOK;
		}
	return Local_ErrorState;
}

uint8_t GPIO_ReadPinValue(PORT port,PIN PinNum,PinValue* pinvla)
{
	uint8_t Local_ErrorState =OK;
			if((port<=PORTH) && (PinNum<=PIN15))
			{
				*pinvla=GET_BIT(GPIOPORT[port]->IDR, PinNum);
			}
			else
			{
				Local_ErrorState=NOK;
			}
	return Local_ErrorState;
}
