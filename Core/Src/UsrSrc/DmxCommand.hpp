#pragma once
#include <array>

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

struct DmxCommand
{
	uint8_t master;
	uint8_t strobe;
	std::array<uint8_t, 4> white;
	std::array<uint8_t, 4> red;

	void load(uint16_t dmxAddr, const uint8_t* dmxData);
	void setZero();

};
