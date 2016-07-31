/*
   此版本为PPM输入版本。
  PPM 输入 D2
  PWM 输入 D2 D4 D7 D8 D12 D13
  切换方式，拨码开关 接A0 电阻值判断。
  输出方式：PWM
  输出引脚：D3 D5 D6 D9 D10 D11
  超声波选用：串口超声波含有方位角
  数量：4
  连接端口 ：RX0 RX1

  RC_[1] = AIL  副翼
  RC_[2] = ELE  升降
  RC_[3] = THR  油门
  RC_[4] = RUD  方向
  RC_[5] = GRY  起落架
  RC_[6] = PIT  螺距
*/
/*PPM解码定义部分*/
const char PPM_INT = 2;//PPM输入引脚定义
unsigned long PPM_HOEL_TIME0;
unsigned long PPM_HOEL_TIME1;
int PPM_ASS = 0;
/***************************/
String comdata = "";
#include<Servo.h>//舵机函数
unsigned int DISTANCE_[4];//超声波距离数据
unsigned int RC_[7];//遥控待输出数据
int OBS_NUMBER[4] = {0x60, 0x61, 0x62, 0x63};//超声波通信地址定义
Servo AIL, ELE, THR, RUD, GRY, PIT;

void setup()
{
  delay(200);//延时等系统供电稳定

  pinMode(PPM_INT, INPUT);//PPM输入引脚
  attachInterrupt(PPM_INT, PPM, CHANGE);//中断定义

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
  PPM();
  if (RC_[6] > 1500) {//避障开启
    for (int i = 1; i > 4 ; i++)
    {
      DISTANCE_[i] = SERIAL_OBS(OBS_NUMBER[i]);
    }
    ALGORITHM();
    PWM_OUT();
  }
  else {//避障关闭
    PWM_OUT();
  }
}
void PWM_OUT() {
  AIL.writeMicroseconds(RC_[1]);
  ELE.writeMicroseconds(RC_[2]);
  THR.writeMicroseconds(RC_[3]);
  RUD.writeMicroseconds(RC_[4]);
  GRY.writeMicroseconds(RC_[5]);
  PIT.writeMicroseconds(RC_[6]);
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

void ALGORITHM() {

}

/*PPM信号解析*/
void PPM() {
  if (digitalRead(PPM_INT) == HIGH)
    PPM_HOEL_TIME0 = micros();
  else {
    PPM_HOEL_TIME1 = micros() - PPM_HOEL_TIME0;
    PPM_ASS = ++PPM_ASS;
    if (PPM_ASS == 8) {
      PPM_ASS = 1;
    }
    if (PPM_HOEL_TIME1 > 3000) {
      PPM_ASS = 7;
    }
    if (PPM_ASS == 1) {
      RC_[1] = PPM_HOEL_TIME1;
    }
    if (PPM_ASS == 2) {
      RC_[2] = PPM_HOEL_TIME1;
    }
    if (PPM_ASS == 3) {
      RC_[3] = PPM_HOEL_TIME1;
    }
    if (PPM_ASS == 4) {
      RC_[4] = PPM_HOEL_TIME1;
    }
    if (PPM_ASS == 5) {
      RC_[5] = PPM_HOEL_TIME1;
    }
    if (PPM_ASS == 6) {
      RC_[6] = PPM_HOEL_TIME1;
    }
  }
}
