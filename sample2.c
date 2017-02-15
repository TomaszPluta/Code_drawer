

#include "stm32f10x.h"

void GPIO_Config(void);
void RCC_Config(void);
void NVIC_Config(void);
void USART_Config(void);



unsigned char buforTx[256];
unsigned char buforRx[256];
int bufTxIndex =0;
int bufRxIndex = 0;



int received;
int test;
int main(void){
  volatile unsigned long int i;
  unsigned int stanPrzyciskow = 56;

  //konfiguracja systemu
  RCC_Config();
  GPIO_Config();

  USART_Config();
//  DMA_Config();
//  DMA_ConfigRx();

	GLCD_Initialize();
	GLCD_ClearScreen();
	GLCD_GoTo(0, 0);
	GLCD_WriteString("ok");



	  NVIC_Config();


int g=0;
char rec;

  while (1) {


 if ((USART1->SR & USART_FLAG_RXNE) != 0){
	 rec = USART_ReceiveData(USART1);
 }
 if (rec > 0)
 {
	 USART_SendData(USART1, rec);
	 GLCD_ClearScreen();
	 GLCD_GoTo(0, 2);
	 GLCD_WriteChar(rec);
	 rec =0;
 }





    for (i=0; i<4000000; i++);


  };
  return 0;
}





void RCC_Config(void)
{
  ErrorStatus HSEStartUpStatus;  //zmienna opisujaca rezultat uruchomienia HSE

  RCC_DeInit();	                                         //Reset ustawien RCC
  RCC_HSEConfig(RCC_HSE_ON);                             //Wlaczenie HSE
  HSEStartUpStatus = RCC_WaitForHSEStartUp();		         //Odczekaj az HSE bedzie gotowy
  if(HSEStartUpStatus == SUCCESS)
  {
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);//
    FLASH_SetLatency(FLASH_Latency_2);                   //ustaw zwloke dla pamieci Flash; zaleznie od taktowania rdzenia
	                                                       //0:<24MHz; 1:24~48MHz; 2:>48MHz
    RCC_HCLKConfig(RCC_SYSCLK_Div1);                     //ustaw HCLK=SYSCLK
    RCC_PCLK2Config(RCC_HCLK_Div1); 					           //ustaw PCLK2=HCLK
    RCC_PCLK1Config(RCC_HCLK_Div2);					             //ustaw PCLK1=HCLK/2
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9); //ustaw PLLCLK = HSE*9 czyli 8MHz * 9 = 72 MHz
    RCC_PLLCmd(ENABLE);                                  //wlacz PLL
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);  //odczekaj na poprawne uruchomienie PLL
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);           //ustaw PLL jako zrodlo sygnalu zegarowego
    while(RCC_GetSYSCLKSource() != 0x08);                //odczekaj az PLL bedzie sygnalem zegarowym systemu

	/*Tu nalezy umiescic kod zwiazny z konfiguracja sygnalow zegarowych potrzebnych w programie peryferiow*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//wlacz taktowanie portu GPIO A
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//wlacz taktowanie portu GPIO B
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);//wlacz taktowanie USART1

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);   //wlacz taktowanie DMA
	//RCC_AHBPeriphClockCmd(DMA1_Channel5, ENABLE); zle?????

  } else {
  }
}

void NVIC_Config(void)
{
  //Konfigurowanie kontrolera przerwan NVIC
//
//#ifdef  VECT_TAB_RAM
//  // Jezeli tablica wektorow w RAM, to ustaw jej adres na 0x20000000
//  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0);
//#else  // VECT_TAB_FLASH
//  // W przeciwnym wypadku ustaw na 0x08000000
//  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
//#endif
//
//

//  NVIC_InitTypeDef NVIC_InitStructure;
//  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
//  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  NVIC_Init(&NVIC_InitStructure);

	NVIC_EnableIRQ(USART1_IRQn);

}


void GPIO_Config(void)
{
  //konfigurowanie portow GPIO
  GPIO_InitTypeDef  GPIO_InitStructure;

  /*Tu nalezy umiescic kod zwiazany z konfiguracja poszczegolnych portow GPIO potrzebnych w programie*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  //PA0-3 - Przyciski
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  //PA9 - Tx
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);

 	//PA10 - Rx
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);


     //PORTC - Wyświetlacz
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
      GPIO_Init(GPIOC, &GPIO_InitStructure);


}


void USART_Config(void)
{
  //konfigurowanie ukladu USART
  USART_InitTypeDef  USART_InitStructure;

  USART_InitStructure.USART_BaudRate = 9600;                                      //Predkosc transmisji =9600bps
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;                     //Dlugosc slowa = 8 bitow
  USART_InitStructure.USART_StopBits = USART_StopBits_1;                          //1 bit stopu
  USART_InitStructure.USART_Parity = USART_Parity_No;                             //Brak kontroli parzystosci
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //Kontrola przeplywu danych (brak)
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	                //Tryb pracy
	USART_Init(USART1, &USART_InitStructure);


//	USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
//	USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);

//	  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
//	  USART_ITConfig(USART1, USART_IT_TC, ENABLE);
	  USART_Cmd(USART1, ENABLE);
}











void USART1_IRQHandler(void)
{
  if(USART_GetITStatus(USART1, USART_IT_TC) != RESET) {
		GLCD_GoTo(0, 1);
		GLCD_WriteString("TCE");
  }

  if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET) {
		GLCD_GoTo(0, 2);
		GLCD_WriteString("TXE");
  }



  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
		GLCD_GoTo(0, 2);
		GLCD_WriteString("TXE");
  }

  USART1->SR &= ~USART_FLAG_RXNE;

  USART1->SR &= ~USART_FLAG_TXE;

  USART1->SR &= ~USART_FLAG_TC;


}
