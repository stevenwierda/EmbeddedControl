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

#endif /* TIME_H_ */
