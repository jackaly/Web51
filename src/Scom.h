#ifndef __SCOM_H__
#define __SCOM_H__

#define _12M_9600_  1
//12M 9600
#ifdef _12M_9600_
#define RH 0xFF
#define RL 0xd9
#endif
//20M 9600
#ifdef _20M_9600_
#define RH 0xFF
#define RL 0xBF
#endif

#define MAXSBUFSIZE  12
#define MAXRBUFSIZE  12

#define COM_HDR_LEN  2

//Output Buf stat: has_data and no_data
#define HASDAT  0
#define NODAT   1

// The Com datastring stat_flag and end_flag
#define SYN 0xAA
#define FIN 0x55

//The stat for COM recieve
#define WAIT_STAT	0x01
#define SYN_STAT	0x02
#define DAT_STAT	0x04
#define FIN_STAT	0x08

struct comhdr {
            unsigned char syn;
            unsigned char len;
         };
typedef struct comhdr com_hdr;

struct comfin { 
            unsigned char fin;
		 };
typedef struct comfin com_fin;

struct comdata { 
           unsigned char ch;
           unsigned char stat;
        };
typedef struct comdata com_data;

extern unsigned char com_outflag;
extern unsigned char com_recvstat;
extern unsigned char com_len;
extern unsigned char com_i;
extern unsigned char com_datalen;
extern unsigned char usbuf[MAXSBUFSIZE];
extern unsigned char urbuf[MAXRBUFSIZE];

#define USHDR ((com_hdr data*)&usbuf[0] )
#define URHDR ((com_hdr data*)&usbuf[0] )
#define USFIN ((com_fin data*)&usbuf[COM_HDR_LEN+2] )
#define USBUF ((com_data data*)&usbuf[COM_HDR_LEN] )
#define URBUF ((com_data data*)&urbuf[COM_HDR_LEN] )
 
/*============================================*/
extern void com_init(void);
extern void com_send(void);
extern void com_sendchar(unsigned char scom);
extern void com_output(void);
extern void com_recv(void);
/*=============================================*/
#endif
