#pragma once
#include <array>


using CCRPtr = volatile uint32_t*;

template <int NUM_LEDS>
class Leds
{
public:



	/**
	 * @param pointers to the capture compare registers of the pwm channels of each led */
	void init(const std::array<CCRPtr, NUM_LEDS>& ccrs, uint32_t maxBrightness)
	{
		ccr = ccrs;
		this->maxBrightness = maxBrightness;
	}

	/**Will apply the values from @p brightness to the hardware */
	void apply()
	{
		//TODO honor max brightness
		for(int i = 0; i < NUM_LEDS; ++i)
		{
			*(ccr[i]) = brightness[i];
		}
	}

	void setAll(uint32_t bri)
	{
		for(int i = 0; i < NUM_LEDS; ++i)
		{
			brightness[i] = bri;
		}
	}


	/**contains the brightness values that will be send to the leds once apply() is called */
	std::array<uint32_t, NUM_LEDS> brightness;
	std::array<CCRPtr, NUM_LEDS> ccr;
	uint32_t maxBrightness;
};
