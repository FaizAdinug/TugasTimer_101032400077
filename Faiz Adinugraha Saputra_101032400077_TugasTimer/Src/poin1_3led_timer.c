#include "stm32f4xx.h"

void GPIO_Init(void) {
    RCC->AHB1ENR |= (1 << 0);

    GPIOA->MODER &= ~((3 << 4) | (3 << 6) | (3 << 8));
    GPIOA->MODER |=  ((1 << 4) | (1 << 6) | (1 << 8));
}

void Timers_Init(void) {
    RCC->APB1ENR |= (1 << 0) | (1 << 1) | (1 << 2);

    TIM2->PSC = 15999;
    TIM2->ARR = 499;
    TIM2->DIER |= (1 << 0);
    NVIC_EnableIRQ(TIM2_IRQn);

    TIM3->PSC = 15999;
    TIM3->ARR = 249;
    TIM3->DIER |= (1 << 0);
    NVIC_EnableIRQ(TIM3_IRQn);

    TIM4->PSC = 15999;
    TIM4->ARR = 99;
    TIM4->DIER |= (1 << 0);
    NVIC_EnableIRQ(TIM4_IRQn);

    TIM2->CR1 |= (1 << 0);
    TIM3->CR1 |= (1 << 0);
    TIM4->CR1 |= (1 << 0);
}

void TIM2_IRQHandler(void) {
    if (TIM2->SR & (1 << 0)) {
        TIM2->SR &= ~(1 << 0);
        GPIOA->ODR ^= (1 << 2);
    }
}

void TIM3_IRQHandler(void) {
    if (TIM3->SR & (1 << 0)) {
        TIM3->SR &= ~(1 << 0);
        GPIOA->ODR ^= (1 << 3);
    }
}

void TIM4_IRQHandler(void) {
    if (TIM4->SR & (1 << 0)) {
        TIM4->SR &= ~(1 << 0);
        GPIOA->ODR ^= (1 << 4);
    }
}

int main(void) {
    GPIO_Init();
    Timers_Init();

    while (1) {
    }
}
