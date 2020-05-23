#include "DmxCommand.hpp"

void DmxCommand::load(uint16_t dmxAddr, const uint8_t* dmxData)
{
	//turn off if dmx data is invalid
	if(!dmxData)
	{
		setZero();
		return;
	}
}

void DmxCommand::setZero()
{
	master = 0;
	strobe = 0;
	white[0] = 0;
	white[1] = 0;
	white[2] = 0;
	white[3] = 0;
	red[0] = 0;
	red[1] = 0;
	red[2] = 0;
	red[3] = 0;
}
