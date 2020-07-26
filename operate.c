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
#include <modes.h>
//#include <inputs.h>


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
*  SYSTEM_STATE = 5 - RDS/FM display
*  SYSTEM_STATE = 6 - BlueTooth Rx
*  SYSTEM_STATE = 7 - BlueTooth Tx
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

        
// SYSTEM_STATE = 0 - system in power down mode
    switch (SYSTEM_STATE)
    {    
    case (0):
    
        if (current_PSUstate.BlueTooth_PWR == 1)
        {
// Send to BlueTooth pause/mute command
        BT_control(1, 4); 
// SENT COMMAND TO DISPLAY ABOUT POWERING DOWN
// SENT COMMAND TO DISPLAY ABOUT POWERING DOWN
// SENT COMMAND TO DISPLAY ABOUT POWERING DOWN
// WAIT 2..3 seconds
// WAIT 2..3 seconds            
// WAIT 2..3 seconds
            next_PSUstate.BlueTooth_PWR = 0;    
        }
        
        if (current_PSUstate.Display_PWR == 1)
        {
// SENT COMMAND TO DISPLAY ABOUT POWERING DOWN
// SENT COMMAND TO DISPLAY ABOUT POWERING DOWN
// SENT COMMAND TO DISPLAY ABOUT POWERING DOWN
// WAIT 2..3 seconds
// WAIT 2..3 seconds            
// WAIT 2..3 seconds
            next_PSUstate.Display_PWR = 0;        
        }
        
        if (current_PSUstate.SigmaDSP_PWR == 1)
        {
// SENT MUTE COMMAND TO SigmaDSP ???
// SENT MUTE COMMAND TO SigmaDSP ???
// SENT MUTE COMMAND TO SigmaDSP ???
// SENT COMMAND TO DISPLAY ABOUT POWERING DOWN
// SENT COMMAND TO DISPLAY ABOUT POWERING DOWN
// SENT COMMAND TO DISPLAY ABOUT POWERING DOWN
// WAIT 2..3 seconds
// WAIT 2..3 seconds            
// WAIT 2..3 seconds            
            next_PSUstate.SigmaDSP_PWR = 0;            
        }
        
        if (current_PSUstate.RPI_PWR == 1)
        {
            if (current_PSUstate.RPi_GPIO_state == 1)
            {
// SENT COMMAND TO DISPLAY ABOUT POWERING DOWN
// SENT COMMAND TO DISPLAY ABOUT POWERING DOWN
// SENT COMMAND TO DISPLAY ABOUT POWERING DOWN
// WAIT 2..3 seconds
// WAIT 2..3 seconds
// WAIT 2..3 seconds
// WAIT UNTILL current_PSUstate.RPi_GPIO_state == 1
// sent command over UART command to RPI to power down
                UART_UartPutString("-SHUTDOWN+");
// WAIT untill RPI powers down
//                while (current_PSUstate.RPi_GPIO_state == 1)
                {
// read back current PSU state    
                    current_PSUstate = psu_config(2, next_PSUstate);
                }
// set RPI PSU to power down state
                next_PSUstate.RPI_PWR = 0;
            }
            else
            {
// SENT COMMAND TO DISPLAY ABOUT POWERING DOWN
// SENT COMMAND TO DISPLAY ABOUT POWERING DOWN
// WAIT 2..3 seconds
// WAIT 2..3 seconds
                next_PSUstate.RPI_PWR = 0;
            }
        }
// disable all power blocks        
        psu_config(1, next_PSUstate);
    
        break;
      
    
    
// SYSTEM_STATE = 1 - system in Player mode
    case (1):
    
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

// read back current PSU state    
        current_PSUstate = psu_config(2, next_PSUstate);

        if (current_PSUstate.RPI_PWR == 1)
            {
 //               while (current_PSUstate.RPi_GPIO_state == 0)
                {
// WAIT untill RPI powers up
// read back current PSU state    
                current_PSUstate = psu_config(2, next_PSUstate);
// SENT INFORMAITON TO DISPLAY ABOUT RPI BOOTING UP
// SENT INFORMAITON TO DISPLAY ABOUT RPI BOOTING UP            
// SENT INFORMAITON TO DISPLAY ABOUT RPI BOOTING UP            
                }
            }                

        if (BT_Tx_STATE == 1)
        {
// ADD DELAY HERE?
// Enable BlueTooth in Tx state - re-connect to latest device
        BT_control(1, 2); 

        } 
// SENT OVER SPI information about Player LED ON
// REPLACE with SPI transfer
        UART_UartPutString("\r\nLED: Player LED ON");       
// REPLACE with SPI transfer
        break;
 
    
    
// SYSTEM_STATE = 2 - system in iRadio mode    
    case (2):
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

// read back current PSU state    
        current_PSUstate = psu_config(2, next_PSUstate);

        if (current_PSUstate.RPI_PWR == 1)
            {
 //               while (current_PSUstate.RPi_GPIO_state == 0)
                {
// WAIT untill RPI powers up
// read back current PSU state    
                current_PSUstate = psu_config(2, next_PSUstate);
// SENT INFORMAITON TO DISPLAY ABOUT RPI BOOTING UP
// SENT INFORMAITON TO DISPLAY ABOUT RPI BOOTING UP            
// SENT INFORMAITON TO DISPLAY ABOUT RPI BOOTING UP            
                }
            }        

        if (BT_Tx_STATE == 1)
        {
// ADD DELAY HERE?
// Enable BlueTooth in Tx state - re-connect to latest device
        BT_control(1, 2); 

        } 
// SENT OVER SPI informaiton about iRadio LED ON
// REPLACE with SPI transfer
        UART_UartPutString("\r\nLED: iRadio LED ON");       
// REPLACE with SPI transfer
        break;
        
    
    
// SYSTEM_STATE = 3 - system in DAB Radio mode
    case (3):
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

// read back current PSU state    
        current_PSUstate = psu_config(2, next_PSUstate);

        if (current_PSUstate.RPI_PWR == 1)
            {
 //               while (current_PSUstate.RPi_GPIO_state == 0)
                {
// WAIT untill RPI powers up
// read back current PSU state    
                current_PSUstate = psu_config(2, next_PSUstate);
// SENT INFORMAITON TO DISPLAY ABOUT RPI BOOTING UP
// SENT INFORMAITON TO DISPLAY ABOUT RPI BOOTING UP            
// SENT INFORMAITON TO DISPLAY ABOUT RPI BOOTING UP            
                }
            }
 
        if (BT_Tx_STATE == 1)
        {
// ADD DELAY HERE?
// Enable BlueTooth in Tx state - re-connect to latest device
        BT_control(1, 2); 

        } 
// SENT OVER SPI informaiton about DAB Radio LED ON
// REPLACE with SPI transfer
        UART_UartPutString("\r\nLED: DAB Radio LED ON");       
// REPLACE with SPI transfer        
        break;

    
    
// SYSTEM_STATE = 4 - system in AuxIn mode    
    case (4):
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

        if (BT_Tx_STATE == 1)
        {
// ADD DELAY HERE?
// Enable BlueTooth in Tx state - re-connect to latest device
        BT_control(1, 2); 

        } 
// SENT OVER SPI informaiton about AuxIN LED ON
// REPLACE with SPI transfer
        UART_UartPutString("\r\nLED: AuxIN LED ON");       
// REPLACE with SPI transfer
        break;

    
    
// SYSTEM_STATE = 5 - system in RDS/FM mode
    case (5):
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
        } 
        
