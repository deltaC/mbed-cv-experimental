/*
 * tim1_clkgen.cpp
 *
 *  Created on: Jul 2, 2026
 *      Author: g_phaidros
 */

#include "periphery.hpp"


TIM1_ClkGen::TIM1_ClkGen(const uint8_t mode, const uint32_t psc, const uint32_t arr) : \
	mode_(mode),  psc_(psc), arr_(arr) {}

int  TIM1_ClkGen::init() {
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

	GPIOA->MODER |= GPIO_MODER_MODER8_1;
	GPIOA->AFR[1] |= (1 << (8 - 8));
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR8;

	if (this->mode_ == 0) {
		TIM1->PSC = this->psc_;
		TIM1->ARR = this->arr_;
		TIM1->CCMR1 |= ( TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 );
		TIM1->CCMR1 |= TIM_CCMR1_OC1PE;
		TIM1->CCR1 = (this->arr_ + 1) / 2;
		TIM1->CCER |= TIM_CCER_CC1E;
		TIM1->BDTR |= TIM_BDTR_MOE;
		TIM1->EGR |= TIM_EGR_UG;
		TIM1->CR1 |= TIM_CR1_ARPE;
		return 0;
	}
	return 1;
}

int TIM1_ClkGen::start() {
	TIM1->CR1 |= TIM_CR1_CEN;
	return 0;
}

int TIM1_ClkGen::stop() {
	TIM1->CR1 &= ~( TIM_CR1_CEN );
	return 0;
}


