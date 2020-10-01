/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include <project.h>
#include <operate.h>
#include <modes.h>
#include <inputs.h>
#include <spi_int.h>

uint8 FM_RADIO_STATION = 1;// variable used to store intercepted FM radio station number

// counter used when reading data over UART    
    uint8 counter = 0;


/*******************************************************************************
* Function Name: BeoM_PSU_state()
********************************************************************************
* Summary:
*  Function monitors SYSTEM and BlueToot state global variables and 
*  enables/disab;es power supply domains accordingly. 
*  SYSTEM_STATE = 0 - power down
*  SYSTEM_STATE = 1 - Player
*  SYSTEM_STATE = 2 - iRadio
*  SYSTEM_STATE = 3 - DAB Radio
*  SYSTEM_STATE = 4 - Aux IN
*  SYSTEM_STATE = 5 - Clock
*  SYSTEM_STATE = 6 - RDS/FM display
*  SYSTEM_STATE = 7 - BlueTooth Rx
*  SYSTEM_STATE = 8 - BlueTooth Tx
*  BT_Tx_STATE = 0  - BT Tx OFF
*  BT_Tx_STATE = 1  - BT Tx ON
*   
* Parameters:
*  Function operates on global variables:
*  SYSTEM_STATE and BT_Tx_STATE
*
* Return:
*  Funciton returns current SYSTEM_STATE nubmer
*
*******************************************************************************/  
uint8 BeoM_PSU_state()  
{

// read back current PSU state    
    current_PSUstate = psu_config(2, next_PSUstate);
// copy existing state of PSU to new settings    
    next_PSUstate = current_PSUstate;
// display counter
    uint8 display_counter = 0;
        
// SYSTEM_STATE = 0 - system in power down mode
    switch (SYSTEM_STATE)
    {    
    case (0):
    
// turn ON standby LED       
        LED_Write(1);  

        if (current_PSUstate.BlueTooth_PWR == 1)
        {
// Send to BlueTooth pause/mute command
            BT_control(1, 4); 
// set BT power variable to 0 -> powering down BT module
            next_PSUstate.BlueTooth_PWR = 0;    
        }        
        
// sent info to display about powering down        
        strcpy((char*)new_display_data_buffer, "Powering down... Bye Bye");
        SPIM_display_write(new_display_data_buffer, 0x00, 0x00);
        
        if (current_PSUstate.SigmaDSP_PWR == 1)
        {
//  0 = Control = 0x052E -> 0x0000 = MUTE
            SPIM_SigmaDSP_write(0);        
// set SigmaDSP power variable to 0 -> powering down SigmaDSP               
            next_PSUstate.SigmaDSP_PWR = 0;            
        }
        
        if (current_PSUstate.RPI_PWR == 1)
        {
// WAIT untill RPI powers down
            if (current_PSUstate.RPi_GPIO_state == 1)
            {
// sent command over UART command to RPI to power down
                UART_UartPutString("-SHUTDOWN+");
// Wait until current_PSUstate.RPi_GPIO_state == 1
                while (current_PSUstate.RPi_GPIO_state == 1)
                {
// read back current PSU state    
                    current_PSUstate = psu_config(2, next_PSUstate);
                }
// set RPi power variable to 0 -> powering down RPi
                next_PSUstate.RPI_PWR = 0;
            }
            else
            {
// set RPi power variable to 0 -> powering down RPi
                next_PSUstate.RPI_PWR = 0;
            }
        }
// DATALINK out command = 12 -> POWER DOWN from aux devices  
// if there is a collision on DATALINK bus, wait 10mS and try again
        while (DATALINK_out(12) == 0)
        {
            CyDelay(10);  
        }
        
        if (current_PSUstate.Display_PWR == 1)
        {
// SENT COMMAND TO DISPLAY ABOUT POWERING DOWN
// SENT COMMAND TO DISPLAY ABOUT POWERING DOWN
// SENT COMMAND TO DISPLAY ABOUT POWERING DOWN
// WAIT 2..3 seconds
// WAIT 2..3 seconds            
// WAIT 2..3 seconds
// set display power variable to 0 -> powering down display module            
            next_PSUstate.Display_PWR = 0;        
        }
        
// disable all power blocks        
        psu_config(1, next_PSUstate);

        break;
      
    
    
// SYSTEM_STATE = 1 - system in Player mode
    case (1):
    
// turn OFF stnadby LED       
        LED_Write(0);      

        if (current_PSUstate.RPi_GPIO_state == 0)
        {
// check if RPi is already enabled and active            
            if (current_PSUstate.RPI_PWR == 0)
            {
// if not, enable RPi
                next_PSUstate.RPI_PWR = 1;    
            }
        }
// check if display module is already powered up
        if (current_PSUstate.Display_PWR == 0)
        {
// if not, enable Display
            next_PSUstate.Display_PWR = 1;        
        }
// check if SigmaDSP module is already powered up        
        if (current_PSUstate.SigmaDSP_PWR == 0)
        {
// if not, enable SigmaDSP            
            next_PSUstate.SigmaDSP_PWR = 1;            
        }

// check if Bluetooth Tx flag is set
        if (BT_Tx_STATE == 1)
        {
// if it is, check if BT is powered up
            if (current_PSUstate.BlueTooth_PWR == 0)
                {
// if not power it up        
                    next_PSUstate.BlueTooth_PWR = 1;    
                }
        }         
        
// enable all necessary blocks        
        psu_config(1, next_PSUstate);  

// DATALINK out command = 11 -> LIST button pressed  
// if there is a collision on DATALINK bus, wait 10mS and try again
        while (DATALINK_out(11) == 0)
        {
            CyDelay(10);  
        }
// DATALINK out command = 10 -> GO button pressed  
// if there is a collision on DATALINK bus, wait 10mS and try again
        while (DATALINK_out(10) == 0)
        {
            CyDelay(10);  
        }
// DATALINK out command = 1 -> 1 button pressed  
// if there is a collision on DATALINK bus, wait 10mS and try again
        while (DATALINK_out(1) == 0)
        {
            CyDelay(10);  
        }        
        
        
// read back current PSU state    
        current_PSUstate = psu_config(2, next_PSUstate);

        if (current_PSUstate.RPI_PWR == 1)
            {
                display_counter = 30;
                while (current_PSUstate.RPi_GPIO_state == 0)
                {
// WAIT untill RPI powers up
// read back current PSU state    
                current_PSUstate = psu_config(2, next_PSUstate);
// SENT INFORMAITON TO DISPLAY ABOUT RPI BOOTING UP
// new data that needs to be sent over SPI to display module
                strcpy((char*)new_display_data_buffer, "Booting up ...          ");
                new_display_data_buffer[22] = '0' + (display_counter / 10);
                new_display_data_buffer[23] = '0' + (display_counter % 10);
                SPIM_display_write(new_display_data_buffer, 0x00, 0x00);    
                CyDelay(1000);
                display_counter = display_counter - 1;
                }
            }                
            
// sent command over UART command to RPI to start Player
        UART_UartPutString("-Player+");
                
        if (BT_Tx_STATE == 1)
        {
// Enable BlueTooth in Tx state - re-connect to latest device
            BT_control(1, 2); 
// SENT OVER SPI information about BT Tx LED ON
// disp_ctrl2 
// CTRL1.0 - BT Tx status set to 1 indicating Tx mode ON
            new_disp_ctrl2 = new_disp_ctrl2 | 0x01;
            new_display_data_flag = 1;                   
        } 
        
// check if SigmaDSP is up - wait untill radback value matches signature
        while (SPIM_SigmaDSP_read(4) != 0xBE01BE02)
        {
// initiate SigmaDSP data port in SPI mode
            SPIM_SigmaDSP_init_SPI();
        }

//  SigmaDSP in RPi mode -> Control = 0x0001
        SPIM_SigmaDSP_write(1);
    
// SENT OVER SPI information about Player LED ON
        new_disp_ctrl1 = 0x01;
        new_display_data_flag = 1;                   
        break;
 
    
    
// SYSTEM_STATE = 2 - system in iRadio mode    
    case (2):
    
// turn OFF stnadby LED       
        LED_Write(0);      
    
        if (current_PSUstate.RPi_GPIO_state == 0)
        {
// check if RPi is already enabled and active            
            if (current_PSUstate.RPI_PWR == 0)
            {
// enable RPi
                next_PSUstate.RPI_PWR = 1;    
            }
        }
        if (current_PSUstate.Display_PWR == 0)
        {
// enable Display
            next_PSUstate.Display_PWR = 1;        
        }
        
        if (current_PSUstate.SigmaDSP_PWR == 0)
        {
// Enable SigmaDSP            
            next_PSUstate.SigmaDSP_PWR = 1;            
        }

// check if Bluetooth Tx flag is set
        if (BT_Tx_STATE == 1)
        {
// if it is, check if BT is powered up
        if (current_PSUstate.BlueTooth_PWR == 0)
            {
// if not power it up        
                next_PSUstate.BlueTooth_PWR = 1;    
            }
        }         
        
// enable all necessary blocks        
        psu_config(1, next_PSUstate);  

// DATALINK out command = 11 -> LIST button pressed  
// if there is a collision on DATALINK bus, wait 10mS and try again
        while (DATALINK_out(11) == 0)
        {
            CyDelay(10);  
        }
// DATALINK out command = 10 -> GO button pressed  
// if there is a collision on DATALINK bus, wait 10mS and try again
        while (DATALINK_out(10) == 0)
        {
            CyDelay(10);  
        }
// DATALINK out command = 2 -> 2 button pressed  
// if there is a collision on DATALINK bus, wait 10mS and try again
        while (DATALINK_out(2) == 0)
        {
            CyDelay(10);  
        } 
        
// read back current PSU state    
        current_PSUstate = psu_config(2, next_PSUstate);

        if (current_PSUstate.RPI_PWR == 1)
            {
                display_counter = 30;
                while (current_PSUstate.RPi_GPIO_state == 0)
                {
// WAIT untill RPI powers up
// read back current PSU state    
                current_PSUstate = psu_config(2, next_PSUstate);
// SENT INFORMAITON TO DISPLAY ABOUT RPI BOOTING UP
// new data that needs to be sent over SPI to display module
                strcpy((char*)new_display_data_buffer, "Booting up ...          ");
                new_display_data_buffer[22] = '0' + (display_counter / 10);
                new_display_data_buffer[23] = '0' + (display_counter % 10);
                SPIM_display_write(new_display_data_buffer, 0x00, 0x00);          
                CyDelay(1000);
                display_counter = display_counter - 1;         
                }
            }        
// sent command over UART command to RPI to start iRadio
        UART_UartPutString("-iRadio+");
            
        if (BT_Tx_STATE == 1)
        {
// Enable BlueTooth in Tx state - re-connect to latest device
            BT_control(1, 2); 
// disp_ctrl2 
// CTRL1.0 - BT Tx status set to 1 indicating Tx mode ON
            new_disp_ctrl2 = new_disp_ctrl2 | 0x01;
            new_display_data_flag = 1;  
        } 
        
// check if SigmaDSP is up - wait untill radback value matches signature
        while (SPIM_SigmaDSP_read(4) != 0xBE01BE02)
        {
// initiate SigmaDSP data port in SPI mode
            SPIM_SigmaDSP_init_SPI();
        } 
        
//  SigmaDSP in RPi mode -> Control = 0x0001
        SPIM_SigmaDSP_write(1);
       
// SENT OVER SPI informaiton about iRadio LED ON
        new_disp_ctrl1 = 0x02;
        new_display_data_flag = 1;   
        break;
        
    
    
// SYSTEM_STATE = 3 - system in DAB Radio mode
    case (3):
    
// turn OFF stnadby LED       
        LED_Write(0);      
    
        if (current_PSUstate.RPi_GPIO_state == 0)
        {
// check if RPi is already enabled and active            
            if (current_PSUstate.RPI_PWR == 0)
            {
// enable RPi
                next_PSUstate.RPI_PWR = 1;    
            }
        }
        if (current_PSUstate.Display_PWR == 0)
        {
// enable Display
            next_PSUstate.Display_PWR = 1;        
        }
        
        if (current_PSUstate.SigmaDSP_PWR == 0)
        {
// Enable SigmaDSP            
            next_PSUstate.SigmaDSP_PWR = 1;            
        }

// check if Bluetooth Tx flag is set
        if (BT_Tx_STATE == 1)
        {
// if it is, check if BT is powered up
        if (current_PSUstate.BlueTooth_PWR == 0)
            {
// if not power it up        
                next_PSUstate.BlueTooth_PWR = 1;    
            }
        } 
        
// enable all necessary blocks        
        psu_config(1, next_PSUstate);  

// DATALINK out command = 11 -> LIST button pressed  
// if there is a collision on DATALINK bus, wait 10mS and try again
        while (DATALINK_out(11) == 0)
        {
            CyDelay(10);  
        }
// DATALINK out command = 10 -> GO button pressed  
// if there is a collision on DATALINK bus, wait 10mS and try again
        while (DATALINK_out(10) == 0)
        {
            CyDelay(10);  
        }
// DATALINK out command = 3 -> 3 button pressed  
// if there is a collision on DATALINK bus, wait 10mS and try again
        while (DATALINK_out(3) == 0)
        {
            CyDelay(10);  
        } 
        
// read back current PSU state    
        current_PSUstate = psu_config(2, next_PSUstate);

        if (current_PSUstate.RPI_PWR == 1)
            {
                display_counter = 30;
                while (current_PSUstate.RPi_GPIO_state == 0)
                {
// WAIT untill RPI powers up
// read back current PSU state    
                current_PSUstate = psu_config(2, next_PSUstate);
// SENT INFORMAITON TO DISPLAY ABOUT RPI BOOTING UP
// new data that needs to be sent over SPI to display module
                strcpy((char*)new_display_data_buffer, "Booting up ...          ");
                new_display_data_buffer[22] = '0' + (display_counter / 10);
                new_display_data_buffer[23] = '0' + (display_counter % 10);
                SPIM_display_write(new_display_data_buffer, 0x00, 0x00);          
                CyDelay(1000);
                display_counter = display_counter - 1;           
                }
            }
 // sent command over UART command to RPI to start DAB
        UART_UartPutString("-DAB+");
        
        if (BT_Tx_STATE == 1)
        {
// Enable BlueTooth in Tx state - re-connect to latest device
            BT_control(1, 2); 
// disp_ctrl2 
// CTRL1.0 - BT Tx status set to 1 indicating Tx mode ON
            new_disp_ctrl2 = new_disp_ctrl2 | 0x01;
            new_display_data_flag = 1;  
        } 

// check if SigmaDSP is up - wait untill radback value matches signature
        while (SPIM_SigmaDSP_read(4) != 0xBE01BE02)
        {
// initiate SigmaDSP data port in SPI mode
            SPIM_SigmaDSP_init_SPI();
        }

//  SigmaDSP in DAB mode -> Control = 0x0002
        SPIM_SigmaDSP_write(2);

// SENT OVER SPI informaiton about DAB Radio LED ON
        new_disp_ctrl1 = 0x04;
// CTRL1.1 - Online status set to 0 indicating offline state
        new_disp_ctrl2 = new_disp_ctrl2 & 0xFD;        
        new_display_data_flag = 1;   
        break;

    
    
// SYSTEM_STATE = 4 - system in AuxIn mode    
    case (4):
    
// turn OFF stnadby LED       
        LED_Write(0);      
    
        if (current_PSUstate.Display_PWR == 0)
        {
// enable Display
            next_PSUstate.Display_PWR = 1;        
        }
        
        if (current_PSUstate.SigmaDSP_PWR == 0)
        {
// Enable SigmaDSP            
            next_PSUstate.SigmaDSP_PWR = 1;            
        }

// check if Bluetooth Tx flag is set
        if (BT_Tx_STATE == 1)
        {
// if it is, check if BT is powered up
        if (current_PSUstate.BlueTooth_PWR == 0)
            {
// if not power it up        
                next_PSUstate.BlueTooth_PWR = 1;    
            }
            
        } 
        
// enable all necessary blocks        
        psu_config(1, next_PSUstate);        

// DATALINK out command = 11 -> LIST button pressed  
// if there is a collision on DATALINK bus, wait 10mS and try again
        while (DATALINK_out(11) == 0)
        {
            CyDelay(10);  
        }
// DATALINK out command = 10 -> GO button pressed  
// if there is a collision on DATALINK bus, wait 10mS and try again
        while (DATALINK_out(10) == 0)
        {
            CyDelay(10);  
        }
// DATALINK out command = 4 -> 4 button pressed  
// if there is a collision on DATALINK bus, wait 10mS and try again
        while (DATALINK_out(4) == 0)
        {
            CyDelay(10);  
        } 

        if (BT_Tx_STATE == 1)
        {
// Enable BlueTooth in Tx state - re-connect to latest device
            BT_control(1, 2); 
// disp_ctrl2 
// CTRL1.0 - BT Tx status set to 1 indicating Tx mode ON
            new_disp_ctrl2 = new_disp_ctrl2 | 0x01;
            new_display_data_flag = 1;  
        } 
        
// check if SigmaDSP is up - wait untill radback value matches signature
        while (SPIM_SigmaDSP_read(4) != 0xBE01BE02)
        {
// initiate SigmaDSP data port in SPI mode
            SPIM_SigmaDSP_init_SPI();
        }

//  SigmaDSP in AuxIN mode -> Control = 0x0003
        SPIM_SigmaDSP_write(3);

// SENT OVER SPI informaiton about AuxIN LED ON
        new_disp_ctrl1 = 0x08;
// CTRL1.1 - Online status set to 0 indicating offline state
        new_disp_ctrl2 = new_disp_ctrl2 & 0xFD;        
        new_display_data_flag = 1;   
        break;


// SYSTEM_STATE = 5 - system in Clock mode
    case (5):
    
// turn OFF stnadby LED       
        LED_Write(0);      
        
        if (current_PSUstate.Display_PWR == 0)
        {
// enable Display
            next_PSUstate.Display_PWR = 1;        
        }
        
// check if Bluetooth Tx flag is set
        if (BT_Tx_STATE == 1)
        {
// if it is, check if BT is powered up
        if (current_PSUstate.BlueTooth_PWR == 0)
            {
// if not power it up        
                next_PSUstate.BlueTooth_PWR = 1;    
            }
// check if SigmaDSP is up            
        if (current_PSUstate.SigmaDSP_PWR == 0)
           {
// if not, enable SigmaDSP            
                next_PSUstate.SigmaDSP_PWR = 1;            
           }    
        } 
        
// enable all necessary blocks        
        psu_config(1, next_PSUstate);        

        if (BT_Tx_STATE == 1)
        {
// Enable BlueTooth in Tx state - re-connect to latest device
            BT_control(1, 2); 
// SENT OVER SPI information about BT Tx LED ON
// disp_ctrl2 
// CTRL1.0 - BT Tx status set to 1 indicating Tx mode ON
            new_disp_ctrl2 = new_disp_ctrl2 | 0x01;
            new_display_data_flag = 1;  
            
// check if SigmaDSP is up - wait untill radback value matches signature
            while (SPIM_SigmaDSP_read(4) != 0xBE01BE02)
            {
// initiate SigmaDSP data port in SPI mode
                SPIM_SigmaDSP_init_SPI();
            }

// DATALINK out command = 11 -> LIST button pressed  
// if there is a collision on DATALINK bus, wait 10mS and try again
            while (DATALINK_out(11) == 0)
            {
                CyDelay(10);  
            }
// DATALINK out command = 10 -> GO button pressed  
// if there is a collision on DATALINK bus, wait 10mS and try again
            while (DATALINK_out(10) == 0)
            {
                CyDelay(10);  
            }
// DATALINK out command = 5 -> 5 button pressed  
// if there is a collision on DATALINK bus, wait 10mS and try again
            while (DATALINK_out(5) == 0)
            {
                CyDelay(10);  
            }  
            
        } 
// SENT OVER SPI informaiton about Clock LED ON
        new_disp_ctrl1 = 0x10;
// CTRL1.1 - Online status set to 0 indicating offline state
        new_disp_ctrl2 = new_disp_ctrl2 & 0xFD;        
        new_display_data_flag = 1;   
        break;        
        
    
// SYSTEM_STATE = 6 - system in RDS/FM mode
    case (6):
    
// turn OFF stnadby LED       
        LED_Write(0);      
    
        if (current_PSUstate.RPi_GPIO_state == 0)
        {
// check if RPi is already enabled and active            
            if (current_PSUstate.RPI_PWR == 0)
            {
// enable RPi
                next_PSUstate.RPI_PWR = 1;    
            }
        }
        if (current_PSUstate.Display_PWR == 0)
        {
// enable Display
            next_PSUstate.Display_PWR = 1;        
        }
// check if Bluetooth Tx flag is set
        if (BT_Tx_STATE == 1)
        {
// if it is, check if BT is powered up
            if (current_PSUstate.BlueTooth_PWR == 0)
            {
// if not power it up        
                next_PSUstate.BlueTooth_PWR = 1;    
            }
// check if SigmaDSP is up            
            if (current_PSUstate.SigmaDSP_PWR == 0)
           {
// if not, enable SigmaDSP            
                next_PSUstate.SigmaDSP_PWR = 1;            
           } 
        } 
        
// enable all necessary blocks        
        psu_config(1, next_PSUstate);  
/*
// DATALINK out command = 11 -> LIST button pressed  
// if there is a collision on DATALINK bus, wait 10mS and try again
        while (DATALINK_out(11) == 0)
        {
            CyDelay(10);  
        }
// DATALINK out command = 10 -> GO button pressed  
// if there is a collision on DATALINK bus, wait 10mS and try again
        while (DATALINK_out(10) == 0)
        {
            CyDelay(10);  
        }
// DATALINK out command = 4 -> 4 button pressed  
// if there is a collision on DATALINK bus, wait 10mS and try again
        while (DATALINK_out(4) == 0)
        {
            CyDelay(10);  
        }   
// delay 100mS to wait for BeoMaster        
        CyDelay(100);  
// DATALINK out command = 6 -> 6 button pressed  
// if there is a collision on DATALINK bus, wait 10mS and try again
        while (DATALINK_out(6) == 0)
        {
            CyDelay(10);  
        }  
*/
// read back current PSU state    
        current_PSUstate = psu_config(2, next_PSUstate);

        if (current_PSUstate.RPI_PWR == 1)
            {
                display_counter = 30;
                while (current_PSUstate.RPi_GPIO_state == 0)
                {
// WAIT untill RPI powers up
// read back current PSU state    
                current_PSUstate = psu_config(2, next_PSUstate);
// SENT INFORMAITON TO DISPLAY ABOUT RPI BOOTING UP
// new data that needs to be sent over SPI to display module
                strcpy((char*)new_display_data_buffer, "Booting up ...          ");
                new_display_data_buffer[22] = '0' + (display_counter / 10);
                new_display_data_buffer[23] = '0' + (display_counter % 10);
                SPIM_display_write(new_display_data_buffer, 0x00, 0x00);          
                CyDelay(1000);
                display_counter = display_counter - 1;            
                }
            }      
// sent command over UART command to RPI to start FM/RDS 
        UART_UartPutString("-RDS+");
        
        if (BT_Tx_STATE == 1)
        {
// Enable BlueTooth in Tx state - re-connect to latest device
            BT_control(1, 2); 
// SENT OVER SPI information about BT Tx LED ON
// disp_ctrl2 
// CTRL1.0 - BT Tx status set to 1 indicating Tx mode ON
            new_disp_ctrl2 = new_disp_ctrl2 | 0x01;
            new_display_data_flag = 1; 

        } 
        
// check if SigmaDSP is up            
        if (current_PSUstate.SigmaDSP_PWR == 1)
        {
// if it is check if you can talk to
// check if SigmaDSP is up - wait untill radback value matches signature
            while (SPIM_SigmaDSP_read(4) != 0xBE01BE02)
            {
// initiate SigmaDSP data port in SPI mode
                SPIM_SigmaDSP_init_SPI();
            }
//  SigmaDSP in mute mode -> Control = 0x0000
            SPIM_SigmaDSP_write(0);          
        } 
        
// SENT OVER SPI informaiton about RDS/FM display LED ON
        new_disp_ctrl1 = 0x20;
// CTRL1.1 - Online status set to 0 indicating offline state
        new_disp_ctrl2 = new_disp_ctrl2 & 0xFD; 
        new_display_data_flag = 1;   
        break;

    
    
// SYSTEM_STATE = 7 - system in BlueTooth Rx mode
    case (7):

// turn OFF stnadby LED       
        LED_Write(0);      
    
        if (current_PSUstate.BlueTooth_PWR == 0)
        {
// enable BlueTooth
            next_PSUstate.BlueTooth_PWR = 1;    
        }
        
        if (current_PSUstate.Display_PWR == 0)
        {
// enable Display
            next_PSUstate.Display_PWR = 1;        
        }
        
        if (current_PSUstate.SigmaDSP_PWR == 0)
        {
// Enable SigmaDSP            
            next_PSUstate.SigmaDSP_PWR = 1;            
        }

// enable all necessary blocks        
        psu_config(1, next_PSUstate);        
/*
// DATALINK out command = 11 -> LIST button pressed  
// if there is a collision on DATALINK bus, wait 10mS and try again
        while (DATALINK_out(11) == 0)
        {
            CyDelay(10);  
        }
// DATALINK out command = 10 -> GO button pressed  
// if there is a collision on DATALINK bus, wait 10mS and try again
        while (DATALINK_out(10) == 0)
        {
            CyDelay(10);  
        }
// DATALINK out command = 4 -> 4 button pressed  
// if there is a collision on DATALINK bus, wait 10mS and try again
        while (DATALINK_out(4) == 0)
        {
            CyDelay(10);  
        } 
// delay 100mS to wait for BeoMaster        
        CyDelay(100);         
// DATALINK out command = 7 -> 7 button pressed  
// if there is a collision on DATALINK bus, wait 10mS and try again
        while (DATALINK_out(7) == 0)
        {
            CyDelay(10);  
        }  
*/       
// clear BT_TX variable indicating that bleutooth is in use as Rx
        BT_Tx_STATE = 0; 
        
// check if SigmaDSP is up - wait untill radback value matches signature
        while (SPIM_SigmaDSP_read(4) != 0xBE01BE02)
        {
// initiate SigmaDSP data port in SPI mode
            SPIM_SigmaDSP_init_SPI();
        }
        
//  SigmaDSP in BT Rx mode -> Control = 0x0004
        SPIM_SigmaDSP_write(4);

// disp_ctrl2 
// CTRL1.0 and CTRP1.1 - BT Tx status and ONLINE status set to 0 indicating Rx mode ON
        new_disp_ctrl2 = new_disp_ctrl2 & 0xFC;
// SENT OVER SPI informaiton about BlueTooth Rx LED ON
        new_disp_ctrl1 = 0x40;
        new_display_data_flag = 1;   
// Enable BlueTooth in Rx mode - re-connect to last device        
        BT_control(2, 2); 
        break;
    
    
    
// SYSTEM_STATE = 8 - system in BlueTooth Tx mode
   case (8):

// turn OFF stnadby LED       
        LED_Write(0);      

        if (current_PSUstate.BlueTooth_PWR == 0)
        {
// enable BlueTooth
            next_PSUstate.BlueTooth_PWR = 1;    
        }
        
        if (current_PSUstate.Display_PWR == 0)
        {
// enable Display
            next_PSUstate.Display_PWR = 1;        
        }
        
        if (current_PSUstate.SigmaDSP_PWR == 0)
        {
// Enable SigmaDSP            
            next_PSUstate.SigmaDSP_PWR = 1;            
        }

// enable all necessary blocks        
        psu_config(1, next_PSUstate);        
/*
// DATALINK out command = 11 -> LIST button pressed  
// if there is a collision on DATALINK bus, wait 10mS and try again
        while (DATALINK_out(11) == 0)
        {
            CyDelay(10);  
        }
// DATALINK out command = 10 -> GO button pressed  
// if there is a collision on DATALINK bus, wait 10mS and try again
        while (DATALINK_out(10) == 0)
        {
            CyDelay(10);  
        }
// DATALINK out command = 4 -> 4 button pressed  
// if there is a collision on DATALINK bus, wait 10mS and try again
        while (DATALINK_out(4) == 0)
        {
            CyDelay(10);  
        } 
// delay 100mS to wait for BeoMaster        
        CyDelay(100);         
// DATALINK out command = 8 -> 8 button pressed  
// if there is a collision on DATALINK bus, wait 10mS and try again
        while (DATALINK_out(8) == 0)
        {
            CyDelay(10);  
        } 
*/        
// set BT_TX variable to 1 indicating that bleutooth is in ues 
        BT_Tx_STATE = 1;  
// Enable BlueTooth in Tx state - re-connect to latest device
        BT_control(1, 2);  

// check if SigmaDSP is up - wait untill radback value matches signature
        while (SPIM_SigmaDSP_read(4) != 0xBE01BE02)
        {
// initiate SigmaDSP data port in SPI mode
            SPIM_SigmaDSP_init_SPI();
        }
            
// SENT OVER SPI informaiton about BlueTooth Tx LED ON
// disp_ctrl2 
// CTRL1.0 - BT Tx status set to 1 indicating Tx mode ON
        new_disp_ctrl2 = new_disp_ctrl2 | 0x01;
        new_display_data_flag = 1; 
        break;
    }
    
    return SYSTEM_STATE;
}




