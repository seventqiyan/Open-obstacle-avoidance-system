/*
  PPM 输入 D2
  PWM 输入 D2 D4 D7 D8 D12 D13
  切换方式，拨码开关 接A0 电阻值判断。
  输出方式：PWM
  输出引脚：D3 D5 D6 D9 D10 D11
  超声波选用：串口三头超声波含有方位角
  数量：4
  连接端口 ：RX0 RX1
  
  RC_[1] = AIL  副翼
  RC_[2] = ELE  升降
  RC_[3] = THR  油门
  RC_[4] = RUD  方向
  RC_[5] = GRY  起落架
  RC_[6] = PIT  螺距
*/
const int SWITCH = A0;
unsigned int A
#include<Servo.h>//舵机函数
unsigned int DISTANCE_[4];//超声波距离数据
unsigned int RC_[6];//遥控解析待输出数据
Servo AIL, ELE, THR, RUD, GRY, PIT;

void setup()
{
  delay(50);
 // pinMode(SWITCH , INPUT);

  AIL.attach(3);//输出引脚定义
  ELE.attach(5);
  THR.attach(6);
  RUD.attach(9);
  GRY.attach(10);
  PIT.attach(11);
  Serial.begin(115200);//串口与超声波通信波特率

}

void loop()
{

}
void PWM_OUT()
{
  AIL.writeMicroseconds(RC_[1]);
  ELE.writeMicroseconds(RC_[2]);
  THR.writeMicroseconds(RC_[3]);
  RUD.writeMicroseconds(RC_[4]);
  GRY.writeMicroseconds(RC_[5]);
  PIT.writeMicroseconds(RC_[6]);
}
void Serial_obs()
{

}
void PPM()
{

}
