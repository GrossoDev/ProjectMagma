#ifndef __TIME_H
#define __TIME_H

#include <stdtypes.h>

/* TIMER.C */
extern void timer_waitticks(int ticks);
extern void timer_install  (void);

extern float timer_ticktosec  (int ticks);
extern float timer_ticktomilli(int ticks);
extern int   timer_sectoticks (int secs);
extern int   timer_millitotick(int milli);

extern volatile unsigned timer_ticks;

/* RTC.C */
extern int rtc_get_utcsecond(void);
extern int rtc_get_utcminute(void);
extern int rtc_get_utchour  (void);
extern int rtc_get_utcday   (void);
extern int rtc_get_utcmonth (void);
extern int rtc_get_utcyear  (void);

#endif