/*******************************************************************************
* Function Name: display_update()
********************************************************************************
* Summary:
*  Function monitors SYSTEM STATE variable and listen to incoming UART messages
*  from RPi. When they arrive, push them to the display module over SPI. 
*  SYSTEM_STATE = 0 - power down    -   NO COMMANDS from RPi
*  SYSTEM_STATE = 1 - Player        -   COMMANDS
*  SYSTEM_STATE = 2 - iRadio        -   COMMANDS
*  SYSTEM_STATE = 3 - DAB Radio     -   COMMANDS
*  SYSTEM_STATE = 4 - Aux IN        -   NO COMMANDS from RPi -> static message
*  SYSTEM_STATE = 5 - Clock         -   NO COMMANDS from RPi -> static message
*  SYSTEM_STATE = 6 - RDS/FM display-   COMMANDS
*  SYSTEM_STATE = 7 - BlueTooth Rx  -   NO COMMANDS from RPi -> BT sents notes
*  SYSTEM_STATE = 8 - BlueTooth Tx  -   NO COMMANDS from RPi -> BT sents notes
*
*  DISPLAY_STATE = 1 - Data         -   sent to display commands from RPi, BT or static
*  DISPLAY_STATE = 2 - signal level -   sent signal level info from SigmaDSP
*  DISPLAY_STATE = 3 - spectrm analyzer -  sent spectrum analyzer info from SigmaDSP
*  DISPLAY_STATE = 4 - Clock 1      -   sent note to display Clock 1
*  DISPLAY_STATE = 5 - Clock 2      -   sent note to display Clock 2
*  DISPLAY_STATE = 6 - blank      -   No data on display (sent spaces)
*   
* Parameters:
*  Function operates on global variable: 
*  SYSTEM_STATE and DISPLAY_STATE
*
* Return:
*  Funciton returns current ????
*
*******************************************************************************/  
uint8 display_update(void)  
{
 // variable used to store read back character over UART
    uint32 ch;         

// System reacts listents to UART commands and pushes them to display when 
// new one arrives. This happens only in DISPLAY_STATE == 1
    if (DISPLAY_STATE == 1)
    {
// disp_ctrl2 
// CTRL1.0 and CTRL1.1 - clear all LED status except BT Tx and ONLINE
        new_disp_ctrl2 = new_disp_ctrl2 & 0x03;
// operate function based on current state of the system    
        switch (SYSTEM_STATE)
        {
// SYSTEM_STATE = 0 - system in power down mode
// no UART messages from RPi  
        case (0):
            break;

// SYSTEM_STATE = 1 - system in Player mode
        case (1):
            ch = UART_UartGetChar();
            if (0 != ch)
            {
                if (counter < 24)
                {
                    new_display_data_buffer[counter] = (uint8)ch;
                    counter = counter + 1;
                }
                if ((';' == ch) && (counter == 24))
                {
                    counter = counter + 1;
                }
                if (('P' == ch) && (counter == 25))
                {
                    counter = counter + 1;
                }
                if (('\r' == ch) && (counter == 26))
                {
                    counter = counter + 1;
                }
                if (('\n' == ch) && (counter == 27))
                {
                    counter = 0;
                    new_display_data_flag = 1;
                }
            }   
        break;
        
    
// SYSTEM_STATE = 2 - system in iRadio mode    
// System reacts listents to UART commands and pushes them to display when 
// new one arrives. This happens only in DISPLAY_STATE == ????
        case (2):
            ch = UART_UartGetChar();
            if (0 != ch)
            {
                if (counter < 24)
                {
                    new_display_data_buffer[counter] = (uint8)ch;
                    counter = counter + 1;
                }
                if ((';' == ch) && (counter == 24))
                {
                    counter = counter + 1;
                }
                if ( ('O' == ch) && (counter == 25) )
                {
// disp_ctrl2 
// CTRL1.1 - Online status set to 1 indicating online state
                    new_disp_ctrl2 = new_disp_ctrl2 | 0x02;
                    counter = counter + 1;
                }
                if ( ('F' == ch) && (counter == 25) )
                {
// disp_ctrl2 
// CTRL1.1 - Online status set to 0 indicating offline state
                    new_disp_ctrl2 = new_disp_ctrl2 & 0xFD;
                    counter = counter + 1;
                }
                if (('\r' == ch) && (counter == 26))
                {
                    counter = counter + 1;
                }
                if (('\n' == ch) && (counter == 27))
                {
                    counter = 0;
                    new_display_data_flag = 1;
                }
            }  
        break;
        
            
// SYSTEM_STATE = 3 - system in DAB Radio mode
// System reacts listents to UART commands and pushes them to display when 
// new one arrives. This happens only in DISPLAY_STATE == ????
        case (3):
            ch = UART_UartGetChar();
            if (0 != ch)
            {
                if (counter < 24)
                {
                    new_display_data_buffer[counter] = (uint8)ch;
                    counter = counter + 1;
                }
                if ((';' == ch) && (counter == 24))
                {
                    counter = counter + 1;
                }
                if (('D' == ch) && (counter == 25))
                {
                    counter = counter + 1;
                }
                if (('\r' == ch) && (counter == 26))
                {
                    counter = counter + 1;
                }
                if (('\n' == ch) && (counter == 27))
                {
                    counter = 0;
                    new_display_data_flag = 1;
                }
            }  
//                        if ( strcmp((char*)current_display_data_buffer,(char*)new_display_data_buffer) == 0 )
        break;
                

// SYSTEM_STATE = 4 - system in AuxIn mode    
// no UART messages from RPi  
        case (4):
// display Note about Aux IN mode
            strcpy((char*)new_display_data_buffer, "Aux IN mode             ");
// start display timer to periodically sent informaiton to display module
// without blocking delay  
            DISPLAY_Timer_Start();
// check if 2 seconds timer expired             
            if (DISPLAY_UPDATE > 0)
            { 
// set flag and sent info to display module
                new_display_data_flag = 1;
                DISPLAY_UPDATE = 0;
            } 
        break;

    
// SYSTEM_STATE = 5 - Clock   
// no UART messages from RPi  
        case (5):
// display clock 1            
            strcpy((char*)new_display_data_buffer, "CLOCK ONE               ");
// start display timer to periodically sent informaiton to display module
// without blocking delay  
            DISPLAY_Timer_Start();
// check if 2 seconds timer expired             
            if (DISPLAY_UPDATE > 0)
            { 
// set flag and sent info to display module
                new_display_data_flag = 1;
                DISPLAY_UPDATE = 0;
            } 
         break;
    
    
// SYSTEM_STATE = 6 - system in RDS/FM mode
// System reacts listents to UART commands and pushes them to display when 
// new one arrives. This happens only in DISPLAY_STATE == ????
        case (6):
            ch = UART_UartGetChar();
            if (0 != ch)
            {
                if (counter < 24)
                {
                    new_display_data_buffer[counter] = (uint8)ch;
                    counter = counter + 1;
                }
                if ((';' == ch) && (counter == 24))
                {
                    counter = counter + 1;
                }
                if (('N' == ch) && (counter == 25))
                {
                    counter = counter + 1;
                }
                if (('\r' == ch) && (counter == 26))
                {
                    counter = counter + 1;
                }
                if (('\n' == ch) && (counter == 27))
                {
                    counter = 0;
                    new_display_data_flag = 1;
                }
            }  
        break;

        
// SYSTEM_STATE = 7 - system in BlueTooth Rx mode
        case (7):
// no UART messages from RPi
// start display timer to delay Bluetooth status information             
            DISPLAY_Timer_Start();
// when in BT mode only, update display to link status after timer expire
            if (DISPLAY_UPDATE > 0)
            { 
// sent to BT module command to display its current status
                BT_control(0, 0); 
                DISPLAY_UPDATE = 0;
            } 
        break;
    
// SYSTEM_STATE = 8 - system in BlueTooth Tx mode
        case (8):
// no UART messages from RPi
// start display timer to delay Bluetooth status information             
            DISPLAY_Timer_Start();
// when in BT mode only, update display to link status after timer expire
            if (DISPLAY_UPDATE > 0)
            { 
// sent to BT module command to display its current status
                BT_control(0, 0); 
                DISPLAY_UPDATE = 0;
            } 
        break;      

        default:
// DEFAULT STATEMENT        
        break;
        }
    }
        

// display signal level info
    else if (DISPLAY_STATE == 2)
    {
//  0 - read back signal level values and encode them into information sent to 
//      display module
        SigmaDSP_to_display(0);
// disp_ctrl2 
// CTRL1.0 and CTRL1.1 - clear all LED status except BT Tx and ONLINE
        new_disp_ctrl2 = new_disp_ctrl2 & 0x03;
// CTRL1.2 - set Signal Level Indicator
        new_disp_ctrl2 = new_disp_ctrl2 | 0x04;
// start display timer to periodically sent informaiton to display module
// without blocking delay  
//        DISPLAY_Timer_Start();
// check if 2 seconds timer expired             
//        if (DISPLAY_UPDATE > 0)
//        { 
// set flag and sent info to display module
        new_display_data_flag = 1;
//            DISPLAY_UPDATE = 0;
//        } 
    }
        
// display spectrum analyzer info
    else if (DISPLAY_STATE == 3)
    {
//  1 - read back spectrum analyser info and encode it into informaiton sent to
//      display module
        SigmaDSP_to_display(1);
// disp_ctrl2 
// CTRL1.0 and CTRL1.1 - clear all LED status except BT Tx and ONLINE
        new_disp_ctrl2 = new_disp_ctrl2 & 0x03;
// CTRL1.3 - set Spectrum Analyser indicator 
        new_disp_ctrl2 = new_disp_ctrl2 | 0x08;
// start display timer to periodically sent informaiton to display module
// without blocking delay  
//        DISPLAY_Timer_Start();
// check if 2 seconds timer expired             
//        if (DISPLAY_UPDATE > 0)
//        { 
// set flag and sent info to display module
        new_display_data_flag = 1;
//            DISPLAY_UPDATE = 0;
//        } 
// set SPI slave select line to display module
//    SPIM_SpiSetActiveSlaveSelect(SPIM_SPI_SLAVE_SELECT1);  
    }
        
// display clock 1
    else if (DISPLAY_STATE == 4)
    {
// display clock 1                              
        strcpy((char*)new_display_data_buffer, "CLOCK ONE               ");
// disp_ctrl2 
// CTRL1.0 and CTRL1.1 - clear all LED status except BT Tx and ONLINE
        new_disp_ctrl2 = new_disp_ctrl2 & 0x03;
// CTRL1.4 - set Clock 1 indicator 
        new_disp_ctrl2 = new_disp_ctrl2 | 0x10;
// start display timer to periodically sent informaiton to display module
// without blocking delay  
        DISPLAY_Timer_Start();
// check if 2 seconds timer expired             
        if (DISPLAY_UPDATE > 0)
        { 
// set flag and sent info to display module
            new_display_data_flag = 1;
            DISPLAY_UPDATE = 0;
        } 
    }
        
// display clock 2
    else if (DISPLAY_STATE == 5)
    {
// display clock 2                                
        strcpy((char*)new_display_data_buffer, "CLOCK TWO               ");
// disp_ctrl2 
// CTRL1.0 and CTRL1.1 - clear all LED status except BT Tx and ONLINE
        new_disp_ctrl2 = new_disp_ctrl2 & 0x03;
// CTRL1.5 - set Clock 2 indicator 
        new_disp_ctrl2 = new_disp_ctrl2 | 0x20;
// start display timer to periodically sent informaiton to display module
// without blocking delay  
        DISPLAY_Timer_Start();
// check if 2 seconds timer expired             
        if (DISPLAY_UPDATE > 0)
        { 
// set flag and sent info to display module
            new_display_data_flag = 1;
            DISPLAY_UPDATE = 0;
        } 
    }
        
// display blank data
    else if (DISPLAY_STATE == 6)
    {
// blank out display data            
        strcpy((char*)new_display_data_buffer, "                        ");
// CTRL1.0 and CTRL1.1 - clear all LED status except BT Tx and ONLINE
        new_disp_ctrl2 = new_disp_ctrl2 & 0x03;
// start display timer to periodically sent informaiton to display module
// without blocking delay  
        DISPLAY_Timer_Start();
// check if 2 seconds timer expired             
        if (DISPLAY_UPDATE > 0)
        { 
// set flag and sent info to display module
            new_display_data_flag = 1;
            DISPLAY_UPDATE = 0;
        } 
    }        
       
    return 0;
}



