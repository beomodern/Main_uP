/*******************************************************************************
* File Name: main.c
*
* Version: 1.0
* Date: 2020
*
* Description:
*  This project is intended to be used as main code that runs on PSoC KIT
*  inside BeoModern system. 
*  It is responsible for monitoring
*  - two push buttons (short and long press)
*  - listenning and responding to commands sent over BeO Datalink
*  It is responsible for controling 
*  - Raspberry Pi that acts as iRadio, mp3/flac player, DAB radio, FM radio
*    station name display
*  - SigmaDSP processor togethre with audio DAC responsible for processing 
*    audio and producing analog sound
*  - Bluetooth module
*  - power supply system (power up and down different blocks)
*  - information sent to the display module
*
*******************************************************************************/

#include <project.h>
#include <inputs.h>
#include <modes.h>
#include <display.h>
#include <operate.h>

// EEPROM storage in work flash, this is defined in Em_EEPROM.c
#if defined (__ICCARM__)
#pragma data_alignment = CY_FLASH_SIZEOF_ROW
const uint8_t Em_EEPROM_em_EepromStorage[Em_EEPROM_PHYSICAL_SIZE] = {0u};
#else
const uint8_t Em_EEPROM_em_EepromStorage[Em_EEPROM_PHYSICAL_SIZE]
CY_SECTION(".cy_checksum_exclude")
__ALIGNED(CY_FLASH_SIZEOF_ROW) = {0u};
#endif /* defined (__ICCARM__) */



