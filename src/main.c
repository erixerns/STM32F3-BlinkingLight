#include<stm32f30x.h>
#include<stm32f30x_rcc.h>
#include<stm32f30x_gpio.h>

void Delay(uint32_t nTime);

int main(){
	GPIO_InitTypeDef GPIO_InitStructure;
	// Enable Peripheral Clocks
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);

	// Configure GPIO
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	// configure system tick
	if(SysTick_Config(SystemCoreClock/1000))
		while(1);
	
	while(1){
		static int ledval = 1;

		// toggle led
		GPIO_WriteBit(GPIOE, GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11, (ledval)? Bit_SET : Bit_RESET);
		ledval = 1 - ledval;

		Delay(250);
	}
	return 0;
}

static __IO uint32_t TimingDelay;

void Delay(uint32_t nTime){
	TimingDelay = nTime;
	while(TimingDelay!=0);
}

void SysTick_Handler(void){
	if(TimingDelay!=0x00)
		TimingDelay--;
}

#ifdef USE_FULL_ASSERT
void assert_failed ( uint8_t * file , uint32_t line)
{
/* Infinite loop */
/* Use GDB to find out why we're here */
while (1);
}
#endif