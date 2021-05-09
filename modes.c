/* ========================================
 *
* Copyright HEMI, 2021
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
#include <spi_int.h>

// variable used to store whole system state 
uint8 SYSTEM_STATE = 0;       
// variable used to store display state 
uint8 DISPLAY_STATE = 0;   
// variable used to store BT Tx state  
uint8 BT_Tx_STATE = 0;      

// flag used to indicate new data ready to be sent over SPI to display module
uint8 new_display_data_flag = 0;
// new data that needs to be sent over SPI to display module
uint8 new_display_data_buffer[24] = {"........................"};
uint8 new_disp_ctrl1 = 0;
uint8 new_disp_ctrl2 = 0;


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
        }
        else
// if system not in power down state, move to next system state based on PWR_OK button press
            {           
                SYSTEM_STATE = SYSTEM_STATE + 1;
                if (SYSTEM_STATE >= 9)
                {
                    SYSTEM_STATE = 1;
                }
// clear push button variable
                PWR_OK_SHORT_V = 0;
            }
// return 1 indicating that button has been pressed
        return 1;
    }
 
    
// check if power button was pressed for long time (1 second) 
// or messsage from display over SPI interface indicates timer expired and move to 
// power down state    
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
// return 1 indicating button press action
        return 1;
    }
    
// check if MODE button was pressed for short time 
    if (MODE_SHORT_V == 1)
    {
// operate function based on current state of the system    
        switch (SYSTEM_STATE)
        {

// SYSTEM_STATE = 0 - system in power down mode
// System shuld react only to display changes in this mode  
// no interaction from systme in power down state   
        case (0):
            break;

// SYSTEM_STATE = 1 - system in Player mode
// System reacts to commands:
// push button MODE Short = next song (DOWN and OK)
        case (1):
//  1 = Button: MODE SHORT  
            if (MODE_SHORT_V == 1)
            {
                UART_UartPutString("-UP+");
                CyDelay(100);  
                UART_UartPutString("-GO+");
                MODE_SHORT_V = 0;
            }
            break;
    
// SYSTEM_STATE = 2 - system in iRadio mode    
// System reacts to commands:
// push button MODE Short = next radio station (DOWN)
        case(2):
//  1 = Button: MODE SHORT  
            if (MODE_SHORT_V == 1)
            {
                UART_UartPutString("-UP+");
                CyDelay(100);  
                UART_UartPutString("-GO+");
                MODE_SHORT_V = 0;
            }
            break;
        
// SYSTEM_STATE = 3 - system in DAB Radio mode
// System reacts to commands:
// push button MODE Short = next radio station (DOWN)
        case(3):
//  1 = Button: MODE SHORT  
            if (MODE_SHORT_V == 1)
            {
                UART_UartPutString("-UP+");
                CyDelay(100);  
                UART_UartPutString("-GO+");
                MODE_SHORT_V = 0;
            }
            break;

// SYSTEM_STATE = 4 - system in AuxIn mode    
// System shuld react only to display changes in this mode  
// no interaction from MODE button in AuxIN state    
        case (4):
            break;
    
    
// SYSTEM_STATE = 5 - Clock
// System shuld react only to intercepted datalink commands with 
// FM station numbers. No interaction from MODE button in AuxIN state    
        case (5):
            break;
    
// SYSTEM_STATE = 6 - system in RDS/FM mode
// System shuld react only to intercepted datalink commands with 
// FM station numbers. No interaction from MODE button in AuxIN state    
        case (6):
            break;    
    
// SYSTEM_STATE = 7 - system in BlueTooth Rx mode
        case (7):
// System reacts to push button MODE Short = re-connecting
//  1 = Button: MODE SHORT  
            if (MODE_SHORT_V == 1)
            {
// BlueTooth start pairing        
                BT_control(2, 1); 
                MODE_SHORT_V = 0;
            }
            break;
    
// SYSTEM_STATE = 8 - system in BlueTooth Tx mode
        case (8):
// System reacts to push button MODE Short = re-connecting
//  1 = Button: MODE SHORT        
            if (MODE_SHORT_V == 1)
            {
// BlueTooth start pairing        
                BT_control(1, 1); 
                MODE_SHORT_V = 0;
            }
            break;      

        default:
// DEFAULT STATEMENT        
            break;

// clear flag            
        MODE_SHORT_V = 0;
// return 1 indicating button press action
        return 1;
        }
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
// return 1 indicating button press action
        return 1;
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
// new data that needs to be sent over SPI to display module
            strcpy((char*)new_display_data_buffer, "BT Pairing - name BT-B20");
// CTRL0.6 - Clear BT Rx indicator 
            new_disp_ctrl1 = new_disp_ctrl1 & 0xBF;
// CTRL1.0 - set BT Tx indicator 
            new_disp_ctrl2 = new_disp_ctrl2 | 0x01;
            new_display_data_flag = 1;
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
// new data that needs to be sent over SPI to display module
            strcpy((char*)new_display_data_buffer, "BlueTooth reconnecting  ");
// CTRL0.6 - Clear BT Rx indicator 
            new_disp_ctrl1 = new_disp_ctrl1 & 0xBF;
// CTRL1.0 - set BT Tx indicator 
            new_disp_ctrl2 = new_disp_ctrl2 | 0x01;
            new_display_data_flag = 1;
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
// new data that needs to be sent over SPI to display module
            strcpy((char*)new_display_data_buffer, "BlueTooth clearing ...  ");
// CTRL0.6 - Clear BT Rx indicator 
            new_disp_ctrl1 = new_disp_ctrl1 & 0xBF;
// CTRL1.0 - set BT Tx indicator 
            new_disp_ctrl2 = new_disp_ctrl2 | 0x01;
            new_display_data_flag = 1;
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
// new data that needs to be sent over SPI to display module
            strcpy((char*)new_display_data_buffer, "BlueTooth mute audio    ");
// CTRL0.6 - Clear BT Rx indicator 
            new_disp_ctrl1 = new_disp_ctrl1 & 0xBF;
// CTRL1.0 - set BT Tx indicator 
            new_disp_ctrl2 = new_disp_ctrl2 | 0x01;
            new_display_data_flag = 1;
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
// new data that needs to be sent over SPI to display module
            strcpy((char*)new_display_data_buffer, "BT Pairing search BT-B20");
            new_disp_ctrl1 = 0x40;
// CTRL1.0 - Clear BT Tx indicator 
            new_disp_ctrl2 = new_disp_ctrl2 & 0xFE;
            new_display_data_flag = 1;
            
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
// SENT OVER SPI informaiton about BlueTooth Rx reconnecting status
// new data that needs to be sent over SPI to display module
            strcpy((char*)new_display_data_buffer, "BlueTooth reconnecting  ");
            new_disp_ctrl1 = 0x40;
// CTRL1.0 - Clear BT Tx indicator 
            new_disp_ctrl2 = new_disp_ctrl2 & 0xFE;
            new_display_data_flag = 1;
     
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
// SENT OVER SPI informaiton about BlueTooth clearing Rx devices
// new data that needs to be sent over SPI to display module
            strcpy((char*)new_display_data_buffer, "BlueTooth clearing ...  ");
            new_disp_ctrl1 = 0x40;
// CTRL1.0 - Clear BT Tx indicator 
            new_disp_ctrl2 = new_disp_ctrl2 & 0xFE;
            new_display_data_flag = 1;       
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
// new data that needs to be sent over SPI to display module
            strcpy((char*)new_display_data_buffer, "BlueTooth PAUSE song    ");
            new_disp_ctrl1 = 0x40;
// CTRL1.0 - Clear BT Tx indicator 
            new_disp_ctrl2 = new_disp_ctrl2 & 0xFE;
            new_display_data_flag = 1;
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
// new data that needs to be sent over SPI to display module
            strcpy((char*)new_display_data_buffer, "BlueTooth PREVIUS song  ");
            new_disp_ctrl1 = 0x40;
// CTRL1.0 - Clear BT Tx indicator 
            new_disp_ctrl2 = new_disp_ctrl2 & 0xFE;
            new_display_data_flag = 1;
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
// new data that needs to be sent over SPI to display module
            strcpy((char*)new_display_data_buffer, "BlueTooth NEXT song     ");
            new_disp_ctrl1 = 0x40;
// CTRL1.0 - Clear BT Tx indicator 
            new_disp_ctrl2 = new_disp_ctrl2 & 0xFE;
            new_display_data_flag = 1; 
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
// new data that needs to be sent over SPI to display module
                    strcpy((char*)new_display_data_buffer, "BlueTooth SBC codec     ");
                    new_display_data_flag = 1; 
                }
// check if BT status = AAC codec - reading back state of the pin directly
                if (CY_SYS_PINS_READ_PIN(CYREG_PRT4_PS,3) == 1)
                {
                    BT_status = 5;    
// SENT OVER SPI informaiton about BlueTooth codec info
// new data that needs to be sent over SPI to display module
                    strcpy((char*)new_display_data_buffer, "BlueTooth AAC codec     ");
                    new_display_data_flag = 1; 
                }
// check if BT statuts = APTx codec
                if (BT_APTX_Read())
                {
                    BT_status = 6;    
// SENT OVER SPI informaiton about BlueTooth codec info
// new data that needs to be sent over SPI to display module
                    strcpy((char*)new_display_data_buffer, "BlueTooth aptX codec    ");
                    new_display_data_flag = 1; 
                }                
// check if BT statuts = APTx HD codec
                if (BT_HD_Read())
                {
                    BT_status = 7;    
// SENT OVER SPI informaiton about BlueTooth codec info
// new data that needs to be sent over SPI to display module
                    strcpy((char*)new_display_data_buffer, "BlueTooth aptX HD codec ");
                    new_display_data_flag = 1; 
                }                
// check if BT statuts = APTx LL codec
                if (BT_LL_Read())
                {
                    BT_status = 8;    
// SENT OVER SPI informaiton about BlueTooth codec info
// new data that needs to be sent over SPI to display module
                    strcpy((char*)new_display_data_buffer, "BlueTooth aptX LL codec ");
                    new_display_data_flag = 1; 

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
                        }
// Provide a 10 ms delay to make the counter approximately periodic every 10 ms 
                        CyDelay(10);
                    }
// if all redbacks of pin state are 1                    
                    if(swCounter >= 149)
                    {
// BT is connected                        
                        BT_status = 1;
// SENT OVER SPI informaiton about BlueTooth status
// new data that needs to be sent over SPI to display module
                        strcpy((char*)new_display_data_buffer, "BlueTooth connected     ");
                        new_display_data_flag = 1; 

// REPLACE with SPI transfer 

                    }
// if more than 50% and less than a 100%   
                    else if ((swCounter < 149) & (swCounter > 50))
                    {
// BT is searching                 
                        BT_status = 2;
// SENT OVER SPI informaiton about BlueTooth status
// new data that needs to be sent over SPI to display module
                        strcpy((char*)new_display_data_buffer, "BlueTooth searching ... ");
                        new_display_data_flag = 1; 
                    }                 
// if less than 30% 
                    else
                        {
// BT in sleep state                               
                            BT_status = 3;
// SENT OVER SPI informaiton about BlueTooth status
// new data that needs to be sent over SPI to display module
                        strcpy((char*)new_display_data_buffer, "BlueTooth in sleep state");
                        new_display_data_flag = 1; 

                        }
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
*  code represents error or decoded command as follow:
*   0 - no new command
*   1 - incorrect start and/or stop value
*   2 - if t = 0 and t+1 = t1 -> error or t = 1 and t+1 = t3 -> error
*  10 - only Aux button pressed - power up to last state
*  11 - Aux button pressed plus one digit number 1 or nubmer one to any of five aux devices
*  12 - Aux button pressed plus one digit number 2 or nubmer two  to any of five aux devices
*  13 - Aux button pressed plus one digit number 3 or nubmer three to any of five aux devices
*  14 - Aux button pressed plus one digit number 4 or nubmer four to any of five aux devices
*  15 - Aux button pressed plus one digit number 5 or nubmer five to any of five aux devices
*  16 - Digit number 6 to any of five aux devices
*  17 - Digit number 7 to any of five aux devices
*  18 - Digit number 8 to any of five aux devices
*  20 - OK/GO/PLAY to any of five aux devices
*  21 - UP/STEP > to any of five aux devices
*  22 - DOWN/< STEP to any of five aux devices
*  23 - LEFT/<< to any of five aux devices
*  24 - RIGHT/>> to any of five aux devices
*  25 - STOP to any of five aux devices
*  26 - POWER OFF to any of five aux devices
*  27 - MENU(onBeo4)/TURN(on MCP) to any of five aux devices
*  28 - EXIT(on Beo4)/RESET(on MCP) to any of five aux devices
*  31 - DISPLAY or yellow to any of five aux devices
*  32 - green to any of five aux devices
*  41 - FM Radio station 1
*  42 - FM Radio station 2
*  43 - FM Radio station 3
*  44 - FM Radio station 4
*  45 - FM Radio station 5
*  46 - FM Radio station 6
*  47 - FM Radio station 7
*  48 - FM Radio station 8
*  49 - FM Radio station 9
*  50 - FM Radio station 10
*  51 - FM Radio station 11
*  52 - FM Radio station 12
*  53 - FM Radio station 13
*  54 - FM Radio station 14
*  55 - FM Radio station 15
*  56 - FM Radio station 16
*  57 - FM Radio station 17
*  58 - FM Radio station 18
*  59 - FM Radio station 19
*  60 - FM Radio station 20
*
*******************************************************************************/  
uint8 datalink_decoder()  
{
// variable used to scan thru DATALINK readback time string 
    uint8 command_counter = 0;  
// variable used when converting bits to hex 
    uint64 hex_weight = 1;  
// variable used to scan thru DATALINK readback time string 
    uint8 decoded_command_table_size = 0;  
// table to store decoded command    
    uint8 TIME_TABLE[64] = {0};
// table to store decoded command    
    uint8 COMMAND_TABLE[64] = {0};
// table to store commands in hex format    
    uint64 COMMAND_HEX = 0;
// variable to store return status
    uint8 status = 0;

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
                
// increase size of counter that will determine table size with decoded word
                decoded_command_table_size = decoded_command_table_size + 1;
            }

            COMMAND_TABLE[0] = 0;

