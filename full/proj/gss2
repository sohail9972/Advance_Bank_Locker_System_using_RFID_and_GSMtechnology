#include<reg52.h>
#define display_port P2      //Data pins connected to port 2 on microcontroller
sbit rs = P3^2;  //RS pin connected to pin 2 of port 3
sbit rw = P3^3;  // RW pin connected to pin 3 of port 3
sbit e =  P3^4;  //E pin connected to pin 4 of port 3
int k;
unsigned char str[26];

void GSM_init()            // serial port initialization 
{
    TMOD=0x20;            // Timer 1 selected, Mode 2(8-bit auto-reload mode)
    TH1=0xfd;            // 9600 baudrate
    SCON=0x50;            // Mode 1(8-bit UART), receiving enabled
    TR1=1;                // Start timer
}
void msdelay(unsigned int time)  // Function for creating delay in milliseconds.
{
    unsigned m,n ;
    for(m=0;m<time;m++)    
    for(n=0;n<1275;n++);
}
void lcd_cmd(unsigned char command)  //Function to send command instruction to LCD
{
    display_port = command;
    rs= 0;
    rw=0;
    e=1;
    msdelay(1);
    e=0;
}

void lcd_data(unsigned char disp_data)  //Function to send display data to LCD
{
    display_port = disp_data;
    rs= 1;
    rw=0;
    e=1;
    msdelay(1);
    e=0;
}

 void lcd_init()    //Function to prepare the LCD  and get it ready
{
    lcd_cmd(0x38);  // for using 2 lines and 5X7 matrix of LCD
    msdelay(10);
    lcd_cmd(0x0F);  // turn display ON, cursor blinking
    msdelay(10);
    lcd_cmd(0x01);  //clear screen
    msdelay(10);
    lcd_cmd(0x80);  // bring cursor to beginning of first line
    msdelay(10);
}         
void lcd_string(unsigned char *str)    // Function to display string on LCD
{
    int i=0;
    while(str[i]!='\0')
    {
       lcd_data(str[i]);                  
       i++;
       msdelay(10);
      if(i==15) lcd_cmd(0xc2);                                          
       }
    return; 
}

void GSM_write(unsigned char ch)    // Function to send commands to GSM
{
    SBUF=ch;        // Put byte in SBUF to send to GSM
    while(TI==0);        //wait until the byte trasmission
    TI=0;            //clear TI to send next byte.      
}

 void GSM_read()     // Function to read the response from GSM
 {     
    while(RI==0);   // Wait until the byte received  
    str[k]=SBUF;    //storing byte in str array
    RI=0;           //clear RI to receive next byte
 }

void main()
{        
    k=0;
    lcd_init();                            
    GSM_init();                
    msdelay(200);
    lcd_string("Interfacing GSM with 8051");
    msdelay(200);
    lcd_cmd(0x01);            //    Clear LCD screen
    msdelay(10);                                     
    GSM_write('A');              // Sending 'A' to GSM module
    lcd_data('A');                 
    msdelay(1);
    GSM_write('T');            // Sending 'T' to GSM module
    lcd_data('T');                 
    msdelay(1);
    GSM_write(0x0d);          // Sending carriage return to GSM module            
    msdelay(50);
    while(1)
    {          
        GSM_read();
        if(str[k-1]=='O' && str[k]=='K'){
            lcd_data(0x20);                      // Write 'Space'
            lcd_data(str[k-1]);
            lcd_data(str[k]);
            break; 
        }
        k=k+1;                                            
    }
}
 