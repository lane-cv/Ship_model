/* time.h: ANSI 'C' (X3J11 Oct 88) library header, section 4.12 */
/* Copyright (C) Codemist Ltd., 1988-1993.                      */
/* Copyright 1991-1993 ARM Limited. All rights reserved.        */
/* version 0.03 */

/*
 * time.h declares two macros, four types and several functions for
 * manipulating time. Many functions deal with a calendar time that
 * represents the current date (according to the Gregorian
 * calendar) and time. Some functions deal with local time, which
 * is the calendar time expressed for some specific time zone, and
 * with Daylight Savings Time, which is a temporary change in the
 * algorithm for determining local time.
 */

/*
 * RCS $Revision: 185525 $
 * Checkin $Date: 2014-05-29 12:44:48 +0100 (Thu, 29 May 2014) $
 * Revising $Author: drodgman $
 */

#ifndef __TIME_h
#define __TIME_h
#include "stm32f10x.h"


void TIM3_CH1_PWM_Init(u16 arr,u16 psc);
void TIM4_CH1_PWM_Init(u16 arr,u16 psc);
void Left(void);
void MidLeft(void);
void Right(void);
void MidRight(void);
void Mid(void);
void MainDGo(void);
void MainCGo(void);
void MainBGo(void);
void MainAGo(void);
void MainStop(void);
void MainDBack(void);
void MainCBack(void);
void MainBBack(void);
void MainABack(void);

#endif

/* end of time.h */

