/* ========================================
 *
 * Copyright HEMI, 2020
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 * 
 * Functions used by BeoModern main PSoC to switch unit into different states including
 * OFF, Clock, Player, iRadio, RDS/FM display, DAB radio, BT Rx, BT Tx, AuxIN
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF HEMI.
 *
 * ========================================
*/

#include <project.h>
#include <modes.h>
#include <inputs.h>



uint8 SYSTEM_STATE = 0;    /* variable used to store whole system state */    
uint8 DISPLAY_STATE = 0;   /* variable used to store display state */ 
uint8 BT_Tx_STATE = 0;     /* variable used to store BT Tx state */     



/*******************************************************************************
* Function Name: buttons_check()
********************************************************************************
* Summary:
*  Button press funciton that checkc button actions. It also initialize state
*  of main system to the latest one stored in emulated EEPROM space. 
*   
* Parameters:
*  None
*
* Return:
*  1 if button was pressed
*  0 if no button were pressed
*
*******************************************************************************/  
uint8 buttons_check()
{
    
// system state array stored in EEPROM
// [0] = SYSTEM_STATE 
// [1] = DISPLAY_STATE
// [2] = BT_Tx_STATE
uint8 array[]= { 0x00, 0x00, 0x00 };

// check if power button was pressed for short time      
    if (PWR_OK_SHORT_V == 1)
    {
// check if system is in power down state
        if (SYSTEM_STATE == 0)
        {
// if in power down state - restore system to last saved state
// Read data from emulated EEPROM
        Em_EEPROM_Read(LOGICAL_EEPROM_START, eepromArray, LOGICAL_EEPROM_SIZE);         
// set variables based on read data
        SYSTEM_STATE = eepromArray[0];
        DISPLAY_STATE = eepromArray[1];
        BT_Tx_STATE = eepromArray[2];
// start with system state in 1 to avoid infinite loop in system state 0
        if (SYSTEM_STATE == 0)
        {
            SYSTEM_STATE = 1;
        }
// clear push button variable
        PWR_OK_SHORT_V = 0;
// TO BE REMOVED
//        UART_UartPutChar(SYSTEM_STATE);
// TO BE REMOVED
        }
        else
// if system not in power down state, move to next system state based on PWR_OK button press
            {           
            SYSTEM_STATE = SYSTEM_STATE + 1;
            if (SYSTEM_STATE >= 8)
            {
                SYSTEM_STATE = 1;
            }
// clear push button variable
            PWR_OK_SHORT_V = 0;
// TO BE REMOVED TO BE REMOVED TO BE REMOVED TO BE REMOVED TO BE REMOVED TO BE REMOVED
//            UART_UartPutChar(SYSTEM_STATE);
// TO BE REMOVED TO BE REMOVED TO BE REMOVED TO BE REMOVED TO BE REMOVED TO BE REMOVED
            }
// return 1 indicating that button has been pressed
        return 1;
    }
 
    
// check if power button was pressed for long time (1 second)        
    if (PWR_OK_LONG_V == 1)
    {
// if it was, prepare array to write it to the EEPROM location
        array[0] =  SYSTEM_STATE;
        array[1] =  DISPLAY_STATE;
        array[2] =  BT_Tx_STATE;
 // Write data to emulated EEPROM
        Em_EEPROM_Write(LOGICAL_EEPROM_START, array, LOGICAL_EEPROM_SIZE);         
        
// set system state to power down mode
        SYSTEM_STATE = 0;
// set display state to power down
        DISPLAY_STATE = 0;
// clear push button variable
        PWR_OK_LONG_V = 0;
// TO BE REMOVED TO BE REMOVED TO BE REMOVED TO BE REMOVED TO BE REMOVED TO BE REMOVED
//        UART_UartPutChar(SYSTEM_STATE);
// TO BE REMOVED TO BE REMOVED TO BE REMOVED TO BE REMOVED TO BE REMOVED TO BE REMOVED
// return 1 indicating button press action
        return 1;
    }

    
// check if MODE button was pressed for short time 
    if (MODE_SHORT_V == 1)
    {
// clear push button variable
//        MODE_SHORT_V = 0;
// TO BE REMOVED TO BE REMOVED TO BE REMOVED TO BE REMOVED TO BE REMOVED TO BE REMOVED
//        UART_UartPutChar(0xAAu);
// TO BE REMOVED TO BE REMOVED TO BE REMOVED TO BE REMOVED TO BE REMOVED TO BE REMOVED
// return 1 indicating button press action
        return 1;
    }

    
// check if MODE button was pressed for long time 
    if (MODE_LONG_V == 1)
    {
// check if system is not in power down state
        if (SYSTEM_STATE != 0)
        {
// if it is not then move to next display state
        DISPLAY_STATE = DISPLAY_STATE + 1;
            if (DISPLAY_STATE >= 8)
            {
                DISPLAY_STATE = 1;
            }
        }
// clear push button variable
        MODE_LONG_V = 0;
// TO BE REMOVED TO BE REMOVED TO BE REMOVED TO BE REMOVED TO BE REMOVED TO BE REMOVED
//        UART_UartPutChar(DISPLAY_STATE);
// TO BE REMOVED TO BE REMOVED TO BE REMOVED TO BE REMOVED TO BE REMOVED TO BE REMOVED
// return 1 indicating button press action
    }

// return 0 indicating no button press action
    return 0;
} 

