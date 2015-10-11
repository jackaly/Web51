
#ifndef _APPTEST_H_
#define _APPTEST_H_
#include "uip.h"
/*
struct apptest_state {
   enum {WELCOME_SENT, WELCOME_ACKED} state;
};  
*/


#define WEBCONNECT  0
#define WEBCLOST	1

struct appstat {
                  unsigned char connstat;
               };

extern struct appstat state;
//extern struct appstat *s;

#define S  ((struct appstat *)(uip_conn->appstate))

#ifndef UIP_APPSTATE_SIZE
  #define UIP_APPSTATE_SIZE (sizeof(struct appstat))
#endif

void app_init(void);
void appcall(void);


#define UIP_APPCALL   appcall


#endif
