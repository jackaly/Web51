
#define XBYTE ((unsigned char volatile xdata*) 0)

/* a few useful Ethernet definitions. */
#define     BUFSIZ          1600
#define     NBUF            10
#define     MIN_PACKET_SIZE 60      /* smallest legal size packet, no fcs    */
#define     MAX_PACKET_SIZE 1514	/* largest legal size packet, no fcs     */
#define     ETHER_ADDR_LEN	6   /* Etherne;a few useful Ethernet definitions.*/

#define     TX_PAGES	    12       
#define     START_PG	    0x40     	/* First page of TX buffer           */
#define		TX_START_PG		START_PG
#define     STOP_PG	        0x80		/* Last page + 1 of RX Ring          */ 
#define     RX_STOP_PG      STOP_PG
#define     RX_START_PG	    START_PG + TX_PAGES
#define     RX_CURR_PG      RX_START_PG + 1

#define     EN_RBUF_STAT	0	    /*  Received frame status                */
#define     EN_RBUF_NXT_PG	1	    /*  Page after this frame                */
#define     EN_RBUF_SIZE_LO	2	    /*  Length of this frame                 */
#define     EN_RBUF_SIZE_HI	3	    /*  Length of this frame                 */
#define     SIZE_OF_8019_HDR 4	    /*  size of 8019 specific packet header  */

#define		SBUFSIZ			1600
#define		BUFSIZ			1600
#define     PKT_DEST		0
#define     PKT_SRC			6
#define     PKT_TYPE		12
#define     SIZE_OF_ETH_PKT_HDR	14

/* IPADDR: The IP address of this 8019 node. */
#define IPADDR0     192
#define IPADDR1     168
#define IPADDR2     0
#define IPADDR3     2

/* NETMASK: The netmask. */
#define IPMASK0 255
#define IPMASK1 255
#define IPMASK2 255
#define IPMASK3 0

/* RIPADDR: IP address of the default router. */
#define RIPADDR0 192
#define RIPADDR1 168 
#define RIPADDR2 0
#define RIPADDR3 1

/* ETHADDR: The Ethernet address. */
#define ETHADDR0 0x52
#define ETHADDR1 0x54
#define ETHADDR2 0x4C
#define ETHADDR3 0xC1
#define ETHADDR4 0x18
#define ETHADDR5 0xCF


/*****************************************************************************/
/* The EN registers - the Realtek RTL8019AS chip registers                   */
/* There are four pages of registers in the chip. You select                 */
/* which page you want, then address them at offsets 00-0F from base.        */
/* The chip command register (EN_CMD) appears in all pages.                  */

#define     CR              XBYTE [0x300]   /*	The command register (for all pages) */
#define     DMA_DATA		XBYTE [0x310]	/*  Remote DMA Port10~17h (for all pages)*/
#define     RESET	        XBYTE [0x318]	/*  Reset Port 18~1fh(for all pages)     */

/* Register accessed at EN_CMD, the RTL8019 base addr                        */
#define     CR_STOP		    0x01	//  Stop and reset the chip              
#define     CR_START	    0x02	//  Start the chip, clear reset          
#define     CR_TRANS	    0x04	//  Transmit a frame                     
#define     CR_RREAD	    0x08	//  Remote read                          
#define     CR_RWRITE	    0x10	//  Remote write                         
#define     CR_NODMA	    0x20	//  Remote DMA                           
#define     CR_PAGE0	    0x00	//  Select page chip registers           
#define     CR_PAGE1	    0x40	//  using the two high-order bits        
#define     CR_PAGE2	    0x80 
#define     CR_PAGE3	    0xc0

