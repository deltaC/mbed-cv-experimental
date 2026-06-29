/*
 * periphery.hpp
 *
 *  Created on: Jun 24, 2026
 *      Author: g_phaidros
 */

#ifndef PERIPHERY_PERIPHERY_HPP_
#define PERIPHERY_PERIPHERY_HPP_

#include "stm32f4xx.h"
#include <stdint.h>

class IPeriphery {
public:
	virtual ~IPeriphery() = default;

	virtual int init() = 0;
};

class GPIO_Port : public IPeriphery {
	const char port_;
	__IO uint32_t* pin_state_; // aligned to ODR but actually contains 16 bits
public:
	GPIO_Port(const char port_);
	int init() override;
	int pin_toggle(int pin_number);
};

#endif /* PERIPHERY_PERIPHERY_HPP_ */
