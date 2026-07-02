/*
 * gpio_port.cpp
 *
 *  Created on: Jun 29, 2026
 *      Author: g_phaidros
 */

#include "periphery.hpp"


GPIO_Port::GPIO_Port(const char port_) : port_(port_) {
	if (this->port_ == 'B')
		this->pin_state_ = 0;
}

int GPIO_Port::init() {
	if (this->port_ == 'B') {
		RCC->AHB1ENR 	|= 	 RCC_AHB1ENR_GPIOBEN;
		GPIOB->MODER 	|= ( GPIO_MODER_MODER0_0 | GPIO_MODER_MODER1_0 | GPIO_MODER_MODER2_0 |
							 GPIO_MODER_MODER3_0 | GPIO_MODER_MODER4_0 | GPIO_MODER_MODER5_0 |
							 GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0 | GPIO_MODER_MODER8_0 |
							 GPIO_MODER_MODER9_0 | GPIO_MODER_MODER10_0 | GPIO_MODER_MODER11_0 |
							 GPIO_MODER_MODER12_0 | GPIO_MODER_MODER13_0 | GPIO_MODER_MODER14_0 |
							 GPIO_MODER_MODER15_0);
		pin_state_ = &(GPIOB->ODR);
		return 0;
	}
	return 1;
}

int GPIO_Port::pinToggle(const int pin_number) {
	if ((pin_number >= 0) && (pin_number < 16) && (port_ == 'B')) {
		if (*(this->pin_state_) & (1 << pin_number)) {
			GPIOB->BSRR = 1 << (pin_number + 16);
		}
		else {
			GPIOB->BSRR = 1 << pin_number;
		}
		return 0;
	}
	return 1;
}