/* 
#define		E8390_STOP		0x01	// Stop and reset the chip 
#define		E8390_START		0x02	// Start the chip, clear reset 
#define		E8390_TRANS		0x04	// Transmit a frame 
#define		E8390_RREAD		0x08	// Remote read 
#define		E8390_RWRITE	0x10	// Remote write  
#define		E8390_SPACKET	0x18	// Send Packet 
#define		E8390_NODMA		0x00	// Remote DMA 
#define		E8390_PAGE0		0x00	// Select page chip registers 
#define		E8390_PAGE1		0x40	// using the two high-order bits 
#define		E8390_PAGE2		0x80	// Page 3 is invalid. 
*/

/* Page 0 register offsets                                                   */
#define     CLDA0		XBYTE [0x301]   // Current Locat DMA 0: RD Low byte of current local dma addr
#define     PSTART      XBYTE [0x301]	// Page Start:  WR Starting page of ring buffer      
#define     CLDA1		XBYTE [0x302]   // Current Locat DMA 1:  RD High byte of current local dma add
#define     PSTOP  	    XBYTE [0x302]	// Page Stop:  WR Ending page +1 of ring buffer     
#define     BNRY	    XBYTE [0x303]	// Boundary Reg:  RD/WR Boundary page of ring buffer   
#define     TSR			XBYTE [0x304]	// Transmit Status Reg: RD Transmit status reg               
#define     TPSR		XBYTE [0x304]	// Transmit Page Start: WR Transmit starting page            
#define     NCR			XBYTE [0x305]	// Number of Collision:  RD Number of collision reg           
#define     TBCR0  	    XBYTE [0x305]	// Transmit Byte Count 0:  WR Low  byte of tx byte count        
#define     FIFO		XBYTE [0x306]	// RD FIFO                              
#define     TBCR1		XBYTE [0x306]	// Transmit Byte Count 1:  WR High byte of tx byte count        
#define     ISR			XBYTE [0x307]	// Interrupt Status Reg:   RD/WR Interrupt status reg           
#define     CRDA0  	    XBYTE [0x308]	// Current Remote DMA 0:  RD low byte of current remote dma add
#define     RSAR0		XBYTE [0x308]	// Remote Start DMA 0:  WR Remote start address reg 0        
#define     CRDA1		XBYTE [0x309]	// Current Remote DMA 1:  RD high byte, current remote dma add.
#define     RSAR1		XBYTE [0x309]	// Remote Start DMA 1:  WR Remote start address reg 1        
#define     RBCR0	    XBYTE [0x30a]	// Remote Byte Count 0:  WR Remote byte count reg 0           
#define     R8019ID0	XBYTE [0x30a]	// Only 8019AS                          
#define     RBCR1		XBYTE [0x30b]	// Remote Byte Count 1:  WR Remote byte count reg 1           
#define     R8019ID1 	XBYTE [0x30b]	// Only 8019AS                          
#define     RSR			XBYTE [0x30c]	// Reciever Status Reg:  RD RX status reg                     
#define     RCR		    XBYTE [0x30c]	// Reciever Configuration Reg:  WR RX configuration reg              
#define     TCR		    XBYTE [0x30d]	// Transmit Configuration Reg:  WR TX configuration reg              
#define     CNTR0	    XBYTE [0x30d]	// RD Rcv alignment error counter       
#define     DCR		    XBYTE [0x30e]	// Data Configuration Reg:  WR Data configuration reg            
#define     CNTR1	    XBYTE [0x30e]	// RD Rcv CRC error counter             
#define     IMR			XBYTE [0x30f]	// Interrupt Mask Reg:  WR Interrupt mask reg                
#define     CNTR2	    XBYTE [0x30f]	// RD Rcv missed frame error counter    
                                                
/* Bits in TSR - Transmit status                               */
#define     TSR_PTX	    0x01	/*  Packet transmitted without error     */
//#define     TSR_ND	    0x02	/*  The transmit wasn't deferred.  ?     */
#define     TSR_COL	    0x04	/*  The transmit collided at least once. */
											/*  Record of collision remain NCR reg.  */
