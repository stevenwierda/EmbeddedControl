/*
 * time.c
 *
 *  Created on: 29 Dec 2020
 *      Author: steve
 */
#include "time.h"
#include "common_data.h"
#include "main_thread.h"

int msec        = 0;
int sec         = 0;
int min         = 0;
int hour        = 0;
int date        = 0;        //date
int month       = 0;
int year        = 0;
int weekday     = 0;        //day of the week

int alarm1Hour = 0;
int alarm1Min = 0;
int alarm1Sec = 10;
int alarm1Msec = 0;
int alarm1Mode = 2;         //0 for nothing 1 for alarm 2 for PWM
int addInterval1Msec = 200;
int addInterval1Sec = 1;
int addInterval1Min  = 0;
int addInterval1Hour = 0;
int alarm1Mon = 0;
int alarm1Tue = 0;
int alarm1Wed = 0;
int alarm1Thu = 0;
int alarm1Fri = 0;
int alarm1Sat = 0;
int alarm1Sun = 0;
int alarm1Active = 0;
int action1 = 0;

int alarm2Hour = 0;
int alarm2Min = 0;
int alarm2Sec = 10;
int alarm2Msec = 0;
int alarm2Mode = 2;
int addInterval2Msec = 200;
int addInterval2Sec = 1;
int addInterval2Min  = 0;
int addInterval2Hour = 0;
int alarm2Mon = 0;
int alarm2Tue = 0;
int alarm2Wed = 0;
int alarm2Thu = 0;
int alarm2Fri = 0;
int alarm2Sat = 0;
int alarm2Sun = 0;
int alarm2Active = 0;
int action2 = 0;

int alarm3Hour = 0;
int alarm3Min = 0;
int alarm3Sec = 10;
int alarm3Msec = 0;
int alarm3Mode = 2;
int addInterval3Msec = 200;
int addInterval3Sec = 1;
int addInterval3Min  = 0;
int addInterval3Hour = 0;
int alarm3Mon = 0;
int alarm3Tue = 0;
int alarm3Wed = 0;
int alarm3Thu = 0;
int alarm3Fri = 0;
int alarm3Sat = 0;
int alarm3Sun = 0;
int alarm3Active = 0;
int action3 = 0;

int alarm4Hour = 0;
int alarm4Min = 0;
int alarm4Sec = 10;
int alarm4Msec = 0;
int alarm4Mode = 2;
int addInterval4Msec = 200;
int addInterval4Sec = 1;
int addInterval4Min  = 0;
int addInterval4Hour = 0;
int alarm4Mon = 0;
int alarm4Tue = 0;
int alarm4Wed = 0;
int alarm4Thu = 0;
int alarm4Fri = 0;
int alarm4Sat = 0;
int alarm4Sun = 0;
int alarm4Active = 0;
int action4 = 0;

int CurrentAlarm = 0;
int autostart = 0;

//I2C Adresses
#define I2C_ADDRESS         0x68
#define I2C_ADDRESSEEPROM   0x57

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

