#include <stdio.h>
#include "DmxReceiver.hpp"

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
		printf("blaaa\n");
	}

	void systick()
	{
		printf("aaa");
	}

}


void dmxFrameReceived(const uint8_t* buffer)
{
	//once we get the buffer it will never change
    dmxBuffer = buffer;
}