// enable all necessary blocks        
        psu_config(1, next_PSUstate);  

// read back current PSU state    
        current_PSUstate = psu_config(2, next_PSUstate);

        if (current_PSUstate.RPI_PWR == 1)
            {
 //               while (current_PSUstate.RPi_GPIO_state == 0)
                {
// WAIT untill RPI powers up
// read back current PSU state    
                current_PSUstate = psu_config(2, next_PSUstate);
// SENT INFORMAITON TO DISPLAY ABOUT RPI BOOTING UP
// SENT INFORMAITON TO DISPLAY ABOUT RPI BOOTING UP            
// SENT INFORMAITON TO DISPLAY ABOUT RPI BOOTING UP            
                }
            }      

        if (BT_Tx_STATE == 1)
        {
// ADD DELAY HERE?
// Enable BlueTooth in Tx state - re-connect to latest device
        BT_control(1, 2); 
        } 
// SENT OVER SPI informaiton about RDS/FM display LED ON
// REPLACE with SPI transfer
        UART_UartPutString("\r\nLED: RDS/FM ON");       
// REPLACE with SPI transfer        
        break;

    
    
// SYSTEM_STATE = 6 - system in BlueTooth Rx mode
    case (6):
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
        
// clear BT_TX variable indicating that bleutooth is in use as Rx
        BT_Tx_STATE = 0; 
