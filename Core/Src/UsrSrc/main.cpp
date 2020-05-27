#include <stdio.h>
#include "DmxReceiver.hpp"
#include <stm32f1xx_hal.h>
#include "DmxCommand.hpp"
#include "Leds.hpp"


volatile bool frameReceived = false;
const uint8_t* dmxBuffer = nullptr;
DmxCommand dmxCmd;
Leds<8> leds(); //TODO init properly

void dmxFrameReceived(const uint8_t* buffer);
uint16_t readDipSwitch();
void runDmxUpdate(const uint16_t dipSwitch, const uint8_t dtMs);
void runStaticEffect(const uint16_t dipSwitch, const uint8_t dtMs);


volatile int dmxCnt = 0;
volatile bool gotFrame = false;

extern "C" {

	void init()
	{
		DmxReceiver::init(dmxFrameReceived);
		dmxCmd.setZero();
		printf("Initialized");
	}

	void loop()
	{
		dmxCmd.print();
		printf("-----------------");
		HAL_Delay(1000);
//		if(gotFrame)
//		{
//			gotFrame=false;
//		for(int i = 1; i < 20; ++i)
//		{
//			printf("%d ", dmxBuffer[i]);
//		}
//		printf("\n");
//
//		printf("hz: %d\n",dmxCnt/(HAL_GetTick()/1000));
//
//
//		}
	}

	void systick()
	{
		const uint16_t dip = readDipSwitch();

		const bool dmxMode = (dip & 0b1000000000) == 0;

		if(dmxMode)
		{
			runDmxUpdate(dip, 1);
		}
		else
		{
			runStaticEffect(dip, 1);
		}

	}

} //end extern c




void runDmxUpdate(const uint16_t dipSwitch, const uint8_t dtMs)
{
	//+1 because the 0'th byte is in a dmx frame is reserved (the buffer is 513 bytes long).
	const uint16_t dmxAddr = (dipSwitch & 0b111111111) + 1;
	dmxCmd.load(dmxAddr, dmxBuffer);


	//for each effect:
	// updateEffect(leds, dt, dmx_data);
	//apply changes

}

/** Runs a simple static light effect based on the dipSwitchValue */
void runStaticEffect(const uint16_t dipSwitch, const uint8_t dtMs)
{
	/* static effects:
	 *
	 */
	//+1 just to be consistent with dmx...
	const uint16_t dmxAddr = (dipSwitch & 0b111111111) + 1;

}

uint16_t readDipSwitch()
{
	uint16_t result = 0;
	result = GPIOA->IDR & 0b11111111; //read GPIOA Pins 0..7
	result |= (GPIOB->IDR & 0b11) << 8; //read GPIOB Pins 0..1
	return result;
}


void dmxFrameReceived(const uint8_t* buffer)
{
	dmxCnt++;
	//once we get the buffer it will never change
    dmxBuffer = buffer;
    gotFrame = true;
}