/*******************************************************************************
* Function Name: BT_control()
********************************************************************************
* Summary:
*  BlueTooth control funciton. Allows set all available bluetooth functions 
*  as well as it reads back BlueTooth module current status
*   
* Parameters:
*  mode:
*    0 = report back status only
*    1 = switch to Tx
*    2 = switch to Rx
*  action:
*    0 = report back status only
*    1 = start pairing
*    2 = re-connect
*    3 = clear all recorded devices
*    4 = pause/mute
*    5 = back (in Rx mode, previus song)
*    6 = next (in Rx mode, next song)
*
* Return:
*    0 = power down
*    1 = connected
*    2 = searching
*    3 = sleep
*    4 = SBC
*    5 = AAC
*    6 = aptX
*    7 = aptxHD
*    8 = aptxLL
*
*******************************************************************************/  
uint8 BT_control(uint8 mode, uint8 action)  
{
    uint8 BT_status = 0;
    uint8 swCounter = 0;
    uint8 loopCounter = 0;
// mode == 1 Tx state
    if (mode == 1)
    {
// enable Tx state        
        BT_Tx_Rx_Write(0);
//    1 = start pairing - double click pairing button      
        if (action == 1)
        {
// SENT OVER SPI informaiton about BlueTooth Tx Pairing status
// REPLACE with SPI transfer
            UART_UartPutString("\r\nBlueTooth Pairing (connect to BT-B20)");       
// REPLACE with SPI transfer
// ensure pairing signal is low            
            BT_RE_CONNECT_Write(0);
// set pairing signal to high             
            BT_RE_CONNECT_Write(1);
// wait 100 ms 
            CyDelay(100);            
// set pairing signal to low                   
            BT_RE_CONNECT_Write(0);
// wait 100 ms 
            CyDelay(100);            
// set pairing signal to high             
            BT_RE_CONNECT_Write(1);
// wait 100 ms 
            CyDelay(100);            
// set pairing signal to low                   
            BT_RE_CONNECT_Write(0);   
        }

//    2 = re-connect - single click pairing button
        if (action == 2)
        {
// SENT OVER SPI informaiton about BlueTooth Rx Reconnecting status
// REPLACE with SPI transfer
            UART_UartPutString("\r\nBlueTooth reconnecting");       
// REPLACE with SPI transfer
// ensure pairing signal is low            
            BT_RE_CONNECT_Write(0);
// set pairing signal to high             
            BT_RE_CONNECT_Write(1);
// wait 100 ms 
            CyDelay(100);            
// set pairing signal to low                   
            BT_RE_CONNECT_Write(0);          
        }
        
//    3 = clear all recorded devices
        if (action == 3)
        {
// SENT OVER SPI informaiton about BlueTooth Tx clearing status
// REPLACE with SPI transfer
            UART_UartPutString("\r\nBlueTooth clearing");       
// REPLACE with SPI transfer
// ensure pairing signal is low            
            BT_RE_CONNECT_Write(0);
// set pairing signal to high             
            BT_RE_CONNECT_Write(1);
// wait 9 seconds 
            CyDelay(9000);            
// set pairing signal to low                   
            BT_RE_CONNECT_Write(0);            
            
        }
//    4 = pause/mute   
        if (action == 4)
        {
// SENT OVER SPI informaiton about BlueTooth Tx mute status
// REPLACE with SPI transfer
            UART_UartPutString("\r\nBlueTooth mute");       
// REPLACE with SPI transfer
// ensure pause signal is low            
            BT_PAUSE_Write(0);
// set pause signal to high             
            BT_PAUSE_Write(1);
// wait 100 ms 
            CyDelay(100);            
// set pause signal to low                   
            BT_PAUSE_Write(0);               
        }
    }
    
    
// mode == 2 Rx state
    else if (mode == 2)
    {
// enable Rx state        
        BT_Tx_Rx_Write(1);
 //    1 = start pairing - double click pairing button      
        if (action == 1)
        {
// SENT OVER SPI informaiton about BlueTooth Rx Pairing status
// REPLACE with SPI transfer
            UART_UartPutString("\r\nBlueTooth Pairing (look for BT-B20)");       
// REPLACE with SPI transfer
// ensure pairing signal is low            
            BT_RE_CONNECT_Write(0);
// set pairing signal to high             
            BT_RE_CONNECT_Write(1);
// wait 100 ms 
            CyDelay(100);            
// set pairing signal to low                   
            BT_RE_CONNECT_Write(0);
// wait 100 ms 
            CyDelay(100);            
// set pairing signal to high             
            BT_RE_CONNECT_Write(1);
// wait 100 ms 
            CyDelay(100);            
// set pairing signal to low                   
            BT_RE_CONNECT_Write(0);   
        }

//    2 = re-connect - single click pairing button
        if (action == 2)
        {
// SENT OVER SPI informaiton about BlueTooth Tx reconnecting status
// REPLACE with SPI transfer
            UART_UartPutString("\r\nBlueTooth reconnecting");       
// REPLACE with SPI transfer            
// ensure pairing signal is low            
            BT_RE_CONNECT_Write(0);
// set pairing signal to high             
            BT_RE_CONNECT_Write(1);
// wait 100 ms 
            CyDelay(100);            
// set pairing signal to low                   
            BT_RE_CONNECT_Write(0);          
        }
        
//    3 = clear all recorded devices
        if (action == 3)
        {
// SENT OVER SPI informaiton about BlueTooth clearing Tx devices
// REPLACE with SPI transfer
            UART_UartPutString("\r\nBlueTooth clearing");       
// REPLACE with SPI transfer            
// ensure pairing signal is low            
            BT_RE_CONNECT_Write(0);
// set pairing signal to high             
            BT_RE_CONNECT_Write(1);
// wait 9 seconds 
            CyDelay(9000);            
// set pairing signal to low                   
            BT_RE_CONNECT_Write(0);            
        }
        
//    4 = pause/mute   
        if (action == 4)
        {
// SENT OVER SPI informaiton about BlueTooth Rx pause status
// REPLACE with SPI transfer
            UART_UartPutString("\r\nBlueTooth PAUSE");       
// REPLACE with SPI transfer   
// ensure pause signal is low            
            BT_PAUSE_Write(0);
// set pause signal to high             
            BT_PAUSE_Write(1);
// wait 100 ms 
            CyDelay(100);            
// set pause signal to low                   
            BT_PAUSE_Write(0);               
        }
        
//    5 = back (in Rx mode, previus song)
        if (action == 5)
        {
// SENT OVER SPI informaiton about BlueTooth Rx previus song
// REPLACE with SPI transfer
            UART_UartPutString("\r\nBlueTooth PREVIUS SONG");       
// REPLACE with SPI transfer 
// ensure previus signal is low            
            BT_PREVIOUS_Write(0);
// set previus signal to high             
            BT_PREVIOUS_Write(1);
// wait 100 ms 
            CyDelay(100);            
// set previous signal to low                   
            BT_PREVIOUS_Write(0);               
        }
        
//    6 = next (in Rx mode, next song)
        if (action == 6)
        {
// SENT OVER SPI informaiton about BlueTooth Rx next song
// REPLACE with SPI transfer
            UART_UartPutString("\r\nBlueTooth NEXT SONG");       
// REPLACE with SPI transfer   
// ensure next signal is low            
            BT_NEXT_Write(0);
// set next signal to high             
            BT_NEXT_Write(1);
// wait 100 ms 
            CyDelay(100);            
// set next signal to low                   
            BT_NEXT_Write(0);               
        }
    }
    
// mode == 0 (or any other) report state only
    else
    {
 // read back current PSU state    
        current_PSUstate = psu_config(2, current_PSUstate);    
 // check if BT module is powered up
        if (current_PSUstate.BlueTooth_PWR == 0)
        {
// if it is not return power down status            
            BT_status = 0;
        }
// if it is powered up, check its current state        
        else
            {
// check if BT statuts = SBC codec
                if (BT_SBC_Read())
                {
                    BT_status = 4;   
// SENT OVER SPI informaiton about BlueTooth codec info
// REPLACE with SPI transfer
                    UART_UartPutString("\r\nBT SBC codec");       
// REPLACE with SPI transfer 
                }
// check if BT status = AAC codec - reading back state of the pin directly
                if (CY_SYS_PINS_READ_PIN(CYREG_PRT4_PS,3) == 1)
                {
                    BT_status = 5;    
// SENT OVER SPI informaiton about BlueTooth codec info
// REPLACE with SPI transfer
                    UART_UartPutString("\r\nBT AAC codec");       
// REPLACE with SPI transfer 
                }
// check if BT statuts = APTx codec
                if (BT_APTX_Read())
                {
                    BT_status = 6;    
// SENT OVER SPI informaiton about BlueTooth codec info
// REPLACE with SPI transfer
                    UART_UartPutString("\r\nBT aptX codec");       
// REPLACE with SPI transfer 

                }                
// check if BT statuts = APTx HD codec
                if (BT_HD_Read())
                {
                    BT_status = 7;    
// SENT OVER SPI informaiton about BlueTooth codec info
// REPLACE with SPI transfer
                    UART_UartPutString("\r\nBT aptX HD codec");       
// REPLACE with SPI transfer 

                }                
// check if BT statuts = APTx LL codec
                if (BT_LL_Read())
                {
                    BT_status = 8;    
// SENT OVER SPI informaiton about BlueTooth codec info
// REPLACE with SPI transfer
                    UART_UartPutString("\r\nBT aptX LL codec");       
// REPLACE with SPI transfer 

                }   
// check if any BT connection is established (by checking codec status)
                if (BT_status < 4)
                {
// if not established check state of BT link
// BT_PAIRING - ON all the time - link established
// BT_PAIRING - ON and OFF every 300..500mS  - searching for device
// BT_PAIRING - ON for 300..500mS every 2 seconds - sleep state
// read back pin state for 1 second and calculate nubmer of 1 states                    
                    for (loopCounter = 0; loopCounter < 150; ++loopCounter)
                    {
// read back pairing state pin                    
                        if (!(BT_PAIRING_Read()))
                        {
// increase swCounter when 1                        
                            swCounter++;
// REMOVE REMOVE REMOVE REMOVE                            
                            LED_Write(1u);
// REMOVE REMOVE REMOVE REMOVE                            
                        }
// Provide a 10 ms delay to make the counter approximately periodic every 10 ms 
                        CyDelay(10);
// REMOVE REMOVE REMOVE REMOVE                        
                        LED_Write(0u);
// REMOVE REMOVE REMOVE REMOVE                        
                    }
// if all redbacks of pin state are 1                    
                    if(swCounter >= 149)
                    {
// BT is connected                        
                        BT_status = 1;
// SENT OVER SPI informaiton about BlueTooth status
// REPLACE with SPI transfer
                        UART_UartPutString("\r\nBT connected");       
// REPLACE with SPI transfer 

                    }
// if more than 50% and less than a 100%   
                    else if ((swCounter < 149) & (swCounter > 50))
                    {
// BT is searching                 
                        BT_status = 2;
// SENT OVER SPI informaiton about BlueTooth status
// REPLACE with SPI transfer
                        UART_UartPutString("\r\nBT searching");       
// REPLACE with SPI transfer 
                    }                 
// if less than 30% 
                    else
                        {
// BT in sleep state                               
                            BT_status = 3;
// SENT OVER SPI informaiton about BlueTooth status
// REPLACE with SPI transfer
                        UART_UartPutString("\r\nBT sleep");       
// REPLACE with SPI transfer 

                        }
// REMOVE REMOVE REMOVE REMOVE
//                    UART_UartPutString("\r\nCOUNTER VALUE = ");
//                    if (swCounter >= 100)
//                    {
//                        UART_UartPutChar('0' + (swCounter/100));                        
//                        swCounter = swCounter - 100;
//                        UART_UartPutChar('0' + (swCounter/10));                        
//                        UART_UartPutChar('0' + (swCounter%10));
//                    }
//                    else
//                        {
//                        UART_UartPutChar('0' + (swCounter/10));                        
//                        UART_UartPutChar('0' + (swCounter%10));
//                        }
// REMOVE REMOVE REMOVE REMOVE                    
                    
// clear counter                        
                    swCounter = 0;
                }
            }
    }
    
    return BT_status;
}