// scan thru t1,t2,t3 table and encode it to 10 data following DATALINK spec
            for (command_counter = 0 ; command_counter < decoded_command_table_size; ++command_counter)
            {
// if t = 0 and t+1 = t1 -> error 
                if ( (COMMAND_TABLE[command_counter] == 0) & (TIME_TABLE[command_counter + 1] == 1) )
                {
                    status = 2;
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
                     status = 2;
                }
            }

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
            
// Map remote control buttons to BeoModern commads
// BeoModern will respond to commands sent to Aux 1/2/3/4/5 inputs
// it will react to nubmers from 0-7, arrows up/down/let/right, power on/off,
// OK, stop/pause and display/color_buttons(toggle display mode)

// only Aux button pressed - power up to last state - return code 10
            if (COMMAND_HEX == 0x000003BC35000000)
            {        
                status = 10;
            }
// Aux button pressed plus one digit number 1 or nubmer one to any of five
// aux devices - return code 11
            else if ( (COMMAND_HEX == 0x000003BC05000000) | 
                    (COMMAND_HEX == 0x0000000000000001) |
                    (COMMAND_HEX == 0x0000000000000501) |
                    (COMMAND_HEX == 0x0000000000000A01) |
                    (COMMAND_HEX == 0x0000000000000601) |
                    (COMMAND_HEX == 0x0000000000012901) )
                {        
                    status = 11;
                }

