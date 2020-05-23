#pragma once
#include <array>

template <int NUM_LEDS>
class Leds
{
public:
	struct Pin
	{

	};

	/**
	 * Constructs the object but does not do any initialization.
	 * Init is done in init().
	 * @param pins A list of pins that will be used for pwm output.
	 * @para */
	Leds(const std::array<Pin, NUM_LEDS>& pins);

	/**lazy init */
	void init();

	/**Will apply the values from @p brightness to the hardware */
	void apply();


	/**contains the brightness values that will be send to the leds once apply() is called */
	std::array<uint16_t, NUM_LEDS> brightness;

};