/*******************************************************************************
* Function Name: datalink_check()
********************************************************************************
* Summary:
*  Functon responsible for interpetting remote control commands and moving system
*  state based on datalink input
*   
* Parameters:
*  command - number reported back by datalink_decoder function. List as follow:
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
* Return:
*  zero
*
*******************************************************************************/  
uint8 datalink_check(uint8 command)
{
    
// system state array stored in EEPROM
// [0] = SYSTEM_STATE 
// [1] = DISPLAY_STATE
// [2] = BT_Tx_STATE
uint8 array[]= { 0x00, 0x00, 0x00 };

// check if system is in power down state
    if (SYSTEM_STATE == 0)
    {
// if in power down state - restore system to last saved state
// Read data from emulated EEPROM
        Em_EEPROM_Read(LOGICAL_EEPROM_START, eepromArray, LOGICAL_EEPROM_SIZE);         
// check if Aux only button was pressed     
        if (command == 10)
        {
// set SYSTEM STATE variables based on EEPROM read back data
            SYSTEM_STATE = eepromArray[0];
// set BT variables based on EEPROM read back data
            BT_Tx_STATE = eepromArray[2];            
// if system state is 0 force to start with system state in 1 
// to avoid infinite loop in system state 0
            if (SYSTEM_STATE == 0)
            {
                SYSTEM_STATE = 1;
            }
        }
// check if Aux + 1 or only 1 button was pressed
// start Player state
        else if (command == 11)
        {
// set SYSTEM STATE variables to Player
            SYSTEM_STATE = 1;
// set BT variables based on EEPROM read back data
            BT_Tx_STATE = eepromArray[2];            
        }
// check if Aux + 2 or only 2 button was pressed
// start iRadio state
        else if (command == 12)
        {
// set SYSTEM STATE variables to iRadio
            SYSTEM_STATE = 2;
// set BT variables based on EEPROM read back data
            BT_Tx_STATE = eepromArray[2];            
        }
// check if Aux + 3 or only 3 button was pressed
// start DAB Radio state
        else if (command == 13)
        {
// set SYSTEM STATE variables to DAB Radio
            SYSTEM_STATE = 3;
// set BT variables based on EEPROM read back data
            BT_Tx_STATE = eepromArray[2];            
        }
// check if Aux + 4 or only 4 button was pressed
// start Aux IN state
        else if (command == 14)
        {
// set SYSTEM STATE variables to Aux IN
            SYSTEM_STATE = 4;
// set BT variables based on EEPROM read back data
            BT_Tx_STATE = eepromArray[2];            
        }
// check if Aux + 5 or only 5 button was pressed
// start Clock state
        else if (command == 15)
        {
// set SYSTEM STATE variables to RDS/FM Radio
            SYSTEM_STATE = 5;
// set BT variables based on EEPROM read back data
            BT_Tx_STATE = eepromArray[2];            
        }
// check if 6 button was pressed
// start RDS/FM Radio state
        else if (command == 16)
        {
// set SYSTEM STATE variables to RDS/FM Radio
            SYSTEM_STATE = 6;
// set BT variables based on EEPROM read back data
            BT_Tx_STATE = eepromArray[2];            
        }
// check if 7 button was pressed
// start Bluetooth Rx state
        else if (command == 17)
        {
// set SYSTEM STATE variables to Bluetooth Rx
            SYSTEM_STATE = 7;
// clear BT_TX variable indicating that bleutooth is in use as Rx
            BT_Tx_STATE = 0;
        }
// check if 8 button was pressed
// start Bluetooth Tx state
        else if (command == 18)
        {
// set SYSTEM STATE variables to Bluetooth Tx
            SYSTEM_STATE = 8;
// set BT_TX variable indicating that bleutooth is in use as Rx
            BT_Tx_STATE = 1;            
        }
// set DISPLAY variables based on EEPROM read back data
        DISPLAY_STATE = eepromArray[1];
    }
    else
        {
// check if Aux + 1 or only 1 button was pressed
// start Player state
            if (command == 11)
            {
// set SYSTEM STATE variables to Player
                SYSTEM_STATE = 1;
            }
// check if Aux + 2 or only 2 button was pressed
// start iRadio state
            else if (command == 12)
            {
// set SYSTEM STATE variables to iRadio
                SYSTEM_STATE = 2;
            }
// check if Aux + 3 or only 3 button was pressed
// start DAB Radio state
            else if (command == 13)
            {
// set SYSTEM STATE variables to DAB Radio
                SYSTEM_STATE = 3;
            }
// check if Aux + 4 or only 4 button was pressed
// start Aux IN state
            else if (command == 14)
            {
// set SYSTEM STATE variables to Aux IN
                SYSTEM_STATE = 4;
            }
// check if Aux + 5 or only 5 button was pressed
// start Clock state
            else if (command == 15)
            {
// set SYSTEM STATE variables to RDS/FM Radio
                SYSTEM_STATE = 5;
            }
// check if 6 button was pressed
// start RDS/FM Radio state
            else if (command == 16)
            {
// set SYSTEM STATE variables to RDS/FM Radio
                SYSTEM_STATE = 6;
            }// check if 6 button was pressed
// check if 7 button was pressed
// start Bluetooth Rx state
            else if (command == 17)
            {
// set SYSTEM STATE variables to Bluetooth Rx
                SYSTEM_STATE = 7;
// clear BT_TX variable indicating that bleutooth is in use as Rx
                BT_Tx_STATE = 0;
            }
// check if 8 button was pressed
// start Bluetooth Tx state
            else if (command == 18)
            {
// set SYSTEM STATE variables to Bluetooth Tx
                SYSTEM_STATE = 8;
// set BT_TX variable indicating that bleutooth is in use as Rx
                BT_Tx_STATE = 1;            
            }
        }
        
// check if POWER OFF command was received     
    if (command == 26)
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
    }
    