// Aux button pressed plus one digit number 2 or nubmer two to any of five
// aux devices - return code 12
            else if ( (COMMAND_HEX == 0x000003BC55000000) |
                    (COMMAND_HEX == 0x0000000000000002) |
                    (COMMAND_HEX == 0x0000000000000502) |
                    (COMMAND_HEX == 0x0000000000000A02) |
                    (COMMAND_HEX == 0x0000000000000602) |
                    (COMMAND_HEX == 0x0000000000012902) )
                {        
                    status = 12;
                }

// Aux button pressed plus one digit number 3 or nubmer three to any of five
// aux devices - return code 13
            else if ( (COMMAND_HEX == 0x000003BCA5000000) |
                    (COMMAND_HEX == 0x0000000000000003) |
                    (COMMAND_HEX == 0x0000000000000503) |
                    (COMMAND_HEX == 0x0000000000000A03) |
                    (COMMAND_HEX == 0x0000000000000603) |
                    (COMMAND_HEX == 0x0000000000012903) )
                {        
                    status = 13;
                }

// Aux button pressed plus one digit number 4 or nubmer four to any of five
// aux devices - return code 14
            else if ( (COMMAND_HEX == 0x000003BC65000000) |
                    (COMMAND_HEX == 0x0000000000000004) |
                    (COMMAND_HEX == 0x0000000000000504) |
                    (COMMAND_HEX == 0x0000000000000A04) |
                    (COMMAND_HEX == 0x0000000000000604) |
                    (COMMAND_HEX == 0x0000000000012904) )
                {        
                    status = 14;
                }

// Aux button pressed plus one digit number 5 or nubmer five to any of five
// aux devices - return code 15
            else if ( (COMMAND_HEX == 0x000003BC85000000) |
                    (COMMAND_HEX == 0x0000000000000005) |
                    (COMMAND_HEX == 0x0000000000000505) |
                    (COMMAND_HEX == 0x0000000000000A05) |
                    (COMMAND_HEX == 0x0000000000000605) |
                    (COMMAND_HEX == 0x0000000000012905) )
                {        
                    status = 15;
                }        

