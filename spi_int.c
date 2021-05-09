/* ========================================
 *
* Copyright HEMI, 2021
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

#include <inputs.h>
#include <spi_int.h>



/*******************************************************************************
* Function Name: SPIM_display_write
********************************************************************************
* Summary:
*  SPI Master initiates the transmission of 25 long message to the SPI Slave. 
*  Funciton adds start and stop bajts to indicate correct transfer.
*  After transfer completion, the dummy bytes sent by the SPIS are cleared from 
*  the RX buffer.
*
* Summary:
*  Funciton reponsible for decoding and displayin commands that were sent over 
*  SPI interface to display. It intercepts 24 ASCI characters and pushes them to 
*  display. It also interprets two control words and manipulates LEDs acordingly
*  to control words state.
*  More than one LED can be ON at one time.
*
* Parameters:
*  input_table[] - table returned by SPI slave routine contining 24 ASCI
*                  characters and 2 control words for LED ON/OFF states
*  disp_ctrl1 - Each bit represents LED on front interface
*               LED control
*               CTRL0.0 - Player
*               CTRL0.1 - iRadio
*               CTRL0.2 - DAB Radio
*               CTRL0.3 - Aux IN
*               CTRL0.4 - Clock    
*               CTRL0.5 - RDS/FM Display
*               CTRL0.6 - BT Rx    
*               CTRL0.7 - NOT USED
                only one LED can be ON at particualr moment in time
*  disp_ctrl2 - Each bit represents LED on front interface
*               LED control
*               CTRL1.0 - BT Tx
*               CTRL1.1 - Online status
*               CTRL1.2 - Signal Level
*               CTRL1.3 - Spectrum Analyser
*               CTRL1.4 - Clock 1
*               CTRL1.5 - Clock 2
*               CTRL1.6 - NOT USED
*               CTRL1.7 - NOT USED
*               more than one LED can be ON at particualr moment in time
* Return:
*  none
*
*******************************************************************************/
uint8 SPIM_display_write(uint8 message_table[], uint8 disp_ctrl1, uint8 disp_ctrl2)
{
// SPI Rx buffer - array used to store data received over SPI interface.    
    uint8 tmpBuffer[PACKET_SIZE] = {0};
// variable to store status message that is returend by the function. It is populated
// with data read back over SPI at 2nd bajt position. 
    uint8 status;
// SPIM TX buffer - array used to store data that will be sent to SPI slave (display)
    uint8 mTxBuffer[PACKET_SIZE] = {0};
// variable to populate Tx buffer with incomming message
    uint8 i = 0;
    
// set SPI slave select line to display
    SPIM_SpiSetActiveSlaveSelect(SPIM_SPI_SLAVE_SELECT1);     

// set start of Tx message 
    mTxBuffer[PACKET_SOP_POS] = (PACKET_SOP);
// populate buffer with incoming 24 characters of data    
    for (i = 1; i<PACKET_SIZE-3; i++)
    {
        mTxBuffer[i] = (message_table[i-1]);
    }
// populate control messages 1 and 2    
    mTxBuffer[PACKET_CTRL1_POS] = disp_ctrl1;
    mTxBuffer[PACKET_CTRL2_POS] = disp_ctrl2;
    
// set end of Tx message    
    mTxBuffer[PACKET_EOP_POS] = (PACKET_EOP);

// Start transfer (message plus start/stop indicators
    SPIM_SpiUartPutArray(mTxBuffer, PACKET_SIZE);
    
// Wait for the end of the transfer. The number of transmitted data
// elements has to be equal to the number of received data elements.
    while((PACKET_SIZE) != SPIM_SpiUartGetRxBufferSize())
    {
    }

// Read data from the RX buffer
    i = 0u;
    while (0u != SPIM_SpiUartGetRxBufferSize())
    {
        tmpBuffer[i] = (uint8)SPIM_SpiUartReadRxData();
        i++;
    }
    
// Check packet format
    if ((tmpBuffer[PACKET_SOP_POS] == PACKET_SOP) &&
        (tmpBuffer[PACKET_EOP_POS] == PACKET_EOP))
    {
 // Return status
        status = tmpBuffer[PACKET_STS_POS];
        
    }
    else
       {
// Invalid packet format, return 0xFF status
        status = 0xFF;
        }

    return (status);
}




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
uint8 SPIM_SigmaDSP_init_SPI(void)
{

// SPIM TX buffer 
    uint8 localBuffer[1] = {0};
// buffer value to 0 (only need to toggle CS line 3 times
    localBuffer[0] = (0x00);
    
// set SPI slave select line to SigmaDSP
    SPIM_SpiSetActiveSlaveSelect(SPIM_SPI_SLAVE_SELECT0); 

// sent SPI message - first /CS toggle
    SPIM_SpiUartPutArray(localBuffer, 1);
// Wait for the end of the transfer. The number of transmitted data
// elements has to be equal to the number of received data elements.
    while((1) != SPIM_SpiUartGetRxBufferSize())
    {
    }
// Clear dummy bytes from RX buffer
    SPIM_SpiUartClearRxBuffer(); 

// wait 100uS    
    CyDelayUs(100);  

// sent SPI message - second /CS toggle
    SPIM_SpiUartPutArray(localBuffer, 1);
// Wait for the end of the transfer. The number of transmitted data
// elements has to be equal to the number of received data elements.
    while((1) != SPIM_SpiUartGetRxBufferSize())
    {
    }
// Clear dummy bytes from RX buffer
    SPIM_SpiUartClearRxBuffer(); 
    
// wait 100uS  
    CyDelayUs(100); 
    
// sent SPI message -third /CS toggle
    SPIM_SpiUartPutArray(localBuffer, 1);
// Wait for the end of the transfer. The number of transmitted data
// elements has to be equal to the number of received data elements.
    while((1) != SPIM_SpiUartGetRxBufferSize())
    {
    }
// Clear dummy bytes from RX buffer
    SPIM_SpiUartClearRxBuffer(); 
    
// set SPI slave select line to display module
    SPIM_SpiSetActiveSlaveSelect(SPIM_SPI_SLAVE_SELECT1); 
    
    return 0;
}



