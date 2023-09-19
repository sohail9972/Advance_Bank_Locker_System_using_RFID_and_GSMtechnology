
//CODE of lcd interfacing with 8051 microcontroller
#include<reg51.h>

void delay(unsigned int i);
void lcd_cmd(unsigned char a);
void lcd_data(unsigned char b);
void lcd_init(void);
void lcd_str(unsigned char *str);
void sendser_char(unsigned char b);
void sendser_str(unsigned char *str);
void sms_send(void);
void delay_ms(unsigned int i);
void clear(void);
void gsm_link(void);
sbit rs=P2^0;
sbit en=P2^1;
sfr ldata=0x90;//port1 
sbit L1=P2^2;
unsigned char a[100],mesg_rec;
unsigned int i;
void ser_int() interrupt 4
{
if(RI==1)
{
RI=0;
a[i]=SBUF;
	i++;
mesg_rec=1;
}

if(TI==1)
{

TI=0;
}


}
void main()

{
	TMOD=0x20;//timer1 mode2 -auto reload mode
	TH1=0xfd;//9600 baud rate
	SCON=0x50;//8bit data ,1start bit,1stop bit
	IE=0x90;//EA=1,ES=1...
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
gsm_link();
	sms_send();
	while(1)

{
	i=0;
	if(mesg_rec==1)
	{
//+CMT
		if(a[2]=='+'&&a[3]=='C'&&a[4]=='M'&&a[5]=='T')
		{
		lcd_cmd(0x01);
		lcd_cmd(0x80);
    lcd_str("   MSG RECIVED   ");
			if(a[49]=='L'&&a[50]=='1'&&a[51]=='O'&&a[52]=='N'&&a[52]=='N')
			{
				L1=1;
				lcd_cmd(0x01);
		lcd_cmd(0x80);
    lcd_str("   LI ONN   ");
				i=0;
				clear();
			
			}
			else if(a[49]=='L'&&a[50]=='1'&&a[51]=='O'&&a[52]=='F'&&a[52]=='F')
			{
				L1=0;
				lcd_cmd(0x01);
		lcd_cmd(0x80);
    lcd_str("   LI OFF   ");
				i=0;
				clear();
			
			}
			else
			{
			lcd_cmd(0x01);
		lcd_cmd(0x80);
    lcd_str("   IN CORRECT TEXT   ");
				i=0;
				clear();
			
			}
		
		
		}
	
	
	}
		

}

}
void sms_send(void)
{
	lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_str(" SMS SENDING");
	delay_ms(650);
sendser_str("AT+CMGS=");
sendser_char(0x22);//"
	sendser_str("+919999999999");
	sendser_char(0x22);//"
	sendser_char(0x0d);
	sendser_str("YT Training Institute");
		sendser_char(0x1a);//sms sent
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_str(" SMS SENT");
	delay_ms(650);
}
void gsm_link(void)
{
	loop:
	i=0;
	sendser_str("AT");
sendser_char(0x0d);
			lcd_cmd(0x01);
		lcd_cmd(0x80);
	if(a[2]=='O'&&a[3]=='K')
	{
	lcd_str(" GSM LINK IS UP");
	
	}
	else
	{
		lcd_str(" GSM CHECKING");
	goto loop;
	}
	 clear();
delay_ms(650);
	
	loop1:
	i=0;
	sendser_str("AT+CMGF=1");
sendser_char(0x0d);
			lcd_cmd(0x01);
		lcd_cmd(0x80);
	if(a[2]=='O'&&a[3]=='K')
	{
	lcd_str(" GSM TEXT MODE");
	
	}
	else
	{
		lcd_str(" GSM NOT IN TEXT");
	goto loop1;
	}
		 clear();
delay_ms(650);

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
void delay_ms(unsigned int i)
{
unsigned int j,k;
	for(j=0;j<i;j++)
	for(k=0;k<1275;k++);
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
	a[i]=0;
	
	}
}