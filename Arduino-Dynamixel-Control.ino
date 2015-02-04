#include <SoftwareSerial.h>

const int rxpin = 2;
const int txpin = 3;
SoftwareSerial Serial_AX(rxpin, txpin);

int pose;

void setup()
{
  
  Serial.begin(1000000);
  Serial_AX.begin(9600);
  
  Dxl_Setup();
  
}

void loop()
{
  Dxl_Control(1, 0);
  Dxl_Control(2, 0);
  Dxl_Control(3, 0);
  Dxl_Control(4, 0);  
  Dxl_Control(5, 0);
  Dxl_Control(6, 0);
  delay(1000);
  Dxl_Control(1, 1000);
  Dxl_Control(2, 1000);
  Dxl_Control(3, 1000);
  Dxl_Control(4, 1000);  
  Dxl_Control(5, 1000);
  Dxl_Control(6, 1000);
  delay(1000);
}

void Dxl_Control(unsigned char ID, unsigned int Angle)
{
  unsigned char Check_Sum, Header=0xFF; 
   
  Serial.write(Header); 
  Serial.write(Header);
  Serial.write(ID);
  Serial.write(0x05);
  Serial.write(0x03);
  Serial.write(0x1E);
  Serial.write(Angle);
  Serial.write(Angle>>8);
  Check_Sum = ~( ID + 0x05 + 0x03 + 0x1E + Angle + (Angle>>8));
  Serial.write(Check_Sum);
}

void Dxl_Setup(void)
{
  char dxl_min=1;
  char dxl_max=6;
  
  for(dxl_min;dxl_min<=dxl_max;dxl_min++)
  {
    Dxl_Control(dxl_min, 512);
    delay(200);
  }
  delay(2000);
}

void Dxl_Omni(int x, int y, int z)
{
  int omni_x = x+y+z;
  int omni_y = x+y+z;
  int omni_z = x+y+z;
  
  Dxl_Control(1, 512-omni_x);
  Dxl_Control(2, 512+omni_x);
  Dxl_Control(3, 512+omni_y);
  Dxl_Control(4, 512-omni_y);
  Dxl_Control(5, 512-omni_z);
  Dxl_Control(6, 512+omni_z);
  delay(1000);
}
