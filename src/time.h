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
int checkAlarm2();
void intervalAlarm2();
void activatePWM2();
int checkAlarm3();
void intervalAlarm3();
void activatePWM3();
int checkAlarm4();
void intervalAlarm4();
void activatePWM4();
void deactivatePWM();
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

void stopAlarm1();
void stopAlarm2();
void stopAlarm3();
void stopAlarm4();

int intervalMsec();
int intervalSec();
int intervalMin();
int intervalHour();

void AchangeMinUp();
void AchangeMinDown();
void AchangeHourUp();
void AchangeHourDown();
void SetWeekday();
int getweekday();
int AgetHour();
int AgetMin();
int Aactive();
void readauto();
void saveauto();
void AutoStartW();
int AutostartR();

//I2C stuff
void sync_time();
void set_time(int,int,int,int,int,int,int);

void savealarm(int);
void savepwm(int);
void alarmpwm1read();
void alarmpwm2read();
void alarmpwm3read();
void alarmpwm4read();


#endif /* TIME_H_ */
