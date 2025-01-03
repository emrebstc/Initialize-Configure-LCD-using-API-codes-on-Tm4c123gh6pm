/*
 * lcd.h
 *
 *  Created on: 9 Kas 2024
 *      Author: Emre
 */

#ifndef LCD_H_
#define LCD_H_

#define LCDPORT         GPIO_PORTB_BASE
#define LCDPORTENABLE   SYSCTL_PERIPH_GPIOB
#define RS              GPIO_PIN_0
#define E               GPIO_PIN_1
#define D4              GPIO_PIN_4
#define D5              GPIO_PIN_5
#define D6              GPIO_PIN_6
#define D7              GPIO_PIN_7


void LCD_ayar(void);
void LCD_komut(unsigned char a);
void LCD_karakteral(unsigned char a);

void LCD_temizle(void);
void LCD_yaz(char *a,int b);
void LCD_asagiyaz(char *a, int b);
void LCD_cursor(char a, char b);

#endif /* LCD_H_ */
