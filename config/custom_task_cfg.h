/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of Quectel Co., Ltd. 2013
*
*****************************************************************************/
/*****************************************************************************
 *
 * Filename:
 * ---------
 *   custom_task_cfg.h
 *
 * Project:
 * --------
 *   OpenCPU
 *
 * Description:
 * ------------
 *   The file intends for multi tasks definition of OpenCPU application. 
 *
 * Author:
 * -------
 * -------
 *
 *============================================================================
 *             HISTORY
 *----------------------------------------------------------------------------
 * 
 ****************************************************************************/

/**
 ******* TAST CONFIG START ********
 *----------------------------------
 * Task Id Name:
 *    Task id name is a totally customized name. Developer just define the name, and the system
 *    will automatically define and assign value.
 *
 * Task Stack Size:
 *    The stack size of task. Range from 1K to 10K.
 *    If there are any file operations to do in task, the stack size of this task
 *    must be set to at least 5K. Or, stack overflow probably happens.
 *
 * Default Value1(2):
 *    Developer doesn't have to specify the value, just use the default definition.
 */

/*----------------------------------------------------------------------------------------------------
 |        Task Entry Function | Task Id Name   | Task Stack Size (Bytes) | Default Value1 | Default Value2 |
 *----------------------------------------------------------------------------------------------------*/
TASK_ITEM(proc_main_task,       main_task_id,   10*1024, DEFAULT_VALUE1, DEFAULT_VALUE2)
TASK_ITEM(proc_reserved1,       reserved1_id,   5*1024, DEFAULT_VALUE1, DEFAULT_VALUE2)
TASK_ITEM(proc_reserved2,       reserved2_id,   5*1024, DEFAULT_VALUE1, DEFAULT_VALUE2)


/********* TAST CONFIG END *********/
