//
// Created by garvet on 08.09.2021.
//

#ifndef ESP_CONNECT_HAL_HPP_
#define ESP_CONNECT_HAL_HPP_

//#define U8G2

#include <cstdint>
#ifdef U8G2
#include "u8g2/u8g2.h"
#endif

using GPIO_TypeDef = unsigned int;
typedef enum
{
    GPIO_PIN_RESET = 0u,
    GPIO_PIN_SET
} GPIO_PinState;

typedef enum
{
    HAL_OK       = 0x00U,
    HAL_ERROR    = 0x01U,
    HAL_BUSY     = 0x02U,
    HAL_TIMEOUT  = 0x03U
} HAL_StatusTypeDef;

typedef enum
{
    UART_HAL_OK       = 0x00U,
    UART_HAL_ERROR    = 0x01U,
    UART_HAL_BUSY     = 0x02U,
    UART_HAL_TIMEOUT  = 0x03U
} UART_HandleTypeDef;


extern GPIO_TypeDef mas_port[16];
extern uint32_t time_tick;
GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef *GPIO_Port, uint16_t GPIO_Pin);
uint32_t HAL_GetTick();
void HAL_Delay(uint32_t delay);
void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);

HAL_StatusTypeDef HAL_UART_Receive_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_UART_Transmit_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);


#endif // ESP_CONNECT_HAL_HPP_
