/*******************************************************************************
* \file SENT_TX_1.h
* \version 1.0
*
* Contains the function prototypes and constants available to the SENT
* component.
*
********************************************************************************
* \copyright
* Copyright 2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#ifndef SENT_TX_1_H
#define SENT_TX_1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "SENT_TX_1_PWM.h"
#include "SENT_TX_1_ISR.h"
#include "SENT_TX_1_CLK.h"


/*******************************************************************************
*    Conditional Compilation Parameters
*******************************************************************************/

#define SENT_TX_1_CRC_IMPLEMENTATION     (1UL)
#define SENT_TX_1_PAUSE_PULSE            (0UL)
#define SENT_TX_1_CLOCK_PERIOD_NS_DECS   (30U)
#define SENT_TX_1_TRANSMIT_MODE          (0UL)

#define SENT_TX_1_CLOCK_ONE_DEC          (10U)
#define SENT_TX_1_CLOCK_ROUND            (5U)

/* The clock divider define */
#define SENT_TX_1_CLOCK_DIVIDER  ((uint16) (((SENT_TX_1_CLOCK_PERIOD_NS_DECS * \
                                                     CYDEV_BCLK__HFCLK__MHZ) + SENT_TX_1_CLOCK_ROUND) / \
                                                     SENT_TX_1_CLOCK_ONE_DEC))


/*******************************************************************************
*   Custom Declarations
*******************************************************************************/

#ifdef CYDEV_VDDIO_MV
    #if (CYDEV_VDDIO_MV < 4850UL)
        #warning "As per the SAE J2716 standard, device should be operating in this range: 4.85 V to 5.15 V."
    #endif /* CYDEV_VDDIO_MV < 4850UL */
#endif /* CYDEV_VDDIO_MV */

#ifdef CYDEV_VDDD_MV
    #if (CYDEV_VDDD_MV < 4850UL)
        #warning "As per the SAE J2716 standard, device should be operating in this range: 4.85 V to 5.15 V."
    #endif /* CYDEV_VDDD_MV < 4850UL */
#endif /* CYDEV_VDDD_MV */

#ifdef CYDEV_VDD_MV
    #if (CYDEV_VDD_MV < 4850UL)
        #warning "As per the SAE J2716 standard, device should be operating in this range: 4.85 V to 5.15 V."
    #endif /* CYDEV_VDD_MV < 4850UL */
#endif /* CYDEV_VDD_MV */


/*******************************************************************************
*   Internal Constants
*******************************************************************************/

#define SENT_TX_1__DISABLED 0
#define SENT_TX_1__ENABLED 1

#define SENT_TX_1__LEGACYCRC 0
#define SENT_TX_1__NEWCRC 1

#define SENT_TX_1__SINGLE_MODE 0
#define SENT_TX_1__CONTINUOUS_MODE 1



/*******************************************************************************
*          API Constants
*******************************************************************************/

#define SENT_TX_1_NIBBLE_MASK    (0xfU)
#define SENT_TX_1_DATA_NIBBLES   (6U)

/* Status + data, crc is calculated automatically */
#define SENT_TX_1_USER_NIBBLES   (SENT_TX_1_DATA_NIBBLES + 1U)

#define SENT_TX_1_ALL_TICKS      (282U)
#define SENT_TX_1_SYNC_TICKS     (56UL)
#define SENT_TX_1_ZERO_TICKS     (12U)

#define SENT_TX_1_CRC_IDX        (7U)

#if (SENT_TX_1_PAUSE_PULSE == SENT_TX_1__ENABLED)
    #define SENT_TX_1_LAST_IDX       (9U)
    #define SENT_TX_1_PAUSE_IDX      (8U)
    #define SENT_TX_1_ALL_NIBBLES    (SENT_TX_1_USER_NIBBLES + 1U)
#else
    #define SENT_TX_1_LAST_IDX       (8U)
    #define SENT_TX_1_ALL_NIBBLES    (SENT_TX_1_USER_NIBBLES)
#endif /* SENT_TX_1_PAUSE_PULSE */

#define SENT_TX_1_NEW_FRAME          (0U)

