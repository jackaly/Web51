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

  eth_reset = 1; //使网卡的RSTDRV引脚变成高电平，网卡是高电平复位的。
  for(i = 0; i < 250; i++);//延时程序，至少需要
  eth_reset = 0; //使网卡的RSTDRV引脚变成低电平，网卡上电复位完毕
  for(i = 0; i < 250; i++);
  temp = RESET;//读网卡的复位端口
  RESET = temp; //写网卡的复位端口
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
   CR = 0x21; //选择页0 的寄存器网卡停止运行因为还没有初始化
   delay_ms(10); //延时10 毫秒,确保芯片进入停止模式
   //使芯片处于mon 和loopback 模式,跟外部网络断开
   page(0);
   RBCR0 = 0x00;
   RBCR1 = 0x00;
   RCR = 0xE0; //monitor mode (no packet receive)
   TCR = 0xE2; //loop back mode
   //使用0x40-0x4B 为网卡的发送缓冲区共12 页刚好可以存储2 个最大的以太网包
   //使用0x4c 0x7f 为网卡的接收缓冲区共52 页
   PSTART = 0x4C; //Pstart 接收缓冲区范围
   PSTOP = 0x80; //Pstop
   BNRY = 0x4C; //BNRY
   TPSR = 0x40; //TPSR 发送缓冲区范围
   ISR = 0xFF;/*清除所有中断标志位*/
   IMR = 0x00;//IMR disable all interrupt
   DCR = 0xC8; //DCR byte dma 8 位dma 方式
   page(1); //选择页1 的寄存器
   CURR = 0x4D; //CURR
   MAR0 = 0xFF; //MAR0
   MAR1 = 0xFF; //MAR1
   MAR2 = 0xFF; //MAR2
   MAR3 = 0xFF; //MAR3
   MAR4 = 0xFF; //MAR4
   MAR5 = 0xFF; //MAR5
   MAR6 = 0xFF; //MAR6
   MAR7 = 0xFF; //MAR7
   set_mac();//初始化MAC 地址和网络相关参数
   //将网卡设置成正常的模式,跟外部网络连接
   page(0);
   RCR = 0xCC; //RCR
   TCR = 0xE0; //TCR
   CR = 0x22; //这时让芯片开始工作?
   ISR = 0xFF; //清除所有中断标志位
}

void send_packet(unsigned char *buf, unsigned int length)   small//ne2000 发包子程序
{    //发送一个数据包的命令,长度最小为60 字节,最大1514 字节需要发送的数据包要先存放在
     // txdnet 缓冲区
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
  for(i = 0; i < 6; i++){ //最多重发6 次
     for(ii = 0; ii < 1000; ii++) //检查txp 为是否为低
       if((CR & 0x04)==0) break;
     if((TSR & 0x01)!=0){
 	     break; //表示发送成功
	 }
     CR = 0x3E;
  }
  
}

unsigned int recv_packet(unsigned char *buf) small//ne2000 收包子程序 
{
   unsigned char i;
   unsigned int ii;
   unsigned int length;
   unsigned char bnry,curr;

   page(0);
   ISR = 0xFF;
   bnry = BNRY; //bnry page have read 读页指针
//comsendchar(bnry);
   page(1);
   curr = CURR; //curr writepoint 8019 写页指针
   page(0);
   if(curr == 0){
      return 0; //读的过程出错
   }
   bnry = bnry++;
   if(bnry > 0x7F) 
     bnry = 0x4C;
//comsendchar(bnry);
//comsendchar(curr);
   if(bnry != curr){ //此时表示有新的数据包在缓冲区里
         //读取一包的前18 个字节:4 字节的8019 头部,6 字节目的地址,6 字节原地址,2 字节协议
         //在任何操作都最好返回page0
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
      //length = length-4; //去掉4 个字节的CRC
      //表示读入的数据包有效
      if(((buf[0] & 0x01)==0)||(buf[1] > 0x7F)||(buf[1] < 0x4C)||(buf[3] > 0x06)){   
	               //接收状态错误,或者next_page_start 错误或者长度错误,将丢弃所有数据包
           page(1);
           curr = CURR; //page1
           page(0); //切换回page0
           bnry = curr-1;
           if(bnry < 0x4C) 
               bnry = 0x7F;
           BNRY = bnry; //write to bnry
		   //comsend("errpacket ");
           return 0;
      }
      else{      //表示数据包是完好的.读取剩下的数据
         if( (((buf[16]<<8)+buf[17]) == 0x0800)||(((buf[16]<<8)+buf[17]) == 0x0806)){
              //协议为IP 或ARP 才接收
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
		 // 将丢弃所有数据包
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
