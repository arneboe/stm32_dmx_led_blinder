#include "DmxReceiver.hpp"
#include "usart.h"
#include <stdio.h>

#define DMX_CONNECTED_TIMEOUT_MS 1000

uint8_t DmxReceiver::buffer[DMX_FRAME_SIZE] = {0};
DmxFrameCallback DmxReceiver::callback = nullptr;
uint32_t DmxReceiver::lastReceivedTime = 0;

void DmxReceiver::init(DmxFrameCallback frameReceivedCallback) {
    callback = frameReceivedCallback;
    HAL_UART_Receive_DMA(&huart3, DmxReceiver::buffer, DMX_FRAME_SIZE);
}

const uint8_t *const DmxReceiver::getBuffer()
{
	return buffer;
}

void DmxReceiver::signalFrameReceived() {
    DmxReceiver::lastReceivedTime = HAL_GetTick();
    if(nullptr != callback)
        callback(buffer);
}

bool DmxReceiver::connected() {
    return (HAL_GetTick() - lastReceivedTime) < DMX_CONNECTED_TIMEOUT_MS;
}

extern "C"
{
	void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
	{

		if(huart->Instance == USART3)
		{
			//TODO NDTR. check if we got any data at all before the error occurred. If yes we got a smaller frame which is also fine.
			//If not dmx has been disconnected
			//receivedBytes = DMX_FRAME_SIZE - __HAL_DMA_GET_COUNTER(huart1.hdmarx);
			HAL_UART_Receive_DMA(&huart3, DmxReceiver::buffer, DMX_FRAME_SIZE);
		}
	}

	void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
	{
		if(huart->Instance == USART3)
		{
			HAL_UART_Receive_DMA(&huart3, DmxReceiver::buffer, DMX_FRAME_SIZE);
			DmxReceiver::signalFrameReceived();
		}
	}
}
