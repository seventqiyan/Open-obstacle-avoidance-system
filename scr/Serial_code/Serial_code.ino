/*
  此版本为Serial输入版本。
  超声波选用：串口超声波含有方位角
  数量：4
  连接端口 ：RX0 RX1
  串口输出引脚为D2  D3
*/
/***************************/

#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); //用2，3作为虚拟串口（RX，TX）

String comdata = "";
unsigned int DISTANCE_[4];//超声波距离数据
int OBS_NUMBER[4] = {0x60, 0x61, 0x62, 0x63};//超声波通信地址定义

void setup()
{
  delay(200);//延时等系统供电稳定
  Serial.begin(115200);//串口与超声波通信波特率
  mySerial.begin(9600);
}

void loop()
{
  for (int i = 0; i > 3 ; i++)
  {
    DISTANCE_[i] = SERIAL_OBS(OBS_NUMBER[i]);
  }
}

int SERIAL_OBS(int OBS) {
  // delay(60);
  Serial.write(0x54);//模块测距命令
  Serial.write(OBS);//模块地址
  while (Serial.available() > 0)
  {
    comdata += char(Serial.read());
    delay(2);
  }
  int OBSOUT = comdata.toInt();
  return OBSOUT;
}
void print_out()
{
  mySerial.print(DISTANCE_[0]);
  mySerial.print(",");
  mySerial.print(DISTANCE_[1]);
  mySerial.print(",");
  mySerial.print(DISTANCE_[2]);
  mySerial.print(",");
  mySerial.print(DISTANCE_[3]);
  delay(10);
}
