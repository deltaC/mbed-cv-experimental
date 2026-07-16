/*
 * i2c_device.cpp
 *
 *  Created on: Jul 2, 2026
 *      Author: g_phaidros
 */

#include "periphery.hpp"


I2C_Device::I2C_Device() : slave_address_(slave_address) {}

int I2C_Device::init() {
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;

	GPIOB->MODER |= GPIO_MODER_MODER8_1 | GPIO_MODER_MODER9_1;
	GPIOB->OTYPER |= GPIO_OTYPER_OT_8 | GPIO_OTYPER_OT_
	GPIOB->PUPDR |= GPIO_PUPDR_PUPDR8_0 | GPIO_PUPDR_PUPDR9_0;
	GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR8_1 | GPIO_OSPEEDER_OSPEEDR9_1;
	GPIOB->AFR[1] |= (4 << (8-8)*4) | (4 << (9-8)*4);

	RCC->APB1RSTR |= RCC_APB1RSTR_I2C1RST;
	RCC->APB1RSTR &= ~RCC_APB1RSTR_I2C1RST;

	I2C1->CR2 |= 48;  // APB1 freq = SysFreq/2
	I2C1->CCR |= 40;   // 400kHz (48MHz / (3 * 0.4Mhz) = 40)
	I2C1->CCR |= I2C_CCR_FS;
	I2C1->TRISE = 15; // 300ns max rise time
	I2C1->CR1 |= I2C_CR1_PE;  // Enable I2C
	return 0;
}

uint8_t I2C_Device::readReg(uint8_t reg) {
	uint8_t data = 0;
	while (I2C1->SR2 & I2C_SR2_BUSY);

	I2C1->CR1 |= I2C_CR1_START;
	while (!(I2C1->SR1 & I2C_SR1_SB));

	I2C1->DR = (this->slave_address_ << 1);
	while (!(I2C1->SR1 & I2C_SR1_ADDR));

	(void)I2C1->SR2;

	I2C1->DR = reg;
	while (!(I2C1->SR1 & I2C_SR1_TXE));

	I2C1->CR1 |= I2C_CR1_START;
	while (!(I2C1->SR1 & I2C_SR1_SB));

	I2C1->DR = (this->slave_address_ << 1) | 1;
	while (!(I2C1->SR1 & I2C_SR1_ADDR));

	I2C1->CR1 &= ~I2C_CR1_ACK;
	(void)I2C1->SR2;

	I2C1->CR1 |= I2C_CR1_STOP;
	while (!(I2C1->SR1 & I2C_SR1_RXNE));

	data = I2C1->DR;
	I2C1->CR1 |= I2C_CR1_ACK;

	return data;
}

int I2C_Device::writeReg(uint8_t reg, uint8_t data) {
	while (I2C1->SR2 & I2C_SR2_BUSY);

	I2C1->CR1 |= I2C_CR1_START;
	while (!(I2C1->SR1 & I2C_SR1_SB));

	I2C1->DR = address << 1;
	while (!(I2C1->SR1 & I2C_SR1_ADDR));
	(void)I2C1->SR2;

      	I2C1->DR = reg;
	while (!(I2C1->SR1 & I2C_SR1_TXE));

	I2C1->DR = data;
	while (!(I2C1->SR1 & I2C_SR1_BTF));

	I2C1->CR1 |= I2C_CR1_STOP;
	return 0;
}
