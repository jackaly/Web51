/*******************************
*  Create by Jackaly
*  Date: 2003 01 01 
*  Ver 0.1
*********************************/

//#include <REG54.H>
//#include "w78e52.h"
#include "const.h"
#include "sja1000.h"

uchar Txdata[13];
uchar Rxdata[13];

uchar sja_acr[4];
uchar sja_amr[4];

void initialzation( void ) reentrant using 0
{
      
      
   while( (ModeControlReg & RM_RR_Bit) == 0x00)   // waiting RM_RR_Bit set£¬Reset model
   {
      ModeControlReg = ModeControlReg |  RM_RR_Bit;
   }
    
    InterruptEnReg = 0x00;   // clear Interrupt Enable Reg */
   
    // Output Control Register  Can[8] */
    OutControlReg = NormalMode | Tx1Float | Tx0PshPull; /* TX1£ºfloat; Tx0: push_pull; normal Output Mode */
    /* Dlock Divider Register can[31] */
    ClockDivideReg = CANMode_Bit | CLKOff_Bit | CBP_Bit | DivBy2; /* PeliCAN Mode ,clost ClkOut£¬INTEL mode */

    /* Bus Timing Register 0/1  Can[6] Can[7]*/
    /* 25kbit/s,  12MHz , The Bus is Sampled three times*/
    BusTiming0Reg = SJWExample | PrescExample;
    BusTiming1Reg = TSEG1Example | TSEG2Example | SAM_Bit;
    
    /*Accept Code Register and Accept Mask register Can[16]--Can[23]*/
    AcceptCode0Reg = sja_acr[0];
    AcceptCode1Reg = sja_acr[1];
    AcceptCode2Reg = sja_acr[2];
    AcceptCode3Reg = sja_acr[3];
    AcceptMask0Reg = sja_amr[0]; 
    AcceptMask1Reg = sja_amr[1]; 
    AcceptMask2Reg = sja_amr[2]; 
    AcceptMask3Reg = sja_amr[3]; 
    
    /* Interrupt Enable Register Can[4]*/
    InterruptEnReg = RIE_Bit;  /* Enable Receive Interrupt*/
    CommandReg = RRB_Bit;      // Release Reveice Buffer
    do /* Waiting RM_RR_Bit Clear */       
    {
       ModeControlReg = 0x00;       /* Mode Control Register Set : Normal mode and Dual Acceptance Filter*/
    }while((ModeControlReg & RM_RR_Bit) != 0x00);
     
     //Sja_cs = Disable_N; /*SJA1000 Disable*/
     //EA = Enable; /* Enable All Mcu Interrupt */
}

void transmit( void ) reentrant using 0
{
  //Sja_cs = Enable_N; /*  SJA1000 Enabel */
  //led = 1;
  do{ 
    } while((StatusReg & TBS_Bit) != TBS_Bit);
  
  TxFramInfo = Txdata[0];  
  TxBuffer1 = Txdata[1];
  TxBuffer2 = Txdata[2];
  TxBuffer3 = Txdata[3]; 
  TxBuffer4 = Txdata[4];
  TxBuffer5 = Txdata[5];
  TxBuffer6 = Txdata[6];
  TxBuffer7 = Txdata[7];
  TxBuffer8 = Txdata[8];
  TxBuffer9 = Txdata[9];
  TxBuffer10 = Txdata[10];
  TxBuffer11 = Txdata[11];
  TxBuffer12 = Txdata[12];
   
  CommandReg = TR_Bit;/* Request send Data */
  //Sja_cs = Disable_N; /*  SJA1000 Disable */
}

uchar receive(void) reentrant using 0
{
 
  //Sja_cs = Enable_N;             /* SJA1000 Enable */
  if (StatusReg & RBS_Bit)
  {
          
       Rxdata[0] = RxFramInfo;
       Rxdata[1] = RxBuffer1;
       Rxdata[2] = RxBuffer2;
       Rxdata[3] = RxBuffer3;
       Rxdata[4] = RxBuffer4;
	   Rxdata[5] = RxBuffer5;
	   Rxdata[6] = RxBuffer6;
	   Rxdata[7] = RxBuffer7;
	   Rxdata[8] = RxBuffer8;
	   Rxdata[9] = RxBuffer9;
	   Rxdata[10] = RxBuffer10;
	   Rxdata[11] = RxBuffer11;
	   Rxdata[12] = RxBuffer12;
          
       CommandReg = RRB_Bit;
       return 0;

   } else {
          
          CommandReg = RRB_Bit | CDO_Bit;
          return 1;
   } 
   //Sja_cs = Disable_N; 
}


