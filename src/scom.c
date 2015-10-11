/*******************************
*  Create by Jackaly
*  Date: 2003 01 01 
*  Ver 0.1
*********************************/

#include <REG54.H>
#include "scom.h"

// output flag
unsigned char com_outflag;
unsigned char com_recvstat;
unsigned char com_len;
unsigned char com_i;
unsigned char com_datalen;
unsigned char usbuf[MAXSBUFSIZE];
unsigned char urbuf[MAXRBUFSIZE];

//unsigned char *urappdata;

void com_init(void)
{
  /* //12M 4800
     TH1 = 0xf3;
	 TL1 = 0xf3;
	 TMOD = 0x20;

	 SCON = 0x50;
	 PCON = 0x80;
  */
  //20M 9600  0xFFBF
  RCAP2H = RH;
  RCAP2L = RL;
  TH2 = RH;
  TL2 = RL;
  T2CON = 0x34; //star timer2
  SCON = 0x50;
  com_recvstat = WAIT_STAT;
  com_len = 0;
  com_i = COM_HDR_LEN;
}

void com_sendchar(unsigned char scom)
{
   //TR2 = 1;
   SBUF = scom;
   while(TI == 0);
   TI = 0;
   //TR2 = 0;
}

void com_send(void)
{
   unsigned char i;
   //TR2 = 1;
   while(usbuf[i]){
     SBUF = usbuf[i];
	 while(TI == 0);
     TI = 0;
	 i++;
     if ( i > (MAXSBUFSIZE-1) ){
       //TR2 = 0;
       return;
     }
   }
   //TR2 = 0;
}


void com_recv(void)
{
   unsigned char c;
   //TR2 = 1;
   //while(RI == 0);
   if (RI == 1) {
      c = SBUF;
      switch( com_recvstat) {
 	    case WAIT_STAT: {
		    if ( c == SYN ){
			   com_recvstat = SYN_STAT;
               URHDR->syn = c;
            }
        } break;
		case SYN_STAT: {
		    if ( c < MAXRBUFSIZE ){
		        com_len = c;				
			}else {
			    com_len = MAXRBUFSIZE ;
			}
			com_recvstat = DAT_STAT;
			URHDR->len = com_len;
        } break;
		case DAT_STAT: {
          if( com_i < com_len ){
 	        if ( c!=0x55){   
			      urbuf[com_i] = c ;
			      com_i++ ;
		    }
			else {
			      com_recvstat = FIN_STAT;
  			      com_i = COM_HDR_LEN;
			      com_len = 0;
		    }
          }
		  else {
               com_recvstat = FIN_STAT;
  			   com_i = COM_HDR_LEN;
			   com_len = 0;
		  }                  
		} break;

	  } //end switch 
	} //end if
	RI = 0;
}

void com_output(void)
{
  USHDR->syn = SYN;
  USHDR->len = COM_HDR_LEN+com_datalen; 
  USFIN->fin = FIN;
  com_send();
}			   
		     


