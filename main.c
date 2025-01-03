#include "stdint.h"
#include "stdbool.h"
#include "driverlib/sysctl.h"
#include "inc/tm4c123gh6pm.h"
#include "lcd.h"

void clockayar();

int main(void) {

    clockayar();
    LCD_ayar();
                            // For other functions, check out lcd.c
        while (1) {

            LCD_yaz("ileri-mikro",0); // "0" For print on first line

            SysCtlDelay(30000000);

            LCD_temizle();

            LCD_asagiyaz("15152211",1); // "1" For print on first line

            SysCtlDelay(30000000);

            LCD_yaz("emrebstc",0);

            SysCtlDelay(30000000);

            LCD_temizle();

        }


}

void clockayar(){
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);
}
