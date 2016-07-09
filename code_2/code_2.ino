/*如果避障响应方向不对修改固定值即可如：1600变1400，1400变1600*/
unsigned int distance_Q0, distance_Q1,angle;
/*以下为传感器引脚定义*/
const int CSB_Q = 0, CSB_H = 1, CSB_Z = 2, CSB_Y = 3;
#include<Servo.h>//Arduino Nano 2;3(Pin)
const int AIL_PWM = 2;//中断输入
const int ELE_PWM = 3;//中断输入
const int LED_PIN = 13;//LED灯
unsigned long RC_AIL_PulseStartTicks, RC_ELE_PulseStartTicks;
volatile int RC_AIL, RC_ELE;
unsigned int OUT_AIL, OUT_ELE;
unsigned int AIL_MIN = 1000, AIL_MAX = 2000;
unsigned int ELE_MIN = 1000, ELE_MAX = 2000;
Servo AIL; Servo ELE;

/*********************************/
void RC_AIL_Void()//AIL中断程序
{
  if (digitalRead( AIL_PWM ) == HIGH)
    RC_AIL_PulseStartTicks = micros();
  else
    RC_AIL = micros() - RC_AIL_PulseStartTicks;
}
void RC_ELE_Void()//ELE中断程序
{
  if (digitalRead( ELE_PWM ) == HIGH)
    RC_ELE_PulseStartTicks = micros();
  else
    RC_ELE = micros() - RC_ELE_PulseStartTicks;
}
void setup()
{
  attachInterrupt(0, RC_AIL_Void, CHANGE);
  attachInterrupt(1, RC_ELE_Void, CHANGE);
  AIL.attach(10);
  ELE.attach(11);
  pinMode(AIL_PWM, INPUT);
  pinMode(ELE_PWM, INPUT);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  ADCSRA |=  (1 << ADPS2);
  ADCSRA &=  ~(1 << ADPS1);
  ADCSRA &=  ~(1 << ADPS0);
}
void loop()
{
  OUT_AIL = map(RC_AIL, AIL_MIN, AIL_MAX, 1000, 2000);
  OUT_ELE = map(RC_ELE, ELE_MIN, ELE_MAX, 1000, 2000);
  digitalWrite(LED_PIN, LOW);
//避障部分代码



 
  AIL.writeMicroseconds(OUT_AIL);
  ELE.writeMicroseconds(OUT_ELE);
  // Print();
}

/*void Print()
  {
  Serial.print("INAIL=");
  Serial.print(RC_AIL);
  Serial.print(" INELE=");
  Serial.print(RC_ELE);
  Serial.print(" OUTAIL=");
  Serial.print(OUT_AIL);
  Serial.print(" OUTELE=");
  Serial.print(OUT_ELE);
  Serial.print(" distance_Q=");
  Serial.print(distance_Q);
  Serial.print(" distance_H=");
  Serial.print(distance_H);
  Serial.print(" distance_Z=");
  Serial.print(distance_Z);
  Serial.print(" distance_Y=");
  Serial.print(distance_Y);
  Serial.println();
  }*/
