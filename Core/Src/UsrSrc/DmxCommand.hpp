#pragma once
#include <array>

struct DmxCommand
{
	uint8_t master;
	uint8_t strobe;
	std::array<uint8_t, 4> white;
	std::array<uint8_t, 4> red;

	void load(uint16_t dmxAddr, const uint8_t* dmxData);
	void setZero();
	void print();

};
