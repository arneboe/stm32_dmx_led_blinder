#include "DmxCommand.hpp"

#define NUM_DMX_CHANNELS 10

#define DMX_MASTER 0
#define DMX_STROBE 1
#define DMX_W1     2
#define DMX_W2     3
#define DMX_W3     4
#define DMX_W4     5
#define DMX_R1     6
#define DMX_R2     7
#define DMX_R3     8
#define DMX_R4     9

#define MAX_ALLOWED_CHANNEL (513 - NUM_DMX_CHANNELS)

void DmxCommand::load(uint16_t dmxAddr, const uint8_t* dmxData)
{
	//turn off if dmx data is invalid
	if(!dmxData)
	{
		setZero();
		return;
	}
	//disable if dmx addr is too large.
	if(dmxAddr > MAX_ALLOWED_CHANNEL)
	{
		setZero();
		return;
	}
	master = dmxData[dmxAddr + DMX_MASTER];
	strobe = dmxData[dmxAddr + DMX_STROBE];
	white[0] = dmxData[dmxAddr + DMX_W1];
	white[1] = dmxData[dmxAddr + DMX_W2];
	white[2] = dmxData[dmxAddr + DMX_W3];
	white[3] = dmxData[dmxAddr + DMX_W4];
	red[0] = dmxData[dmxAddr + DMX_R1];
	red[1] = dmxData[dmxAddr + DMX_R2];
	red[2] = dmxData[dmxAddr + DMX_R3];
	red[3] = dmxData[dmxAddr + DMX_R4];
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

void DmxCommand::print()
{
	printf("master: %d\n", master);
	printf("strob : %d\n", strobe);
	printf("white0: %d\n", white[0]);
	printf("white1: %d\n", white[1]);
	printf("white2: %d\n", white[2]);
	printf("white3: %d\n", white[3]);
	printf("red0  : %d\n", red[0]);
	printf("red1  : %d\n", red[1]);
	printf("red2  : %d\n", red[2]);
	printf("red3  : %d\n", red[3]);

}