/*******************************************************************************
* Function Name: psu_config()
********************************************************************************
* Summary:
*  Power supply control funciton that enables/disables differnt BeoModern blocks
*  and reports back their current state.
*  It controls power supplies to:
*  - Raspberry Pi
*     - it reads back and reports state of RPi GPIO indicatign its state ON/OFF
*  - SigmaDSP EVB
*  - BlueTooth module
*  - Display module
*   
* Parameters:
*  switch - if 1, PSU states to be set, if other than 1 return current state
*  structure with expected stated of controlled blocks 
*
* Return:
*  structure with current states of controlled blocks 
*
*******************************************************************************/  
psuState psu_config(uint8 action, psuState new_PSUstate)  
{
// action == 1 indicates setting PSU
    if (action == 1)
    {
// enabling (1) or disabling (0) power supply for display module
        PWR_DISP_Write (new_PSUstate.Display_PWR); 
// enabling (1) or disabling (0) power supply for bluetooth module
        PWR_BT_Write (new_PSUstate.BlueTooth_PWR); 
// enabling (1) or disabling (0) power supply for SigmaDSP EVB
        PWR_SDSP_Write (new_PSUstate.SigmaDSP_PWR);
// enabling (1) or disabling (0) power supply for Raspberry Pi 
        PWR_RPI_Write (new_PSUstate.RPI_PWR);
    }
// reading back state of display enable/disable pin
    new_PSUstate.Display_PWR = PWR_DISP_ReadDataReg();
// reading back state of BlueTooth enable/disable pin
    new_PSUstate.BlueTooth_PWR = PWR_BT_ReadDataReg(); 
// reading back state of SigmaDSP enable/disable pin
    new_PSUstate.SigmaDSP_PWR = PWR_SDSP_ReadDataReg();
// reading back state of Raspberry Pi enable/disable pin
    new_PSUstate.RPI_PWR = PWR_RPI_ReadDataReg();
// reading back status pin that indicates Raspberry Pi state (1 = ON, 0 = OFF)
    new_PSUstate.RPi_GPIO_state = CY_SYS_PINS_READ_PIN(CYREG_PRT4_PS,2);
// returning current state of PSU controls
    return new_PSUstate;
}




