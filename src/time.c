/*
 * time.c
 *
 *  Created on: 29 Dec 2020
 *      Author: steve
 */
#include "time.h"
#include "common_data.h"

int msec =9;
int sec = 9;
int min = 9;
int hour =9;
int date = 9;        //date
int month = 9;
int year = 99;
int weekday =1;      //day of the week

struct alarm{
  int day;
  int hour: 1;
  int min;
  int sec;
  int msec;
  int alarmMon;
  int alarmTue;
  int alarmWed;
  int alarmThu;
  int alarmFri;
  int alarmSat;
  int alarmSun;

  int addIntervalMsec;
  int addIntervalSec;
  int addIntervalMin;
  int addIntervalHour;
  int addIntervalDay;

} Alarm;
struct alarm alarm1;
struct alarm alarm2;
struct alarm alarm3;
struct alarm alarm4;
struct alarm currentAlarm;

int alarmHour = 0;
int alarmMin = 0;
int alarmSec = 10;
int alarmMsec = 0;
int alarmDay = 1;
int alarmMode = 2;
int addIntervalMsec = 200;
int addIntervalSec = 1;
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

//I2C variabbles
#define I2C_ADDRESS   0x68
uint8_t rtc_reg[7] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06};

//get the time from the RTC
void sync_time()
{
    //variable
    uint8_t buffer[7] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    //change i2c slave address
    g_i2c0.p_api->reset(g_i2c0.p_ctrl);
    g_i2c0.p_api->slaveAddressSet(g_i2c0.p_ctrl, I2C_ADDRESS, I2C_ADDR_MODE_7BIT);

    //set rtc register address
    g_i2c0.p_api->write(g_i2c0.p_ctrl, &rtc_reg[0], 1, true);

    //for loop to read hours, minutes, seconds from RTC
    for(uint8_t i = 0; i<7;i++)
    {
        g_i2c0.p_api->read(g_i2c0.p_ctrl, &buffer[i], 1, false);
        buffer[i] = (uint8_t)(((buffer[i] & 0xF0) >> 4) * 10 + (buffer[i] & 0x0F));
    }

    if(buffer[1] != 0 && buffer[6] != 0){//zorgen dat er niets gescreven wordt bij een communicatiefout
        sec         = buffer[0];
        min         = buffer[1];
        hour        = buffer[2];
        date        = buffer[3];
        weekday     = buffer[4];
        month       = buffer[5];
        year        = buffer[6] +2000;
    }
}

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
                    date = date + 1;
                    weekday = weekday + 1;
                    if(weekday == 8){
                        weekday = 1;
                    }
                    if(month == 2){
                        if((year % 4) == 0 && date == 29){
                            date = 0;
                            month = 3;
                        }
                        else if(date == 28){
                            date = 0;
                            month = 3;
                        }
                    }
                    else if((month == 7 || (month % 2 == 1)) && date == 31){
                        date = 1;
                        month = month + 1;
                    }
                    else if(month % 2 == 0 && date == 30){
                        date = 1;
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
    set_time(sec, min, hour, weekday, date, month, year);
}

void changeYearDown(){
    year = year - 1;
    set_time(sec, min, hour, weekday, date, month, year);
}

void changeMonthUp(){
    month = month + 1;
    if (month == 13){
        month = 0;
    }
    set_time(sec, min, hour, weekday, date, month, year);
}

void changeMonthDown(){
    month = month - 1;
    if (month == 0){
        month = 12;
    }
    set_time(sec, min, hour, weekday, date, month, year);
}

void changeWeekdayUp(){
    weekday = weekday + 1;
    if (weekday == 8){
        weekday = 1;
    }
    set_time(sec, min, hour, weekday, date, month, year);
}

void changeWeekdayDown(){
    weekday = weekday - 1;
    if (weekday == 0){
        weekday = 7;
    }
    set_time(sec, min, hour, weekday, date, month, year);
}

void changeDayUp(){
    date = date + 1;
    if (date == 31){
        date = 1;
    }
    //hier moet ook de uitzondering van schrikkeljaar en 31,30 komen
    set_time(sec, min, hour, weekday, date, month, year);
}

void changeDayDown(){
    date = date - 1;
    if (date == 0){
        date = 31;
    }
  //hier moet ook de uitzondering van schrikkeljaar en 31,30 komen
    set_time(sec, min, hour, weekday, date, month, year);
}

void changeMinUp(){
    min = min + 1;
    if (min == 60){
        min = 0;
    }
    set_time(sec, min, hour, weekday, date, month, year);
}

void changeMinDown(){
    min = min - 1;
    if (min == -1){
        min = 59;
    }
    set_time(sec, min, hour, weekday, date, month, year);
}

void changeHourUp(){
    hour = hour + 1;
    if (hour == 24){
        hour = 0;
    }
    set_time(sec, min, hour, weekday, date, month, year);
}

void changeHourDown(){
    hour = hour - 1;
    if (hour == -1){
        hour = 23;
    }
    set_time(sec, min, hour, weekday, date, month, year);
}

int getYear(){
    return year;
}

int getMonth(){
    return month;
}

