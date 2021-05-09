/*******************************************************************************
* File Name: main.c
*
* Copyright HEMI, 2021
* All Rights Reserved
* UNPUBLISHED, LICENSED SOFTWARE.
* Version: 1.0
*
* Description:
*  This project is intended to be used as main code that runs on PSoC KIT
*  inside BeoModern system. 
*  It is responsible for monitoring
*  - two push buttons (short and long press)
*  - listenning and responding to commands sent over BeO Datalink
*  - listenning and responding to commands sent over SPI Interface from display 
*    unit
*  It is responsible for controling 
*  - Raspberry Pi that acts as iRadio, mp3/flac player, DAB radio, source of 
*    FM radio station name that is displayed when enabled
*  - SigmaDSP processor togethre with audio DAC responsible for processing 
*    audio and producing analog sound
*  - Bluetooth module
*  - power supply system (power up and down different blocks of whole BeoModern)
*  - information sent to the display module that are displayed on alphanumeric 
*    display and on LED status displays
*
*******************************************************************************/

#include <project.h>
#include <inputs.h>
#include <modes.h>
#include <spi_int.h>
#include <operate.h>
#include <string.h>

// EEPROM storage in work flash, this is defined in Em_EEPROM.c
#if defined (__ICCARM__)
#pragma data_alignment = CY_FLASH_SIZEOF_ROW
const uint8_t Em_EEPROM_em_EepromStorage[Em_EEPROM_PHYSICAL_SIZE] = {0u};
#else
const uint8_t Em_EEPROM_em_EepromStorage[Em_EEPROM_PHYSICAL_SIZE]
CY_SECTION(".cy_checksum_exclude")
__ALIGNED(CY_FLASH_SIZEOF_ROW) = {0u};
#endif /* defined (__ICCARM__) */

int main()
{   
// variable used by routine used to quickly move to load mode
    uint8 currentSTATE = 9;    
// variable used by routine used to quickly move to load mode    
    uint8 BTSTATE = 9;   
// initial datalink command code    
    uint8 datalink_command = 0;
    
// display data variables
    uint8 display_return = 0;
    uint8 current_display_data_buffer[24] = {"...4....4....4....4....4"};
    uint8 current_disp_ctrl1 = 0;
    uint8 current_disp_ctrl2 = 0;    
    
// Initalize EEPROM with the start address of the memory location
    Em_EEPROM_Init((uint32_t)Em_EEPROM_em_EepromStorage);
    
//Manually set P4.2 as input. Used to Read Raspberry Pi status
    CY_SYS_PINS_SET_DRIVE_MODE(CYREG_PRT4_PC,2,CY_SYS_PINS_DM_DIG_HIZ);
//Manually set P4.3 as input. Used to Read BT AAC status
    CY_SYS_PINS_SET_DRIVE_MODE(CYREG_PRT4_PC,3,CY_SYS_PINS_DM_DIG_HIZ);
    
// Start push button timers    
    Timer_1_Start();
    Timer_2_Start();

// Start DATALINK timer
    DATALINK_Timer_Start();

// Start DISPLAY timer
    DISPLAY_Timer_Start();
    
// initialize interrupt routines for push buttons
    PWR_OK_MODE_SHORT_StartEx(PWR_OK_MODE_SHORT_ISR);    
    MODE_LONG_StartEx(MODE_LONG_ISR);
    PWR_OK_LONG_StartEx(PWR_OK_LONG_ISR);
    
// initialize DATALINK timer interrupt and set up handler for it
    DATALINK_INTRRUPT_StartEx(DATALINK_INTRRUPTHandler);    
   
// initialize DISPLAY timer interrupt and set up handler for it
    DISPLAY_Timer_INT_StartEx(DISPLAY_Timer_INTHandler);    
    
// Enable interrupt routines
    CyGlobalIntEnable;
    
// Start SCB (UART mode) operation 
    UART_Start();

// Start SCB (SPI Master mode) operation 
    SPIM_Start();

// inifinite loop - this uP is always ON
    for (;;)
    {
// if return information over SPI from display module is 0x5A it indicates that 
// timer in display module expired and whole system should go into power down state
        if (display_return == 0x5A)
        {
// set flag to 1 indicating move into power off state
            PWR_OK_LONG_V = 1;      
// clear SPI message to allow boot up next time. 
            display_return = 0x00;
        }
        
// check if there are any activities with 2 push buttons (short or long press occured)
        buttons_check();

// check if activity on datalink interface was deteced        
        if (DATALINK_TABLE_COUNTER_MAX != 0)
        {
// if it was, check if command was addressed to BeoModern unit
            datalink_command = datalink_decoder();
            if ((datalink_command >= 10) & (datalink_command <=60) )
            {
// if it was, react to it                
                datalink_check(datalink_command);
            }
        }
        
// check if system state changed due to datalink command or pushbuttons activities        
        if ( ( currentSTATE > SYSTEM_STATE ) || ( currentSTATE < SYSTEM_STATE ) )
        {
// switch beomodern state to new state and set current state to new value
            currentSTATE = BeoM_PSU_state();
// read back new bluetooth state
            BTSTATE = BT_control(0,0);
// configure power supply control to fulfil needs of new beomodern state            
            current_PSUstate = psu_config(1, next_PSUstate);
// flush display data before updating display with new display info            
            strcpy((char*)new_display_data_buffer, "                        ");                                          
        }
    
// update information sent over SPI to display based on current state and selected mode
        display_update();
        
// check if there is new data ready to be sent to display over SPI interface
        if (new_display_data_flag == 1)
        {
// copy new data into buffer that will be sent to display            
            strcpy((char*)current_display_data_buffer,(char*)new_display_data_buffer);
// copy new control values that will be sent to display            
            current_disp_ctrl1 = new_disp_ctrl1;
            current_disp_ctrl2 = new_disp_ctrl2;
// sent data over SPI to display module
            display_return = SPIM_display_write(current_display_data_buffer, current_disp_ctrl1, current_disp_ctrl2);
// 20mS delay between SPI commands to handle buffer update on SPI slave side 
// update of alphanumeric displays is slow - delay is necessary to give time to handle it
            CyDelay(20);
// clear flag indicating new data to display             
            new_display_data_flag = 0;
        }
      
        
// TO BE REMOVED TO BE REMOVED
// Enters bootload state when button on PSoC board is pressed
        if (Pin_1_Read() == 0x00)        
            {
            Bootloadable_1_Load();
            }    
// TO BE REMOVED TO BE REMOVED            
        
    }
}

/* [] END OF FILE */