#define     TSR_ABT	    0x08	/*  The transmit collided 16 times, and was deferred. */
#define     TSR_CRS	    0x10	/*  The carrier sense was lost.          */
#define     TSR_FU	    0x20	/*  A "FIFO underrun" occurred during transmit. */
#define     TSR_CDH	    0x40	/*  The collision detect "heartbeat" signal was lost. */
#define     TSR_OWC	    0x80	/*  There was an out-of-window collision.*/
/*  After slot time, there was collision. This case was excuted retransmission.  ? */
                                    
              
/* Bits in ISR - Interrupt status register        (RD WR)                */
#define     ISR_PRX   	  0x01	/*  Receiver, no error                   */
#define     ISR_PTX	      0x02	/*  Transceiver, no error                */
#define     ISR_RXE	      0x04	/*  Receiver, with error                 */
#define     ISR_TXE	      0x08	/*  Transmitter, with error              */
#define     ISR_OVW	      0x10	/*  Receiver overwrote the ring          */
                       /*  Gap area of receiver ring buffer was disappeared  */ 
#define     ISR_CNT	      0x20	/*  Counters need emptying               */
                                    /* MSB of network tally counter became 1 */
#define     ISR_RDC	      0x40	/*  remote dma complete                  */
#define     ISR_RESET     0x80	/*  Reset completed                      */
#define     ISR_ALL	      0x35	/*3f  Interrupts we will enable 	 */
                                	/*  RST RDC CNT OVW TXE RXE PTX PRX		 */
/* Bits in RSR and received packet status byte                           */
#define     RSR_RRX  	0x01	/*  Received a good packet               */
#define     RSR_CRC	    0x02	/*  CRC error(CNTR1++)                   */
#define     RSR_FAE	    0x04	/*  Frame alignment error(CNTR0++)       */
                                    /*Packet isn't finished in byte boundary.*/
#define     RSR_FO	    0x08	/*  FIFO overrun when receiving          */
#define     RSR_MPA	    0x10	/*  Missed packet.. Gap area isn't exist */
             /* or because of monitor mode, packet is not buffered (CNTR2++) */
#define     RSR_PHY	    0x20	/* Physical/multicase address            */
 
#define     RSR_DIS	    0x40	/*  Receiver disable.set in monitor mode */
#define     RSR_DEF	    0x80	/*  Deferring because of collision       */
                                
/*****************************************************************************/
/* Some generic ethernet register configurations.                            */
#define E8390_TX_IRQ_MASK   0x0A  /* For register EN0_ISR */
#define E8390_RX_IRQ_MASK   0x05                                           */
#define E8390_RXCONFIG      0x04 /* EN0_RXCR: broadcasts, no multicast & errors */
#define E8390_RXOFF         0x20    /* EN0_RXCR: Accept no packets */
#define E8390_TXCONFIG      0x00 /* EN0_TXCR: Normal transmit mode */
#define E8390_TXOFF         0x02    /* EN0_TXCR: Transmitter off */
/*****************************************************************************/

/* Bits in RCR - RX configuration reg                                   */
//#define     ENRXCR_RXCONFIG 0x04 	/* EN0_RXCR: broadcasts,no multicast,errors */
#define     RCR_RXCONFIG 0x00 	/* EN0_RXCR: only unicast */
#define     RCR_SEP	     0x01	/*  Save error packets(admit)            */
#define     RCR_AR	     0x02	/*  Accept runt pckt(below 64bytes)      */
#define     RCR_AB	     0x04	/*  Accept broadcasts when 1             */
#define     RCR_AM	     0x08	/*  Multicast (if pass filter) when 0    */
#define     RCR_PRO 	 0x10	/*  Promiscuous physical addresses when 1*/
											/* when 0,accept assigned PAR0~5 address */
#define     RCR_MON	     0x20	/*  Monitor mode (no packets rcvd)       */

