/*
 * time.c
 *
 *  Created on: 29 Dec 2020
 *      Author: steve
 */
#include "time.h"
#include "common_data.h"

int msec = 0;
int sec = 0;
int min = 0;
int hour = 0;
int day = 1;
int month = 1;
int year = 2020;
int daynr = 2;

int alarmHour = 0;
int alarmMin = 0;
int alarmSec = 10;
int alarmMsec = 0;
int alarmDay = 1;
int alarmMode = 2;
int addIntervalMsec = 100;
int addIntervalSec = 0;
int addIntervalMin  = 0;
int addIntervalHour = 0;
int addIntervalDay = 0;
int alarmMon = 0;
int alarmTue = 0;
int alarmWed = 0;
int alarmThu = 0;
int alarmFri = 0;
int alarmSat = 0;
int alarmSun = 0;
int alarmActive = 0;
int action = 0;


void addMs(){
    msec = msec + 1;
    if(msec >= 1000){
        msec = msec - 1000;
        sec = sec + 1;
        if(sec >= 60){
            sec = sec - 60;
            min = min + 1;
            if(min >= 60){
                min = min - 60;
                hour = hour + 1;
                if(hour >= 24){
                    hour = hour - 24;
                    day = day + 1;
                    daynr = daynr + 1;
                    if(daynr == 8){
                        daynr = 1;
                    }
                    if(month == 2){
                        if((year % 4) == 0 && day == 29){
                            day = 0;
                            month = 3;
                        }
                        else if(day == 28){
                            day = 0;
                            month = 3;
                        }
                    }
                    else if((month == 7 || (month % 2 == 1)) && day == 31){
                        day = 1;
                        month = month + 1;
                    }
                    else if(month % 2 == 0 && day == 30){
                        day = 1;
                        month = month + 1;
                    }
                    if(month == 13){
                        month = 1;
                        year = year + 1;
                    }
                }
            }
        }
    }
}
void changeYearUp(){
    year = year + 1;

}

void changeYearDown(){
    year = year - 1;
}

void changeMonthUp(){
    month = month + 1;
    if (month == 13){
        month = 0;
    }
}

void changeMonthDown(){
    month = month - 1;
    if (month == 0){
        month = 12;
    }
}

void changeDaynrUp(){
    daynr = daynr + 1;
    if (daynr == 8){
        daynr = 1;
    }
}

void changeDaynrDown(){
    daynr = daynr - 1;
    if (daynr == 0){
        daynr = 7;
    }
}

void changeDayUp(){
    day = day + 1;
    if (day == 8){
        day = 1;
    }
}

void changeDayDown(){
    day = day - 1;
    if (day == 0){
        day = 7;
    }
}

void changeMinUp(){
    min = min + 1;
    if (min == 60){
        min = 0;
    }
}

void changeMinDown(){
    min = min - 1;
    if (min == -1){
        min = 59;
    }
}

void changeHourUp(){
    hour = hour + 1;
    if (hour == 24){
        hour = 0;
    }
}

void changeHourDown(){
    hour = hour - 1;
    if (hour == -1){
        hour = 23;
    }
}

int getYear(){
    return year;
}

int getMonth(){
    return month;
}

int getDay(){
    return day;
}

int getHour(){
    return hour;
}

int getMin(){
    return min;
}

int getSec(){
    return sec;
}

int getMsec(){
    return msec;
}

int getDaynr(){
    return daynr;
}

int checkAlarm(){
   if(hour == alarmHour && min == alarmMin && sec == alarmSec && alarmMsec == msec && alarmActive == 1){
       if(alarmMode == 1){
           if((alarmMon == 1 && daynr == 1)||
               (alarmTue == 1 && daynr == 2)||
               (alarmWed == 1 && daynr == 3)||
               (alarmThu == 1 && daynr == 4)||
               (alarmFri == 1 && daynr == 5)||
               (alarmSat == 1 && daynr == 6)||
               (alarmSun == 1 && daynr == 7)){
               action = 1;
               return action;
           }
       }
       else if(alarmMode == 2){
           if(day == alarmDay){
               if (action == 0){
                   action = 1;
               }
               else{
                   action = 0;
               }
               intervalAlarm();
               return action;
           }
       }
   }
   return 3;
}

void intervalAlarm(){
    alarmMsec = alarmMsec + addIntervalMsec;
    if (alarmMsec >= 1000){
        alarmMsec = alarmMsec - 1000;
        alarmSec = alarmSec + 1;
    }
    alarmSec = alarmSec + addIntervalSec;
    if (alarmSec >= 60){
        alarmSec = alarmSec - 60;
        alarmMin = alarmMin + 1;
    }
    alarmMin = alarmMin + addIntervalMin;
    if (alarmMin >= 60){
        alarmMin = alarmMin - 60;
        alarmHour = alarmHour + 1;
    }
    alarmHour = alarmHour + addIntervalHour;
    if (alarmHour >= 24){
        alarmHour = alarmHour - 24;
        alarmDay = alarmDay + 1;
    }
    alarmDay = alarmDay + addIntervalDay;
    if (alarmDay == 8){
        alarmDay = 1;
    }
}

