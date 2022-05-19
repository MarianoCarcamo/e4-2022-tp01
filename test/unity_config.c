#include "unity_config.h""
#include <stm32f1xx.h>


#define PIN_CNF_AFO_PP (0b10)
#define PIN_MOD_LS (0b10)
#define PIN_CNF_AN (0b00)
#define PIN_MOD_IN (0b00)
#define USART_STOP_1 (0b00)

#define USART_BRR_FIXP_FACTOR 16UL
#define USART_BRR_OVERSAMPLE 16UL
void unityOutputStart(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN | RCC_APB2ENR_IOPAEN | RCC_APB2ENR_USART1EN;
    GPIOA->CRH = (GPIOA->CRH & ~(GPIO_CRH_CNF9 | GPIO_CRH_MODE9)) 
                 | (PIN_CNF_AFO_PP << GPIO_CRH_CNF9_Pos)
                 | (PIN_MOD_LS << GPIO_CRH_MODE9_Pos);
    SystemCoreClockUpdate();
    USART1->CR1 |= USART_CR1_UE;
    USART1->CR2 = (USART1->CR2 & ~(USART_CR2_STOP)) | (USART_STOP_1 << USART_CR2_STOP_Pos) ;
    USART1->BRR = (SystemCoreClock*USART_BRR_FIXP_FACTOR) / (115200*USART_BRR_OVERSAMPLE);
    USART1->CR1 |= USART_CR1_TE;
}

void unityOutputChar(char c)
{
    while (!(USART1->SR & USART_SR_TXE));
    USART1->DR = c&0xFF;
}
void unityOutputFlush(void)
{
    while (!(USART1->SR & USART_SR_TC));
}
void unityOutputComplete(void)
{
    unityOutputFlush();
    USART1->CR1 &= ~(USART_CR1_UE);
    GPIOA->CRH = (GPIOA->CRH & ~(GPIO_CRH_CNF9 | GPIO_CRH_MODE9)) 
                 | (PIN_CNF_AN << GPIO_CRH_CNF9_Pos)
                 | (PIN_MOD_IN << GPIO_CRH_MODE9_Pos);
    RCC->APB2ENR &= ~(RCC_APB2ENR_USART1EN);
}

