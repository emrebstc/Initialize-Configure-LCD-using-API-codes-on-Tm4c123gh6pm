/*
 * lcd.c
 *
 *  Created on: 9 Kas 2024
 *      Author: Emre
 */

#include "stdint.h"
#include "stdbool.h"
#include "inc/tm4c123gh6pm.h"
#include "driverlib/gpio.h"
#include "driverlib/gpio.c"
#include "driverlib/sysctl.h"
#include "driverlib/sysctl.c"
#include "math.h"
#include "inc/hw_gpio.h"
#include "string.h"
#include "lcd.h"

void otuzhex(){
         int i;
         for (i=1;i<=3;i++){
         SysCtlDelay(100000);
         GPIO_PORTB_DATA_R &= 0x0FE;
         GPIO_PORTB_DATA_R |= 0x0F0;
         GPIO_PORTB_DATA_R |= 0x02;
         SysCtlDelay(1000);
         GPIO_PORTB_DATA_R |= 0x0F0;
         }
}

void LCD_komut(unsigned char a) {

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (a & 0xf0) ); //mesela 0x85 geldi > ilk  4 bit yani 8 ilk once atanýyor
        GPIOPinWrite(LCDPORT, RS, 0x00);
        GPIOPinWrite(LCDPORT, E, 0x02);

        SysCtlDelay(1000);

        GPIOPinWrite(LCDPORT, E, 0x00);

        SysCtlDelay(10000);

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (a & 0x0f) << 4 ); //ondan sonra diger geri kalan 5 atanýyor fakat data pinleri 4 bit oldugundan 4 bit otelemek gerekiyor
        GPIOPinWrite(LCDPORT, RS, 0x00);
        GPIOPinWrite(LCDPORT, E, 0x02);

        SysCtlDelay(1000);

        GPIOPinWrite(LCDPORT, E, 0x00);

        SysCtlDelay(10000);

}


void LCD_ayar() {
    SYSCTL_RCGCGPIO_R |= 0x02; // Port B için aktifleþtirme
    while((SYSCTL_PRGPIO_R & 0x02) == 0) {} // portB etkinleþtirilene kadar beklemek için
    GPIO_PORTB_DIR_R |= 0x0F3;  // I/O secimi
    GPIO_PORTB_DEN_R |= 0x0F3;  // pullup

    otuzhex();

    SysCtlDelay(50000);

        LCD_komut(0x0F); //LCDyi ac (ekran ac/kapa komutu) ekran acýk kursor acýk kursor blink acik
        LCD_temizle();

}

void LCD_karakteral(unsigned char a) {

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (a & 0xf0) );
        GPIOPinWrite(LCDPORT, RS, 0x01);
        GPIOPinWrite(LCDPORT, E, 0x02);

        SysCtlDelay(10);
        GPIOPinWrite(LCDPORT, E, 0x00);
        SysCtlDelay(50000);

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (a & 0x0f) << 4 );
        GPIOPinWrite(LCDPORT, RS, 0x01);
        GPIOPinWrite(LCDPORT, E, 0x02);

        SysCtlDelay(10);
        GPIOPinWrite(LCDPORT, E, 0x00);
        SysCtlDelay(50000);

}

void LCD_yaz(char *a,int b) {
    int j;
    if(b==0){
    for (j=0; j<16; j++) {
        if (j<strlen(a)) {
            LCD_cursor(0,j);
            LCD_karakteral(a[j]);
        }

    }
    LCD_komut(0xC0 + 16); //Cursor gozukmesin
}
    else if (b==1) {
        for (j=0; j<16; j++) {
                if (j<strlen(a)) {
                    LCD_cursor(1,j);
                    LCD_karakteral(a[j]);
                }

            }
            LCD_komut(0xC0 + 16);
    }
}


void LCD_cursor(char a, char b){

    if (a==0) {
        LCD_komut(0x80 + (b % 16)); //kursor 1. satir + b kadar sutun
    }
    else {LCD_komut(0xC0 + (b % 16)); //kursor 2.satir + b kadar sutun
    }
}

void LCD_temizle(void){
        LCD_komut(0x01);
        SysCtlDelay(50);
        LCD_cursor(0,0);
        SysCtlDelay(50);
}



void LCD_asagiyaz(char *a, int b) {
    LCD_cursor(b, 0);
    for (b=0; b<strlen(a); b++) {
        LCD_karakteral(a[b]);
    }
    b++;
    LCD_cursor(b, 0);
    LCD_komut(0xC0 + 16); //Cursor gozukmesin
}