void main()
{   
 // TO BE REMOVED TO BE REMOVED
    uint32 ch;          /* variable used by routine used to quickly move to load mode */
//    uint8 swCounter;    /* variable used by routine used to quickly move to load mode */
//    uint8 table_counter;          /* variable used to scan thru DATALINK redback string */
 // TO BE REMOVED TO BE REMOVED
 
    uint8 currentSTATE = 9;    /* variable used by routine used to quickly move to load mode */
    uint8 BTSTATE = 9;    /* variable used by routine used to quickly move to load mode */
    
// Initalize EEPROM with the start address of the memory location
    Em_EEPROM_Init((uint32_t)Em_EEPROM_em_EepromStorage);
    

//Manually set P4.2 as input. Used to Read Raspberry Pi status
    CY_SYS_PINS_SET_DRIVE_MODE(CYREG_PRT4_PC,2,CY_SYS_PINS_DM_DIG_HIZ);
//Manually set P4.3 as input. Used to Read BT AAC status
    CY_SYS_PINS_SET_DRIVE_MODE(CYREG_PRT4_PC,3,CY_SYS_PINS_DM_DIG_HIZ);

    
// start push button timers    
    Timer_1_Start();
    Timer_2_Start();

// initialize interrupt routines for push buttons
    PWR_OK_MODE_SHORT_StartEx(PWR_OK_MODE_SHORT_ISR);    
    MODE_LONG_StartEx(MODE_LONG_ISR);
    PWR_OK_LONG_StartEx(PWR_OK_LONG_ISR);

// Starts DATALINK timer
    DATALINK_Timer_Start();
    
// Enable DATALING timer interrupt and set up handler for it
    DATALINK_INTRRUPT_StartEx(DATALINK_INTRRUPTHandler);    
    
// Enable interrupt routines
    CyGlobalIntEnable;
    
// Start SCB (UART mode) operation 
    UART_Start();


//    SPI_Start();
      
/* 
    // Writing data into the SPIS TX software buffer 
    SPIS_SpiUartWriteTxData(0x11u);
    SPIS_SpiUartWriteTxData(0x22u);

    // Writing data into the SPIM software buffer 
    SPIM_SpiUartWriteTxData(0x99u);
    SPIM_SpiUartWriteTxData(0xAAu);
    
    while(0u == (SPIM_GetMasterInterruptSource() & SPIM_INTR_MASTER_SPI_DONE))
    {
        // Wait while Master completes transfer 
    }
    
    // Clear interrupt source after transfer completion 
    SPIM_ClearMasterInterruptSource(SPIM_INTR_MASTER_SPI_DONE);
    
    
    for(i=0u; i<8u; i++)
    {
        // Read data from SPIS RX  hardware FIFO
        LCD_PrintHexUint8(SPIS_SpiUartReadRxData());
    }
*/  
    

    for (;;)
    {
/* COMMENTED FOR DATALINK TESTING       
        buttons_check();
        UART_UartPutString("\r\ncurrent state = ");
        UART_UartPutChar('0' + currentSTATE);
        UART_UartPutString(" SYSTEM STATE = ");
        UART_UartPutChar('0' + SYSTEM_STATE);
        
        
        if ( ( currentSTATE > SYSTEM_STATE ) | ( currentSTATE < SYSTEM_STATE ) )
        {
//            UART_UartPutString("\r\nDIFFERENT = ");
            currentSTATE = BeoM_PSU_state();
//            UART_UartPutChar('0' + currentSTATE);
        }
        else
        {
//            UART_UartPutString("\r\nTHE SAME = ");
//            currentSTATE = BeoM_PSU_state(); 
//            UART_UartPutChar('0' + currentSTATE);
        }


// simulate MODE SHORT press        
        if (MODE_SHORT_V == 1)
        {
            BeoM_PSU_current_mode(7); 
            MODE_SHORT_V = 0;
        }
COMMENTED FOR DATALINK TESTING  */
       
        ch = UART_UartGetChar();
         
        if (DATALINK_TABLE_COUNTER_MAX != 0)
        {
        UART_UartPutString(" \r\n");        
        UART_UartPutChar('0' + (DATALINK_TABLE_COUNTER_MAX / 10));               
        UART_UartPutChar('0' + (DATALINK_TABLE_COUNTER_MAX % 10));               
//        UART_UartPutString("\r\n");
        datalink_decoder();
        }
        


//        UART_UartPutString("\r\nInput character = ");
//        UART_UartPutChar(ch);
        
/* COMMENTED FOR DATALINK TESTING
        if ( (ch - '0') <= 8 )
            {
//                BT_control(2, (ch - '0'));  
            BeoM_PSU_current_mode(ch - '0'); 
            }
        
        if ('b' == ch)   
            { 
                BT_Tx_STATE = 0;
            }
            
        BTSTATE = BT_control(0,0);
        UART_UartPutString("\r\nBT STATE = ");
        UART_UartPutChar('0' + BTSTATE);
 COMMENTED FOR DATALINK TESTING */       
        
 /*       
        current_PSUstate = psu_config(1, next_PSUstate);
        current_PSUstate = psu_config(2, next_PSUstate);
        UART_UartPutString(" BT = ");
        UART_UartPutChar('0' + current_PSUstate.BlueTooth_PWR);
        UART_UartPutString(" DISP = ");
        UART_UartPutChar('0' + current_PSUstate.Display_PWR);
        UART_UartPutString(" SDSP = ");
        UART_UartPutChar('0' + current_PSUstate.SigmaDSP_PWR);
        UART_UartPutString(" RPI = ");
        UART_UartPutChar('0' + current_PSUstate.RPI_PWR);
        UART_UartPutString(" RPI_STATE = ");
        UART_UartPutChar('0' + current_PSUstate.RPi_GPIO_state);               
        UART_UartPutString(" \r\n");
 */                                               


// TO BE REMOVED TO BE REMOVED
        /* Reset the software counter if SW1 is not pressed (Pulled high) */
//        ch = UART_UartGetChar(); 
//        UART_UartPutChar(ch);
        if ('/' == ch)        
//        if(Pin_1_Read())
//            {
//            swCounter = 0;
//            }
//        else
//            {
    /* Increment the counter if SW1 is pressed (Shorted to GND) */
//            swCounter++;
//            }
    /* Provide a 10 ms delay to make the counter approximately periodic every 10 ms */
//        CyDelay(10);
    /* Check if the software counter has passed 1 s (100 * 10 ms)
        ==> Since the software counter is incremented only when SW1 is
        ==> pressed, SW1 is pressed for more than 1 seconds
        ==> Enter bootloader mode */
//        if(swCounter > 100)
            {
            Bootloadable_1_Load();
            }   
// TO BE REMOVED TO BE REMOVED
    }
}

/* [] END OF FILE */
