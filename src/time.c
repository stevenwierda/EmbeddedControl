/*
 * time.c
 *
 *  Created on: 29 Dec 2020
 *      Author: steve
 */
#include "time.h"
#include "common_data.h"

int msec         =0;
int sec         = 0;
int min         = 0;
int hour        = 0;
int date        = 0;        //date
int month       = 0;
int year        = 0;
int weekday     = 0;      //day of the week

int alarm1Hour = 0;
int alarm1Min = 0;
int alarm1Sec = 10;
int alarm1Msec = 0;
int alarm1Day = 1;
int alarm1Mode = 2;
int addInterval1Msec = 200;
int addInterval1Sec = 1;
int addInterval1Min  = 0;
int addInterval1Hour = 0;
int addInterval1Day = 0;
int alarm1Mon = 0;
int alarm1Tue = 0;
int alarm1Wed = 0;
int alarm1Thu = 0;
int alarm1Fri = 0;
int alarm1Sat = 0;
int alarm1Sun = 0;
int alarm1Active = 0;
int action = 0;

int alarm2Hour = 0;
int alarm2Min = 0;
int alarm2Sec = 10;
int alarm2Msec = 0;
int alarm2Day = 1;
int alarm2Mode = 2;
int addInterval2Msec = 200;
int addInterval2Sec = 1;
int addInterval2Min  = 0;
int addInterval2Hour = 0;
int addInterval2Day = 0;
int alarm2Mon = 0;
int alarm2Tue = 0;
int alarm2Wed = 0;
int alarm2Thu = 0;
int alarm2Fri = 0;
int alarm2Sat = 0;
int alarm2Sun = 0;
int alarm2Active = 0;

int alarm3Hour = 0;
int alarm3Min = 0;
int alarm3Sec = 10;
int alarm3Msec = 0;
int alarm3Day = 1;
int alarm3Mode = 2;
int addInterval3Msec = 200;
int addInterval3Sec = 1;
int addInterval3Min  = 0;
int addInterval3Hour = 0;
int addInterval3Day = 0;
int alarm3Mon = 0;
int alarm3Tue = 0;
int alarm3Wed = 0;
int alarm3Thu = 0;
int alarm3Fri = 0;
int alarm3Sat = 0;
int alarm3Sun = 0;
int alarm3Active = 0;

int alarm4Hour = 0;
int alarm4Min = 0;
int alarm4Sec = 10;
int alarm4Msec = 0;
int alarm4Day = 1;
int alarm4Mode = 2;
int addInterval4Msec = 200;
int addInterval4Sec = 1;
int addInterval4Min  = 0;
int addInterval4Hour = 0;
int addInterval4Day = 0;
int alarm4Mon = 0;
int alarm4Tue = 0;
int alarm4Wed = 0;
int alarm4Thu = 0;
int alarm4Fri = 0;
int alarm4Sat = 0;
int alarm4Sun = 0;
int alarm4Active = 0;

int CurrentAlarm = 1;

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
        weekday     = buffer[3];
        date        = buffer[4];
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
   //all exceptions when changing the date
   if(month == 2){
       if((year % 4) == 0 && date == 30){
           date = 1;
           month = 3;
       }
       else if((year % 4) != 0 && date == 29){
           date = 1;
           month = 3;
       }
   }
   else if((month == 7 || (month % 2 == 1)) && date == 32){
       date = 1;
       month = month + 1;
   }
   else if(month % 2 == 0 && date == 31){
       date = 1;
       month = month + 1;
   }
    set_time(sec, min, hour, weekday, date, month, year);
}

