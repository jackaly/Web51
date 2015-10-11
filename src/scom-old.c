#include "scom.h"
#include <REG54.H>

void cominit(void)
{
  /* 12M 4800
     TH1 = 0xf3;
	 TL1 = 0xf3;
	 TMOD = 0x20;

	 SCON = 0x50;
	 PCON = 0x80;
  */
  // 12M 9600 0xFFD9
  //20M 9600  0xFFBF
  RCAP2H = 0xff;
  RCAP2L = 0xBF;
  TH2 = 0xFF;
  TL2 = 0xBF;
  T2CON = 0x30;
  SCON = 0x50;
}


void comsend(unsigned char scom[50]) small
{
   unsigned char i;
   //unsigned char data scom[50];
   
   TR2 = 1;
   //scom[50] = s[50];
   i = 0;
   while(scom[i]!=0x00){
     SBUF = scom[i];
	 while(TI == 0);
     TI = 0;
	 i++;
   }
   TR2 = 0;
}

void comsendchar(unsigned char scom) small
{
   TR2 = 1;
   SBUF = scom;
   while(TI == 0);
   TI = 0;
   TR2 = 0;
}


