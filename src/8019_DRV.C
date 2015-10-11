/*
  
/*******************************
*  eth_8019 drv
*  Create by Jackaly
*  Date: 2003 01 01 
*  Ver 0.1
*********************************/
*/  
#include <REG54.H>
#include "C51init.h"
#include "scom.h"
#include "net_drv.h"


unsigned char data txbuf_select = 0;

void rst()
{
  unsigned int data i;
  unsigned char data temp;

  eth_reset = 1; //ʹ������RSTDRV���ű�ɸߵ�ƽ�������Ǹߵ�ƽ��λ�ġ�
  for(i = 0; i < 250; i++);//��ʱ����������Ҫ
  eth_reset = 0; //ʹ������RSTDRV���ű�ɵ͵�ƽ�������ϵ縴λ���
  for(i = 0; i < 250; i++);
  temp = RESET;//�������ĸ�λ�˿�
  RESET = temp; //д�����ĸ�λ�˿�
  for( i = 0; i < 250; i++); 
}

void page(unsigned char pagenumber)
{ 
   unsigned char data temp; 
   temp = CR ;                   //command register 
   temp = temp & 0x3b;
   pagenumber = pagenumber << 6; 
   temp = temp | pagenumber;
   CR = temp;
}

void set_mac()

{ 
   page(1);

   PAR0 = ETHADDR0; //PAR0
   PAR1 = ETHADDR1; //PAR1
   PAR2 = ETHADDR2; //PAR2
   PAR3 = ETHADDR3; //PAR3
   PAR4 = ETHADDR4; //PAR4
   PAR5 = ETHADDR5; //PAR5

}

delay_ms(unsigned int ms)
{
  unsigned int i, n;
  n = ms * 100;
  for (i = 0; i < n; i++);
} 

void rtl8019_init(void)   small    // 8019 init
{
   
   rst();
   CR = 0x21; //ѡ��ҳ0 �ļĴ�������ֹͣ������Ϊ��û�г�ʼ��
   delay_ms(10); //��ʱ10 ����,ȷ��оƬ����ֹͣģʽ
   //ʹоƬ����mon ��loopback ģʽ,���ⲿ����Ͽ�
   page(0);
   RBCR0 = 0x00;
   RBCR1 = 0x00;
   RCR = 0xE0; //monitor mode (no packet receive)
   TCR = 0xE2; //loop back mode
   //ʹ��0x40-0x4B Ϊ�����ķ��ͻ�������12 ҳ�պÿ��Դ洢2 ��������̫����
   //ʹ��0x4c 0x7f Ϊ�����Ľ��ջ�������52 ҳ
   PSTART = 0x4C; //Pstart ���ջ�������Χ
   PSTOP = 0x80; //Pstop
   BNRY = 0x4C; //BNRY
   TPSR = 0x40; //TPSR ���ͻ�������Χ
   ISR = 0xFF;/*��������жϱ�־λ*/
   IMR = 0x00;//IMR disable all interrupt
   DCR = 0xC8; //DCR byte dma 8 λdma ��ʽ
   page(1); //ѡ��ҳ1 �ļĴ���
   CURR = 0x4D; //CURR
   MAR0 = 0xFF; //MAR0
   MAR1 = 0xFF; //MAR1
   MAR2 = 0xFF; //MAR2
   MAR3 = 0xFF; //MAR3
   MAR4 = 0xFF; //MAR4
   MAR5 = 0xFF; //MAR5
   MAR6 = 0xFF; //MAR6
   MAR7 = 0xFF; //MAR7
   set_mac();//��ʼ��MAC ��ַ��������ز���
   //���������ó�������ģʽ,���ⲿ��������
   page(0);
   RCR = 0xCC; //RCR
   TCR = 0xE0; //TCR
   CR = 0x22; //��ʱ��оƬ��ʼ����?
   ISR = 0xFF; //��������жϱ�־λ
}

void send_packet(unsigned char *buf, unsigned int length)   small//ne2000 �����ӳ���
{    //����һ�����ݰ�������,������СΪ60 �ֽ�,���1514 �ֽ���Ҫ���͵����ݰ�Ҫ�ȴ����
     // txdnet ������
  unsigned char data i;
  unsigned int data ii;
  
  page(0);
  if(length < 60) 
      length = 60;
/*==========================
  for(i=0; i<length; i++){
	comsendchar(buf[i]);
  }
==========================*/
  txbuf_select=!txbuf_select;
  if(txbuf_select)
     RSAR1 = 0x40 ; //txdwrite highaddress
  else
     RSAR1 = 0x46 ; //txdwrite highaddress
  RSAR0 = 0x00; //read page address low
  RBCR1 = length>>8; //read count high
  RBCR0 = length&0xFF; //read count low;
  CR = 0x12; //write dma, page0
  for(ii = 0; ii < length; ii++)  //Write Remote DMA
     DMA_DATA = buf[ii];

  if(txbuf_select) 
     TPSR = 0x40; //txd packet start;
  else TPSR = 0x46; //txd packet start;
  TBCR1 = length>>8; //high byte counter
  TBCR0 = length&0xFF; //low byte counter
  CR = 0x3E; //to sendpacket;
  for(i = 0; i < 6; i++){ //����ط�6 ��
     for(ii = 0; ii < 1000; ii++) //���txp Ϊ�Ƿ�Ϊ��
       if((CR & 0x04)==0) break;
     if((TSR & 0x01)!=0){
 	     break; //��ʾ���ͳɹ�
	 }
     CR = 0x3E;
  }
  
}

