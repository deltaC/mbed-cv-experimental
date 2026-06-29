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

	virtual void init() = 0;
};

class GPIO_port : IPeriphery {
	const char port_;
	__IO uint16_t pin_state_;
public:
	GPIO_port (const char port_) : port_(port_) {
		this->pin_state_ = 0;
	}

	void init() override {
		if (port_ == 'B') {
			RCC->AHB1ENR 	|= 	RCC_AHB1ENR_GPIOBEN;
			GPIOB->MODER 	|= 	GPIO_MODER_MODER0_0;
			GPIOB->OSPEEDR 	|= 	GPIO_OSPEEDER_OSPEEDR0;
		}
	}

	void pin_toggle(int pin_number) {
		if ((pin_number >= 0) && (pin_number < 16)) {
			if (pin_state_ & (1 << pin_number)) {
				pin_state_ &= ~(1 << pin_number);
				GPIOB->BSRR = 1 << (pin_number + 16);
			}
			else {
				pin_state_ |= (1 << pin_number);
				GPIOB->BSRR = 1 << pin_number;
			}
		}
	}
};

#endif /* PERIPHERY_PERIPHERY_HPP_ */
