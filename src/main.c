/*******************************
*  Create by Jackaly
*  Date: 2003 01 01 
*  Ver 0.1
*********************************/

#include <REG54.H>
#include <stdio.h>
#include "const.h"
#include "C51init.h" 
#include "net_drv.h"
#include "uip.h"
#include "uip_arp.h"
#include "scom.h"
#include "apptest.h"

#define BUF ((struct uip_eth_hdr *)&uip_buf[0])

const unsigned int serverip[2] = { HTONS((192<<8)|168),
                                   HTONS((0<<8)|7)
                                 };
/*the COM functions
extern void com_init(void);
extern void com_send(void);
extern void com_sendchar(unsigned char scom);
extern void com_output(void);
extern void com_recv(void);
*/

void main(void)
{

  unsigned int i;
  unsigned char arptimer;
  struct uip_conn* conn;
  for (i = 0; i < 10000; i++);  // Waiting Other Device Reset;  About 125ms  
  
  // W78e52 and sja1000 initialzation
  IE = 0x00;   // Disable All interrupt   
  //PX0 = HIGH; // Expand Interrupt 0 is Priority_High
  PX1 = HIGH;
  IE1 = Int_Edge_Act; //Int1 is Edge flag;
  LED0 = 0;
  LED1 = 0;
  //CHPENR = 0x87;
  //CHPENR = 0x59;
  //CHPCON = 0x10;
  //CHPENR = 0x00;
  
  com_init();
  
  rtl8019_init();
  LED1=~LED1;
  //comsend("8019iniend\n");
  uip_arp_init(); 
  
  
  uip_init();
  app_init();
  //comsend("running\n");
  LED0 =~LED0;
  EA = ENABLE;         // All Interrupt Will Enable  
  ES = ENABLE;
  uip_listen(HTONS(2345));
  
  arptimer = 0;
/*==========*/
  while(1) {
      if ( com_recvstat == FIN_STAT){
         if(state.connstat == WEBCLOST){
		   conn = uip_connect(&serverip,HTONS(12345));
  		   if (conn != NULL ){
		     state.connstat = WEBCONNECT;
			 S->connstat = WEBCONNECT;

		   }
         }
       
      }
    
      //The TCP/IP program
      uip_len = recv_packet(&uip_buf);	  
      if(uip_len == 0) {
          for(i = 0; i < UIP_CONNS; i++) {
             uip_periodic(i);
			 //comsend("periodic ");
	         if(uip_len > 0) {
	             uip_arp_out();
	             send_packet(&uip_buf, uip_len);
	         }
          }
      // Call the ARP timer function every 10 seconds. 
       if(++arptimer == 20) {	
	         uip_arp_timer();
	         arptimer = 0;
         }
      
      } 
	  
	  else {
	       
           if(BUF->type == htons(UIP_ETHTYPE_IP)) {
	           uip_arp_ipin();
	           uip_input();
	           //comsend("uip_input ");
	          if(uip_len > 0) {
	               uip_arp_out();
	               send_packet(&uip_buf, uip_len);
				   //comsend("u_sent ");
	          }
           } else if(BUF->type == htons(UIP_ETHTYPE_ARP)) {
                 //comsend("arp_in ");
	             uip_arp_arpin();				 
	             if(uip_len > 0) {
				      send_packet(&uip_buf, uip_len);
					  //comsend("a_sent ");
	             }
           }// end if(BUF->type....
      }// end if(uip_len == 0)....else...   
                 
  } // end while(1)
/*========*/
} 

void com_rec_int (void) interrupt 4 using 0
{
  
  EA = DISABLE;
  com_recv();
  EA = ENABLE;
}

    