/* Bits in TCR - TX configuration reg                                   */
#define     TCR_TXCONFIG 0x00    /* Normal transmit mode                  */
#define     TCR_CRC	     0x01	/*  inhibit CRC,do not append crc when 1 */
#define     TCR_LOOP	 0x02	/*  set internal loopback mode     ?     */
#define     TCR_LB01	 0x06	/*  encoded loopback control       ?     */
#define     TCR_ATD	     0x08	/*  auto tx disable                      */
/* when 1, if specified multicast packet was received, disable transmit      */ 
#define     TCR_OFST	 0x10	/*  collision offset enable              */
/* selection of collision algorithm. When 0, gererally back-off algorithm select */

/* Bank0/Reg0E                                                               */
/* Bits in DCR - Data config register                                   */
#define     DCR_WTS	    0x01	    /*  byte transfer mode selection         */        
/*#endif    */
#define     DCR_BOS	    0x02	    /*  byte order selection                 */
                                    /* 0: MD15-8, LSB on MD7-0;little endian */
                                    /* 1: MSB on MD7-0, LSB on MD15-8     ?  */
#define     DCR_LAS	    0x04	    /* long addr selection (must be set to zero) */
                                    /* when 1 is 32bit address mode          */
#define     DCR_LS	    0x08	    /* loopback select       set is normal  mode      */
                                    /* 0: Loopback mode select. Bits 1 and 2 of the
                                       TCR must also be programmed for Loopback
                                       1: Normal operation                            */
#define     DCR_ARM	        0x10	/*  autoinitialize remote when 1         */
#define     DCR_FT00	    0x00	/*  fifo treshold   2 byte               */
#define     DCR_FT01	    0x20	/*                  4 byte               */  
#define     DCR_FT10	    0x40	/*                  8 byte               */
#define     DCR_FT11	    0x60	/*                 12 byte               */

/* Page 1 register offsets                                                   */
#define     PAR0	    XBYTE [0x301]	// RD/WR This board's physical ethernet addr */
#define     PAR1	    XBYTE [0x302]
#define     PAR2	    XBYTE [0x303]
#define     PAR3	    XBYTE [0x304]
#define     PAR4	    XBYTE [0x305]
#define     PAR5	    XBYTE [0x306]
#define     CURR	    XBYTE [0x307]   // RD/WR current page reg */
//#define		EN1_CURPAG		EN1_CURR
#define     MAR0        XBYTE [0x308]   // RD/WR Multicast filter mask array (8 bytes) */
#define     MAR1		XBYTE [0x309]
#define     MAR2        XBYTE [0x30a]
#define     MAR3        XBYTE [0x30b]
#define     MAR4        XBYTE [0x30c]
#define     MAR5        XBYTE [0x30d]
#define     MAR6        XBYTE [0x30e]
#define     MAR7        XBYTE [0x30f]

/* Page 2 register offsets                                                   */
#define     STARTPG_R     XBYTE [0x301]   // RD only Reg.           
#define     STOPPG_R      XBYTE [0x302]
#define     TPSR_R		  XBYTE [0x304]
#define     RXCR_R		  XBYTE [0x30c]
#define     TXCR_R		  XBYTE [0x30d]
#define     DCR_R		  XBYTE [0x30e]
#define     IMR_R	      XBYTE [0x30f]

/* // Page 3 register offsets    There is no Reg. in the DP8390.                
#define     CR9346			XBYTE [0x301]   // RD/WR There is no Reg. in the DP8390 
#define     BPAGE			XBYTE [0x302]   // RD/WR 
#define     CONFIG0			XBYTE [0x303]   // RD    
#define     CONFIG1			XBYTE [0x304]   // RD/WR 
#define     CONFIG2			XBYTE [0x305]   // RD/WR 
#define     CONFIG3			XBYTE [0x306]   // RD/WR 
#define     CONFIG4			XBYTE [0x30d]   // RD    
#define     CSNSAV          XBYTE [0x308]   // RD    
#define     HLTCLK			XBYTE [0x309]   // WR 
#define     INTR			XBYTE [0x30B]   // RD  
*/