// Digit number 6 to any of five aux devices - return code 16
            else if ( (COMMAND_HEX == 0x0000000000000006) |
                    (COMMAND_HEX == 0x0000000000000506) |
                    (COMMAND_HEX == 0x0000000000000A06) |
                    (COMMAND_HEX == 0x0000000000000606) |
                    (COMMAND_HEX == 0x0000000000012906) )
                {        
                    status = 16;
                }        

// Digit number 7 to any of five aux devices - return code 17
            else if ( (COMMAND_HEX == 0x0000000000000007) |
                    (COMMAND_HEX == 0x0000000000000507) |
                    (COMMAND_HEX == 0x0000000000000A07) |
                    (COMMAND_HEX == 0x0000000000000607) |
                    (COMMAND_HEX == 0x0000000000012907) )
                {        
                    status = 17;
                }        

// Digit number 8 to any of five aux devices - return code 18
            else if ( (COMMAND_HEX == 0x0000000000000008) |
                    (COMMAND_HEX == 0x0000000000000508) |
                    (COMMAND_HEX == 0x0000000000000A08) |
                    (COMMAND_HEX == 0x0000000000000608) |
                    (COMMAND_HEX == 0x0000000000012908) )
                {        
                    status = 18;
                } 
                
// OK/GO/PLAY to any of five aux devices - return code 20
            else if ( (COMMAND_HEX == 0x0000000000000035) |
                    (COMMAND_HEX == 0x0000000000000535) |
                    (COMMAND_HEX == 0x0000000000000A35) |
                    (COMMAND_HEX == 0x0000000000000635) |
                    (COMMAND_HEX == 0x0000000000012935) )
                {        
                    status = 20;
                } 

// UP/STEP > to any of five aux devices - return code 21
            else if ( (COMMAND_HEX == 0x000000000000001E) |
                    (COMMAND_HEX == 0x000000000000051E) |
                    (COMMAND_HEX == 0x0000000000000A1E) |
                    (COMMAND_HEX == 0x000000000000061E) |
                    (COMMAND_HEX == 0x000000000001291E) )
                {        
                    status = 21;
                }         
        
// DOWN/< STEP to any of five aux devices - return code 22
            else if ( (COMMAND_HEX == 0x000000000000001F) |
                    (COMMAND_HEX == 0x000000000000051F) |
                    (COMMAND_HEX == 0x0000000000000A1F) |
                    (COMMAND_HEX == 0x000000000000061F) |
                    (COMMAND_HEX == 0x000000000001291F) )
                {        
                    status = 22;
                } 

// LEFT/<< to any of five aux devices - return code 23
            else if ( (COMMAND_HEX == 0x0000000000000032) |
                    (COMMAND_HEX == 0x0000000000000532) |
                    (COMMAND_HEX == 0x0000000000000A32) |
                    (COMMAND_HEX == 0x0000000000000632) |
                    (COMMAND_HEX == 0x0000000000012932) )
                {        
                    status = 23;
                } 

// RIGHT/>> to any of five aux devices - return code 24
            else if ( (COMMAND_HEX == 0x0000000000000034) |
                    (COMMAND_HEX == 0x0000000000000534) |
                    (COMMAND_HEX == 0x0000000000000A34) |
                    (COMMAND_HEX == 0x0000000000000634) |
                    (COMMAND_HEX == 0x0000000000012934) )
                {        
                    status = 24;
                } 

// STOP to any of five aux devices - return code 25
            else if ( (COMMAND_HEX == 0x0000000000000036) |
                    (COMMAND_HEX == 0x0000000000000536) |
                    (COMMAND_HEX == 0x0000000000000A36) |
                    (COMMAND_HEX == 0x0000000000000636) |
                    (COMMAND_HEX == 0x0000000000012936) )
                {        
                    status = 25;
                } 

// POWER OFF to any of five aux devices - return code 26
            else if ( COMMAND_HEX == 0x0000003BC1400200 )
                {        
                    status = 26;
                } 

// MENU(onBeo4)/TURN(on MCP) to any of five aux devices - return code 27
            else if ( (COMMAND_HEX == 0x000000000000005C) |
                    (COMMAND_HEX == 0x000000000000055C) |
                    (COMMAND_HEX == 0x0000000000000A5C) |
                    (COMMAND_HEX == 0x000000000000065C) |
                    (COMMAND_HEX == 0x000000000001295C) |
                    (COMMAND_HEX == 0x0000000000000046) |
                    (COMMAND_HEX == 0x0000000000000546) |
                    (COMMAND_HEX == 0x0000000000000A46) |
                    (COMMAND_HEX == 0x0000000000000646) |
                    (COMMAND_HEX == 0x0000000000012946) )
                {        
                    status = 27;
                } 

// EXIT(on Beo4)/RESET(on MCP) to any of five aux devices - return code 28
            else if ( (COMMAND_HEX == 0x000000000000007F) |
                    (COMMAND_HEX == 0x000000000000057F) |
                    (COMMAND_HEX == 0x0000000000000A7F) |
                    (COMMAND_HEX == 0x000000000000067F) |
                    (COMMAND_HEX == 0x000000000001297F) |
                    (COMMAND_HEX == 0x0000003BC348741A) )
                {        
                    status = 28;
                } 
            
// DISPLAY or yellow to any of five aux devices - return code 31
            else if ( (COMMAND_HEX == 0x0000000000000059) |
                    (COMMAND_HEX == 0x0000000000000559) |
                    (COMMAND_HEX == 0x0000000000000A59) |
                    (COMMAND_HEX == 0x0000000000000659) |
                    (COMMAND_HEX == 0x0000000000012959) |
                    (COMMAND_HEX == 0x00000000000000D4) |
                    (COMMAND_HEX == 0x00000000000005D4) |
                    (COMMAND_HEX == 0x0000000000000AD4) |
                    (COMMAND_HEX == 0x00000000000006D4) |
                    (COMMAND_HEX == 0x00000000000129D4) )
            {        
                status = 31;
            } 