#if (SENT_TX_1_TRANSMIT_MODE == SENT_TX_1__SINGLE_MODE)
    #if (SENT_TX_1_PWM_CY_TCPWM_V2 == 0U)
        #define SENT_TX_1_END_OF_FRAME   (SENT_TX_1_LAST_IDX + 4U)
        #define SENT_TX_1_STOP_COUNTER   (SENT_TX_1_LAST_IDX + 3U)
        #define SENT_TX_1_PREPARE_TO_STOP_COUNTER   (SENT_TX_1_LAST_IDX + 2U)
    #else
        #define SENT_TX_1_END_OF_FRAME   (SENT_TX_1_LAST_IDX + 3U)
        #define SENT_TX_1_STOP_COUNTER   (SENT_TX_1_LAST_IDX + 2U)
        #define SENT_TX_1_PREPARE_TO_STOP_COUNTER   (SENT_TX_1_LAST_IDX + 1U)
    #endif /* (SENT_TX_1_PWM_CY_TCPWM_V2 == 0U) */
#else
    #define SENT_TX_1_END_OF_FRAME   (SENT_TX_1_LAST_IDX)
#endif /* SENT_TX_1_PAUSE_PULSE */

#define SENT_TX_1_SEED                (0x5U)
#define SENT_TX_1_PWM_LOW_TICKS       (0x5U)
#define SENT_TX_1_TICKS_PREP_TO_STOP  ((uint32) SENT_TX_1_PWM_LOW_TICKS - 1U)

/* Need to take into account that PSoC 4000 has different version of TCPWM V2 HW */
#if (CY_PSOC4_4000)
    #define SENT_TX_1_COMP_PREP_TO_STOP   (SENT_TX_1_PWM_LOW_TICKS)
#else
    #define SENT_TX_1_COMP_PREP_TO_STOP   (0U)
#endif /* CY_PSOC4_4000 */

/** \addtogroup group_constants
* @{ */

/**
* \defgroup group_sent_status SENT TX status definitions
* \{
* Definitions of SENT TX status
*/

/** The define to show the data is sent and the component is ready 
* to send a new data */
#define SENT_TX_1_READY        (0U)

/** The define to show the component is sending previous data */
#define SENT_TX_1_BUSY         (1U)
/** \} group_sent_status */
/** @} constants */


/*******************************************************************************
*       Function Prototypes
*******************************************************************************/

/** \addtogroup group_general
* @{ */
/** \cond INTERNAL */
CY_ISR_PROTO(SENT_TX_1_Interrupt); 
/** \endcond */

void   SENT_TX_1_Init(void);
void   SENT_TX_1_UpdateData(uint8 const data[]);
void   SENT_TX_1_Start(uint8 const data[]);
static  CY_INLINE void SENT_TX_1_Enable(void);
static  CY_INLINE void SENT_TX_1_Stop(void);
static  CY_INLINE uint8 SENT_TX_1_GetStatus(void);
/** @} general */

/** \addtogroup group_power
* @{ */
uint32   SENT_TX_1_Sleep(void);
static void CY_INLINE SENT_TX_1_Wakeup(void);
/** @} power */


/*******************************************************************************
*    Variables with external linkage 
*******************************************************************************/

/** \addtogroup group_globals
@{ */
extern uint8  SENT_TX_1_initVar;
extern uint8 SENT_TX_1_status;
/** @} group_globals */


/*******************************************************************************
* Function Name: SENT_TX_1_Enable
****************************************************************************//**
*
* Enables the PWM that is used in SENT_TX_1 to generate pulses.
*
*******************************************************************************/
static CY_INLINE void SENT_TX_1_Enable(void)
{
    SENT_TX_1_PWM_Enable();
}


/*******************************************************************************
* Function Name: SENT_TX_1_Stop
****************************************************************************//**
*
*  Disables SENT_TX_1.
*
*******************************************************************************/
static CY_INLINE void SENT_TX_1_Stop(void)
{
    SENT_TX_1_PWM_Stop();
}


/*******************************************************************************
* Function Name: SENT_TX_1_GetStatus
****************************************************************************//**
*
* Returns the state of SENT readiness to send new data message.
*
* \return
* Status of readiness to send new data, see \ref group_sent_status.
*
*******************************************************************************/
static CY_INLINE uint8 SENT_TX_1_GetStatus(void)
{
    return (SENT_TX_1_status);
}


/*******************************************************************************
* Function Name: SENT_TX_1_Wakeup
****************************************************************************//**
*
* Restores the user configuration and restores the enable state.
*
*******************************************************************************/
static CY_INLINE void SENT_TX_1_Wakeup(void)
{
    SENT_TX_1_PWM_Wakeup();
}

#endif /* SENT_TX_1_H */


/* [] END OF FILE */
