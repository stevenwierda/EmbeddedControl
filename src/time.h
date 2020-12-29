/*
 * time.h
 *
 *  Created on: 29 Dec 2020
 *      Author: steve
 */

#ifndef TIME_H_
#define TIME_H_
extern int msec;
extern int sec;
extern int min;
extern int hour;
extern int day;
extern int month;
extern int year;
extern int daynr;

void addHunderdms();
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
int gethour();
int getMin();
int getSec();
int getMsec();
int getDaynr();

#endif /* TIME_H_ */
