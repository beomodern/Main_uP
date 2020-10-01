/* ========================================
 *
 * Copyright HEMI, 2020
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 * 
 * Functions used by BeoModern main PSoC to display informaiton on BeoModern
 * front display as well as front LEDs
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF HEMI.
 *
 * ========================================
*/

#ifndef DISPLAY_H_   /* Include guard */
#define DISPLAY_H_

#include <project.h>
  
    
/***************************************
*            Constants
****************************************/
// Tx
// Packet size
#define TxPACKET_SIZE      (28u)

// Byte position within the packet (start, end)
#define TxPACKET_SOP_POS  (0u)
#define TxPACKET_CTRL1_POS  (25u)
#define TxPACKET_CTRL2_POS  (26u)
#define TxPACKET_EOP_POS  (27u)
    
// Rx    
// Packet size
#define RxPACKET_SIZE      (3u)    

// Byte position within the packet (start, status, end)
#define RxPACKET_SOP_POS  (0u)
#define RxPACKET_STS_POS  (1u)
#define RxPACKET_EOP_POS  (2u)    

// Start and end of the packet markers/
#define PACKET_SOP      (0x01u)
#define PACKET_EOP      (0x17u)    
    
// This dummy buffer used by SPIM when it receives status packet.
const uint8 dummyBuffer[TxPACKET_SIZE];



/*******************************************************************************
* Function Name: SPIM_display_write
********************************************************************************
* Summary:
*  SPIM initiates the transmission of a command packet to the SPIS. After
*  transfer completion, the dummy bytes sent by the SPIS are cleared from the
*  RX buffer.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SPIM_display_write(uint8 message_table[], uint8 disp_ctrl1, uint8 disp_ctrl2);


/*******************************************************************************
* Function Name: SPIM_display_read
********************************************************************************
* Summary:
*  SPIM initiates the transmission of a dummy packet to collect the status
*  information from the SPIS. After the transfer is complete the format of
*  the packet is verified and the status is returned. If the format of the
*  packet is invalid the unknown status is returned.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
uint32 SPIM_display_read(void);


/*******************************************************************************
* Function Name: SPIM_SigmaDSP_init_SPI
********************************************************************************
* Summary:
*  This function toggles 3 times /CS line that selects SigmaDSP on SPI port
*  This in turn enables serial port in SPI mode for further transactions. 
*
* Parameters:
*  None
*
* Return:
*  zero
*
*******************************************************************************/
uint8 SPIM_SigmaDSP_init_SPI(void);


/*******************************************************************************
* Function Name: SPIM_SigmaDSP_write
********************************************************************************
* Summary:
*  This function sents commands over SPI interface to SigmaDSP
*  Commands are controled thru command parameter and are listed below. 
*
* Parameters:
*  0 = Control = 0x052E -> 0x0000 = MUTE
*  1 = Control = 0x052E -> 0x0001 = RPi
*  2 = Control = 0x052E -> 0x0002 = DAB
*  3 = Control = 0x052E -> 0x0003 = AuxIN
*  4 = Control = 0x052E -> 0x0004 = BlueTooth Rx
*  5 = LED = 0x0531 -> 0x0000 = OFF
*  6 = LED = 0x0531 -> 0x0001 = ON
*
* Return:
*  zero
*
*******************************************************************************/
uint8 SPIM_SigmaDSP_write(uint8 command);



/*******************************************************************************
* Function Name: SPIM_SigmaDSP_read
********************************************************************************
* Summary:
*  This function sents commands over SPI interface to SigmaDSP. Command itends 
*  to read back SPI register values and return them as one 32 bit value.
*
* Parameters:
* Parameters:
*  0 = LEVEL = 0x0175
*  1 = Spectrum analyzer -> Right = 0x0520
*  2 = Spectrum analyzer -> Left = 0x051F
*  3 = Spectrum analyzer -> Left&Right = 0x0521
*  4 = CODE = 0x0029
*
* Return:
*  0 = LEVEL -> 0x0000aabb
*    -> aa - 0x00 - 0x10 - left channel 
*    -> bb - 0x00 - 0x10 - right channel
*  1 = Spectrum analyzer -> Right
*    b31-b28 - NOT_USED
*    b27-b24 - 31.5Hz
*    b23-b20 - 63Hz
*    b19-b16 - 125Hz
*    b15-b12 - 250Hz
*    b11-b8 - 500Hz
*    b7-b4 - 1000Hz
*    b3-b0 - 2000Hz        
*  2 = Spectrum analyzer -> Left
*    b31-b28 - NOT_USED
*    b27-b24 - 31.5Hz
*    b23-b20 - 63Hz
*    b19-b16 - 125Hz
*    b15-b12 - 250Hz
*    b11-b8 - 500Hz
*    b7-b4 - 1000Hz
*    b3-b0 - 2000Hz        
*  3 = Spectrum analyzer -> Left&Right
*    LEFT
*    b31-b28 - NOT_USED
*    b27-b24 - 4000Hz
*    b23-b20 - 8000Hz
*    b19-b16 - 16000Hz
*    RIGHT
*    b15-b12 - NOT_USED
*    b11-b8 - 4000Hz
*    b7-b4 - 8000Hz
*    b3-b0 - 16000Hz
*  4 = CODE 
*   expected fixed value -> 32 bit word = 0xBE01BE02
*
*******************************************************************************/
uint32 SPIM_SigmaDSP_read(uint8 command);


#endif // DISPLAY_H_

/* [] END OF FILE */
