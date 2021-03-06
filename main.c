/*
******************************************************************************
File:     main.c
Info:     Generated by Atollic TrueSTUDIO(R) 6.0.0   2016-09-26

The MIT License (MIT)
Copyright (c) 2009-2016 Atollic AB

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************************
*/

/* Includes */
#include <stddef.h>
#include "stm32l1xx.h"


/* Private typedef */
/* Private define  */
/* Private macro */
/* Private variables */
/* Private function prototypes */
/* Private functions */


/**
**===========================================================================
**
**  Abstract: main program
**
**===========================================================================
*/
int main(void)
{
  int i = 0;
  int button;

  /**
  *  IMPORTANT NOTE!
  *  See the <system_*.c> file and how/if the SystemInit() function updates 
  *  SCB->VTOR register. Sometimes the symbol VECT_TAB_SRAM needs to be defined 
  *  when building the project if code has been located to RAM and interrupts 
  *  are used. Otherwise the interrupt table located in flash will be used.
  *  E.g.  SCB->VTOR = 0x20000000;  
  */

  /**
  *  At this stage the microcontroller clock setting is already configured,
  *  this is done through SystemInit() function which is called from startup
  *  file (startup_stm32l1xx_hd.s) before to branch to application main.
  *  To reconfigure the default setting of SystemInit() function, refer to
  *  system_stm32l1xx.c file
  */
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);  // Zapnutie hodin na periferii
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC,ENABLE);   // Zapnutie hodin na periferii

   GPIOA->MODER |=(0b01)<<(10);   // nastavenie modu na vystup
   GPIOA->OTYPER &=~((1)<<5);
   GPIOA->PUPDR |=(0b01)<<(10);
   GPIOA->OSPEEDR |=(0b11)<<(10);

   GPIOC->MODER |= ((0b00)<<(26));   // nastavenie modu na vystup
   GPIOC->OTYPER &= ~((0b1)<<13);
   GPIOC->PUPDR |= ((0b00)<<(26));   // nastavenie UP

  /* TODO - Add your application code here */

   //uloha1
GPIOA->ODR |=1<<5;   // zasvietenie LED

GPIOA->ODR &=~((1)<<5);  // Zhasnutie led


GPIOA->BSRRL |=1<<5;       // nastavenie High

GPIOA->BSRRH |=(1<<5);     // nastavenie low

GPIOA->BSRRL |=1<<5;     // nastavenie high


int impulz=0;


  /* Infinite loop */
  while (1)
  {   //uloha1-1
/*
	  if(GPIOA->ODR & ((uint32_t)(1<<5)) )     // zistenie ci je led zapnuta alebo nie
	  {
		  GPIOA->ODR &=~((1)<<5);                // ak ano zhasni

	  }

	  //delay(10000);
	  else{

		  GPIOA->ODR |=1<<5;                  // ak nie zasviet

	  }

	  for(int i=0;i<1000000;i++){             // pauza na blikanie

	 	  }

	 	  */


	  //uloha2

	  if(GPIOC->IDR & ((uint32_t)(1<<13))){     // precitanie stavu tlacidla
	  		button=0 ;                           // nestlacene
	  }
	  	else{
	  		button=1;                             //stlacene
	  	}

   //uloha3-1         blikanie LED
/*
	  for(int i=0;i<1000000;i++){

	  }
	  GPIOA->ODR |=1<<5;

	  for(int i=0;i<1000000;i++){

	  }
	  GPIOA->ODR &=~((1)<<5);
*/
/*
	  //uloha3-2                                 // svietenie podla stlacenia tlacidla
	  if (button==1){GPIOA->ODR |=1<<5;}
	  if(button==0){ GPIOA->ODR &=~((1)<<5);}


	  //uloha3-3                 ///prepinanie stavu LED pomocou tlacidla
*/

	  if(button==1){

		  impulz=impulz+1;
		  if(impulz>=10){              // iba ak je stlacene nad 10 impulzov
			  if(GPIOA->ODR & ((uint32_t)(1<<5)) ){              // zistenie ci je led zapnuta alebo nie
				  GPIOA->ODR &=~((1)<<5);

			  }
			  else{
				  GPIOA->ODR |=1<<5;

			  }
		  }
	  }

	  if(button==0){impulz=0;}       // vynulovanie pocitadl impulzov po uvolneni tlacidla

  }
  return 0;
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/*
 * Minimal __assert_func used by the assert() macro
 * */
void __assert_func(const char *file, int line, const char *func, const char *failedexpr)
{
  while(1)
  {}
}

/*
 * Minimal __assert() uses __assert__func()
 * */
void __assert(const char *file, int line, const char *failedexpr)
{
   __assert_func (file, line, NULL, failedexpr);
}