// SENT OVER SPI informaiton about BlueTooth Rx LED ON
// Enable BlueTooth in Rx mode - re-connect to last device        
        BT_control(2, 2); 
// REPLACE with SPI transfer
        UART_UartPutString("\r\nLED: BlueTooth Rx LED ON");       
// REPLACE with SPI transfer
        break;
    
    
    
// SYSTEM_STATE = 7 - system in BlueTooth Tx mode
   case (7):
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
        
// set BT_TX variable to 1 indicating that bleutooth is in ues 
        BT_Tx_STATE = 1;  
// Enable BlueTooth in Tx state - re-connect to latest device
        BT_control(1, 2);         
// SENT OVER SPI informaiton about BlueTooth Tx LED ON
// REPLACE with SPI transfer
        UART_UartPutString("\r\nLED: BlueTooth Tx LED ON");       
// REPLACE with SPI transfer
        break;
    }
    
    return SYSTEM_STATE;
}



/*******************************************************************************
* Function Name: BeoM_current_mode()
********************************************************************************
* Summary:
*  Function monitors SYSTEM STATE variabel and listen to incoming commands from
*  push buttons and over Datalink. 
*  it then reacts accordingly to active state. 
*  SYSTEM_STATE = 0 - power down
*  SYSTEM_STATE = 1 - Player
*  SYSTEM_STATE = 2 - iRadio
*  SYSTEM_STATE = 3 - DAB Radio
*  SYSTEM_STATE = 4 - Aux IN
*  SYSTEM_STATE = 5 - RDS/FM display
*  SYSTEM_STATE = 6 - BlueTooth Rx
*  SYSTEM_STATE = 7 - BlueTooth Tx
*
*   
* Parameters:
*  Function operates on global variable:
*  SYSTEM_STATE and expect to be called witch command nubmer
*  Input commands:
*  1 = UP
*  2 = DOWN
*  3 = NEXT
*  4 = PREVIUS
*  5 = OK/GO
*  6 = STOP
*  7 = Button: MODE SHORT
*  ??? = FM station nubmers
*
* Return:
*  Funciton returns current ????
*
*******************************************************************************/  
uint8 BeoM_PSU_current_mode(uint8 command)  
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
// over data link:
// RIGHT = NEXT song or into folder
// LEFT = PREVIUS song or out of the folder       
// UP = song or folder up
// DOWN = song or folder down
// OK = OK/Go command confirming selection
// PAUSE/STOP = pause currently played song        
    case (1):
        switch (command)
        {
//  1 = UP
//  2 = DOWN
//  3 = NEXT
//  4 = PREVIUS
//  5 = OK/GO
//  6 = STOP
//  7 = Button: MODE SHORT         
        case (1):
            UART_UartPutString("-UP+\r\n");
            break;
        case (2):
            UART_UartPutString("-DOWN+\r\n");
            break;
        case (3):
            UART_UartPutString("-NEXT+\r\n");
            break;
        case (4):
            UART_UartPutString("-BACK+\r\n");
            break;
        case (5):
            UART_UartPutString("-GO+\r\n");
            break;
        case (6):
            UART_UartPutString("-STOP+\r\n");
            break;
        case (7):
            UART_UartPutString("-DOWN+\r\n");
            CyDelay(100);  
            UART_UartPutString("-GO+\r\n");
            break;
        
        default:
            break;

        }
        break;
        
    
