/*******************************
*  Create by Jackaly
*  Date: 2003 01 01 
*  Ver 0.1
*********************************/


#include "uip.h"
/*===================================================
#include "apptest.h"

void apptest(void) {
  struct apptest_state *s;
  s = (struct apptest_state *)uip_conn->appstate;
  if(uip_connected()) {
     s->state = WELCOME_SENT;
     uip_send("Welcome!\n", 9);
     return;
  }
  if(uip_acked() && s->state == WELCOME_SENT) {
     s->state = WELCOME_ACKED;
  }
  if(uip_newdata()) {
     uip_send("ok\n", 3);
  }
  if(uip_rexmit()) {
     switch(s->state) {
       case WELCOME_SENT:
            uip_send("Welcome!\n", 9);
            break;
       case WELCOME_ACKED:
            uip_send("ok\n", 3);
            break;
	 }
   }
}

=========================================================*/

#include "scom.h"
#include "apptest.h"


struct appstat state;


void app_init()
{
  state.connstat = WEBCLOST;
}


void appcall(void)
{
  //register struct uip_conn *connr = uip_conn;
  

  unsigned char i; 
 
  if( uip_connected()){
     if( S->connstat == WEBCONNECT){
        uip_send(&urbuf,(urbuf[1]+1));
		S->connstat = WEBCLOST;
     }
  }
  if(uip_rexmit()){
      uip_send(&urbuf,(urbuf[1]+1));
  }
  if(uip_closed()){
    if( S->connstat == WEBCONNECT){
        S->connstat = WEBCLOST;
	}
  }
  if( uip_newdata() ){
    if( uip_len >(MAXSBUFSIZE-COM_HDR_LEN-1)) 
	   com_datalen = MAXSBUFSIZE - COM_HDR_LEN -1;
	else com_datalen = uip_len;
    for( i=0; i<com_datalen; i++){
       usbuf[i+COM_HDR_LEN]= uip_appdata[i];       
    }	
    com_output(); 
  }
}
        
    
   





