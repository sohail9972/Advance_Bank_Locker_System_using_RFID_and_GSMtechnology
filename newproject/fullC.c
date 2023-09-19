//CODE of lcd interfacing with 8051 microcontroller
#include<reg51.h>
#include<string.h>
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

void keypad();
sbit re=P2^0;		//gsm receive
sbit tr=P2^1;		//gsm transmitter
sbit rs=P3^2;
sbit en=P3^3;
sbit m11=P3^4;
sbit m12=P3^5;
sfr ldata=0x90;//port1 
sbit r1=P2^0;
sbit r2=P2^1;
sbit r3=P2^2;
sbit r4=P2^3;
sbit c1=P2^4;
sbit c2=P2^5;
sbit c3=P2^6;

unsigned char a[60],mesg_rec,pwd[5],ps,pas[5];
unsigned int i=0,atempt=0,iJ=0,s=0;
unsigned int j,trigg,testing;
void ser_int() interrupt 4
{
if(RI==1)
{

a[i]=SBUF;
i++;
RI=0;
if (strlen(a)==52){
mesg_rec=1;
}
}

if(TI==1)
{

TI=0;
}


}
void main()

{

	m11=0;
	m12=0;
	TMOD=0x20;//timer1 mode2 -auto reload mode
	TH1=0xfd;//9600 baud rate
	SCON=0x50;//8bit data ,1start bit,1stop bit
	IE=0x90;//EA=1,ES=1...
	TR1=1;
	trigg=0;
	
	lcd_init();
	lcd_str("   WELCOME TO   ");
	lcd_cmd(0xc0);
	lcd_str("   OUR PROJECT   ");
	delay(65000);
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	lcd_str("   BANK LOCKER    ");
	lcd_cmd(0xc0);
	lcd_str("   SECURITY SYSTEM   ");
	delay(65000);
	gsm_link();
	testing=1;
	while(testing==1)
{	
	testing=0;
	
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	lcd_str("   Waiting For    ");
	lcd_cmd(0xc0);
	lcd_str("   RFID Tag   ");
	
	for(iJ=0;iJ<10;iJ++)
	{
		while(RI==0);
		RI=0;//suc 1char recived 
		delay(1000);
		a[iJ]=SBUF;//a[0]='1',a[1]='0'
		
	}
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	lcd_str("   reading done    ");
	delay(65000);
	a[10]='\0';
	mesg_rec=0;
	if(0==strcmp("10003B0CA7",a))
	{
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_str(" WELCOME USER 1");
		trigg=1;
		lcd_cmd(0xc0);
		lcd_str(a);
		delay(65000);
		clear();
	}
	else if(0==strcmp("10003B0CAE",a))
	{
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_str(" WELCOME USER 2");
		trigg=1;
		lcd_cmd(0xc0);
		lcd_str(a);
		delay(65000);
				clear();
	}
	else
	{
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_str(" USER NOT FOUND ");
		lcd_cmd(0xc0);
		lcd_str(a);
		delay(65000);
		clear();
	}

	if (trigg==1)
	{
		clear(); //edited
		sms_send();
		delay(100);
		i=0;
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	lcd_str(" RECIEVING    ");
		lcd_cmd(0xc0);
	lcd_str("   PASSWORD   ");
		while(RI==0);
		
			delay(65000);
		if(mesg_rec==1)
	{
		//+CMT
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_str("   PASSWORD   ");
		lcd_cmd(0xc0);
		lcd_str("   RECIEVED   ");
		delay(65000);
		
		if(a[2]=='+'&&a[3]=='C'&&a[4]=='M'&&a[5]=='T')  //ok+CMTuewhekjhjfwkfjfghtredfghjuytghjhgfdghjygdfK1234
		{
			
		j=0;
		for(i =49 ; i<53;i++)
		{
			
			pas[j]=a[i];
			j++;
		}
		pas[4]='\0';
		}
	}
	while (atempt<3){
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	lcd_str(" ENTER PASSWORD   ");
	lcd_cmd(0xc0);
	for(ps=0;ps<5;ps++)
	{
	pwd[ps]='\0';

	}
	ps=0;
	while(ps<4)//"1234\0"
	{
	keypad();
	
	}
	/*pwd[0]='1';
	pwd[1]='2';
	pwd[2]='3';
	pwd[3]='4';
	pwd[4]='\0';*/
	if(0==strcmp(pwd,pas))
		{
		
		delay(65000);
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_str("ENTERED PASSWORD");
		lcd_cmd(0xc0);
		lcd_str("   IS CORRECT   ");
		delay(65000);delay(65000);
			//delay_ms(500);
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_str("   LOCKER IS    ");
		lcd_cmd(0xc0);
		lcd_str("    OPENING     ");
		m11=1;
		m12=0;
		delay(65000);delay(65000);
		//delay_ms(500);
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_str(" LOCKER OPENED  ");
		lcd_cmd(0xc0);
		lcd_str("                ");
		s=1;
		sms_send();
		
		m11=0;
		m12=0;
		//delay(65000);delay(65000);
		delay_ms(500);
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_str(" LOCKER CLOSING ");
		lcd_cmd(0xc0);
		lcd_str("                ");
		m11=0;
		m12=1;
		delay_ms(1000);			
		lcd_cmd(0x80);
		lcd_str(" LOCKER CLOSED  ");
		lcd_cmd(0xc0);
		lcd_str("                ");
		m11=0;
		m12=0;
		//delay(65000);delay(65000);
		delay_ms(500);
		break;
		}
		else
		{
				
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_str("ENTERED PASSWORD");
		lcd_cmd(0xc0);
		lcd_str(" IS INCORRECT   ");
			lcd_cmd(0xc0);
			lcd_str(pas);
		//delay(65000);delay(65000);
			delay_ms(500);
		atempt+=1;
		}
		if (atempt==3){
			lcd_cmd(0x01);
			lcd_cmd(0x80);
			lcd_str("multiple invalid");
			lcd_cmd(0xc0);
			lcd_str(" login attempts ");
			sms_send();
			
	}
}
	
	}
}
}