/*******************************************************************************
* Function Name: SPIM_SigmaDSP_write
********************************************************************************
* Summary:
*  This function sents commands over SPI interface to SigmaDSP
*  Commands are controled thru command parameter and are listed below. 
*
* Parameters:
*  0 = Control = 0x0535 -> 0x0000 = MUTE
*  1 = Control = 0x0535 -> 0x0001 = RPi
*  2 = Control = 0x0535 -> 0x0002 = DAB
*  3 = Control = 0x0535 -> 0x0003 = AuxIN
*  4 = Control = 0x0535 -> 0x0004 = BlueTooth Rx
*  5 = LED = 0x0538 -> 0x0000 = OFF
*  6 = LED = 0x0538 -> 0x0001 = ON
*
* Return:
*  zero
*
*******************************************************************************/
uint8 SPIM_SigmaDSP_write(uint8 command)
{
// buffer for data to be sent over SPI to SigmaDSP 
    uint8 writeBuffer[7] = {0};
// first buffer byte set to value 0x00 indicating write data    
    writeBuffer[0] = (0x00);
// 3, 4 and 5 buffer bytes set to 0x00 all data sent over SPI have its MSBs = 0    
    writeBuffer[3] = (0x00);
    writeBuffer[4] = (0x00);    
    writeBuffer[5] = (0x00);    

// set SPI slave select line to SigmaDSP
    SPIM_SpiSetActiveSlaveSelect(SPIM_SPI_SLAVE_SELECT0); 
    
    switch (command)
    {    
//  0 = Control = 0x0535 -> 0x0000 = MUTE
    case (0):
        writeBuffer[1] = (0x05);
        writeBuffer[2] = (0x35);
        writeBuffer[6] = (0x00);    
        break;
//  1 = Control = 0x0535 -> 0x0001 = RPi
    case (1):
        writeBuffer[1] = (0x05);
        writeBuffer[2] = (0x35);
        writeBuffer[6] = (0x01);    
        break;
//  2 = Control = 0x0535 -> 0x0002 = DAB
    case (2):
        writeBuffer[1] = (0x05);
        writeBuffer[2] = (0x35);
        writeBuffer[6] = (0x02);    
        break;        
//  3 = Control = 0x0535 -> 0x0003 = AuxIN
    case (3):
        writeBuffer[1] = (0x05);
        writeBuffer[2] = (0x35);
        writeBuffer[6] = (0x03);    
        break;
//  4 = Control = 0x0535 -> 0x0004 = BlueTooth Rx
    case (4):
        writeBuffer[1] = (0x05);
        writeBuffer[2] = (0x35);
        writeBuffer[6] = (0x04);    
        break;        
//  5 = LED = 0x053 -> 0x0000 = OFF
    case (5):
        writeBuffer[1] = (0x05);
        writeBuffer[2] = (0x38);
        writeBuffer[6] = (0x00);    
        break;
//  6 = LED = 0x0538 -> 0x0001 = ON
    case (6):
        writeBuffer[1] = (0x05);
        writeBuffer[2] = (0x38);
        writeBuffer[6] = (0x01);    
        break;         
    }        
// Start buffer transfer over SPI interface to SigmaDSP
    SPIM_SpiUartPutArray(writeBuffer, 7);

// Wait for the end of the transfer. The number of transmitted data
// elements has to be equal to the number of received data elements.
    while((7) != SPIM_SpiUartGetRxBufferSize())
    {
    }
// Clear dummy bytes from RX buffer
    SPIM_SpiUartClearRxBuffer();  

// set SPI slave select line to display module
    SPIM_SpiSetActiveSlaveSelect(SPIM_SPI_SLAVE_SELECT1);     
    
    return 0;
}


