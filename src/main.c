#include "stm32f1xx.h"
#include "GPIO_drive.h"

//delay declaration
void delay(int rep);

int signal=0;
int main(void){

GPIO_init(port_A,0,Input_mode,Input_PP);
GPIO_init(port_C,13,Output_50Mhz,Output_GP_PP);
GPIO_init(port_A,12,Output_50Mhz,Output_GP_PP);
__disable_irq();
AFIO->EXTICR[0]=0X00;
EXTI->IMR |=1;
EXTI->RTSR |=1;
NVIC_EnableIRQ(EXTI0_IRQn);
__enable_irq();

 while(1){
	 GPIO_write(port_A,12,signal);
	 if(signal){
		 delay(10);

		 GPIO_toggle(port_C,13);

	 delay(1);

	 }
	 else{
		GPIO_write(port_C,13,0);
	 }
 }


}

void delay(int rep){
	for(;rep>0;rep--){
		for(int i=0;i<100000;i++)
		{

		}
	}
}

void EXTI0_IRQHandler(){

	EXTI->PR|=1;
	if(signal){
		signal=0;
	}
	else signal=1;
}

































