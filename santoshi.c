#include<p18f4580.h>
#define RS PORTCbits.RC0
#define E PORTCbits.RC1
#define IN1 PORTCbits.RC3
#define IN2 PORTCbits.RC4
#define ENA PORTCbits.RC2
void delay(int a)
{
int i,j;
for(i=0;i<a;i++)
for(j=0;j<100;j++);
}
void pwm_delay0(void)
{
T2CON=0X01;
CCP1CON=0x0C; /* Set the PWM duty cycle by writing to the CCPR1L register and CCP1CON<5:4>b*/
CCPR1L= 0; /* Set the duty cycle period by writing to the CCPR1L register */
T2CONbits.T2CKPS1=0; /* Timer2 clock prescalar select bit */
T2CONbits.T2CKPS0=1;
T2CONbits.TMR2ON=1; /* Timer2 ON bit */
PR2=0;
}
void pwm_delay25(void)
{
T2CON=0X01;
CCP1CON=0x0C; /* Set the PWM duty cycle by writing to the CCPR1L register and CCP1CON<5:4>b*/
CCPR1L= 16; /* Set the duty cycle period by writing to the CCPR1L register */
T2CONbits.T2CKPS1=0; /* Timer2 clock prescalar select bit */
T2CONbits.T2CKPS0=1;
T2CONbits.TMR2ON=1; /* Timer2 ON bit */
PR2=64;
}
void pwm_delay50(void)
{
T2CON=0X01;
CCP1CON=0x0C; /* Set the PWM duty cycle by writing to the CCPR1L register and CCP1CON<5:4>b*/
CCPR1L= 65; /* Set the duty cycle period by writing to the CCPR1L register */
T2CONbits.T2CKPS1=0; /* Timer2 clock prescalar select bit */
T2CONbits.T2CKPS0=1;
T2CONbits.TMR2ON=1; /* Timer2 ON bit */
PR2=128;
}
void pwm_delay75(void)
{
T2CON=0X01;
CCP1CON=0x0C; /* Set the PWM duty cycle by writing to the CCPR1L register and CCP1CON<5:4>b*/
CCPR1L=144; /* Set the duty cycle period by writing to the CCPR1L register */
T2CONbits.T2CKPS1=0; /* Timer2 clock prescalar select bit */
T2CONbits.T2CKPS0=1;
T2CONbits.TMR2ON=1; /* Timer2 ON bit */
PR2=191;
}
void pwm_delay100(void)
{
T2CON=0X01;
CCP1CON=0x0C; /* Set the PWM duty cycle by writing to the CCPR1L register and CCP1CON<5:4>b*/
CCPR1L= 244; /* Set the duty cycle period by writing to the CCPR1L register */
T2CONbits.T2CKPS1=0; /* Timer2 clock prescalar select bit */
T2CONbits.T2CKPS0=1;
T2CONbits.TMR2ON=1; /* Timer2 ON bit */
PR2=249;
}
void main()
{
int adc_val,i;
TRISAbits.TRISA0=1;
TRISC=0x00;
ADCON0=0x01;
ADCON1=0x0D;
ADCON2=0x80;
while(1)
{
ADCON0bits.GO=1;
while(ADCON0bits.GO==1);
adc_val=ADRESH;
adc_val=adc_val<<8;
adc_val=adc_val+ADRESL;
if(adc_val==0)
{
IN1=0;
pwm_delay0();//less speed of motor DC=24
IN2=0;
}
if(adc_val>0 && adc_val<=255)
{
IN1=1;
pwm_delay25();
IN2=0;
}
if(adc_val>255 && adc_val<=512)
{
IN1=1;
pwm_delay50();//more speed of motor DC=97
IN2=0;
}
if(adc_val>512 && adc_val<=767)
{
IN1=1;
pwm_delay75();
IN2=0;
}
if(adc_val>767 && adc_val<=1023)
{
IN1=1;
pwm_delay100();
IN2=0;
}
}
}