int getDate(){
    return date;
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

int getWeekday(){
    return weekday;
}

int checkAlarm(){
   if(hour == currentAlarm.day && min == alarmMin && sec == alarmSec && alarmMsec == msec && alarmActive == 1){
       if(alarmMode == 1){
           if((alarmMon == 1 && weekday == 1)||
               (alarmTue == 1 && weekday == 2)||
               (alarmWed == 1 && weekday == 3)||
               (alarmThu == 1 && weekday == 4)||
               (alarmFri == 1 && weekday == 5)||
               (alarmSat == 1 && weekday == 6)||
               (alarmSun == 1 && weekday == 7)){
               action = 1;
               return action;
           }
       }
       else if(alarmMode == 2){
           if(date == alarmDay){
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

void activatePWM(){
    alarmActive = 1;
    alarmMode = 2;
    alarmMsec = msec + addIntervalMsec;
    if (alarmMsec >= 1000){
        alarmMsec = alarmMsec - 1000;
        alarmSec = alarmSec + 1;
    }
    alarmSec = sec + addIntervalSec;
    if (alarmSec >= 60){
        alarmSec = alarmSec - 60;
        alarmMin = alarmMin + 1;
    }
    alarmMin = min + addIntervalMin;
    if (alarmMin >= 60){
        alarmMin = alarmMin - 60;
        alarmHour = alarmHour + 1;
    }
    alarmHour = hour + addIntervalHour;
    if (alarmHour >= 24){
        alarmHour = alarmHour - 24;
        alarmDay = alarmDay + 1;
    }
    alarmDay = date + addIntervalDay;
    if (alarmDay == 8){
        alarmDay = 1;
    }
}

void deactivatePWM(){
    alarmActive = 0;
}

void setIntervalHourPlus(){
    addIntervalHour=addIntervalHour+1;
    if (addIntervalHour <= 24){
        addIntervalHour = 0;
    }
}

void setIntervalHourMin(){
    if (addIntervalHour >= 0){
        addIntervalHour=addIntervalHour-1;
    }
}

void setIntervalMinPlus(){
    addIntervalMin=addIntervalMin+1;
    if (addIntervalMin <= 60){
        addIntervalMin = 0;
    }
}

void setIntervalMinMin(){
    addIntervalMin=addIntervalMin-1;
    if (addIntervalMin >= 10){
        addIntervalMin=59;
    }
}

void setIntervalSecPlus(){
    addIntervalSec=addIntervalSec+1;
    if (addIntervalSec <= 60){
        addIntervalSec = 0;
    }
}

void setIntervalSecMin(){
    if (addIntervalSec >= 10){
        addIntervalSec=addIntervalSec-1;
    }
}

void setIntervalMsecPlus(){
    addIntervalMsec=addIntervalMsec+10;
    if (addIntervalMsec <= 1000){
        addIntervalMsec=0;
    }
}

void setIntervalMsecMin(){
    if (addIntervalMsec >= 10){
        addIntervalMsec=addIntervalMsec-10;
    }
}

int intervalMsec(){
    return addIntervalMsec;
}

int intervalSec(){
    return addIntervalSec;
}

int intervalMin(){
    return addIntervalMin;
}

int intervalHour(){
    return addIntervalHour;
}

void startAlarm(){
    alarmActive = 1;
    alarmMode = 1;
}

//function to set the current time and save it to RTC
void set_time(s_time_secs, s_time_mins, s_time_hours, s_time_days, s_time_date, s_time_month, s_time_year)
{
    //het moet mogelijk zijn om de tijd vanaf het scherm te veranderen.
    //Om dat voor elkaar te krijgen moet deze functie aangeroepen worden met de correcte parameters.

    uint8_t  rtc_set_time[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    //change i2c slave adress
    g_i2c0.p_api->reset(g_i2c0.p_ctrl);
    g_i2c0.p_api->slaveAddressSet(g_i2c0.p_ctrl, I2C_ADDRESS, I2C_ADDR_MODE_7BIT);


    //set rtc register address
    //g_i2c0.p_api->write(g_i2c0.p_ctrl, &rtc_reg[0], 1, false);

    rtc_set_time[1] = (uint8_t)(((s_time_secs/10) << 4) | (s_time_secs % 10));
    rtc_set_time[2] = (uint8_t)(((s_time_mins/10) << 4) | (s_time_mins % 10));
    rtc_set_time[3] = (uint8_t)(((s_time_hours/10) << 4) | (s_time_hours % 10));

    rtc_set_time[4] = (uint8_t)((s_time_days % 10));
    rtc_set_time[5] = (uint8_t)(((s_time_date/10) << 4) | (s_time_date % 10));
    rtc_set_time[6] = (uint8_t)(((s_time_month/10) << 4) | (s_time_month % 10));   //hier wordt geen rekening gehouden met het century bit maar dat zou niet nodig moeten zijn
    rtc_set_time[7] = (uint8_t)((((s_time_year-2000)/10) << 4) | ((s_time_year-2000) % 10));

    g_i2c0.p_api->write(g_i2c0.p_ctrl, &rtc_set_time[0], 8, false);
}
