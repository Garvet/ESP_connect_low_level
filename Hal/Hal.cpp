//
// Created by garvet on 08.09.2021.
//

#include "Hal.hpp"

GPIO_TypeDef mas_port[16]{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint32_t time_tick = 0;

GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef *GPIO_Port, uint16_t GPIO_Pin) {
    return GPIO_PinState(GPIO_Port[GPIO_Pin]);
}
uint32_t HAL_GetTick() {
    return time_tick;
}

void HAL_Delay(uint32_t delay) {
    time_tick += delay;
}
void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState) {
    if(*GPIOx == 0)
        mas_port[GPIO_Pin] = PinState;
}

HAL_StatusTypeDef HAL_UART_Receive_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size) {
    if (*huart == UART_HAL_ERROR) {
        *huart = UART_HAL_BUSY;
        return HAL_ERROR;
    }
    else {
        return HAL_BUSY;
    }
}

HAL_StatusTypeDef HAL_UART_Transmit_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size) {
    if (*huart == UART_HAL_OK) {
        *huart = UART_HAL_TIMEOUT;
        return HAL_OK;
    }
    else {
        return HAL_TIMEOUT;
    }
}
