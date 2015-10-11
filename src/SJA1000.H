// Define SJA1000 Register  

//#include "const.h"
#define XBYTE ((unsigned char volatile xdata*) 0)

#define PeliCANMode 1
// Mode Register Address and Bit Defined 
#define ModeControlReg XBYTE[0]
#define RM_RR_Bit 0x01         // Reset Mode
#if defined (PeliCANMode)
#define LOM_Bit 0x02           // listen only Mode
#define STM_Bit 0x04           // self test mode 
#define AFM_Bit 0x08           // Acceptance Filter Mode: Single mode
#define SM_Bit 0x10            // Sleep Mode
#endif

// Interrupt Enable Register 
#if defined (PeliCANMode)
#define InterruptEnReg XBYTE[4] // PeliCAN Mode
#define RIE_Bit 0x01 // Receive Interrupt Enable
#define TIE_Bit 0x02 // Send Interrupt Enable
#define EIE_Bit 0x04 // Error Warning Interrupt Enable
#define DOIE_Bit 0x08 // Data Overrun Interrupt Enable
#define WUIE_Bit 0x10 // Wake_up Interrupt Enable
#define EPIE_Bit 0x20 // Error Passive Interrupt Enable
#define ALIE_Bit 0x40 // Arbitration Lost Interrupt Enable
#define BEIE_Bit 0x80 // Bus Error Interrupt
#else                 // BasicCAN Mode
#define InterruptEnReg XBYTE[0] // Control Register
#define RIE_Bit 0x02 // reveice Interrupt Enable
#define TIE_Bit 0x04 // Send Interrupt Enable
#define EIE_Bit 0x08 // Error Interrupt Enable
#define DOIE_Bit 0x10 // Data Overrun Interrupt Enable
#endif
// Command register 
#define CommandReg XBYTE[1]
#define TR_Bit 0x01 // Transmission Request
#define AT_Bit 0x02 // Abort Transmission 
#define RRB_Bit 0x04 // Release Reveice Buffer
#define CDO_Bit 0x08 // Clear Data Overrun
#if defined (PeliCANMode)
#define SRR_Bit 0x10 // Self Reception Request
#else // BasicCAN Mode
#define GTS_Bit 0x10 // Sleep Mode 
#endif

// Status Register
#define StatusReg XBYTE[2] 
#define RBS_Bit 0x01 //  Reveice Buffer Status
#define DOS_Bit 0x02 // Data overrun status
#define TBS_Bit 0x04 // Transmit buffer status
#define TCS_Bit 0x08 // Transmission Complete status
#define RS_Bit 0x10 // Reveice status
#define TS_Bit 0x20 // Transmit status
#define ES_Bit 0x40 // Error status
#define BS_Bit 0x80 // Bus status

// Interrupt Register
#define InterruptReg XBYTE[3]
#define RI_Bit 0x01 // Reveice Interrupt
#define TI_Bit 0x02 // TransMit Interrupt
#define EI_Bit 0x04 // Error Warning interrupt
#define DOI_Bit 0x08 // data overrun interrupt
#define WUI_Bit 0x10 // wake_up interrupt 
#if defined (PeliCANMode)
#define EPI_Bit 0x20 // error passive interrupt 
#define ALI_Bit 0x40 // Arbitration Lost Interrupt 
#define BEI_Bit 0x80 // bus error interrupt
#endif

// Bus timing register 0 and 1
#define BusTiming0Reg XBYTE[6]
#define BusTiming1Reg XBYTE[7]
#define SAM_Bit 0x80   //Bus is sampled three times 

// Output Control register
#define OutControlReg XBYTE[8]
/*OCMODE1 OCMODE0 */
#define BiPhaseMode 0x00 // Bi_Phase Output mode 
#define Testmode         // Test Output mode 
#define NormalMode 0x02 // Normal OutPut mode 
#define ClkOutMode 0x03 // Clock Output Mode 
// TX1 OutPut Pin Configuration
#define OCPOL1_Bit 0x20 
#define Tx1Float 0x00 // Float 
#define Tx1PullDn 0x40 // Pull Down
#define Tx1PullUp 0x80 // Pull Up
#define Tx1PshPull 0Xc0 // Push_pull
// TX0 output pin configuration
#define OCPOL0_Bit 0x04 
#define Tx0Float 0x00 // Float
#define Tx0PullDn 0x08 // Pull Down
#define Tx0PullUp 0x10 // Pull Up
#define Tx0PshPull 0X18 // push_pull