//function to set the current time and save it to RTC
void set_time(int s_time_secs, int s_time_mins, int s_time_hours, int s_time_days, int s_time_date, int s_time_month, int s_time_year){
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

void savealarm(int current){
    int alarmHour[4] = {alarm1Hour, alarm2Hour, alarm3Hour, alarm4Hour};
    int alarmMin[4] = {alarm1Min, alarm2Min, alarm3Min, alarm4Min};
    int alarmMode[4] = {alarm1Mode, alarm2Mode, alarm3Mode, alarm4Mode};
    int alarmMon[4] = {alarm1Mon, alarm2Mon, alarm3Mon, alarm4Mon};
    int alarmTue[4] = {alarm1Tue, alarm2Tue, alarm3Tue, alarm4Tue};
    int alarmWed[4] = {alarm1Wed, alarm2Wed, alarm3Wed, alarm4Wed};
    int alarmThu[4] = {alarm1Thu, alarm2Thu, alarm3Thu, alarm4Thu};
    int alarmFri[4] = {alarm1Fri, alarm2Fri, alarm3Fri, alarm4Fri};
    int alarmSat[4] = {alarm1Sat, alarm2Sat, alarm3Sat, alarm4Sat};
    int alarmSun[4] = {alarm1Sun, alarm2Sun, alarm3Sun, alarm4Sun};
    int alarmActive[4] = {alarm1Active, alarm2Active, alarm3Active, alarm4Active};

    int alarmDay = alarmMon[current - 1] + 2*alarmTue[current - 1] + 4*alarmWed[current - 1] + 8*alarmThu[current - 1] + 16*alarmFri[current - 1] + 32*alarmSat[current - 1] + 64*alarmSun[current - 1];

    uint8_t Wtotal[7];

    Wtotal[0] = current;
    Wtotal[1] = 0x00;
    Wtotal[2] = alarmHour[current - 1];
    Wtotal[3] = alarmMin[current - 1];
    Wtotal[4] = alarmDay;
    Wtotal[5] = alarmMode[current - 1];
    Wtotal[6] = alarmActive[current - 1];

    //houd de functies in de main in de gaten omdat daar de rtc aangeroepen wordt, dit kan een probleem zijn.
    g_i2c0.p_api->reset(g_i2c0.p_ctrl);
    g_i2c0.p_api->slaveAddressSet(g_i2c0.p_ctrl, I2C_ADDRESSEEPROM, I2C_ADDR_MODE_7BIT);

    //set het adres met 2 bytes en schrijf daarna de bytes van de rest van de data.
    g_i2c0.p_api->write(g_i2c0.p_ctrl, &Wtotal[0], 7, false); //7 bytes scrijven
}

void savepwm(int current){
    int alarmMode[4] = {alarm1Mode, alarm2Mode, alarm3Mode, alarm4Mode};
    int addIntervalMsec[4] = {addInterval1Msec, addInterval2Msec, addInterval3Msec, addInterval4Msec};
    int addIntervalSec[4] = {addInterval1Sec, addInterval2Sec, addInterval3Sec, addInterval4Sec};
    int addIntervalMin[4]  = {addInterval1Min, addInterval2Min, addInterval3Min, addInterval4Min};
    int addIntervalHour[4] = {addInterval1Hour, addInterval2Hour, addInterval3Hour, addInterval4Hour};
    int alarmActive[4] = {alarm1Active, alarm2Active, alarm3Active, alarm4Active};

    uint8_t Wtotal[8];

    Wtotal[0] = current;
    Wtotal[1] = 0x03;
    Wtotal[2] = alarmMode[current - 1];
    Wtotal[3] = alarmActive[current - 1];
    Wtotal[4] = addIntervalHour[current - 1];
    Wtotal[5] = addIntervalMin[current - 1];
    Wtotal[6] = addIntervalSec[current - 1];
    Wtotal[7] = addIntervalMsec[current - 1] / 10;

    //houd de functies in de main in de gaten omdat daar de rtc aangeroepen wordt, dit kan een probleem zijn.
    g_i2c0.p_api->reset(g_i2c0.p_ctrl);
    g_i2c0.p_api->slaveAddressSet(g_i2c0.p_ctrl, I2C_ADDRESSEEPROM, I2C_ADDR_MODE_7BIT);

    //set het adres met 2 bytes en schrijf daarna de bytes van de rest van de data.
    g_i2c0.p_api->write(g_i2c0.p_ctrl, &Wtotal[0], 8, false); //8 bytes scrijven
}

void alarmpwm1read(){
    uint8_t Rtotal[2];
    uint8_t arv[9];

    Rtotal[0] = 0x01;
    Rtotal[1] = 0x00;

    g_i2c0.p_api->reset(g_i2c0.p_ctrl);
    g_i2c0.p_api->slaveAddressSet(g_i2c0.p_ctrl, I2C_ADDRESSEEPROM, I2C_ADDR_MODE_7BIT);

    g_i2c0.p_api->write(g_i2c0.p_ctrl, &Rtotal[0], 2, false);

    g_i2c0.p_api->read(g_i2c0.p_ctrl, &arv[0], 9, true);
    alarm1Hour = arv[0];
    alarm1Min = arv[1];
    alarm1Mode = arv[3];
    if(alarm1Mode == 2){
        activatePWM1();
    }
    if(autostart == 1){
        alarm1Active = arv[4];
    }
    else{
        alarm1Active = 0;
    }
    //save the new state for active to make sure it saves it
    savepwm(1);
    addInterval1Hour = arv[5];
    addInterval1Min = arv[6];
    addInterval1Sec = arv[7];
    addInterval1Msec = arv[8];
    addInterval1Msec = addInterval1Msec*10;
    if (arv[2] > 63){
        alarm1Sun = 1;
        arv[2] = arv[2] - 64;
    }
    else alarm1Sun = 0;
    if (arv[2] > 31){
        alarm1Sat = 1;
        arv[2] = arv[2] - 32;
    }
    else alarm1Sat = 0;
    if (arv[2] > 15){
        alarm1Fri = 1;
        arv[2] = arv[2] - 16;
    }
    else alarm1Fri = 0;
    if (arv[2] > 7){
        alarm1Thu = 1;
        arv[2] = arv[2] - 8;
    }
    else alarm1Thu = 0;
    if (arv[2] > 3){
        alarm1Wed = 1;
        arv[2] = arv[2] - 4;
    }
    else alarm1Wed = 0;
    if (arv[2] > 1){
        alarm1Tue = 1;
        arv[2] = arv[2] - 2;
    }
    else alarm1Tue = 0;
    alarm1Mon = arv[2];
}

void alarmpwm2read(){
    uint8_t Rtotal[2];
    uint8_t arv[9];

    Rtotal[0] = 0x02;
    Rtotal[1] = 0x00;

    g_i2c0.p_api->reset(g_i2c0.p_ctrl);
    g_i2c0.p_api->slaveAddressSet(g_i2c0.p_ctrl, I2C_ADDRESSEEPROM, I2C_ADDR_MODE_7BIT);

    g_i2c0.p_api->write(g_i2c0.p_ctrl, &Rtotal[0], 2, false);

    g_i2c0.p_api->read(g_i2c0.p_ctrl, &arv[0], 9, true);
    alarm2Hour = arv[0];
    alarm2Min = arv[1];
    alarm2Mode = arv[3];
    if(alarm2Mode == 2){
        activatePWM2();
    }
    if(autostart == 1){
        alarm2Active = arv[4];
    }
    else{
        alarm2Active = 0;
    }
    //save the new state for active to make sure it saves it
    savepwm(2);
    addInterval2Hour = arv[5];
    addInterval2Min = arv[6];
    addInterval2Sec = arv[7];
    addInterval2Msec = arv[8];
    addInterval2Msec = addInterval2Msec*10;
    if (arv[2] > 63){
        alarm2Sun = 1;
        arv[2] = arv[2] - 64;
    }
    else alarm2Sun = 0;
    if (arv[2] > 31){
        alarm2Sat = 1;
        arv[2] = arv[2] - 32;
    }
    else alarm2Sat = 0;
    if (arv[2] > 15){
        alarm2Fri = 1;
        arv[2] = arv[2] - 16;
    }
    else alarm2Fri = 0;
    if (arv[2] > 7){
        alarm2Thu = 1;
        arv[2] = arv[2] - 8;
    }
    else alarm2Thu = 0;
    if (arv[2] > 3){
        alarm2Wed = 1;
        arv[2] = arv[2] - 4;
    }
    else alarm2Wed = 0;
    if (arv[2] > 1){
        alarm2Tue = 1;
        arv[2] = arv[2] - 2;
    }
    else alarm2Tue = 0;
    alarm2Mon = arv[2];
}

void alarmpwm3read(){
    uint8_t Rtotal[2];
    uint8_t arv[9];

    Rtotal[0] = 0x03;
    Rtotal[1] = 0x00;

    g_i2c0.p_api->reset(g_i2c0.p_ctrl);
    g_i2c0.p_api->slaveAddressSet(g_i2c0.p_ctrl, I2C_ADDRESSEEPROM, I2C_ADDR_MODE_7BIT);

    g_i2c0.p_api->write(g_i2c0.p_ctrl, &Rtotal[0], 2, false);

    g_i2c0.p_api->read(g_i2c0.p_ctrl, &arv[0], 9, true);
    alarm3Hour = arv[0];
    alarm3Min = arv[1];
    alarm3Mode = arv[3];
    if(alarm3Mode == 2){
        activatePWM3();
    }
    if(autostart == 1){
        alarm3Active = arv[4];
    }
    else{
        alarm3Active = 0;
    }
    //save the new state for active to make sure it saves it
    savepwm(3);
    addInterval3Hour = arv[5];
    addInterval3Min = arv[6];
    addInterval3Sec = arv[7];
    addInterval3Msec = arv[8];
    addInterval3Msec = addInterval3Msec*10;
    if (arv[2] > 63){
        alarm3Sun = 1;
        arv[2] = arv[2] - 64;
    }
    else alarm3Sun = 0;
    if (arv[2] > 31){
        alarm3Sat = 1;
        arv[2] = arv[2] - 32;
    }
    else alarm3Sat = 0;
    if (arv[2] > 15){
        alarm3Fri = 1;
        arv[2] = arv[2] - 16;
    }
    else alarm3Fri = 0;
    if (arv[2] > 7){
        alarm3Thu = 1;
        arv[2] = arv[2] - 8;
    }
    else alarm3Thu = 0;
    if (arv[2] > 3){
        alarm3Wed = 1;
        arv[2] = arv[2] - 4;
    }
    else alarm3Wed = 0;
    if (arv[2] > 1){
        alarm3Tue = 1;
        arv[2] = arv[2] - 2;
    }
    else alarm3Tue = 0;
    alarm3Mon = arv[2];
}

void alarmpwm4read(){
    uint8_t Rtotal[2];
    uint8_t arv[9];

    Rtotal[0] = 0x04;
    Rtotal[1] = 0x00;

    g_i2c0.p_api->reset(g_i2c0.p_ctrl);
    g_i2c0.p_api->slaveAddressSet(g_i2c0.p_ctrl, I2C_ADDRESSEEPROM, I2C_ADDR_MODE_7BIT);

    g_i2c0.p_api->write(g_i2c0.p_ctrl, &Rtotal[0], 2, false);

    g_i2c0.p_api->read(g_i2c0.p_ctrl, &arv[0], 9, true);
    alarm4Hour = arv[0];
    alarm4Min = arv[1];
    alarm4Mode = arv[3];
    if(alarm4Mode == 2){
        activatePWM4();
    }
    if(autostart == 1){
        alarm4Active = arv[4];
    }
    else{
        alarm4Active = 0;
    }
    //save the new state for active to make sure it saves it
    savepwm(4);
    addInterval4Hour = arv[5];
    addInterval4Min = arv[6];
    addInterval4Sec = arv[7];
    addInterval4Msec = arv[8];
    addInterval4Msec = addInterval4Msec*10;
    if (arv[2] > 63){
        alarm4Sun = 1;
        arv[2] = arv[2] - 64;
    }
    else alarm4Sun = 0;
    if (arv[2] > 31){
        alarm4Sat = 1;
        arv[2] = arv[2] - 32;
    }
    else alarm4Sat = 0;
    if (arv[2] > 15){
        alarm4Fri = 1;
        arv[2] = arv[2] - 16;
    }
    else alarm4Fri = 0;
    if (arv[2] > 7){
        alarm4Thu = 1;
        arv[2] = arv[2] - 8;
    }
    else alarm4Thu = 0;
    if (arv[2] > 3){
        alarm4Wed = 1;
        arv[2] = arv[2] - 4;
    }
    else alarm4Wed = 0;
    if (arv[2] > 1){
        alarm4Tue = 1;
        arv[2] = arv[2] - 2;
    }
    else alarm4Tue = 0;
    alarm4Mon = arv[2];
}

void saveauto(int val){
    //scrhijf de waardes van de EEPROM wanneer er een verandering is en de user klaar is en op de terug knop drukt.
    uint8_t Rtotal[3] = {0x05, 0x00, val};

    //houd de functies in de main in de gaten omdat daar de rtc aangeroepen wordt, dit kan een probleem zijn.
    g_i2c0.p_api->reset(g_i2c0.p_ctrl);
    g_i2c0.p_api->slaveAddressSet(g_i2c0.p_ctrl, I2C_ADDRESSEEPROM, I2C_ADDR_MODE_7BIT);

    //set het adres met 2 bytes en schrijf daarna de bytes van de rest van de data.
    g_i2c0.p_api->write(g_i2c0.p_ctrl, &Rtotal[0], 3, false); //2 bytes scrijven
}

void readauto(){
    uint8_t Rtotal[2]={0x05,0x00};

    g_i2c0.p_api->reset(g_i2c0.p_ctrl);
    g_i2c0.p_api->slaveAddressSet(g_i2c0.p_ctrl, I2C_ADDRESSEEPROM, I2C_ADDR_MODE_7BIT);

    g_i2c0.p_api->write(g_i2c0.p_ctrl, &Rtotal[0], 2, false);

    g_i2c0.p_api->read(g_i2c0.p_ctrl, &autostart, 1, true);
}


void addMs(){
    msec = msec + 1;
    if(msec >= 1000){
        msec = msec - 1000;
        sec = sec + 1;
        printf( "%i/%i/%i - %i:%i:%i := current time \n", getYear(), getMonth(), getDate(), getHour(), getMin(), getSec());
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
    if(hour == alarm1Hour && min == alarm1Min && alarm1Active == 1 && sec == 1 && msec == 1){
       if(alarm1Mode == 1){
           if((alarm1Mon == 1 && weekday == 1)||
               (alarm1Tue == 1 && weekday == 2)||
               (alarm1Wed == 1 && weekday == 3)||
               (alarm1Thu == 1 && weekday == 4)||
               (alarm1Fri == 1 && weekday == 5)||
               (alarm1Sat == 1 && weekday == 6)||
               (alarm1Sun == 1 && weekday == 7)){
               if (action1 == 0){
                   action1 = 1;
                   printf( "%i/%i/%i - %i:%i:%i :", getYear(), getMonth(), getDate(), getHour(), getMin(), getSec());
                   printf("alarm 1 high \n");
               }
               else{
                   action1 = 0;
                   printf( "%i/%i/%i - %i:%i:%i :", getYear(), getMonth(), getDate(), getHour(), getMin(), getSec());
                   printf("alarm 1 low \n");
               }
           }
       }
       else if(alarm1Mode == 2 && sec == alarm1Sec && alarm1Msec == msec){
           if (action1 == 0){
               action1 = 1;
               printf( "%i/%i/%i - %i:%i:%i :", getYear(), getMonth(), getDate(), getHour(), getMin(), getSec());
               printf("alarm 1 high \n");
           }
           else{
               action1 = 0;
               printf( "%i/%i/%i - %i:%i:%i :", getYear(), getMonth(), getDate(), getHour(), getMin(), getSec());
               printf("alarm 1 low \n");
           }
           intervalAlarm1();
       }
   }
   else if(alarm1Mode == 0){
       action1 = 3;
   }
   return action1;
}

int checkAlarm2(){
   if(hour == alarm2Hour && min == alarm2Min && alarm2Active == 1 && sec == 1 && msec == 1){
       if(alarm2Mode == 1){
           if((alarm2Mon == 1 && weekday == 1)||
               (alarm2Tue == 1 && weekday == 2)||
               (alarm2Wed == 1 && weekday == 3)||
               (alarm2Thu == 1 && weekday == 4)||
               (alarm2Fri == 1 && weekday == 5)||
               (alarm2Sat == 1 && weekday == 6)||
               (alarm2Sun == 1 && weekday == 7)){
               if (action2 == 0){
                   action2 = 1;
                   printf( "%i/%i/%i - %i:%i:%i :", getYear(), getMonth(), getDate(), getHour(), getMin(), getSec());
                   printf("alarm 2 high \n");
               }
               else{
                   action2 = 0;
                   printf( "%i/%i/%i - %i:%i:%i :", getYear(), getMonth(), getDate(), getHour(), getMin(), getSec());
                   printf("alarm 2 low \n");
               }
           }
       }
       else if(alarm2Mode == 2 && sec == alarm2Sec && alarm2Msec == msec){
               if (action2 == 0){
                   action2 = 1;
                   printf( "%i/%i/%i - %i:%i:%i :", getYear(), getMonth(), getDate(), getHour(), getMin(), getSec());
                   printf("alarm 2 high \n");
               }
               else{
                   action2 = 0;
                   printf( "%i/%i/%i - %i:%i:%i :", getYear(), getMonth(), getDate(), getHour(), getMin(), getSec());
                   printf("alarm 2 low \n");
               }
               intervalAlarm2();
       }
       else if(alarm2Mode == 0){
           action2 = 3;
       }
   }
   return action2;
}

int checkAlarm3(){
    if(hour == alarm3Hour && min == alarm3Min && alarm3Active == 1 && sec == 1 && msec == 1){
       if(alarm3Mode == 1){
           if((alarm3Mon == 1 && weekday == 1)||
               (alarm3Tue == 1 && weekday == 2)||
               (alarm3Wed == 1 && weekday == 3)||
               (alarm3Thu == 1 && weekday == 4)||
               (alarm3Fri == 1 && weekday == 5)||
               (alarm3Sat == 1 && weekday == 6)||
               (alarm3Sun == 1 && weekday == 7)){
               if (action3 == 0){
                   action3 = 1;
                   printf( "%i/%i/%i - %i:%i:%i :", getYear(), getMonth(), getDate(), getHour(), getMin(), getSec());
                   printf("alarm 3 high \n");
               }
               else{
                   action3 = 0;
                   printf( "%i/%i/%i - %i:%i:%i :", getYear(), getMonth(), getDate(), getHour(), getMin(), getSec());
                   printf("alarm 3 low \n");
               }
           }
       }
       else if(alarm3Mode == 2 && sec == alarm3Sec && alarm3Msec == msec){
           if (action3 == 0){
               action3 = 1;
               printf( "%i/%i/%i - %i:%i:%i :", getYear(), getMonth(), getDate(), getHour(), getMin(), getSec());
               printf("alarm 3 high \n");
           }
           else{
               action3 = 0;
               printf( "%i/%i/%i - %i:%i:%i :", getYear(), getMonth(), getDate(), getHour(), getMin(), getSec());
               printf("alarm 3 low \n");
           }
           intervalAlarm3();
       }
   }
   else if(alarm3Mode == 0){
       action3 = 3;
   }
   return action3;
}

int checkAlarm4(){
    if(hour == alarm4Hour && min == alarm4Min && alarm4Active == 1 && sec == 1 && msec == 1){
       if(alarm4Mode == 1){
           if((alarm4Mon == 1 && weekday == 1)||
               (alarm4Tue == 1 && weekday == 2)||
               (alarm4Wed == 1 && weekday == 3)||
               (alarm4Thu == 1 && weekday == 4)||
               (alarm4Fri == 1 && weekday == 5)||
               (alarm4Sat == 1 && weekday == 6)||
               (alarm4Sun == 1 && weekday == 7)){
               if (action4 == 0){
                   action4 = 1;
                   printf( "%i/%i/%i - %i:%i:%i :", getYear(), getMonth(), getDate(), getHour(), getMin(), getSec());
                   printf("alarm 4 high \n");
               }
               else{
                   action4 = 0;
                   printf( "%i/%i/%i - %i:%i:%i :", getYear(), getMonth(), getDate(), getHour(), getMin(), getSec());
                   printf("alarm 4 low \n");
               }
           }
       }
       else if(alarm4Mode == 2 && sec == alarm4Sec && alarm4Msec == msec){
           if (action4 == 0){
               action4 = 1;
               printf( "%i/%i/%i - %i:%i:%i :", getYear(), getMonth(), getDate(), getHour(), getMin(), getSec());
               printf("alarm 4 high \n");
           }
           else{
               action4 = 0;
               printf( "%i/%i/%i - %i:%i:%i :", getYear(), getMonth(), getDate(), getHour(), getMin(), getSec());
               printf("alarm 4 low \n");
           }
           intervalAlarm4();
       }
   }
   else if(alarm4Mode == 0){
       action4 = 3;
   }
   return action4;
}

void intervalAlarm1(){
    alarm1Msec = alarm1Msec + addInterval1Msec;
    if (alarm1Msec >= 1000){
        alarm1Msec = 0;
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
    }
}

void intervalAlarm2(){
    alarm2Msec = alarm2Msec + addInterval2Msec;
    if (alarm2Msec >= 1000){
        alarm2Msec = 0;
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
    }
}

void intervalAlarm3(){
    alarm3Msec = alarm3Msec + addInterval3Msec;
    if (alarm3Msec >= 1000){
        alarm3Msec = 0;
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
    }
}

void intervalAlarm4(){
    alarm4Msec = alarm4Msec + addInterval4Msec;
    if (alarm4Msec >= 1000){
        alarm4Msec = 0;
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
    }
}


void activatePWM1(){
    alarm1Active = 1;
    alarm1Mode = 2;
    alarm1Msec = msec + addInterval1Msec;
    if (alarm1Msec >= 1000){
        alarm1Msec = 0;
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
    }
}
void activatePWM2(){
    alarm2Active = 1;
    alarm2Mode = 2;
    alarm2Msec = msec + addInterval2Msec;
    if (alarm2Msec >= 1000){
        alarm2Msec = 0;
        alarm2Sec = alarm2Sec + 1;
    }
    alarm2Sec = sec + addInterval2Sec;
    if (alarm2Sec >= 60){
        alarm2Sec = alarm2Sec - 60;
        alarm2Min = alarm2Min + 1;
    }
    alarm2Min = min + addInterval2Min;
    if (alarm2Min >= 60){
        alarm2Min = alarm2Min - 60;
        alarm2Hour = alarm2Hour + 1;
    }
    alarm2Hour = hour + addInterval2Hour;
    if (alarm2Hour >= 24){
        alarm2Hour = alarm2Hour - 24;
    }
}

void activatePWM3(){
    alarm3Active = 1;
    alarm3Mode = 2;
    alarm3Msec = msec + addInterval3Msec;
    if (alarm3Msec >= 1000){
        alarm3Msec = 0;
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
    }
}

void activatePWM4(){
    alarm4Active = 1;
    alarm4Mode = 2;
    alarm4Msec = msec + addInterval4Msec;
    if (alarm4Msec >= 1000){
        alarm4Msec = 0;
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
        addInterval4Hour++;
        if (addInterval4Hour >= 24){
            addInterval4Hour = 0;
        }
    }
}

void setIntervalHourMin(){
    if (CurrentAlarm == 1){
        addInterval1Hour=addInterval1Hour-1;
        if (addInterval1Hour < 0){
            addInterval1Hour = 24;
        }
    }else if(CurrentAlarm == 2){
        addInterval2Hour=addInterval2Hour-1;
        if (addInterval2Hour < 0){
            addInterval2Hour = 24;
        }
    }else if(CurrentAlarm == 3){
        addInterval3Hour=addInterval3Hour-1;
        if (addInterval3Hour < 0){
            addInterval3Hour = 24;
        }
    }else if(CurrentAlarm == 4){
        addInterval4Hour--;
        if (addInterval4Hour < 0){
            addInterval4Hour = 24;
        }
    }
}

void setIntervalMinPlus(){
    if (CurrentAlarm == 1){
        addInterval1Min++;
        if (addInterval1Min >= 60){
            addInterval1Min = 0;
        }
    }else if(CurrentAlarm == 2){
        addInterval2Min++;
        if (addInterval2Min >= 60){
            addInterval2Min = 0;
        }
    }else if(CurrentAlarm == 3){
        addInterval3Min++;
        if (addInterval3Min >= 60){
            addInterval3Min = 0;
        }
    }else if(CurrentAlarm == 4){
        addInterval4Min++;
        if (addInterval4Min >= 60){
            addInterval4Min = 0;
        }
    }
}

void setIntervalMinMin(){
    if (CurrentAlarm == 1){
        addInterval1Min--;
        if (addInterval1Min < 0){
            addInterval1Min=59;
        }
    }else if(CurrentAlarm == 2){
        addInterval2Min--;
        if (addInterval2Min < 0){
            addInterval2Min=59;
        }
    }else if(CurrentAlarm == 3){
        addInterval3Min--;
        if (addInterval3Min < 0){
            addInterval3Min=59;
        }
    }else if(CurrentAlarm == 4){
        addInterval4Min--;
        if (addInterval4Min < 0){
            addInterval4Min=59;
        }
    }
}

void setIntervalSecPlus(){
    if (CurrentAlarm == 1){
        addInterval1Sec++;
        if (addInterval1Sec > 59){
            addInterval1Sec = 0;
        }
    }else if (CurrentAlarm == 2){
        addInterval2Sec++;
        if (addInterval2Sec > 59){
            addInterval2Sec = 0;
        }
    }else if (CurrentAlarm == 3){
        addInterval3Sec++;
        if (addInterval3Sec > 59){
            addInterval3Sec = 0;
        }
    }else if (CurrentAlarm == 4){
        addInterval4Sec++;
        if (addInterval4Sec > 59){
            addInterval4Sec = 0;
        }
    }
}

void setIntervalSecMin(){
    if (CurrentAlarm == 1){
        addInterval1Sec--;
        if (addInterval1Sec < 0){
            addInterval1Sec = 59;
        }
    }else if (CurrentAlarm == 2){
        addInterval2Sec--;
        if (addInterval2Sec < 0){
        }
    }else if (CurrentAlarm == 3){
        addInterval3Sec--;
        if (addInterval3Sec < 0){
            addInterval3Sec = 59;
        }
    }else if (CurrentAlarm == 4){
        addInterval4Sec--;
        if (addInterval4Sec < 0){
            addInterval4Sec = 59;

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
        addInterval4Msec=addInterval3Msec+10;
        if (addInterval4Msec >= 1000){
            addInterval4Msec=0;
        }
    }
}

void setIntervalMsecMin(){
    if (CurrentAlarm == 1){
        if (addInterval1Msec >= 10){
            addInterval1Msec=addInterval1Msec-10;
            if(addInterval1Msec < 10){
                addInterval1Msec = 990;
            }
        }
    }
    else if (CurrentAlarm == 2){
        if (addInterval2Msec >= 10){
            addInterval2Msec=addInterval2Msec-10;
            if(addInterval2Msec < 10){
                addInterval2Msec = 990;
            }
        }
    }
    else if (CurrentAlarm == 3){
        if (addInterval3Msec >= 10){
            addInterval3Msec=addInterval3Msec-10;
            if(addInterval3Msec < 10){
                addInterval3Msec = 990;
            }
        }
    }
    else if (CurrentAlarm == 4){
        if (addInterval4Msec >= 10){
            addInterval4Msec=addInterval4Msec-10;
            if(addInterval4Msec < 10){
                addInterval4Msec = 990;
            }
        }
    }
 }

int intervalMsec(){
    int var = 0;
    if (CurrentAlarm == 1){
        var = addInterval1Msec;
    }else if(CurrentAlarm == 2){
        var = addInterval2Msec;
    }else if(CurrentAlarm == 3){
        var = addInterval3Msec;
    }else if(CurrentAlarm == 4){
        var = addInterval4Msec;
    }
    return var;
}

int intervalSec(){
    int var = 0;
    if (CurrentAlarm == 1){
        var = addInterval1Sec;
    }else if(CurrentAlarm == 2){
        var = addInterval2Sec;
    }else if(CurrentAlarm == 3){
        var = addInterval3Sec;
    }else if(CurrentAlarm == 4){
        var = addInterval4Sec;
    }
    return var;
}

int intervalMin(){
    int var = 0;
    if (CurrentAlarm == 1){
        return addInterval1Min;
    }else if(CurrentAlarm == 2){
        return addInterval2Min;
    }else if(CurrentAlarm == 3){
        return addInterval3Min;
    }else if(CurrentAlarm == 4){
        return addInterval4Min;
    }
    return var;
}

int intervalHour(){
    int var = 0;
    if (CurrentAlarm == 1){
        var = addInterval1Hour;
    }else if(CurrentAlarm == 2){
        var = addInterval2Hour;
    }else if(CurrentAlarm == 3){
        var = addInterval3Hour;
    }else if(CurrentAlarm == 4){
        var = addInterval4Hour;
    }
    return var;
}

void startAlarm1(){
    alarm1Active = 1;
    alarm1Mode = 1;
    alarm1Sec = 0;
    alarm1Msec = 0;
}

void startAlarm2(){
    alarm2Active = 1;
    alarm2Mode = 1;
    alarm2Sec = 0;
    alarm2Msec = 0;
}

void startAlarm3(){
    alarm3Active = 1;
    alarm3Mode = 1;
    alarm3Sec = 0;
    alarm3Msec = 0;
}

void startAlarm4(){
    alarm4Active = 1;
    alarm4Mode = 1;
    alarm4Sec = 0;
    alarm4Msec =0;
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

void setAlarmsel(int Alarm){
    CurrentAlarm = Alarm;
}

int getAlarm(){
    return CurrentAlarm;
}

void AchangeMinUp(){
    switch(CurrentAlarm){
        case 1:
            alarm1Min = alarm1Min + 1;
            if (alarm1Min > 59){
                alarm1Min = 0;
            }
            break;
        case 2:
            alarm2Min = alarm2Min + 1;
            if (alarm2Min > 59){
                alarm2Min = 0;
            }
            break;
        case 3:
            alarm3Min = alarm3Min + 1;
            if (alarm3Min > 59){
                alarm3Min = 0;
            }
            break;

        case 4:
            alarm4Min = alarm4Min + 1;
            if (alarm4Min > 59){
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
                alarm1Min = 59;
            }
            break;

        case 2:
            alarm2Min = alarm2Min - 1;
            if (alarm2Min < 0){
                alarm2Min = 59;
            }
            break;
        case 3:
            alarm3Min = alarm3Min - 1;
            if (alarm3Min < 0){
                alarm3Min = 59;
            }
            break;

        case 4:
            alarm4Min = alarm4Min - 1;
            if (alarm4Min < 0){
                alarm4Min = 59;
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
            alarm4Hour = alarm4Hour + 1;
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

void SetWeekday(int Aweekday[]){
    switch(CurrentAlarm){
    case 1:
        alarm1Mon = Aweekday[0];
        alarm1Tue = Aweekday[1];
        alarm1Wed = Aweekday[2];
        alarm1Thu = Aweekday[3];
        alarm1Fri = Aweekday[4];
        alarm1Sat = Aweekday[5];
        alarm1Sun = Aweekday[6];
        break;
    case 2:
        alarm2Mon = Aweekday[0];
        alarm2Tue = Aweekday[1];
        alarm2Wed = Aweekday[2];
        alarm2Thu = Aweekday[3];
        alarm2Fri = Aweekday[4];
        alarm2Sat = Aweekday[5];
        alarm2Sun = Aweekday[6];
        break;
    case 3:
        alarm3Mon = Aweekday[0];
        alarm3Tue = Aweekday[1];
        alarm3Wed = Aweekday[2];
        alarm3Thu = Aweekday[3];
        alarm3Fri = Aweekday[4];
        alarm3Sat = Aweekday[5];
        alarm3Sun = Aweekday[6];
        break;
    case 4:
        alarm4Mon = Aweekday[0];
        alarm4Tue = Aweekday[1];
        alarm4Wed = Aweekday[2];
        alarm4Thu = Aweekday[3];
        alarm4Fri = Aweekday[4];
        alarm4Sat = Aweekday[5];
        alarm4Sun = Aweekday[6];
        break;
    }
}

int getweekday(int index){
    int ALweekday[7];
    switch(CurrentAlarm){
    case 1:
        ALweekday[0] = alarm1Mon;
        ALweekday[1] = alarm1Tue;
        ALweekday[2] = alarm1Wed;
        ALweekday[3] = alarm1Thu;
        ALweekday[4] = alarm1Fri;
        ALweekday[5] = alarm1Sat;
        ALweekday[6] = alarm1Sun;
        break;
    case 2:
        ALweekday[0] = alarm2Mon;
        ALweekday[1] = alarm2Tue;
        ALweekday[2] = alarm2Wed;
        ALweekday[3] = alarm2Thu;
        ALweekday[4] = alarm2Fri;
        ALweekday[5] = alarm2Sat;
        ALweekday[6] = alarm2Sun;
        break;
    case 3:
        ALweekday[0] = alarm3Mon;
        ALweekday[1] = alarm3Tue;
        ALweekday[2] = alarm3Wed;
        ALweekday[3] = alarm3Thu;
        ALweekday[4] = alarm3Fri;
        ALweekday[5] = alarm3Sat;
        ALweekday[6] = alarm3Sun;
        break;
    case 4:
        ALweekday[0] = alarm4Mon;
        ALweekday[1] = alarm4Tue;
        ALweekday[2] = alarm4Wed;
        ALweekday[3] = alarm4Thu;
        ALweekday[4] = alarm4Fri;
        ALweekday[5] = alarm4Sat;
        ALweekday[6] = alarm4Sun;
        break;
}
   return ALweekday[index];
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

int Aactive(int CurrentA){
    int Active;
    switch(CurrentA){
        case 1:
            Active = alarm1Active;
           break;
        case 2:
            Active = alarm2Active;
            break;
        case 3:
            Active = alarm3Active;
            break;
        case 4:
            Active = alarm4Active;
            break;
        default:
            Active = 0;
            break;
    }
    return Active;
}
//if the button is pressed start all the Alarms otherwise it requires a manual user input
void AutoStartW(){
    if(autostart == 0){
        autostart = 1;
    }
    else{
        autostart = 0;
    }
    saveauto(autostart);
}

int AutostartR(){
    return autostart;
}

