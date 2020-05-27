#include <stdio.h>
#include "DmxReceiver.hpp"
#include <stm32f1xx_hal.h>
#include "DmxCommand.hpp"
#include "Leds.hpp"
#include "tim.h"


volatile bool frameReceived = false;
const uint8_t* dmxBuffer = nullptr;
DmxCommand dmxCmd;
Leds<8> leds;

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

		HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
		HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
		HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
		HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
		HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
		HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
		HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
		HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);

		leds.init(std::array<CCRPtr, 8>{
			&(htim1.Instance->CCR1),
			&(htim1.Instance->CCR2),
			&(htim1.Instance->CCR3),
			&(htim1.Instance->CCR4),
			&(htim2.Instance->CCR1),
			&(htim2.Instance->CCR2),
			&(htim3.Instance->CCR1),
			&(htim3.Instance->CCR2)},255);


		printf("Initialized");
	}

	void loop()
	{


		static uint8_t val = 0;
		val++;
		leds.setAll(val);
		leds.apply();

		HAL_Delay(20);

//
//		dmxCmd.print();
//		printf("-----------------");
//		HAL_Delay(1000);
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

		//TODO think about maybe using 16 bit dmx channels instead of 8 bit.

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
	 * bits
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