void keypad(void)
{

		delay(65000);
		c1=c2=c3=1;
		r1=r2=r3=r4=0;
		if(c1==0)//c1 is pressed 
		{
			r1=r2=r3=r4=1;
			c1=c2=c3=0;
		  if(r1==0)//r1 is pressed 
			{
			lcd_data('1');pwd[ps]='1';ps++; //pwd[0]='1',pwd[1]='2',pwd[2]='3',pwd[3]='4'
			}
			if(r2==0)//r2 is pressed 
			{
			lcd_data('4');pwd[ps]='4';ps++;
			}
		  if(r3==0)//r1 is pressed 
			{
			lcd_data('7');pwd[ps]='7';ps++; 
				}
			if(r4==0)//r2 is pressed 
			{
			lcd_data('*');pwd[ps]='*';ps++; 
			}
		}
				else if(c2==0)//c1 is pressed 
		{
			r1=r2=r3=r4=1;
			c1=c2=c3=0;
		  if(r1==0)//r1 is pressed 
			{
			lcd_data('2');pwd[ps]='2';ps++; 
			}
			if(r2==0)//r2 is pressed 
			{
			lcd_data('5');pwd[ps]='5';ps++; 
			}
		  if(r3==0)//r1 is pressed 
			{
			lcd_data('8');pwd[ps]='8';ps++; 
			}
			if(r4==0)//r2 is pressed 
			{
			lcd_data('0');pwd[ps]='0';ps++;
			}				
		}
		
				else if(c3==0)//c1 is pressed 
		{
			r1=r2=r3=r4=1;
			c1=c2=c3=0;
		  if(r1==0)//r1 is pressed 
			{
			lcd_data('3');pwd[ps]='3';ps++;
			}				
			if(r2==0)//r2 is pressed 
			{
			lcd_data('6');pwd[ps]='6';ps++; 
			}
		  if(r3==0)//r1 is pressed 
			{
			lcd_data('9');pwd[ps]='9';ps++;
			}
			if(r4==0)//r2 is pressed 
			{
			lcd_data('#');pwd[ps]='#';ps++; 
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
	if(s==1)
	{
	sendser_str("BANK LOCKER IS OPENED SUCCESSFULLY");
	}
	if (atempt==3){
	sendser_str("YOUR LOCKER HAD MULTIPLE ACCESS ATEMPTS");
	}
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
	lcd_str(a);
	sendser_str(a);
	delay_ms(100);
	if(a[0]=='O'&& a[1]=='K')
	{
		lcd_cmd(0x01);
	lcd_cmd(0x80);
	lcd_str(" GSM LINK IS UP ");
	}
	else
	{
		lcd_str("  GSM CHECKING  ");
		goto loop;
	}
	clear();
	delay_ms(200);
	
	loop1:
	i=0;
	sendser_str("AT+CMGF=1");
	sendser_char(0x0d);
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	delay_ms(100);
	if(a[0]=='O'&&a[1]=='K')
	{
	lcd_str("  GSM TEXT MODE ");
	
	}
	else
	{
		lcd_str("GSM NOT IN TEXT ");
	goto loop1;
	}
		 clear();
delay_ms(650);

}

void lcd_init()
{
	lcd_cmd(0x38);
	lcd_cmd(0x0C);
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
  rs=1; 
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
	for(i=0;i<60;i++)
	{
	a[i]=0;
	
	}
}