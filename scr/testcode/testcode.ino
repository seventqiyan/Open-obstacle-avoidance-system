int PPM = 2;
unsigned long  asshoeltime;
unsigned long  asshoeltime2;
int ass =0;
int C1=0;
int C2=0;
int C3=0;
int C4=0;
int C5=0;
int C6=0;

void setup()
{
   Serial.begin(9600);
   pinMode(PPM, INPUT);
   attachInterrupt(0, fuck, CHANGE); 
}

void fuck() {
  
   if (digitalRead(PPM) == HIGH)
                asshoeltime = micros();   
  else{
  
  asshoeltime2 = micros() - asshoeltime;
  ass=++ass;
    if (ass==8){
    ass=1;
  }
    if (asshoeltime2>3000){
    ass=7;
   }
   if (ass==1){
     C1=asshoeltime2;
   }
   if (ass==2){
     C2=asshoeltime2;
   }     
   if (ass==3){
     C3=asshoeltime2;
   }
   if (ass==4){
     C4=asshoeltime2;
   } 
   if (ass==5){
     C5=asshoeltime2;
   } 
   if (ass==6){
     C6=asshoeltime2;
   } 
  }
}