// check if DISPLAY or yellow_button command was received     
    if (command == 31)
    {
// check if system is not in power down state
        if (SYSTEM_STATE != 0)
        {
// if it is not then move to next display state
            DISPLAY_STATE = DISPLAY_STATE + 1;
            if (DISPLAY_STATE >= 7)
            {
                DISPLAY_STATE = 1;
            }
        }
    }

// check if green_button command was received     
    if (command == 32)
    {
// check if system is not in power down state
        if (SYSTEM_STATE != 0)
        {
// if it is not then move to previus display state
            DISPLAY_STATE = DISPLAY_STATE - 1;
            if (DISPLAY_STATE <= 0)
            {
                DISPLAY_STATE = 6;
            }
        }
    }
    
// check if system is in Player state
    if (SYSTEM_STATE == 1)
    {
// if in player state and command that arrives are relevant to player react to them
// check OK/GO/PLAY button was pressed     
        if (command == 20)
        {
// sent GO command to RPi ofer UART            
            UART_UartPutString("-GO+");  
        }
// check UP/ STEP > button was pressed     
        else if (command == 21)
        {
// sent UP command to RPi ofer UART            
            UART_UartPutString("-DOWN+");  
        }
// check DOWN/< STEP button was pressed     
        else if (command == 22)
        {
// sent DOWN command to RPi ofer UART            
            UART_UartPutString("-UP+");  
        }
// check LEFT/<< button was pressed     
        else if (command == 23)
        {
// sent BACK command to RPi ofer UART            
            UART_UartPutString("-BACK+");  
        }
// check RIGHT/>> button was pressed     
        else if (command == 24)
        {
// sent NEXT command to RPi ofer UART            
            UART_UartPutString("-NEXT+");  
        }
// check STOP button was pressed     
        else if (command == 25)
        {
// sent STOP command to RPi ofer UART            
            UART_UartPutString("-STOP+");  
        }
    }
    