// green to any of five aux devices - return code 32
            else if ( (COMMAND_HEX == 0x00000000000000D5) |
                    (COMMAND_HEX == 0x00000000000005D5) |
                    (COMMAND_HEX == 0x0000000000000AD5) |
                    (COMMAND_HEX == 0x00000000000006D5) |
                    (COMMAND_HEX == 0x00000000000129D5) )
            {        
                status = 32;
            } 

// FM Radio station 1 - return code 41
            else if ( COMMAND_HEX == 0x0000003BC1400001 )
            {        
                status = 41;
            }             
// FM Radio station 2 - return code 42
            else if ( COMMAND_HEX == 0x0000003BC1400002 )
            {        
                status = 42;
            }             
// FM Radio station 3 - return code 43
            else if ( COMMAND_HEX == 0x0000003BC1400003 )
            {        
                status = 43;
            }             
// FM Radio station 4 - return code 44
            else if ( COMMAND_HEX == 0x0000003BC1400004 )
            {        
                status = 44;
            }             
// FM Radio station 5 - return code 45
            else if ( COMMAND_HEX == 0x0000003BC1400005 )
            {        
                status = 45;
            }             
// FM Radio station 6 - return code 46
            else if ( COMMAND_HEX == 0x0000003BC1400006 )
            {        
                status = 46;
            }             
// FM Radio station 7 - return code 47
            else if ( COMMAND_HEX == 0x0000003BC1400007 )
            {        
                status = 47;
            }             
// FM Radio station 8 - return code 48
            else if ( COMMAND_HEX == 0x0000003BC1400008 )
            {        
                status = 48;
            }             
// FM Radio station 9 - return code 49
            else if ( COMMAND_HEX == 0x0000003BC1400009 )
            {        
                status = 49;
            }             
// FM Radio station 10 - return code 50
            else if ( COMMAND_HEX == 0x0000003BC140000A )
            {        
                status = 50;
            }             
// FM Radio station 11 - return code 51
            else if ( COMMAND_HEX == 0x0000003BC140000B )
            {        
                status = 51;
            }             
// FM Radio station 12 - return code 52
            else if ( COMMAND_HEX == 0x0000003BC140000C )
            {        
                status = 52;
            }             
// FM Radio station 13 - return code 53
            else if ( COMMAND_HEX == 0x0000003BC140000D )
            {        
                status = 53;
            }             
// FM Radio station 14 - return code 54
            else if ( COMMAND_HEX == 0x0000003BC140000E )
            {        
                status = 54;
            }             
// FM Radio station 15 - return code 55
            else if ( COMMAND_HEX == 0x0000003BC140000F )
            {        
                status = 55;
            }             
// FM Radio station 16 - return code 56
            else if ( COMMAND_HEX == 0x0000003BC1400010 )
            {        
                status = 56;
            }             
// FM Radio station 17 - return code 57
            else if ( COMMAND_HEX == 0x0000003BC1400011 )
            {        
                status = 57;
            }             
// FM Radio station 18 - return code 58
            else if ( COMMAND_HEX == 0x0000003BC1400012 )
            {        
                status = 58;
            }             
// FM Radio station 19 - return code 59
            else if ( COMMAND_HEX == 0x0000003BC1400013 )
            {        
                status = 59;
            }             
// FM Radio station 20 - return code 60
            else if ( COMMAND_HEX == 0x0000003BC1400014 )
            {        
                status = 60;
            }             
        }
        else
            {
// incorrect start and/or stop value - return 1 value
            status = 1;
            }
    }

// reset time string table indicating readiness for decoding of new command                             
        DATALINK_TABLE_COUNTER_MAX = 0;
// no new command - return 0 value
        return status;
}




