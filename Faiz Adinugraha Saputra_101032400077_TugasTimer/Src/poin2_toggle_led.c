#include "stm32f4xx.h"

volatile int flag = 0;

void EXTI9_5_IRQHandler(void) {
    if (EXTI->PR & (1 << 5)) {
        EXTI->PR |= (1 << 5);
        EXTI->IMR &= ~(1 << 5);
        TIM2->CNT = 0;
        TIM2->CR1 |= (1 << 0);
    }
}

void TIM2_IRQHandler(void) {
    if (TIM2->SR & (1 << 0)) {
        TIM2->SR &= ~(1 << 0);
        TIM2->CR1 &= ~(1 << 0);

        if ((GPIOA->IDR & (1 << 5)) == 0) {
            flag = 1;
        }

        EXTI->PR |= (1 << 5);
        EXTI->IMR |= (1 << 5);
    }
}

int main(void) {
    RCC->AHB1ENR |= (1 << 0);
    RCC->APB1ENR |= (1 << 0);
    RCC->APB2ENR |= (1 << 14);

    GPIOA->MODER &= ~(3 << 8);
    GPIOA->MODER |= (1 << 8);

    GPIOA->MODER &= ~(3 << 10);
    GPIOA->PUPDR &= ~(3 << 10);
    GPIOA->PUPDR |= (1 << 10);

    GPIOA->ODR &= ~(1 << 4);

    SYSCFG->EXTICR[1] &= ~(0xF << 4);
    EXTI->IMR |= (1 << 5);
    EXTI->FTSR |= (1 << 5);
    NVIC_EnableIRQ(EXTI9_5_IRQn);

    TIM2->PSC = 15999;
    TIM2->ARR = 49;
    TIM2->DIER |= (1 << 0);
    NVIC_EnableIRQ(TIM2_IRQn);

    while (1) {
        if (flag == 1) {
            flag = 0;
            GPIOA->ODR ^= (1 << 4);
        }
    }
}