// check if system is in iRadio state
    if (SYSTEM_STATE == 2)
    {
// if in iRadio state and command that arrives are relevant to iRadio react to them
// check OK/GO/PLAY button was pressed     
        if (command == 20)
        {
// sent GO command to RPi ofer UART            
            UART_UartPutString("-GO+");  
        }
// check UP/STEP > or RIGHT/>> button or was pressed     
        else if ((command == 21) | (command == 24))
        {
// sent UP command to RPi ofer UART            
            UART_UartPutString("-DOWN+");  
        }
// check DOWN/< STEP or LEFT/<< button or was pressed     
        else if ((command == 22) | (command == 23))
        {
// sent DOWN command to RPi ofer UART            
            UART_UartPutString("-UP+");  
        }
    }    

// check if system is in DAB Radio state
    if (SYSTEM_STATE == 3)
    {
// if in DAB Radio state and command that arrives are relevant to DAB Radio react to them
// check OK/GO/PLAY button was pressed     
        if (command == 20)
        {
// sent GO command to RPi ofer UART            
            UART_UartPutString("-GO+");  
        }
// check UP/STEP > or RIGHT/>> button or was pressed     
        else if ((command == 21) | (command == 24))
        {
// sent UP command to RPi ofer UART            
            UART_UartPutString("-DOWN+");  
        }
// check DOWN/< STEP or LEFT/<< button or was pressed     
        else if ((command == 22) | (command == 23))
        {
// sent DOWN command to RPi ofer UART            
            UART_UartPutString("-UP+");  
        }
    }     
    
