#ifndef __SCOM_H__
#define __SCOM_H__

//12M 9600

#define RH 0xFF
#define RL 0xd9

extern void cominit(void);
extern void comsend(unsigned char s[]) small;
extern void comsendchar(unsigned char scom) small;

#endif