/*******************************************************************************
* Function Name: datalink_decoder()
********************************************************************************
* Summary:
*  Function responsible for encoding raw datalink timing informaiton into
*  commands
*   
* Parameters:
*  No parameters as input. Function operates on global varaibles set by interrupt 
*  routine
*
* Return:
*  number of decoded command
*  0 - no new command
*
*******************************************************************************/  
uint8 datalink_decoder()  
{
// variable used to scan thru DATALINK readback time string 
    uint8 command_counter = 0;  
// variable used when converting bits to hex 
    uint64 hex_weight = 1;  
// variable used to move thru hex table  
//    uint8 hex_table_pointer = 0; 
// variable used to scan thru DATALINK readback time string 
    uint8 decoded_command_table_size = 0;  
// table to store decoded command    
    uint8 TIME_TABLE[64] = {0};
// table to store decoded command    
    uint8 COMMAND_TABLE[64] = {0};
// table to store commands in hex format    
    uint64 COMMAND_HEX = 0;

// check if new command is available to decode    
    if (DATALINK_TABLE_COUNTER_MAX != 0)
    {
// check if new time string has correct start and stop characters        
        if ( (80 - DATALINK_TABLE[1] >= 0) & 
             (80 - DATALINK_TABLE[1] < 15) &
             (80 - DATALINK_TABLE[2] >= 0) & 
             (80 - DATALINK_TABLE[2] < 15) &
             (80 - DATALINK_TABLE[3] >= 64) & 
             (80 - DATALINK_TABLE[3] <= 80) &
             (80 - DATALINK_TABLE[4] >= 0) & 
             (80 - DATALINK_TABLE[4] < 15) &
             (80 - DATALINK_TABLE[DATALINK_TABLE_COUNTER_MAX] >= 47) & 
             (80 - DATALINK_TABLE[DATALINK_TABLE_COUNTER_MAX] < 64) )
        {
// scan thru time table and convert measured time informations 
// into string of t1 = 1 ,t2 = 2, t3 = 3 time designators
            for (command_counter = 4 ; command_counter <= ( DATALINK_TABLE_COUNTER_MAX - 1 ); ++command_counter)
            {    
// invert convert number (down-count from 80) to number of DATALINK clock (5120Hz) ticks
// divide them by 15 and add 1 to get t1 = 1 ,t2 = 2, t3 = 3 times
                TIME_TABLE[command_counter - 4] = ((80 - DATALINK_TABLE[command_counter]) / 15) + 1;
// TO BE REMOVED TO BE REMOVED
//                UART_UartPutChar('0' + TIME_TABLE[command_counter - 4]);
// TO BE REMOVED TO BE REMOVED 
// increase size of counter that will determine table size with decoded word
                decoded_command_table_size = decoded_command_table_size + 1;
            }
// TO BE REMOVED TO BE REMOVED            
//            UART_UartPutString("\r\n"); 
// TO BE REMOVED TO BE REMOVED            
            COMMAND_TABLE[0] = 0;
// scan thru t1,t2,t3 table and encode it to 10 data following DATALINK spec
            for (command_counter = 0 ; command_counter < decoded_command_table_size; ++command_counter)
            {
// if t = 0 and t+1 = t1 -> error 
                if ( (COMMAND_TABLE[command_counter] == 0) & (TIME_TABLE[command_counter + 1] == 1) )
                {
                    return 2;
                }
// if t = 0 and t+1 = t2 -> 0
                else if ( (COMMAND_TABLE[command_counter] == 0) & (TIME_TABLE[command_counter + 1] == 2) )
                {
                    COMMAND_TABLE[command_counter + 1] = 0;
                }
// if t = 0 and t+1 = t3 -> 1
                else if ( (COMMAND_TABLE[command_counter] == 0) & (TIME_TABLE[command_counter + 1] == 3) )
                {
                    COMMAND_TABLE[command_counter + 1] = 1;
                }
// if t = 1 and t+1 = t1 -> 1
                else if ( (COMMAND_TABLE[command_counter] == 1) & (TIME_TABLE[command_counter + 1] == 1) )
                {
                    COMMAND_TABLE[command_counter + 1] = 0;
                }
// if t = 1 and t+1 = t2 -> 1
                else if ( (COMMAND_TABLE[command_counter] == 1) & (TIME_TABLE[command_counter + 1] == 2) )
                {
                    COMMAND_TABLE[command_counter + 1] = 1;
                }
// if t = 1 and t+1 = t3 -> error
                else if ( (COMMAND_TABLE[command_counter] == 1) & (TIME_TABLE[command_counter + 1] == 3) )
                {
                     return 2;
                }
// TO BE REMOVED TO BE REMOVED                             
//                UART_UartPutChar('0' + COMMAND_TABLE[command_counter]);
// TO BE REMOVED TO BE REMOVED 
            }
 // TO BE REMOVED TO BE REMOVED  
            UART_UartPutString("\r\n"); 
// TO BE REMOVED TO BE REMOVED    
// convert table with bit informaiton into 64 bits number for easier manipulation later on 
            if (decoded_command_table_size > 0)
            {
// scan thru table with bits starting from LSB                
                for (command_counter = decoded_command_table_size-1 ; command_counter > 0 ; --command_counter)
                {
// add bits values and its weight into one nubmer                    
                    COMMAND_HEX = COMMAND_HEX + COMMAND_TABLE[command_counter] * hex_weight; 
// increase weight value                    
                    hex_weight = 2 * hex_weight;
                }
            }
            
// TO BE REMOVED TO BE REMOVED 
            if (((COMMAND_HEX & 0xF000000000000000) >> 60) >0x09)
            {
                UART_UartPutChar('0' + (((COMMAND_HEX & 0xF000000000000000) >> 60) + 0x08));
            }
            else
            {
                UART_UartPutChar('0' + ((COMMAND_HEX & 0xF000000000000000) >> 60));
            }

            if (((COMMAND_HEX & 0x0F00000000000000) >> 56) >0x09)
            {
                UART_UartPutChar('0' + (((COMMAND_HEX & 0x0F00000000000000) >> 56) + 0x08));
            }
            else
            {
                UART_UartPutChar('0' + ((COMMAND_HEX & 0x0F00000000000000) >> 56));
            }
            
            if (((COMMAND_HEX & 0x00F0000000000000) >> 52) >0x09)
            {
                 UART_UartPutChar('0' + (((COMMAND_HEX & 0x00F0000000000000) >> 52) + 0x08));
            }
            else
            {
                 UART_UartPutChar('0' + ((COMMAND_HEX & 0x00F0000000000000) >> 52));
            }
            
            if (((COMMAND_HEX & 0x000F000000000000) >> 48) >0x09)
            {
                UART_UartPutChar('0' + (((COMMAND_HEX & 0x000F000000000000) >> 48) + 0x08));
            }
            else
            {
                UART_UartPutChar('0' + ((COMMAND_HEX & 0x000F000000000000) >> 48));
            }
            
            if (((COMMAND_HEX & 0x0000F00000000000) >> 44) >0x09)
            {
                  UART_UartPutChar('0' + (((COMMAND_HEX & 0x0000F00000000000) >> 44) + 0x08));
            }
            else
            {
                UART_UartPutChar('0' + ((COMMAND_HEX & 0x0000F00000000000) >> 44));
            }
            
            if (((COMMAND_HEX & 0x00000F0000000000) >> 40) >0x09)
            {
                UART_UartPutChar('0' + (((COMMAND_HEX & 0x00000F0000000000) >> 40) + 0x08));
            }
            else
            {
                UART_UartPutChar('0' + ((COMMAND_HEX & 0x00000F0000000000) >> 40));
            }
            
            if (((COMMAND_HEX & 0x000000F000000000) >> 36) >0x09)
            {
                UART_UartPutChar('0' + (((COMMAND_HEX & 0x000000F000000000) >> 36) + 0x08));
            }
            else
            {
                UART_UartPutChar('0' + ((COMMAND_HEX & 0x000000F000000000) >> 36));
            }
            
            if (((COMMAND_HEX & 0x0000000F00000000) >> 32) >0x09)
            {
                UART_UartPutChar('0' + (((COMMAND_HEX & 0x0000000F00000000) >> 32) + 0x08));
            }
            else
            {
                UART_UartPutChar('0' + ((COMMAND_HEX & 0x0000000F00000000) >> 32));
            }
            
            if (((COMMAND_HEX & 0x00000000F0000000) >> 28) >0x09)
            {
                UART_UartPutChar('0' + (((COMMAND_HEX & 0x00000000F0000000) >> 28) + 0x08));
            }
            else
            {
                UART_UartPutChar('0' + ((COMMAND_HEX & 0x00000000F0000000) >> 28));
            }
            
            if (((COMMAND_HEX & 0x000000000F000000) >> 24) >0x09)
            {
                UART_UartPutChar('0' + (((COMMAND_HEX & 0x000000000F000000) >> 24) + 0x08));
            }
            else
            {
                UART_UartPutChar('0' + ((COMMAND_HEX & 0x000000000F000000) >> 24));
            }
            
            if (((COMMAND_HEX & 0x0000000000F00000) >> 20) >0x09)
            {
                UART_UartPutChar('0' + (((COMMAND_HEX & 0x0000000000F00000) >> 20) + 0x08));
            }
            else
            {
                UART_UartPutChar('0' + ((COMMAND_HEX & 0x0000000000F00000) >> 20));
            }
            
            if (((COMMAND_HEX & 0x00000000000F0000) >> 16) >0x09)
            {
                UART_UartPutChar('0' + (((COMMAND_HEX & 0x00000000000F0000) >> 16) + 0x08));
            }
            else
            {
                UART_UartPutChar('0' + ((COMMAND_HEX & 0x00000000000F0000) >> 16));
            }
            
            if (((COMMAND_HEX & 0x000000000000F000) >> 12) >0x09)
            {
                UART_UartPutChar('0' + (((COMMAND_HEX & 0x000000000000F000) >> 12) + 0x08));
            }
            else
            {
                UART_UartPutChar('0' + ((COMMAND_HEX & 0x000000000000F000) >> 12));
            }
            
            if (((COMMAND_HEX & 0x0000000000000F00) >> 8) >0x09)
            {
                UART_UartPutChar('0' + (((COMMAND_HEX & 0x0000000000000F00) >> 8) + 0x08));
            }
            else
            {
                UART_UartPutChar('0' + ((COMMAND_HEX & 0x0000000000000F00) >> 8));
            }
                        
            if (((COMMAND_HEX & 0x00000000000000F0) >> 4) >0x09)
            {
                UART_UartPutChar('0' + (((COMMAND_HEX & 0x00000000000000F0) >> 4) + 0x08));
            }
            else
            {
                UART_UartPutChar('0' + ((COMMAND_HEX & 0x00000000000000F0) >> 4));
            }
            
            if ((COMMAND_HEX & 0x000000000000000F) >0x09)
            {
                UART_UartPutChar('0' + ((COMMAND_HEX & 0x000000000000000F) + 0x08));
            }
            else
            {
                UART_UartPutChar('0' + (COMMAND_HEX & 0x000000000000000F));
            }
// TO BE REMOVED TO BE REMOVED 
            
            
// reset time string table indicating readiness for decoding of new command                 
            DATALINK_TABLE_COUNTER_MAX = 0;
// return decoded command designator
            return 2;
                
        }
        else
            {
// reset time string table indicating readiness for decoding of new command                                 
                DATALINK_TABLE_COUNTER_MAX = 0;
// incorrect start and/or stop value - return 1 value
                return 1;
            }
    }
    else
        {
// reset time string table indicating readiness for decoding of new command                             
            DATALINK_TABLE_COUNTER_MAX = 0;
// no new command - return 0 value
            return 0;
        }    
}


/* [] END OF FILE */