// check if FM radio station number command was intercepted     
    if ((command >= 41) & (command <= 60))
    {
// if so, store radio station nubmer in globaal variable
        FM_RADIO_STATION = command - 40;
// if in RM/RDS Radio state and command that user changes RF radio stations, react to them
    if (SYSTEM_STATE == 6)
        {
            UART_UartPutString("-FM_");    
            UART_UartPutChar('0' + (FM_RADIO_STATION / 10));               
            UART_UartPutChar('0' + (FM_RADIO_STATION % 10));
            UART_UartPutString("+");  
        }
    }    

// check if system is in Bluetooth Rx state
    if (SYSTEM_STATE == 7)
    {
// if in Bluetooth Rx state and command that arrives are relevant to BT Rx react to them
// check OK/GO/PLAY button was pressed     
        if (command == 20)
        {
// sent to BT module command to pause currently played song
            BT_control(2, 4); 
// start display timer to delay Bluetooth status information             
            DISPLAY_Timer_Start();
        }
// check MENU(onBeo4)/TURN(on MCP) button was pressed     
        if (command == 27)
        {
// sent to BT module command to start pairing            
            BT_control(2, 1);
// start display timer to delay Bluetooth status information             
            DISPLAY_Timer_Start();
        }
// check EXIT(on Beo4)/RESET(on MCP) button was pressed     
        if (command == 28)
        {
// sent to BT module command to clear all recorded devices            
            BT_control(2, 3);
// start display timer to delay Bluetooth status information             
            DISPLAY_Timer_Start();
        }
// check UP/STEP > or RIGHT/>> button or was pressed     
        else if ((command == 21) | (command == 24))
        {
// sent to BT module command to move to previus song            
            BT_control(2, 6); 
// start display timer to delay Bluetooth status information             
            DISPLAY_Timer_Start();
        }
// check DOWN/< STEP or LEFT/<< button or was pressed     
        else if ((command == 22) | (command == 23))
        {
// sent to BT module comand to move to next song            
            BT_control(2, 5); 
// start display timer to delay Bluetooth status information             
            DISPLAY_Timer_Start();
        }
// check STOP button was pressed     
        else if (command == 25)
        {
// sent to BT module command to re-connect            
            BT_control(2, 2);
// start display timer to delay Bluetooth status information             
            DISPLAY_Timer_Start();
        }
    }      
    
