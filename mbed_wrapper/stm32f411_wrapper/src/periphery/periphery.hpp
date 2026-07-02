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
	int pinToggle(const int pin_number);
};


class I2C_Device : public IPeriphery {
	uint8_t slave_address_;
public:
	I2C_Device(const uint8_t slave_address);
	int init() override;
	uint8_t readReg(uint8_t reg);
	int writeReg(uint8_t reg, uint8_t data);
};


class TIM1_ClkGen : public IPeriphery {
	uint8_t mode_;
	uint32_t psc_;
	uint32_t arr_;
public:
	TIM1_ClkGen(const uint8_t mode, const uint32_t psc, const uint32_t arr);
	int init() override;
	int start();
	int stop();
};

#endif /* PERIPHERY_PERIPHERY_HPP_ */