// SYSTEM_STATE = 2 - system in iRadio mode    
// System reacts to commands:
// push button MODE Short = next radio station (DOWN)
// over data link:
// UP = previus radio station
// DOWN = next radio station
    case(2):
        switch (command)
        {
//  1 = UP
//  2 = DOWN
//  5 = OK/GO
//  7 = Button: MODE SHORT         
        case (1):
            UART_UartPutString("-UP+\r\n");
            break;
        case (2):
            UART_UartPutString("-DOWN+\r\n");
            break;
        case (5):
            UART_UartPutString("-GO+\r\n");
            break;
        case (7):
            UART_UartPutString("-DOWN+\r\n");
            CyDelay(100);  
            UART_UartPutString("-GO+\r\n");
            break;
        
        default:
            break;
        }
        break;

        
// SYSTEM_STATE = 3 - system in DAB Radio mode
// System reacts to commands:
// push button MODE Short = next radio station (DOWN)
// over data link:
// UP = previus radio station
// DOWN = next radio station
    case(3):
        switch (command)
        {
//  1 = UP
//  2 = DOWN
//  5 = OK/GO
//  7 = Button: MODE SHORT         
        case (1):
            UART_UartPutString("-UP+\r\n");
            break;
        case (2):
            UART_UartPutString("-DOWN+\r\n");
            break;
        case (5):
            UART_UartPutString("-GO+\r\n");
            break;
        case (7):
            UART_UartPutString("-DOWN+\r\n");
            CyDelay(100);  
            UART_UartPutString("-GO+\r\n");
            break;
        
        default:
            break;
        }
        break;
                

// SYSTEM_STATE = 4 - system in AuxIn mode    
// System shuld react only to display changes in this mode  
// no interaction from systme in AuxIN state    
// No system commands associated with this mode
    case (4):
        break;
    
    
// SYSTEM_STATE = 5 - system in RDS/FM mode
    case (5):
    switch (command)
        {
//  8 = FM/RDS station number        
        case (8):
            UART_UartPutString("-FM_01+\r\n");
// NEED TO ADD HERE CONVENTON TO DEL88IVER FM STATION NUMBERS
            break;
        
        default:
            break;
        }    
        break;

        
// SYSTEM_STATE = 6 - system in BlueTooth Rx mode
    case (6):
        
// System reacts to commands:
// push button MODE Short = re-connecting
// over data link:
// PAIRING = ???
// CLEARING = all previus settings ???        
// RECONNECTING = OK/Go command
// UP = previus song
// DOWN = next song
// PAUSE/STOP = pause currently played song     
//  3 = NEXT
//  4 = PREVIUS
//  5 = OK/GO
//  6 = STOP
//  7 = Button: MODE SHORT      
    switch (command)
        {
        case (3):
// BlueTooth next song        
            BT_control(2, 6); 
            break;
        case (4):
// BlueTooth previous song        
            BT_control(2, 5); 
            break;
        case (5):
// BlueTooth re-connect        
            BT_control(2, 2); 
            break;
        case (6):
// BlueTooth pause        
            BT_control(2, 4); 
            break;
        case (7):
// BlueTooth start pairing        
            BT_control(2, 1); 
            break;
        }
        break;
    
// SYSTEM_STATE = 7 - system in BlueTooth Tx mode
    case (7):
    
// System reacts to commands:
// push button MODE Short = re-connecting
// over data link:
// PAIRING = ???
// CLEARING = all previus settings ???        
// RECONNECTING = OK/Go command
// MUTE = mute audio on currently played song    
//  5 = OK/GO
//  6 = STOP
//  7 = Button: MODE SHORT         
    
    switch (command)
        {
        case (5):
// BlueTooth re-connect        
            BT_control(1, 2); 
            break;
        case (6):
// BlueTooth pause        
            BT_control(1, 4); 
            break;
        case (7):
// BlueTooth start pairing        
            BT_control(1, 1); 
            break;
        }
        
        break;

    
    default:
// DEFAULT STATEMENT        
        break;
    
    }
    
    return 0;
}

/* [] END OF FILE */