void changeDayDown(){
   date = date - 1;
   //all exceptions when changing the date
   if(month == 3){
       if((year % 4) == 0 && date == 0){
           date = 29;
           month = 2;
       }
       else if(date == 0){
           date = 29;
           month = 2;
       }
   }
   else if((month == 7 || (month % 2 == 1)) && date == 0){
       date = 30;
       month = month - 1;
   }
   else if(month % 2 == 0 && date == 0){
       date = 31;
       month = month - 1;
   }
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

int checkAlarm1(){
   if(hour == alarm1Hour && min == alarm1Min && sec == alarm1Sec && alarm1Msec == msec && alarm1Active == 1){
       if(alarm1Mode == 1){
           if((alarm1Mon == 1 && weekday == 1)||
               (alarm1Tue == 1 && weekday == 2)||
               (alarm1Wed == 1 && weekday == 3)||
               (alarm1Thu == 1 && weekday == 4)||
               (alarm1Fri == 1 && weekday == 5)||
               (alarm1Sat == 1 && weekday == 6)||
               (alarm1Sun == 1 && weekday == 7)){
               action = 1;
               return action;
           }
       }
       else if(alarm1Mode == 2){
           if(date == alarm1Day){
               if (action == 0){
                   action = 1;
               }
               else{
                   action = 0;
               }
               intervalAlarm1();
               return action;
           }
       }
   }
   return 3;
}

int checkAlarm2(){
   if(hour == alarm2Hour && min == alarm2Min && sec == alarm2Sec && alarm2Msec == msec && alarm2Active == 1){
       if(alarm2Mode == 1){
           if((alarm2Mon == 1 && weekday == 1)||
               (alarm2Tue == 1 && weekday == 2)||
               (alarm2Wed == 1 && weekday == 3)||
               (alarm2Thu == 1 && weekday == 4)||
               (alarm2Fri == 1 && weekday == 5)||
               (alarm2Sat == 1 && weekday == 6)||
               (alarm2Sun == 1 && weekday == 7)){
               action = 1;
               return action;
           }
       }
       else if(alarm2Mode == 2){
           if(date == alarm2Day){
               if (action == 0){
                   action = 1;
               }
               else{
                   action = 0;
               }
               intervalAlarm2();
               return action;
           }
       }
   }
   return 3;
}

int checkAlarm3(){
   if(hour == alarm3Hour && min == alarm3Min && sec == alarm3Sec && alarm3Msec == msec && alarm3Active == 1){
       if(alarm3Mode == 1){
           if((alarm3Mon == 1 && weekday == 1)||
               (alarm3Tue == 1 && weekday == 2)||
               (alarm3Wed == 1 && weekday == 3)||
               (alarm3Thu == 1 && weekday == 4)||
               (alarm3Fri == 1 && weekday == 5)||
               (alarm3Sat == 1 && weekday == 6)||
               (alarm3Sun == 1 && weekday == 7)){
               action = 1;
               return action;
           }
       }
       else if(alarm3Mode == 2){
           if(date == alarm3Day){
               if (action == 0){
                   action = 1;
               }
               else{
                   action = 0;
               }
               intervalAlarm3();
               return action;
           }
       }
   }
   return 3;
}

int checkAlarm4(){
   if(hour == alarm4Hour && min == alarm4Min && sec == alarm4Sec && alarm4Msec == msec && alarm4Active == 1){
       if(alarm4Mode == 1){
           if((alarm4Mon == 1 && weekday == 1)||
               (alarm4Tue == 1 && weekday == 2)||
               (alarm4Wed == 1 && weekday == 3)||
               (alarm4Thu == 1 && weekday == 4)||
               (alarm4Fri == 1 && weekday == 5)||
               (alarm4Sat == 1 && weekday == 6)||
               (alarm4Sun == 1 && weekday == 7)){
               action = 1;
               return action;
           }
       }
       else if(alarm1Mode == 2){
           if(date == alarm1Day){
               if (action == 0){
                   action = 1;
               }
               else{
                   action = 0;
               }
               intervalAlarm4();
               return action;
           }
       }
   }
   return 3;
}

void intervalAlarm1(){
    alarm1Msec = alarm1Msec + addInterval1Msec;
    if (alarm1Msec >= 1000){
        alarm1Msec = alarm1Msec - 1000;
        alarm1Sec = alarm1Sec + 1;
    }
    alarm1Sec = alarm1Sec + addInterval1Sec;
    if (alarm1Sec >= 60){
        alarm1Sec = alarm1Sec - 60;
        alarm1Min = alarm1Min + 1;
    }
    alarm1Min = alarm1Min + addInterval1Min;
    if (alarm1Min >= 60){
        alarm1Min = alarm1Min - 60;
        alarm1Hour = alarm1Hour + 1;
    }
    alarm1Hour = alarm1Hour + addInterval1Hour;
    if (alarm1Hour >= 24){
        alarm1Hour = alarm1Hour - 24;
        alarm1Day = alarm1Day + 1;
    }
    alarm1Day = alarm1Day + addInterval1Day;
    if (alarm1Day == 8){
        alarm1Day = 1;
    }
}

void intervalAlarm2(){
    alarm2Msec = alarm2Msec + addInterval2Msec;
    if (alarm2Msec >= 1000){
        alarm2Msec = alarm2Msec - 1000;
        alarm2Sec = alarm2Sec + 1;
    }
    alarm2Sec = alarm2Sec + addInterval2Sec;
    if (alarm2Sec >= 60){
        alarm2Sec = alarm2Sec - 60;
        alarm2Min = alarm2Min + 1;
    }
    alarm2Min = alarm2Min + addInterval2Min;
    if (alarm2Min >= 60){
        alarm2Min = alarm2Min - 60;
        alarm2Hour = alarm2Hour + 1;
    }
    alarm2Hour = alarm2Hour + addInterval2Hour;
    if (alarm2Hour >= 24){
        alarm2Hour = alarm2Hour - 24;
        alarm2Day = alarm2Day + 1;
    }
    alarm2Day = alarm2Day + addInterval2Day;
    if (alarm2Day == 8){
        alarm2Day = 1;
    }
}

void intervalAlarm3(){
    alarm3Msec = alarm2Msec + addInterval3Msec;
    if (alarm3Msec >= 1000){
        alarm3Msec = alarm3Msec - 1000;
        alarm3Sec = alarm3Sec + 1;
    }
    alarm3Sec = alarm3Sec + addInterval3Sec;
    if (alarm3Sec >= 60){
        alarm3Sec = alarm3Sec - 60;
        alarm3Min = alarm3Min + 1;
    }
    alarm3Min = alarm3Min + addInterval3Min;
    if (alarm3Min >= 60){
        alarm3Min = alarm3Min - 60;
        alarm3Hour = alarm3Hour + 1;
    }
    alarm3Hour = alarm3Hour + addInterval3Hour;
    if (alarm3Hour >= 24){
        alarm3Hour = alarm3Hour - 24;
        alarm3Day = alarm3Day + 1;
    }
    alarm3Day = alarm3Day + addInterval3Day;
    if (alarm3Day == 8){
        alarm3Day = 1;
    }
}

void intervalAlarm4(){
    alarm4Msec = alarm4Msec + addInterval4Msec;
    if (alarm4Msec >= 1000){
        alarm4Msec = alarm4Msec - 1000;
        alarm4Sec = alarm4Sec + 1;
    }
    alarm4Sec = alarm4Sec + addInterval4Sec;
    if (alarm4Sec >= 60){
        alarm4Sec = alarm4Sec - 60;
        alarm4Min = alarm4Min + 1;
    }
    alarm4Min = alarm4Min + addInterval4Min;
    if (alarm4Min >= 60){
        alarm4Min = alarm4Min - 60;
        alarm4Hour = alarm4Hour + 1;
    }
    alarm4Hour = alarm4Hour + addInterval4Hour;
    if (alarm4Hour >= 24){
        alarm4Hour = alarm4Hour - 24;
        alarm4Day = alarm4Day + 1;
    }
    alarm4Day = alarm4Day + addInterval4Day;
    if (alarm4Day == 8){
        alarm4Day = 1;
    }
}


void activatePWM1(){
    alarm1Active = 1;
    alarm1Mode = 2;
    alarm1Msec = msec + addInterval1Msec;
    if (alarm1Msec >= 1000){
        alarm1Msec = alarm1Msec - 1000;
        alarm1Sec = alarm1Sec + 1;
    }
    alarm1Sec = sec + addInterval1Sec;
    if (alarm1Sec >= 60){
        alarm1Sec = alarm1Sec - 60;
        alarm1Min = alarm1Min + 1;
    }
    alarm1Min = min + addInterval1Min;
    if (alarm1Min >= 60){
        alarm1Min = alarm1Min - 60;
        alarm1Hour = alarm1Hour + 1;
    }
    alarm1Hour = hour + addInterval1Hour;
    if (alarm1Hour >= 24){
        alarm1Hour = alarm1Hour - 24;
        alarm1Day = alarm1Day + 1;
    }
    alarm1Day = date + addInterval1Day;
    if (alarm1Day == 8){
        alarm1Day = 1;
    }
}

void activatePWM2(){
    alarm2Active = 1;
    alarm2Mode = 2;
    alarm2Msec = msec + addInterval2Msec;
    if (alarm2Msec >= 1000){
        alarm2Msec = alarm2Msec - 1000;
        alarm2Sec = alarm2Sec + 1;
    }
    alarm2Sec = sec + addInterval2Sec;
    if (alarm2Sec >= 60){
        alarm2Sec = alarm2Sec - 60;
        alarm2Min = alarm2Min + 1;
    }
    alarm1Min = min + addInterval2Min;
    if (alarm2Min >= 60){
        alarm2Min = alarm2Min - 60;
        alarm2Hour = alarm2Hour + 1;
    }
    alarm2Hour = hour + addInterval2Hour;
    if (alarm2Hour >= 24){
        alarm2Hour = alarm2Hour - 24;
        alarm2Day = alarm2Day + 1;
    }
    alarm2Day = date + addInterval2Day;
    if (alarm2Day == 8){
        alarm2Day = 1;
    }
}

void activatePWM3(){
    alarm3Active = 1;
    alarm3Mode = 2;
    alarm3Msec = msec + addInterval3Msec;
    if (alarm3Msec >= 1000){
        alarm3Msec = alarm3Msec - 1000;
        alarm3Sec = alarm3Sec + 1;
    }
    alarm3Sec = sec + addInterval3Sec;
    if (alarm3Sec >= 60){
        alarm3Sec = alarm3Sec - 60;
        alarm3Min = alarm3Min + 1;
    }
    alarm3Min = min + addInterval3Min;
    if (alarm3Min >= 60){
        alarm3Min = alarm3Min - 60;
        alarm3Hour = alarm3Hour + 1;
    }
    alarm3Hour = hour + addInterval3Hour;
    if (alarm3Hour >= 24){
        alarm3Hour = alarm3Hour - 24;
        alarm3Day = alarm1Day + 1;
    }
    alarm3Day = date + addInterval3Day;
    if (alarm3Day == 8){
        alarm3Day = 1;
    }
}

void activatePWM4(){
    alarm4Active = 1;
    alarm4Mode = 2;
    alarm4Msec = msec + addInterval4Msec;
    if (alarm4Msec >= 1000){
        alarm4Msec = alarm4Msec - 1000;
        alarm4Sec = alarm4Sec + 1;
    }
    alarm4Sec = sec + addInterval4Sec;
    if (alarm4Sec >= 60){
        alarm4Sec = alarm4Sec - 60;
        alarm4Min = alarm4Min + 1;
    }
    alarm4Min = min + addInterval4Min;
    if (alarm4Min >= 60){
        alarm4Min = alarm4Min - 60;
        alarm4Hour = alarm4Hour + 1;
    }
    alarm4Hour = hour + addInterval4Hour;
    if (alarm4Hour >= 24){
        alarm4Hour = alarm4Hour - 24;
        alarm4Day = alarm4Day + 1;
    }
    alarm4Day = date + addInterval4Day;
    if (alarm4Day == 8){
        alarm4Day = 1;
    }
}

void deactivatePWM(){
    if (CurrentAlarm == 1){
        alarm1Active = 0;
    }else if(CurrentAlarm == 2){
        alarm2Active = 0;
    }else if(CurrentAlarm == 3){
        alarm3Active = 0;
    }else if(CurrentAlarm == 4){
        alarm4Active = 0;
    }
}

void setIntervalHourPlus(){
    if (CurrentAlarm == 1){
        addInterval1Hour=addInterval1Hour+1;
        if (addInterval1Hour >= 24){
            addInterval1Hour = 0;
        }
    }else if(CurrentAlarm == 2){
        addInterval2Hour=addInterval2Hour+1;
        if (addInterval2Hour >= 24){
            addInterval2Hour = 0;
        }
    }else if(CurrentAlarm == 3){
        addInterval3Hour=addInterval3Hour+1;
        if (addInterval3Hour >= 24){
            addInterval3Hour = 0;
        }
    }else if(CurrentAlarm == 4){
        addInterval4Hour=addInterval4Hour+1;
        if (addInterval4Hour >= 24){
            addInterval4Hour = 0;
        }
    }
}

void setIntervalHourMin(){
    if (CurrentAlarm == 1){
        if (addInterval1Hour >= 0){
            addInterval1Hour=addInterval1Hour-1;
        }
    }else if(CurrentAlarm == 2){
        if (addInterval2Hour >= 0){
            addInterval2Hour=addInterval2Hour-1;
        }
    }else if(CurrentAlarm == 3){
        if (addInterval3Hour >= 0){
            addInterval3Hour=addInterval3Hour-1;
        }
    }else if(CurrentAlarm == 4){
        if (addInterval4Hour >= 0){
            addInterval4Hour=addInterval4Hour-1;
        }
    }
}

void setIntervalMinPlus(){
    if (CurrentAlarm == 1){
        addInterval1Min=addInterval1Min+1;
        if (addInterval1Min >= 60){
            addInterval1Min = 0;
        }
    }else if(CurrentAlarm == 2){
        addInterval2Min=addInterval2Min+1;
        if (addInterval2Min >= 60){
            addInterval2Min = 0;
        }
    }else if(CurrentAlarm == 3){
        addInterval3Min=addInterval3Min+1;
        if (addInterval3Min >= 60){
            addInterval3Min = 0;
        }
    }else if(CurrentAlarm == 4){
        addInterval4Min=addInterval4Min+1;
        if (addInterval4Min >= 60){
            addInterval4Min = 0;
        }
    }
}

void setIntervalMinMin(){
    if (CurrentAlarm == 1){
        addInterval1Min=addInterval1Min-1;
        if (addInterval1Min >= 10){
            addInterval1Min=59;
        }
    }else if(CurrentAlarm == 2){
        addInterval2Min=addInterval2Min-1;
        if (addInterval2Min >= 10){
            addInterval2Min=59;
        }
    }else if(CurrentAlarm == 3){
        addInterval3Min=addInterval3Min-1;
        if (addInterval3Min >= 10){
            addInterval3Min=59;
        }
    }else if(CurrentAlarm == 4){
        addInterval4Min=addInterval4Min-1;
        if (addInterval4Min >= 10){
            addInterval4Min=59;
        }
    }
}

void setIntervalSecPlus(){
    if (CurrentAlarm == 1){
        addInterval1Sec=addInterval1Sec+1;
        if (addInterval1Sec >= 60){
            addInterval1Sec = 0;
        }
    }else if (CurrentAlarm == 2){
        addInterval2Sec=addInterval2Sec+1;
        if (addInterval2Sec >= 60){
            addInterval2Sec = 0;
        }
    }else if (CurrentAlarm == 3){
        addInterval3Sec=addInterval3Sec+1;
        if (addInterval3Sec >= 60){
            addInterval3Sec = 0;
        }
    }else if (CurrentAlarm == 4){
        addInterval4Sec=addInterval4Sec+1;
        if (addInterval4Sec >= 60){
            addInterval4Sec = 0;
        }
    }
}

void setIntervalSecMin(){
    if (CurrentAlarm == 1){
        if (addInterval1Sec >= 10){
            addInterval1Sec=addInterval1Sec-1;
        }
    }else if (CurrentAlarm == 2){
        if (addInterval2Sec >= 10){
            addInterval2Sec=addInterval2Sec-1;
        }
    }else if (CurrentAlarm == 3){
        if (addInterval3Sec >= 10){
            addInterval3Sec=addInterval3Sec-1;
        }
    }else if (CurrentAlarm == 4){
        if (addInterval4Sec >= 10){
            addInterval4Sec=addInterval4Sec-1;
        }
    }
}

void setIntervalMsecPlus(){
    if (CurrentAlarm == 1){
        addInterval1Msec=addInterval1Msec+10;
        if (addInterval1Msec >= 1000){
            addInterval1Msec=0;
        }
    }else if (CurrentAlarm == 2){
        addInterval2Msec=addInterval2Msec+10;
        if (addInterval2Msec >= 1000){
            addInterval2Msec=0;
        }
    }else if (CurrentAlarm == 3){
        addInterval3Msec=addInterval3Msec+10;
        if (addInterval3Msec >= 1000){
            addInterval3Msec=0;
        }
    }else if (CurrentAlarm == 4){
        addInterval3Msec=addInterval3Msec+10;
        if (addInterval3Msec >= 1000){
            addInterval3Msec=0;
        }
    }
}

void setIntervalMsecMin(){
    if (CurrentAlarm == 1){
        if (addInterval1Msec >= 10){
            addInterval1Msec=addInterval1Msec-10;
        }
    }else if (CurrentAlarm == 2){
        if (addInterval2Msec >= 10){
            addInterval2Msec=addInterval2Msec-10;
        }
    }else if (CurrentAlarm == 3){
        if (addInterval3Msec >= 10){
            addInterval3Msec=addInterval3Msec-10;
        }
    }else if (CurrentAlarm == 4){
        if (addInterval4Msec >= 10){
            addInterval4Msec=addInterval4Msec-10;
        }
    }
}

int intervalMsec(){
    if (CurrentAlarm == 1){
        return addInterval1Msec;
    }else if(CurrentAlarm == 2){
        return addInterval2Msec;
    }else if(CurrentAlarm == 3){
        return addInterval3Msec;
    }else if(CurrentAlarm == 4){
        return addInterval4Msec;
    }
}

int intervalSec(){
    if (CurrentAlarm == 1){
        return addInterval1Sec;
    }else if(CurrentAlarm == 2){
        return addInterval2Sec;
    }else if(CurrentAlarm == 3){
        return addInterval3Sec;
    }else if(CurrentAlarm == 4){
        return addInterval4Sec;
    }
}

int intervalMin(){
    if (CurrentAlarm == 1){
        return addInterval1Min;
    }else if(CurrentAlarm == 2){
        return addInterval2Min;
    }else if(CurrentAlarm == 3){
        return addInterval3Min;
    }else if(CurrentAlarm == 4){
        return addInterval4Min;
    }
}

int intervalHour(){
    if (CurrentAlarm == 1){
        return addInterval1Hour;
    }else if(CurrentAlarm == 2){
        return addInterval2Hour;
    }else if(CurrentAlarm == 3){
        return addInterval3Hour;
    }else if(CurrentAlarm == 4){
        return addInterval4Hour;
    }
}

void startAlarm1(){
    alarm1Active = 1;
    alarm1Mode = 1;
}

void startAlarm2(){
    alarm2Active = 1;
    alarm2Mode = 1;
}

void startAlarm3(){
    alarm3Active = 1;
    alarm3Mode = 1;
}

void startAlarm4(){
    alarm4Active = 1;
    alarm4Mode = 1;
}

void stopAlarm1(){
    alarm1Active = 0;
    alarm1Mode = 0;
}

void stopAlarm2(){
    alarm2Active = 0;
    alarm2Mode = 0;
}

void stopAlarm3(){
    alarm3Active = 0;
    alarm3Mode = 0;
}

void stopAlarm4(){
    alarm4Active = 0;
    alarm4Mode = 0;
}

void setAlarmsel(Alarm){
    CurrentAlarm = Alarm;
}

int getAlarm(){
    return CurrentAlarm;
}

void AchangeMinUp(){
    switch(CurrentAlarm){
        case 1:
            alarm1Min = alarm1Min + 1;
            if (alarm1Min > 60){
                alarm1Min = 0;
            }
            break;

        case 2:
            alarm2Min = alarm2Min + 1;
            if (alarm2Min > 60){
                alarm2Min = 0;
            }
            break;
        case 3:
            alarm3Min = alarm3Min + 1;
            if (alarm3Min > 60){
                alarm3Min = 0;
            }
            break;

        case 4:
            alarm4Min = alarm4Min + 1;
            if (alarm4Min > 60){
                alarm4Min = 0;
            }
            break;

        default:
            break;
    }
}

void AchangeMinDown(){
    switch(CurrentAlarm){
        case 1:
            alarm1Min = alarm1Min - 1;
            if (alarm1Min < 0){
                alarm1Min = 60;
            }
            break;

        case 2:
            alarm2Min = alarm2Min - 1;
            if (alarm2Min < 0){
                alarm2Min = 60;
            }
            break;
        case 3:
            alarm3Min = alarm3Min - 1;
            if (alarm3Min < 0){
                alarm3Min = 60;
            }
            break;

        case 4:
            alarm4Min = alarm4Min - 1;
            if (alarm4Min < 0){
                alarm4Min = 60;
            }
            break;

        default:
            break;
    }
}

void AchangeHourUp(){
    switch(CurrentAlarm){
        case 1:
            alarm1Hour = alarm1Hour + 1;
            if (alarm1Hour > 23){
                alarm1Hour = 0;
            }
            break;

        case 2:
            alarm2Hour = alarm2Hour + 1;
            if (alarm2Hour > 23){
                alarm2Hour = 0;
            }
            break;
        case 3:
            alarm3Hour = alarm3Hour + 1;
            if (alarm3Hour > 23){
                alarm3Hour = 0;
            }
            break;

        case 4:
            alarm4Hour = alarm3Hour + 1;
            if (alarm4Hour > 23){
                alarm4Hour = 0;
            }
            break;

        default:
            break;
    }
}

void AchangeHourDown(){
    switch(CurrentAlarm){
        case 1:
            alarm1Hour = alarm1Hour - 1;
            if (alarm1Hour < 0){
                alarm1Hour = 23;
            }
            break;

        case 2:
            alarm2Hour = alarm2Hour - 1;
            if (alarm2Hour < 0){
                alarm2Hour = 23;
            }
            break;
        case 3:
            alarm3Hour = alarm3Hour - 1;
            if (alarm3Hour < 0){
                alarm3Hour = 23;
            }
            break;

        case 4:
            alarm4Hour = alarm4Hour - 1;
            if (alarm4Hour < 0){
                alarm4Hour = 23;
            }
            break;

        default:
            break;
    }
}

void SetWeekday(int weekday[]){
    switch(CurrentAlarm){
        case 1:
            alarm1Mon = weekday[0];
            alarm1Tue = weekday[1];
            alarm1Wed = weekday[2];
            alarm1Thu = weekday[3];
            alarm1Fri = weekday[4];
            alarm1Sat = weekday[5];
            alarm1Sun = weekday[6];
            break;
        case 2:
            alarm2Mon = weekday[0];
            alarm2Tue = weekday[1];
            alarm2Wed = weekday[2];
            alarm2Thu = weekday[3];
            alarm2Fri = weekday[4];
            alarm2Sat = weekday[5];
            alarm2Sun = weekday[6];
            break;
        case 3:
            alarm3Mon = weekday[0];
            alarm3Tue = weekday[1];
            alarm3Wed = weekday[2];
            alarm3Thu = weekday[3];
            alarm3Fri = weekday[4];
            alarm3Sat = weekday[5];
            alarm3Sun = weekday[6];
            break;
        case 4:
            alarm4Mon = weekday[0];
            alarm4Tue = weekday[1];
            alarm4Wed = weekday[2];
            alarm4Thu = weekday[3];
            alarm4Fri = weekday[4];
            alarm4Sat = weekday[5];
            alarm4Sun = weekday[6];
            break;
    }
}

int AgetHour(){
    int Aget = 0;
    switch(CurrentAlarm){
        case 1:
           Aget = alarm1Hour;
           break;
        case 2:
            Aget = alarm2Hour;
            break;
        case 3:
            Aget = alarm3Hour;
            break;
        case 4:
            Aget = alarm4Hour;
            break;
        default:
            break;
    }
    return Aget;
}

int AgetMin(){
    int Aget = 0;
    switch(CurrentAlarm){
        case 1:
           Aget = alarm1Min;
           break;
        case 2:
            Aget = alarm2Min;
            break;
        case 3:
            Aget = alarm3Min;
            break;
        case 4:
            Aget = alarm4Min;
            break;
        default:
            break;
    }
    return Aget;
}


//function to set the current time and save it to RTC
void set_time(s_time_secs, s_time_mins, s_time_hours, s_time_days, s_time_date, s_time_month, s_time_year){
    //to write the values to the RTC the pointer needs to be set at 0 thats why the writing of the values starts at [1]
    uint8_t  rtc_set_time[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    //change i2c slave adress
    g_i2c0.p_api->reset(g_i2c0.p_ctrl);
    g_i2c0.p_api->slaveAddressSet(g_i2c0.p_ctrl, I2C_ADDRESS, I2C_ADDR_MODE_7BIT);

    rtc_set_time[1] = (uint8_t)(((s_time_secs/10) << 4) | (s_time_secs % 10));
    rtc_set_time[2] = (uint8_t)(((s_time_mins/10) << 4) | (s_time_mins % 10));
    rtc_set_time[3] = (uint8_t)(((s_time_hours/10) << 4) | (s_time_hours % 10));

    rtc_set_time[4] = (uint8_t)(s_time_days);
    rtc_set_time[5] = (uint8_t)(((s_time_date/10) << 4) | (s_time_date % 10));
    rtc_set_time[6] = (uint8_t)(((s_time_month/10) << 4) | (s_time_month % 10));   //hier wordt geen rekening gehouden met het century bit maar dat zou niet nodig moeten zijn
    rtc_set_time[7] = (uint8_t)((((s_time_year-2000)/10) << 4) | ((s_time_year-2000) % 10));

    g_i2c0.p_api->write(g_i2c0.p_ctrl, &rtc_set_time[0], 8, false);
}