/*******************************************************************************
* Function Name: SigmaDSP_to_display()
********************************************************************************
* Summary:
*  Function 
*   
* Parameters:
*  0 - read back signal level values and encode them into information sent to 
*      display module
*  1 - read back spectrum analyser info and encode it into informaiton sent to
*      display module
*
* Return:
*  Funciton returns zero value
*
*******************************************************************************/  
uint8 SigmaDSP_to_display(uint8 mode)  
{
// variable used to store values returned from SigmaDSP 
    uint32 status = 0;
// variable used to produce level informaiton on display
    uint8 display_counter = 0;
    
    
// execute sequence based on mode informaiton
    switch (mode)
    {    
// 0 = LEVEL
    case (0):
// 0 = LEVEL info -> 0x0000aabb
//    -> aa - 0x00 - 0x10 - left channel 
//    -> bb - 0x00 - 0x10 - right channel
        status = SPIM_SigmaDSP_read(0);
// display data
// 0 = empty display
// 1 = bottom (right) empty square
// 2 = top (left) empty square
// 3 = both bottom and top (left and right) empty squares        
// 5 = bottom (right) full square
// 6 = top (left) full square
// 7 = both bottom and top (left and right) full squares        
// 8 = arrow left
// 9 = arrow right
// prepare status header for display    
        new_display_data_buffer[0] = '8';
        new_display_data_buffer[1] = '9';
     
// check and display signals below 0dB        
        for (display_counter = 0; display_counter<=0x13; display_counter++)
        {
// left and right channel info            
            if ( (((status >> 8) & 0x000000FF) >= display_counter) && ((status & 0x000000FF) >= display_counter) )
            {
                new_display_data_buffer[display_counter+2] = '3';
            }
// left channel info
            else if ( (((status >> 8) & 0x000000FF) >= display_counter) && ((status & 0x000000FF) < display_counter) )
            {
                new_display_data_buffer[display_counter+2] = '2';
            }
// right channel info
            else if ( (((status >> 8) & 0x000000FF) < display_counter) && ((status & 0x000000FF) >= display_counter) )
            {
                new_display_data_buffer[display_counter+2] = '1';
            }
            else 
// fill remining places with zeros            
                {
                    new_display_data_buffer[display_counter+2] = '0';
                }
        }
                
        new_display_data_buffer[2] = '0';
                
// check and display signals below and 0dB and above
        for (display_counter = 0x13; display_counter<=0x15; display_counter++)
        {
// left and right channel info            
            if ( (((status >> 8) & 0x000000FF) >= display_counter) && ((status & 0x000000FF) >= display_counter) )
            {
                new_display_data_buffer[display_counter+2] = '7';
            }
// left channel info
            else if ( (((status >> 8) & 0x000000FF) >= display_counter) && ((status & 0x000000FF) < display_counter) )
            {
                new_display_data_buffer[display_counter+2] = '6';
            }
// right channel info
            else if ( (((status >> 8) & 0x000000FF) < display_counter) && ((status & 0x000000FF) >= display_counter) )
            {
                new_display_data_buffer[display_counter+2] = '5';
            }
            else 
// fill remining places with zeros            
                {
                    new_display_data_buffer[display_counter+2] = '0';
                }
        }
        
        break;

        
// 1 = spectrum analyser        
    case (1):
// prepare headers to indicate levt and right channels 
        new_display_data_buffer[0] = ' ';
        new_display_data_buffer[1] = 'L';
// read back 
// 2 = Spectrum analyzer -> Left 
//    b31-b28 - NOT_USED
        status = SPIM_SigmaDSP_read(2);
//    b27-b24 - 31.5Hz
        new_display_data_buffer[2] = '0' + ((status >> 24) & 0x0000000F);
//    b23-b20 - 63Hz
        new_display_data_buffer[3] = '0' + ((status >> 20) & 0x0000000F);
//    b19-b16 - 125Hz
        new_display_data_buffer[4] = '0' + ((status >> 16) & 0x0000000F);
//    b15-b12 - 250Hz
        new_display_data_buffer[5] = '0' + ((status >> 12) & 0x0000000F);
//    b11-b8 - 500Hz
        new_display_data_buffer[6] = '0' + ((status >> 8) & 0x0000000F);
//    b7-b4 - 1000Hz        
        new_display_data_buffer[7] = '0' + ((status >> 4) & 0x0000000F);       
//    b3-b0 - 2000Hz                
        new_display_data_buffer[8] = '0' + (status & 0x0000000F);

// read back
// 3 = Spectrum analyzer -> Left&Right 
//    b31-b28 - NOT_USED
//    b15-b12 - NOT_USED
        status = SPIM_SigmaDSP_read(3);        
//    LEFT
//    b27-b24 - 4000Hz
       new_display_data_buffer[9] = '0' + ((status >> 24) & 0x0000000F);
//    b23-b20 - 8000Hz
        new_display_data_buffer[10] = '0' + ((status >> 20) & 0x0000000F);
//    b19-b16 - 16000Hz
        new_display_data_buffer[11] = '0' + ((status >> 16) & 0x0000000F);
        
//    RIGHT
        new_display_data_buffer[12] = ' ';
        new_display_data_buffer[13] = 'R';
//    b11-b8 - 4000Hz
        new_display_data_buffer[21] = '0' + ((status >> 8) & 0x0000000F);
//    b7-b4 - 8000Hz       
        new_display_data_buffer[22] = '0' + ((status >> 4) & 0x0000000F);       
//    b3-b0 - 16000Hz                
        new_display_data_buffer[23] = '0' + (status & 0x0000000F);
 
//read back
// 1 = Spectrum analyzer -> Right 
//    b31-b28 - NOT_USED
        status = SPIM_SigmaDSP_read(1);
//    b27-b24 - 31.5Hz
        new_display_data_buffer[14] = '0' + ((status >> 24) & 0x0000000F);
//    b23-b20 - 63Hz
        new_display_data_buffer[15] = '0' + ((status >> 20) & 0x0000000F);
//    b19-b16 - 125Hz
        new_display_data_buffer[16] = '0' + ((status >> 16) & 0x0000000F);
//    b15-b12 - 250Hz
        new_display_data_buffer[17] = '0' + ((status >> 12) & 0x0000000F);
//    b11-b8 - 500Hz
        new_display_data_buffer[18] = '0' + ((status >> 8) & 0x0000000F);
//    b7-b4 - 1000Hz        
        new_display_data_buffer[19] = '0' + ((status >> 4) & 0x0000000F);       
//    b3-b0 - 2000Hz                
        new_display_data_buffer[20] = '0' + (status & 0x0000000F);

        break;
    }
    
    return 0;
}


/*******************************************************************************
* Function Name: DATALINK_times()
********************************************************************************
* Summary:
*  Function responsible for producing activity on DATALINK line following
*  DATALINK standard.
*   
* Parameters:
*  time - 1 for t1 = 3.125mS 
*         2 for t2 = 6.250mS
*         3 for t3 = 9.375mS
*         4 for t4 = 12.500mS
*         5 for t5 = 15.625mS
*
* Return:
*  1 if all good
*  0 if there was a clash on datalink port (another device transmitted)
*
*******************************************************************************/  
uint8 DATALINK_times(uint8 time)  
{
// counter used for time t1..t5 commands    
    uint32 datalink_counter = 0;

// check if DATALINK is not already engadged (held low by some other device)    
    if (DATALINK_Read() == 0)
    {
// if it is return 0 and stop        
        return 0;
    }
    else
        {
// if it is not then held datalink line low for 1.5625mS
            DATALINK_Write(0x00);
            CyDelay(1);
            CyDelayUs(562);
            DATALINK_Write(0x01);
        }
 // wait 10uS for DATALINK pin to settle before checkign its state
    CyDelayUs(10);

// based on input commad hold datalink line high for prescribed amount of time.
// check if line is high (not taken over by another device) during that period of time
// if datalink line will go low, stop symbol tranmission and return 0    
    switch (time)
        {

// t1 = 3.125mS 
        case (1):
            for (datalink_counter = 0; datalink_counter <=1565 ; datalink_counter++)
            {
                if (DATALINK_Read() == 0x00)
                {
                    return 0;
                }   
            }
            break;

// t2 = 6.250mS
        case (2):
            for (datalink_counter = 0; datalink_counter <=4665 ; datalink_counter++)    
            {
                if (DATALINK_Read() == 0x00)
                {
                    return 0;
                }   
            }
            break;

// t3 = 9.375mS
        case (3):            
            for (datalink_counter = 0; datalink_counter <=7760 ; datalink_counter++)    
            {
                if (DATALINK_Read() == 0x00)
                {
                    return 0;
                }   
            }
            break;

// t4 = 12.500mS
        case (4):
            for (datalink_counter = 0; datalink_counter <=11000 ; datalink_counter++)    
            {
                if (DATALINK_Read() == 0x00)
                {
                    return 0;
                }   
            }
            break;

// t5 = 15.625mS
            case (5):
            for (datalink_counter = 0; datalink_counter <=14050 ; datalink_counter++)    
            {
                if (DATALINK_Read() == 0x00)
                {
                    return 0;
                }   
            }
            break;
        }

// return 1 if all good
    return 1;
}


