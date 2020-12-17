# rtc_dig_clock(24 hour format 17/12/2020)

-----------------
hr:min:sec
dd/mm/yyyy   DAY
-----------------

//3 switch digital clock using 8051,RTC,LCD;
//extra 1 switch can be added to make total of 4 switches.
//this extra switch is for led.
//sine we were done this project completely in software we just neglected this feature

//at89c51,ds1307,lm016l,switch
//keil_v5 C51,proteus 8 professional

//i2c protocol is used to communicate between rtc and 8051; 
//check comments in source code for furthem logic info.
//12 hour format upgradation is pending(17/12/2020)