unsigned int recv_packet(unsigned char *buf) small//ne2000 �հ��ӳ��� 
{
   unsigned char i;
   unsigned int ii;
   unsigned int length;
   unsigned char bnry,curr;

   page(0);
   ISR = 0xFF;
   bnry = BNRY; //bnry page have read ��ҳָ��
//comsendchar(bnry);
   page(1);
   curr = CURR; //curr writepoint 8019 дҳָ��
   page(0);
   if(curr == 0){
      return 0; //���Ĺ��̳���
   }
   bnry = bnry++;
   if(bnry > 0x7F) 
     bnry = 0x4C;
//comsendchar(bnry);
//comsendchar(curr);
   if(bnry != curr){ //��ʱ��ʾ���µ����ݰ��ڻ�������
         //��ȡһ����ǰ18 ���ֽ�:4 �ֽڵ�8019 ͷ��,6 �ֽ�Ŀ�ĵ�ַ,6 �ֽ�ԭ��ַ,2 �ֽ�Э��
         //���κβ�������÷���page0
      page(0);
      RSAR1 = bnry; //read page address high
      RSAR0 = 0x00; //read page address low
      RBCR1 = 0x00; //read count high
      RBCR0 = 18; //read count low;
      CR = 0x0A; //read dma
      for(i = 0; i < 18; i++)
         buf[i] = DMA_DATA;
	  
	  length = (unsigned int)(buf[3]<<8) + buf[2] - 4;
	  //pkt_len = (word)(ethernet_8390_hdr[3]<<8) + ethernet_8390_hdr[2] - 4
      //length =buf[3]<<8 + buf[2];
      //length = length-4; //ȥ��4 ���ֽڵ�CRC
      //��ʾ��������ݰ���Ч
      if(((buf[0] & 0x01)==0)||(buf[1] > 0x7F)||(buf[1] < 0x4C)||(buf[3] > 0x06)){   
	               //����״̬����,����next_page_start ������߳��ȴ���,�������������ݰ�
           page(1);
           curr = CURR; //page1
           page(0); //�л���page0
           bnry = curr-1;
           if(bnry < 0x4C) 
               bnry = 0x7F;
           BNRY = bnry; //write to bnry
		   //comsend("errpacket ");
           return 0;
      }
      else{      //��ʾ���ݰ�����õ�.��ȡʣ�µ�����
         if( (((buf[16]<<8)+buf[17]) == 0x0800)||(((buf[16]<<8)+buf[17]) == 0x0806)){
              //Э��ΪIP ��ARP �Ž���
             RSAR1 = bnry; //read page address high
             RSAR0 = 4; //read page address low
             RBCR1 = (unsigned char)length >> 8; //read count high
             RBCR0 = (unsigned char)length & 0xFF; //read count low;
             CR = 0x0A; //read dma
             for(ii = 0; ii < length; ii++){
                   buf[ii] = DMA_DATA;
			 }
			 /*========================
             for(i=0; i<length; i++){
		       comsendchar(buf[i]);
		     }
			 =========================*/
			 bnry = curr-1;//next page start-1
             if( bnry < 0x4C) 
                bnry = 0x7F;
             BNRY = bnry; //write to bnry
             return length ; //have new packet
         }
		 // �������������ݰ�
         bnry = curr-1;//next page start-1
         if( bnry < 0x4C) 
             bnry = 0x7F;
         BNRY = bnry; //write to bnry
		 //comsend("notIP ");
         return 0; //have new packet
      }
   }
   //comsend("brny==curr ");
   return 0;
}

/*uchar *sed_FormatPacket( BYTE *destEAddr, WORD ethType )
{
	Move( destEAddr, txbuf, 6 );     //*	Make a destination address 
	Move( sed_lclEthAddr, txbuf+6, 6 ); //* Make a source address 

	*(WORD *)(EthTxBuf+12) = ethType;	//*	Make a Ethertype	
	return ( EthTxBuf+14 );
}*/