/*******************************************************************************
* Function Name: SPIM_SigmaDSP_read
********************************************************************************
* Summary:
*  This function sents commands over SPI interface to SigmaDSP. Command itends 
*  to read back SPI register values and return them as one 32 bit value.
*
* Parameters:
* Parameters:
*  0 = LEVEL = 0x0514
*  1 = Spectrum analyzer -> Right = 0x0526
*  2 = Spectrum analyzer -> Left = 0x0527
*  3 = Spectrum analyzer -> Left&Right = 0x0528
*  4 = CODE = 0x001B
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
uint32 SPIM_SigmaDSP_read(uint8 command)
{
// variable used to return read command value    
    uint32 status = 0;

// variable used by read buffer command    
    uint8 i;

// buffer for data to be read over SPI from SigmaDSP 
    uint8 readBuffer[7] = {0};
// buffer for data to be sent over SPI to SigmaDSP 
    uint8 writeBuffer[7] = {0};
// first buffer byte set to value 0x01 indicating read data    
    writeBuffer[0] = (0x01);
// 3, 4, 5 and 6 buffer bytes set to 0x00 - dummy bytes sent to only toggle SCLK line    
    writeBuffer[3] = (0x00);
    writeBuffer[4] = (0x00);    
    writeBuffer[5] = (0x00); 
    writeBuffer[6] = (0x00); 
//    writeBuffer[7] = (0x00); 

// set SPI slave select line to SigmaDSP
    SPIM_SpiSetActiveSlaveSelect(SPIM_SPI_SLAVE_SELECT0); 
    
// set read address based on incoming command
    switch (command)
    {    
//  0 = LEVEL = 0x0514
    case (0):
        writeBuffer[1] = (0x05);
        writeBuffer[2] = (0x14);
        break;
//  1 = Spectrum analyzer -> Right = 0x0526
    case (1):
        writeBuffer[1] = (0x05);
        writeBuffer[2] = (0x26);
        break;
//  2 = Spectrum analyzer -> Left = 0x0527
    case (2):
        writeBuffer[1] = (0x05);
        writeBuffer[2] = (0x27);
        break;        
//  3 = Spectrum analyzer -> Left&Right = 0x0528
    case (3):
        writeBuffer[1] = (0x05);
        writeBuffer[2] = (0x28);
        break;
//  4 = CODE = 0x001B
    case (4):
        writeBuffer[1] = (0x00);
        writeBuffer[2] = (0x1B);
        break;        
    }            
    
// Start SPI transfer
    SPIM_SpiUartPutArray(writeBuffer, 7);

// Wait for the end of the transfer. The number of transmitted data
// elements has to be equal to the number of received data elements.
    while (7 != SPIM_SpiUartGetRxBufferSize())
    {
    }

// Clear dummy bytes from TX buffer
    SPIM_SpiUartClearTxBuffer();

// Read data from the RX buffer
    i = 0u;
    while (0u != SPIM_SpiUartGetRxBufferSize())
    {
        readBuffer[i] = SPIM_SpiUartReadRxData();
//        UART_UartPutChar('0' + readBuffer[i]);
        i++;
    }
    
// Clear dummy bytes from RX buffer
    SPIM_SpiUartClearRxBuffer();
    
    
// format read back values into one 32 bit variable that is returned by 
// this function
    switch (command)
    {    
// 0 = LEVEL -> 0x0000aabb
//    -> aa - 0x00 - 0x10 - left channel 
//    -> bb - 0x00 - 0x10 - right channel
    case (0):
        status = readBuffer[5];
        status = status << 8;
        status = status | readBuffer[6];
        break;
// 1 = Spectrum analyzer -> Right
// b31-b28 - NOT_USED
// b27-b24 - 31.5Hz
// b23-b20 - 63Hz
// b19-b16 - 125Hz
// b15-b12 - 250Hz
// b11-b8 - 500Hz
// b7-b4 - 1000Hz
// b3-b0 - 2000Hz        
    case (1):
        status = readBuffer[3];
        status = status << 8;
        status = status | readBuffer[4];
        status = status << 8;
        status = status | readBuffer[5];
        status = status << 8;
        status = status | readBuffer[6];
        break;
//  2 = Spectrum analyzer -> Left
// b31-b28 - NOT_USED
// b27-b24 - 31.5Hz
// b23-b20 - 63Hz
// b19-b16 - 125Hz
// b15-b12 - 250Hz
// b11-b8 - 500Hz
// b7-b4 - 1000Hz
// b3-b0 - 2000Hz        
    case (2):
        status = readBuffer[3];
        status = status << 8;
        status = status | readBuffer[4];
        status = status << 8;
        status = status | readBuffer[5];
        status = status << 8;
        status = status | readBuffer[6];
        break;        
//  3 = Spectrum analyzer -> Left&Right
// LEFT
// b31-b28 - NOT_USED
// b27-b24 - 4000Hz
// b23-b20 - 8000Hz
// b19-b16 - 16000Hz
// RIGHT
// b15-b12 - NOT_USED
// b11-b8 - 4000Hz
// b7-b4 - 8000Hz
// b3-b0 - 16000Hz
    case (3):
        status = readBuffer[3];
        status = status << 8;
        status = status | readBuffer[4];
        status = status << 8;
        status = status | readBuffer[5];
        status = status << 8;
        status = status | readBuffer[6];        
        break;
//  4 = CODE 
// expected fixed value -> 32 bit word = 0xBE01BE02
    case (4):
        status = readBuffer[3];
        status = status << 8;
        status = status | readBuffer[4];
        status = status << 8;
        status = status | readBuffer[5];
        status = status << 8;
        status = status | readBuffer[6];
// REMOVE    
//        status = 0xBE01BE02;
// REMOVE    
        break;        
    }                
 
    
// set SPI slave select line to display module
    SPIM_SpiSetActiveSlaveSelect(SPIM_SPI_SLAVE_SELECT1);   
    
    return (status);
}


/* [] END OF FILE */
