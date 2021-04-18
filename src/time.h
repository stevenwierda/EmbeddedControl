/*
 * time.h
 *
 *  Created on: 29 Dec 2020
 *      Author: steven hello
 */

#ifndef TIME_H_
#define TIME_H_
#include <stdbool.h>
#include <bsp_api.h>
#include "main_thread.h"

void addMs();
void changeYearUp();
void changeYearDown();
void changeMonthUp();
void changeMonthDown();
void changeDayUp();
void changeDayDown();
void changeWeekdayUp();
void changeWeekdayDown();
void changeHourUp();
void changeHourDown();
void changeMinUp();
void changeMinDown();
void changeSecUp();
void changeSecDown();
void changeMsecUp();
void changeMsecDown();

int getYear();
int getMonth();
int getDate();
int getHour();
int getMin();
int getSec();
int getMsec();
int getWeekday();

int checkAlarm1();
void intervalAlarm1();
void activatePWM1();
void deactivate1PWM();
int checkAlarm2();
void intervalAlarm2();
void activatePWM2();
void deactivate2PWM();
int checkAlarm3();
void intervalAlarm3();
void activatePWM3();
void deactivate3PWM();
int checkAlarm4();
void intervalAlarm4();
void activatePWM4();
void deactivate4PWM();
//void setIntervalMsecMin();

void setIntervalHourPlus();
void setIntervalHourMin();
void setIntervalMinPlus();
void setIntervalMinMin();
void setIntervalSecPlus();
void setIntervalSecMin();
void setIntervalMsecPlus();
void setIntervalMsecMin();
void startAlarm();

void setAlarmsel(int);
int getAlarm();

void startAlarm1();
void startAlarm2();
void startAlarm3();
void startAlarm4();

int intervalMsec();
int intervalSec();
int intervalMin();
int intervalHour();

//I2C stuff
void sync_time();
void set_time(int,int,int,int,int,int,int);


#endif /* TIME_H_ */
