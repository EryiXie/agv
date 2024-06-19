#include "MeOrion.h"
//#include <Arduino.h>
#include "SoftwareSerial.h"
#include <Wire.h>

MeUSBHost usbhost(PORT_3);
MeEncoderMotor motor1(0x09, SLOT1); 
MeEncoderMotor motor2(0x09, SLOT2); 
MeEncoderMotor motor3(0x08, SLOT1); 
MeEncoderMotor motor4(0x08, SLOT2); 

int moveSpeed = 25;
unsigned char stop_flag=0;

void setup()
{
  usbhost.init(USB1_0);  
  Serial.begin(9600);
  motor1.begin();
  motor2.begin();
  motor3.begin();
  motor4.begin();
}

void loop()
{
  Stop_run();
  control();
}

void control()
{
  if(!usbhost.device_online)
  {
    Serial.print("no device found!\n");
    usbhost.probeDevice();//Device is not online ,initialization   
    delay(100);
  }
  else
  {
    int len = usbhost.host_recv();//Read data length
    parseJoystick(usbhost.RECV_BUFFER);
    delay(5);
  }
}

void parseJoystick(unsigned char * buf)
{
  unsigned char temp2=buf[2];  //Remote control receive data
  unsigned char temp3=buf[3];
  unsigned char temp4=buf[4];

  Serial.print(temp2);
  /*
  if(temp2==128)
  {
    if(temp3==128)  
    {
        stop_flag++;
        if(stop_flag>2)
       {
          Stop_run();    //Release the keys/Stop motor 
          stop_flag=3;
       }    
    }
    if(temp3==0) Forward_run();    //Forward keys (1 keys) 
    if(temp3==255) Backward_rum(); //Backward keys (3 keys)
  }
  if(temp2==255)
  {    
    if(temp3==0)  RightUp_run();     //Forward and Right keys (1 and 2 keys) 
    if(temp3==128)  Right_run();     //Right keys(2 keys)  
    if(temp3==255)  RightDown_run(); //Backward and Right keys(2 and 3 keys)
  }
  if(temp2==0)
  { 
    if(temp3==0)  LeftUp_run();      //Forward and lift keys(1 and 4 keys)   
    if(temp3==128)  Left_run();      //Life keys(4 keys) 
    if(temp3==255)  LeftDown_run();  //Backward and Lift keys(3 and 4 keys)
  }
  
   if(temp4==79)      //Fork keys(8 keys)
  {
     Speed_down();   //Speed Decrease
  }
  else if(temp4==31) //Triangle keys(7 keys)
  {
     Speed_up();     //Speed up
  }
  else if(temp4==143) //Square keys(5 keys)
  {
     TurnLeft_run();  //Spot Turn To Left
     stop_flag=0;
  }
  else if(temp4==47) //Round keys(6 keys)
  { 
     TurnRight_run();//Spot Turn To Right
     stop_flag=0;
  }  
  */
}



// ALL MOVES
void Forward_run() 
{  
  motor1.runSpeed(-moveSpeed);
  motor2.runSpeed(moveSpeed);
  motor3.runSpeed(-moveSpeed);
  motor4.runSpeed(moveSpeed);
}
void Backward_run() 
{
  motor1.runSpeed(moveSpeed);
  motor2.runSpeed(-moveSpeed);
  motor3.runSpeed(moveSpeed);
  motor4.runSpeed(-moveSpeed);
}
void Right_run()  
{
  motor1.runSpeed(-moveSpeed);
  motor2.runSpeed(-moveSpeed);
  motor3.runSpeed(moveSpeed);
  motor4.runSpeed(moveSpeed);
}
void Left_run()  
{
  motor1.runSpeed(moveSpeed);
  motor2.runSpeed(moveSpeed);
  motor3.runSpeed(-moveSpeed);
  motor4.runSpeed(-moveSpeed);
}
void RightDown_run()
{
  motor1.runSpeed(0);
  motor2.runSpeed(-moveSpeed);
  motor3.runSpeed(moveSpeed);
  motor4.runSpeed(0);
}
void RightUp_run()
{
  motor1.runSpeed(-moveSpeed);
  motor2.runSpeed(0);
  motor3.runSpeed(0);
  motor4.runSpeed(moveSpeed);
}
void LeftDown_run()
{
  motor1.runSpeed(moveSpeed);
  motor2.runSpeed(0);
  motor3.runSpeed(0);
  motor4.runSpeed(-moveSpeed);
}
void LeftUp_run()
{
  motor1.runSpeed(0);
  motor2.runSpeed(moveSpeed);
  motor3.runSpeed(-moveSpeed);
  motor4.runSpeed(0);
}
void TurnRight_run()
{
  motor1.runSpeed(-moveSpeed);
  motor2.runSpeed(-moveSpeed);
  motor3.runSpeed(-moveSpeed);
  motor4.runSpeed(-moveSpeed);
}
void TurnLeft_run()
{
  motor1.runSpeed(moveSpeed);
  motor2.runSpeed(moveSpeed);
  motor3.runSpeed(moveSpeed);
  motor4.runSpeed(moveSpeed);
}

void Speed_up()
{
  moveSpeed=moveSpeed+3;
  if(moveSpeed>50)  moveSpeed=50;
}
void Speed_down()
{
   moveSpeed=moveSpeed-3;
  if(moveSpeed<0)  moveSpeed=0;
}
void Stop_run()
{
  motor1.runSpeed(0);
  motor2.runSpeed(0);
  motor3.runSpeed(0);
  motor4.runSpeed(0);
}