/*******************************************************************************
* Function Name: DATALINK_out()
********************************************************************************
* Summary:
*  Function reposnisble for sending data over datalink port. Implementaton is quite 
*  crude due to the fact that device will require only two commands. Power up 
*  (in Aux mode) and power down.
*   
* Parameters:
*  command = 0 -> 0 button pressed 
*          = 1 -> 1 button pressed
*          = 2 -> 2 button pressed
*          = 3 -> 3 button pressed
*          = 4 -> 4 button pressed
*          = 5 -> 5 button pressed
*          = 6 -> 6 button pressed
*          = 7 -> 7 button pressed
*          = 8 -> 8 button pressed
*          = 9 -> 9 button pressed
*          = 10 -> GO button pressed
*          = 11 -> LIST button pressed
*          = 12 -> POWER DOWN from aux devices 
*
* Return:
*  0 = conflict on DATALINK port was recorded function didn't finish its 
*      command transmission
*  1 = command sent succesfully (no confilct on DATALINK line)
*
*******************************************************************************/  
uint8 DATALINK_out(uint8 command)  
{
    switch (command)
        {
// 0 button pressed 
        case (0):
            DATALINK_INTRRUPT_Disable();
// START 1151 
            if (DATALINK_times(1) == 0) { return 0; }
            if (DATALINK_times(1) == 0) { return 0; }
            if (DATALINK_times(5) == 0) { return 0; }
            if (DATALINK_times(1) == 0) { return 0; }
// DATA
// 2222  
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
// 2223  
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(3) == 0) { return 0; }
// 1222 
            if (DATALINK_times(1) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
// 2222 
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
// 41  
            if (DATALINK_times(4) == 0) { return 0; }
            if (DATALINK_times(1) == 0) { return 0; }
     
            DATALINK_INTRRUPT_Enable();
            
            break;
            
// 1 button pressed
        case (1):
            DATALINK_INTRRUPT_Disable();
// START 1151 
            if (DATALINK_times(1) == 0) { return 0; }
            if (DATALINK_times(1) == 0) { return 0; }
            if (DATALINK_times(5) == 0) { return 0; }
            if (DATALINK_times(1) == 0) { return 0; }
// DATA
// 2222  
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
// 2223  
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(3) == 0) { return 0; }
// 1222 
            if (DATALINK_times(1) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
// 2223 
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(3) == 0) { return 0; }
// 41  
            if (DATALINK_times(4) == 0) { return 0; }
            if (DATALINK_times(1) == 0) { return 0; }
         
            DATALINK_INTRRUPT_Enable();

            break;

// 2 button pressed
        case (2):
            DATALINK_INTRRUPT_Disable();
// START 1151 
            if (DATALINK_times(1) == 0) { return 0; }
            if (DATALINK_times(1) == 0) { return 0; }
            if (DATALINK_times(5) == 0) { return 0; }
            if (DATALINK_times(1) == 0) { return 0; }
// DATA
// 2222  
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
// 2223  
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(3) == 0) { return 0; }
// 1222 
            if (DATALINK_times(1) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
// 2231 
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(3) == 0) { return 0; }
            if (DATALINK_times(1) == 0) { return 0; }
// 41  
            if (DATALINK_times(4) == 0) { return 0; }
            if (DATALINK_times(1) == 0) { return 0; }
         
            DATALINK_INTRRUPT_Enable();

            break;

// 3 button pressed
        case (3):
            DATALINK_INTRRUPT_Disable();
// START 1151 
            if (DATALINK_times(1) == 0) { return 0; }
            if (DATALINK_times(1) == 0) { return 0; }
            if (DATALINK_times(5) == 0) { return 0; }
            if (DATALINK_times(1) == 0) { return 0; }
// DATA
// 2222  
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
// 2223  
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(3) == 0) { return 0; }
// 1222 
            if (DATALINK_times(1) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
// 2232 
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(3) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
// 41  
            if (DATALINK_times(4) == 0) { return 0; }
            if (DATALINK_times(1) == 0) { return 0; }
         
            DATALINK_INTRRUPT_Enable();

            break;            

// 4 button pressed
        case (4):
            DATALINK_INTRRUPT_Disable();
// START 1151 
            if (DATALINK_times(1) == 0) { return 0; }
            if (DATALINK_times(1) == 0) { return 0; }
            if (DATALINK_times(5) == 0) { return 0; }
            if (DATALINK_times(1) == 0) { return 0; }
// DATA
// 2222  
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
// 2223  
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(3) == 0) { return 0; }
// 1222 
            if (DATALINK_times(1) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
// 2312 
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(3) == 0) { return 0; }
            if (DATALINK_times(1) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
// 41  
            if (DATALINK_times(4) == 0) { return 0; }
            if (DATALINK_times(1) == 0) { return 0; }
         
            DATALINK_INTRRUPT_Enable();

            break;     
            
// 5 button pressed
        case (5):
            DATALINK_INTRRUPT_Disable();
// START 1151 
            if (DATALINK_times(1) == 0) { return 0; }
            if (DATALINK_times(1) == 0) { return 0; }
            if (DATALINK_times(5) == 0) { return 0; }
            if (DATALINK_times(1) == 0) { return 0; }
// DATA
// 2222  
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
// 2223  
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(3) == 0) { return 0; }
// 1222 
            if (DATALINK_times(1) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
// 2313 
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(3) == 0) { return 0; }
            if (DATALINK_times(1) == 0) { return 0; }
            if (DATALINK_times(3) == 0) { return 0; }
