/*
 * button.c
 *
 *  Created on: Jul 31, 2020
 *      Author: Kefford
 */

#include "main.h"
#include "button.h"

extern TIM_HandleTypeDef htim7;
extern TIM_HandleTypeDef htim16;

static uint8_t prv_firstEdge           = 1;
static uint8_t prv_buttonPressCount    = 0;
static uint8_t prv_lastButtonCount     = 0;
static uint8_t prv_buttonEventPending  = 0;

#ifdef DEBUG
static uint8_t ledCount = 0;

typedef struct
{
      GPIO_TypeDef * port;
      uint16_t pin;
} ledPortPin_t;

ledPortPin_t leds[8] = {{LD3_GPIO_Port,LD3_Pin}, {LD5_GPIO_Port,LD5_Pin}, {LD7_GPIO_Port,LD7_Pin}, {LD9_GPIO_Port,LD9_Pin}, {LD10_GPIO_Port,LD10_Pin}, {LD8_GPIO_Port,LD8_Pin}, {LD6_GPIO_Port,LD6_Pin}, {LD4_GPIO_Port,LD4_Pin}};
#endif



uint8_t button_has_event(void)
{
   return prv_buttonEventPending;
}

uint8_t button_get_press_count(void)
{
   prv_buttonEventPending = 0;
   return prv_lastButtonCount;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
   if(GPIO_Pin == BLUE_BUTTON_Pin && prv_firstEdge)
   {
      prv_firstEdge = 0;
      HAL_TIM_Base_Start_IT(&htim7);

#ifdef DEBUG
      HAL_GPIO_TogglePin(leds[ledCount].port, leds[ledCount].pin);
      ledCount++;
      if(ledCount >= 8)
      {
         ledCount = 0;
      }
#endif
   }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
   if(htim->Instance == TIM7)    // Short Delay Timer
   {
      // may be first button press or a subsequent button press so stop both timers
      HAL_TIM_Base_Stop_IT(&htim7);
      HAL_TIM_Base_Stop_IT(&htim16);

      // allow interrupts to be detected again by a new button press
      prv_firstEdge = 1;

      prv_buttonPressCount++;

      // reset long timer and wait for another button press or timeout
      __HAL_TIM_SET_COUNTER(&htim16, 0);
      HAL_TIM_Base_Start_IT(&htim16);
   }
   else if(htim->Instance == TIM16)    // Long Delay Timer
   {
      // button has been pressed at least once and long delay timer has elapsed
      HAL_TIM_Base_Stop_IT(&htim16);

      prv_lastButtonCount = prv_buttonPressCount;
      prv_buttonPressCount = 0;
      prv_buttonEventPending = 1;

//#ifdef DEBUG
      HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
//#endif
   }
}