// Acceptance Filter register
#if defined (PeliCANMode)
#define AcceptCode0Reg XBYTE[16]
#define AcceptCode1Reg XBYTE[17]
#define AcceptCode2Reg XBYTE[18]
#define AcceptCode3Reg XBYTE[19]
// Acceptance Mask Filter register
#define AcceptMask0Reg XBYTE[20]
#define AcceptMask1Reg XBYTE[21]
#define AcceptMask2Reg XBYTE[22]
#define AcceptMask3Reg XBYTE[23]
#else // BasicCAN Mode 
#define AcceptCodeReg XBYTE[4]
#define AcceptMaskReg XBYTE[5]
#endif
// Rx-Buffer Address 
#if defined (PeliCANMode)
#define RxFramInfo XBYTE[16]
#define RxBuffer1 XBYTE[17]
#define RxBuffer2 XBYTE[18]
#define RxBuffer3 XBYTE[19]
#define RxBuffer4 XBYTE[20]
#define RxBuffer5 XBYTE[21]
#define RxBuffer6 XBYTE[22]
#define RxBuffer7 XBYTE[23]
#define RxBuffer8 XBYTE[24]
#define RxBuffer9 XBYTE[25]
#define RxBuffer10 XBYTE[26]
#define RxBuffer11 XBYTE[27]
#define RxBuffer12 XBYTE[28]
#else // BasicCAN mode 
#define RxBuffer1 XBYTE[20]
#define RxBuffer2 XBYTE[21]
#define RxBuffer3 XBYTE[22]
#define RxBuffer4 XBYTE[23]
#define RxBuffer5 XBYTE[24]
#define RxBuffer6 XBYTE[25]
#define RxBuffer7 XBYTE[26]
#define RxBuffer8 XBYTE[27]
#define RxBuffer9 XBYTE[28]
#define RxBuffer10 XBYTE[29]
#endif
// Tx buffer Address
#if defined (PeliCANMode)
// Write Only Address
#define TxFramInfo XBYTE[16]
#define TxBuffer1 XBYTE[17]
#define TxBuffer2 XBYTE[18]
#define TxBuffer3 XBYTE[19]
#define TxBuffer4 XBYTE[20]
#define TxBuffer5 XBYTE[21]
#define TxBuffer6 XBYTE[22]
#define TxBuffer7 XBYTE[23]
#define TxBuffer8 XBYTE[24]
#define TxBuffer9 XBYTE[25]
#define TxBuffer10 XBYTE[26]
#define TxBuffer11 XBYTE[27]
#define TxBuffer12 XBYTE[28]
// Read Only Address
#define TxFramInFoRd XBYTE[96]
#define TxBufferRd1 XBYTE[97]
#define TxBufferRd2 XBYTE[98]
#define TxBufferRd3 XBYTE[99]
#define TxBufferRd4 XBYTE[100]
#define TxBufferRd5 XBYTE[101]
#define TxBufferRd6 XBYTE[102]
#define TxBufferRd7 XBYTE[103]
#define TxBufferRd8 XBYTE[104]
#define TxBufferRd9 XBYTE[105]
#define TxBufferRd10 XBYTE[106]
#define TxBufferRd11 XBYTE[107]
#define TxBufferRd12 XBYTE[108]
#else // BasicCAN Mode 
#define TxBuffer1 XBYTE[10]
#define TxBuffer2 XBYTE[11]
#define TxBuffer3 XBYTE[12]
#define TxBuffer4 XBYTE[13]
#define TxBuffer5 XBYTE[14]
#define TxBuffer6 XBYTE[15]
#define TxBuffer7 XBYTE[16]
#define TxBuffer8 XBYTE[17]
#define TxBuffer9 XBYTE[18]
#define TxBuffer10 XBYTE[19]
#endif

// Other Regisger  
#if defined (PeliCANMode)
#define ArbLostCapReg XBYTE[11]  // Arbitration Lost capture register
#define ErrCodeCapReg XBYTE[12]  // error code capture register
#define ErrWarnLimitReg XBYTE[13] // error warning limit register
#define RxErrCountReg XBYTE[14]   // Rx Error Count Register 
#define TxErrCountReg XBYTE[15]  // Tx Error count  register
#define RxMsgCountReg XBYTE[29]   // Rx message counter register
#define RxBufstartAdr XBYTE[30]    // Rx buffer star adress register
#endif

// clock divider register
#define ClockDivideReg XBYTE[31]
#define DivBy1 0x07  // CLKOUT=Fosc
#define DivBy2 0x00  //CLKOUT=1/2 Fosc
#define CLKOff_Bit 0x08 // Clock Off: Allows the external CLKOUT pin of the SJA1000 to be disabled
#define RXINTEN_Bit 0x20 //Rx_Int_En: Allows the TX1 output to be used as a dedicated receive interrupt output
#define CBP_Bit 0x40 // allows to bypass the CAN input comparator and is only possible in reset mode
#define CANMode_Bit 0x80 // CAN  Mode : peliCAN mode 

// baud = Focs/2*BRP*(TSEG1+TSEG2+1)

// Focs = 12M , baud = 25 kBit/s
#define PrescExample 0x13 // divide 8
#define SJWExample 0x00 // SJW 4 
#define TSEG1Example 0x07 // TSEG1 8
#define TSEG2Example 0x20 // TSEG2 3 


extern void initialzation( void ) reentrant  ;
extern void transmit( void ) reentrant  ;
extern unsigned char receive(void) reentrant  ;