// 41  
            if (DATALINK_times(4) == 0) { return 0; }
            if (DATALINK_times(1) == 0) { return 0; }
         
            DATALINK_INTRRUPT_Enable();

            break;                 
/*
// 6 button pressed
        case (6):
            DATALINK_INTRRUPT_Disable();
// START 1151 
            if (DATALINK_times(1) == 0) { return 0; }
            if (DATALINK_times(1) == 0) { return 0; }
            if (DATALINK_times(5) == 0) { return 0; }
            if (DATALINK_times(1) == 0) { return 0; }
// DATA
// 2222  
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
// 2223  
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(3) == 0) { return 0; }
// 1222 
            if (DATALINK_times(1) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
// 2321 
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(3) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(1) == 0) { return 0; }
// 41  
            if (DATALINK_times(4) == 0) { return 0; }
            if (DATALINK_times(1) == 0) { return 0; }
         
            DATALINK_INTRRUPT_Enable();

            break;                        

// 7 button pressed
        case (7):
            DATALINK_INTRRUPT_Disable();
// START 1151 
            if (DATALINK_times(1) == 0) { return 0; }
            if (DATALINK_times(1) == 0) { return 0; }
            if (DATALINK_times(5) == 0) { return 0; }
            if (DATALINK_times(1) == 0) { return 0; }
// DATA
// 2222  
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
// 2223  
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(3) == 0) { return 0; }
// 1222 
            if (DATALINK_times(1) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
// 2322 
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(3) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
// 41  
            if (DATALINK_times(4) == 0) { return 0; }
            if (DATALINK_times(1) == 0) { return 0; }
         
            DATALINK_INTRRUPT_Enable();

            break;                        

// 8 button pressed
        case (8):
            DATALINK_INTRRUPT_Disable();
// START 1151 
            if (DATALINK_times(1) == 0) { return 0; }
            if (DATALINK_times(1) == 0) { return 0; }
            if (DATALINK_times(5) == 0) { return 0; }
            if (DATALINK_times(1) == 0) { return 0; }
// DATA
// 2222  
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
// 2223  
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(3) == 0) { return 0; }
// 1222 
            if (DATALINK_times(1) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
// 3122 
            if (DATALINK_times(3) == 0) { return 0; }
            if (DATALINK_times(1) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
// 41  
            if (DATALINK_times(4) == 0) { return 0; }
            if (DATALINK_times(1) == 0) { return 0; }
         
            DATALINK_INTRRUPT_Enable();

            break;         

// 9 button pressed
        case (9):
            DATALINK_INTRRUPT_Disable();
// START 1151 
            if (DATALINK_times(1) == 0) { return 0; }
            if (DATALINK_times(1) == 0) { return 0; }
            if (DATALINK_times(5) == 0) { return 0; }
            if (DATALINK_times(1) == 0) { return 0; }
// DATA
// 2222  
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
// 2223  
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(3) == 0) { return 0; }
// 1222 
            if (DATALINK_times(1) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
// 3123 
            if (DATALINK_times(3) == 0) { return 0; }
            if (DATALINK_times(1) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(3) == 0) { return 0; }
// 41  
            if (DATALINK_times(4) == 0) { return 0; }
            if (DATALINK_times(1) == 0) { return 0; }
         
            DATALINK_INTRRUPT_Enable();

            break;             
*/            
// GO button pressed
        case (10):
            DATALINK_INTRRUPT_Disable();
// START 1151 
            if (DATALINK_times(1) == 0) { return 0; }
            if (DATALINK_times(1) == 0) { return 0; }
            if (DATALINK_times(5) == 0) { return 0; }
            if (DATALINK_times(1) == 0) { return 0; }
// DATA
// 2222  
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
// 2223  
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(3) == 0) { return 0; }
// 2122 
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(1) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
// 2232 
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(3) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
// 41  
            if (DATALINK_times(4) == 0) { return 0; }
            if (DATALINK_times(1) == 0) { return 0; }
         
            DATALINK_INTRRUPT_Enable();
              
            break;
            
// LIST button pressed
        case (11):
            DATALINK_INTRRUPT_Disable();
// START 1151 
            if (DATALINK_times(1) == 0) { return 0; }
            if (DATALINK_times(1) == 0) { return 0; }
            if (DATALINK_times(5) == 0) { return 0; }
            if (DATALINK_times(1) == 0) { return 0; }
// DATA
// 2222  
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
// 2223  
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(3) == 0) { return 0; }
// 1313 
            if (DATALINK_times(1) == 0) { return 0; }
            if (DATALINK_times(3) == 0) { return 0; }
            if (DATALINK_times(1) == 0) { return 0; }
            if (DATALINK_times(3) == 0) { return 0; }
// 2122 
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(1) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
// 41  
            if (DATALINK_times(4) == 0) { return 0; }
            if (DATALINK_times(1) == 0) { return 0; }
         
            DATALINK_INTRRUPT_Enable();
              
            break;
            
// POWER DOWN from aux devices 
        case (12):
            DATALINK_INTRRUPT_Disable();
// START 1151 
            if (DATALINK_times(1) == 0) { return 0; }
            if (DATALINK_times(1) == 0) { return 0; }
            if (DATALINK_times(5) == 0) { return 0; }
            if (DATALINK_times(1) == 0) { return 0; }
// DATA
// 2222  
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
// 2223  
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(3) == 0) { return 0; }
// 1222 
            if (DATALINK_times(1) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
// 3212 
            if (DATALINK_times(3) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
            if (DATALINK_times(1) == 0) { return 0; }
            if (DATALINK_times(2) == 0) { return 0; }
// 41  
            if (DATALINK_times(4) == 0) { return 0; }
            if (DATALINK_times(1) == 0) { return 0; }
     
            DATALINK_INTRRUPT_Enable();
            
            break;
            
        }
    return 1;
}

/* [] END OF FILE */
