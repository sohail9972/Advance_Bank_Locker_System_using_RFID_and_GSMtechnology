#include<reg51.h>
#include<string.h>
void delay(unsigned int i);
void lcd_cmd(unsigned char a);
void lcd_data(unsigned char b);
void lcd_init(void);
void lcd_str(unsigned char *str);
void sendser_char(unsigned char b);
void sendser_str(unsigned char *str);
sbit rs=P2^0;
sbit en=P2^1;
unsigned int i;
unsigned char a[100];
sfr ldata=0x90;//port1 
void clear(void);
void main()

{

	TMOD=0x20;//timer1 mode2 -auto reload mode
	TH1=0xfd;//9600 baud rate
	SCON=0x50;//8bit data ,1start bit,1stop bit
	TR1=1;
lcd_init();
	lcd_str("   WELCOME TO   ");
	lcd_cmd(0xc0);
	lcd_str("   MY PROJECT   ");
	
	delay(65000);
		lcd_cmd(0x01);
		lcd_cmd(0x80);
lcd_str("   YT TRAINING   ");
	lcd_cmd(0xc0);
	lcd_str("   INSTITUTE   ");
	delay(65000);
	while(1)

{
			lcd_cmd(0x01);
		lcd_cmd(0x80);
lcd_str("   Waiting For    ");
	lcd_cmd(0xc0);
	lcd_str("   RFID Tag   ");
	for(i=0;i<10;i++)
	{
	while(RI==0);//suc 1 char recived 
		RI=0;
		a[i]=SBUF;//a[0]='1',a[1]='0'
	
	
	}
	a[10]='\0';
	if(0==strcmp("10003B0CA7",a))
	{
				lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_str(" EMPLOYEE NO : 1");
	lcd_cmd(0xc0);
	lcd_str(a);
		delay(65000);
		clear();
	}
		else if(0==strcmp("10003B0CAE",a))
	{
				lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_str(" EMPLOYEE NO : 2");
	lcd_cmd(0xc0);
	lcd_str(a);
		delay(65000);
				clear();
	}
	else
	{
					lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_str(" INVALID TAG");
	lcd_cmd(0xc0);
	lcd_str(a);
		delay(65000);
			clear();
	}

}

}

void lcd_init()
{
lcd_cmd(0x38);
	lcd_cmd(0x0c);
	lcd_cmd(0x01);
	lcd_cmd(0x80);


}
void delay(unsigned int i)
{
unsigned int j;
	for(j=0;j<i;j++);
}

void lcd_cmd(unsigned char a)
{
  rs=0;//cmd 
	ldata=a;
	en=1;
	delay(5);
	en=0;
	delay(5);
}
void lcd_data(unsigned char b)
{
  rs=1;//data 
	ldata=b;
	en=1;
	delay(5);
	en=0;
	delay(5);
}
void lcd_str(unsigned char *str)
{
while(*str)
{
	lcd_data(*str++);
}

}


void sendser_char(unsigned char b)
{
SBUF=b;
	while(TI==0);
	TI=0;
}


void sendser_str(unsigned char *str)
{
while(*str)
{
	sendser_char(*str++);
}

}
void clear(void)
{

unsigned int i;
	for(i=0;i<100;i++)
	{
	a[i]='\0';
	
	}
}
