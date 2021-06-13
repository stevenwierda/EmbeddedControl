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
 * UART_Framework_MG.h
 * Header files for functions written in UART_FRAMEWORK_MG.c
 */

#ifndef UART_FRAMEWORK_MG_H_
#define UART_FRAMEWORK_MG_H_
#define SEMI_HOSTING
#include "main_thread.h"

ssp_err_t sf_comms0_close(void);
ssp_err_t sf_comms0_lock(sf_comms_lock_t  lock_type,UINT   timeout);
ssp_err_t sf_comms0_open(void);
ssp_err_t sf_comms0_read(uint8_t  * const p_dest,uint32_t const bytes,UINT    const timeout);
ssp_err_t sf_comms0_unlock(sf_comms_lock_t    lock_type);
ssp_err_t sf_comms0_versionGet(ssp_version_t  * const p_version);
ssp_err_t sf_comms0_write(uint8_t  const * const p_src,uint32_t   const bytes,UINT    const timeout);

#endif
