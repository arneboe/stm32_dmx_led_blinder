#include <stdio.h>
#include "DmxReceiver.hpp"
#include <stm32f1xx_hal.h>

void dmxFrameReceived(const uint8_t* buffer);

volatile bool frameReceived = false;
const uint8_t* dmxBuffer = nullptr;

extern "C" {

	void init()
	{
		DmxReceiver::init(dmxFrameReceived);
		printf("Initialized");
	}

	/** This is the user entry method. It is call forever from main() */
	void loop()
	{

	}

	void systick()
	{
		auto x = HAL_GetTick();

		//update dmx address from switches

		//for each effect:
		// updateEffect(leds, dt, dmx_data);
		//apply changes

	}

}


void dmxFrameReceived(const uint8_t* buffer)
{
	//once we get the buffer it will never change
    dmxBuffer = buffer;
}

