/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
* other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
* EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
* SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS
* SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
* this software. By using this software, you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2017 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/



/**
 * UART_FRAMEWORK_MG.c
 * Functions to open, start, configure, write to and read from, and close UART Framework.
 *  Quick tips to customize this example:
 *  1) Configure the timeout setting of the UART Framework
 */

#include <stdio.h>
#include <UART_Framework_MG.h>

/**
 * Close the UART Framework.
 **/
ssp_err_t sf_comms0_close(void)
{
    ssp_err_t err = g_sf_comms0.p_api->close(g_sf_comms0.p_ctrl);
    
    if (SSP_SUCCESS != err)
    {
#ifdef SEMI_HOSTING
		if (CoreDebug->DHCSR & CoreDebug_DHCSR_C_DEBUGEN_Msk)
		{
			//Debugger is connected
			//printf("g_sf_comms0.p_api->close failed - error = 0x%x\r\n", err);
		}
#endif
		while(1)
		{
		}
    }
    
    return err;
}

/**
 * Lock the communications driver. Reserve exclusive access to the communications driver.
 * lock_type    - Locking type
 * 						- Transmission
 * 						- Reception
 * 						- Transmission and Reception
 * timeout      - ThreadX timeout. Options include TX_NO_WAIT (0x00000000), TX_WAIT_FOREVER (0xFFFFFFFF),
 *                and timeout value (0x00000001 through 0xFFFFFFFE) in ThreadX tick counts.
 **/
ssp_err_t sf_comms0_lock(sf_comms_lock_t  lock_type, UINT   timeout)
{
    ssp_err_t err = g_sf_comms0.p_api->lock(g_sf_comms0.p_ctrl,lock_type,timeout);
    
   if (SSP_SUCCESS != err)
   {
#ifdef SEMI_HOSTING
		if (CoreDebug->DHCSR & CoreDebug_DHCSR_C_DEBUGEN_Msk)
		{
			//Debugger is connected
			//printf("g_sf_comms0.p_api->lock failed - error = 0x%x\r\n", err);
		}
#endif
		while(1)
		{
		}
   }
   
   return err;
}

/**
 *  Open UART Framework 0.
 **/
ssp_err_t sf_comms0_open(void)
{
   ssp_err_t err = g_sf_comms0.p_api->open(g_sf_comms0.p_ctrl, g_sf_comms0.p_cfg);
   
   if (SSP_SUCCESS != err)
   {
#ifdef SEMI_HOSTING
		if (CoreDebug->DHCSR & CoreDebug_DHCSR_C_DEBUGEN_Msk)
		{
			//Debugger is connected
			//printf("g_sf_comms0.p_api->open failed - error = 0x%x\r\n", err);
		}
#endif
		while(1)
		{
		}
   }
   
   return err;
}

/**
 * Use UART Comms Framework 0 to read data from communications driver.  This call will return after the number of bytes requested is read or if
 * a timeout occurs while waiting for access to the driver.
 * p_dest       - Destination address where read data is stored
 * bytes        - Read data length
 * timeout      - ThreadX timeout. Options include TX_NO_WAIT (0x00000000), TX_WAIT_FOREVER (0xFFFFFFFF),
 *                and timeout value (0x00000001 through 0xFFFFFFFE) in ThreadX tick counts.
 **/
ssp_err_t sf_comms0_read(uint8_t  * const p_dest, uint32_t const bytes, UINT const timeout)
{
   ssp_err_t err = g_sf_comms0.p_api->read(g_sf_comms0.p_ctrl, p_dest, bytes, timeout);
   
   if (SSP_SUCCESS != err)
   {
#ifdef SEMI_HOSTING
		if (CoreDebug->DHCSR & CoreDebug_DHCSR_C_DEBUGEN_Msk)
		{
			//Debugger is connected
			//printf("g_sf_comms0.p_api->read failed - error = 0x%x\r\n", err);
		}
#endif
		while(1)
		{
		}
   }
   
   return err;
}

/**
 *  Unlock the communications driver. Release exclusive access to the communications driver.
 * lock_type    - Locking type
 * 						- Transmission
 * 						- Reception
 * 						- Transmission and Reception
 **/
ssp_err_t sf_comms0_unlock(sf_comms_lock_t    lock_type)
{
   ssp_err_t err = g_sf_comms0.p_api->unlock(g_sf_comms0.p_ctrl,lock_type);
   
   if (SSP_SUCCESS != err)
   {
#ifdef SEMI_HOSTING
		if (CoreDebug->DHCSR & CoreDebug_DHCSR_C_DEBUGEN_Msk)
		{
			//Debugger is connected
			//printf("g_sf_comms0.p_api->unlock failed - error = 0x%x\r\n", err);
		}
#endif
		while(1)
		{
		}
   }
   
   return err;
}

/**
 * Store the driver version in the provided pointer, p_version.
 * p_version     - Pointer to store driver version.
 **/
ssp_err_t sf_comms0_versionGet(ssp_version_t  * const p_version)
{
    ssp_err_t err = g_sf_comms0.p_api->versionGet(p_version);
    
   if (SSP_SUCCESS != err)
   {
#ifdef SEMI_HOSTING
		if (CoreDebug->DHCSR & CoreDebug_DHCSR_C_DEBUGEN_Msk)
		{
			//Debugger is connected
			//printf("g_sf_comms0.p_api->versionGet failed - error = 0x%x\r\n", err);
		}
#endif
		while(1)
		{
		}
   }
   
   return err;
}

/**
 *  Write data to communications driver using UART COMMS Framework 0.  This call will return after all bytes are written or if a timeout occurs
 *  while waiting for access to the driver.
 *  p_src        - Source address to read data out from
 *  bytes        - Write data length
 *  timeout      - ThreadX timeout. Options include TX_NO_WAIT (0x00000000), TX_WAIT_FOREVER (0xFFFFFFFF),
 *                 and timeout value (0x00000001 through 0xFFFFFFFE) in ThreadX tick counts.
 **/
ssp_err_t sf_comms0_write(uint8_t  const * const p_src, uint32_t   const bytes, UINT    const timeout)
{
   ssp_err_t err = g_sf_comms0.p_api->write(g_sf_comms0.p_ctrl, p_src, bytes, timeout);
   
   if (SSP_SUCCESS != err)
   {
#ifdef SEMI_HOSTING
		if (CoreDebug->DHCSR & CoreDebug_DHCSR_C_DEBUGEN_Msk)
		{
			//Debugger is connected
			//printf("g_sf_comms0.p_api->write failed - error = 0x%x\r\n", err);
		}
#endif
		while(1)
		{
		}
   }
   
   return err;
}

