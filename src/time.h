/*
 * time.h
 *
 *  Created on: 29 Dec 2020
 *      Author: steve
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
void changeDaynrUp();
void changeDaynrDown();
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
int getDay();
int getHour();
int getMin();
int getSec();
int getMsec();
int getDaynr();

int checkAlarm();
void intervalAlarm();
void activatePWM();
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

int intervalMsec();
int intervalSec();
int intervalMin();
int intervalHour();

//I2C stuff
void sync_time();
void set_time(int,int,int,int,int,int,int);

#endif /* TIME_H_ */