// check if system is in Bluetooth Tx state
    if (SYSTEM_STATE == 8)
    {
// if in Bluetooth Tx state and command that arrives are relevant to BT Tx react to them
// check OK/GO/PLAY button was pressed     
        if (command == 20)
        {
// sent to BT module command to mute currently played audio
            BT_control(1, 4);  
// start display timer to delay Bluetooth status information             
            DISPLAY_Timer_Start();
        }
// check MENU(onBeo4)/TURN(on MCP) button was pressed     
        if (command == 27)
        {
// sent to BT module command to start pairing            
            BT_control(1, 1);
// start display timer to delay Bluetooth status information             
            DISPLAY_Timer_Start();
        }
// check EXIT(on Beo4)/RESET(on MCP) button was pressed     
        if (command == 28)
        {
// sent to BT module command to clear all recorded devices            
            BT_control(1, 3);
// start display timer to delay Bluetooth status information             
            DISPLAY_Timer_Start();
        }
// check STOP button was pressed     
        else if (command == 25)
        {
// sent to BT module command to re-connect            
            BT_control(1, 2);
// start display timer to delay Bluetooth status information             
            DISPLAY_Timer_Start();
        }
    }      
    
// clear command number after that
    command = 0;
    
// return 0 indicating no button press action
    return 0;
}


/* [] END OF FILE */
