//控制端

int value = 0 ;
int pwm0 = 0 ;
int Power; //电
int DW1,DW2,DW3;
int XNAdd = 0;
int XNSub = 0;
int Auto_Speed = 0;
int Keep_Speed = 0;

void setup(){
  pinMode(13,OUTPUT);
  digitalWrite(13, HIGH);
  Serial.begin(9600);
  analogReference(DEFAULT);
  
  pinMode(12,OUTPUT);//328P工作指示灯
  digitalWrite(12, HIGH);

  pinMode(7,INPUT);
    pinMode(9,INPUT);
      pinMode(8,INPUT);



  
/*
  pinMode(2,OUTPUT);
  digitalWrite(2, HIGH);
  pinMode(4,OUTPUT);
  digitalWrite(4, HIGH);

  pinMode(6,OUTPUT);
  digitalWrite(6, HIGH);
  pinMode(10,OUTPUT);
  digitalWrite(10, HIGH);
  */
}

void loop(){
  Power = analogRead(1);
  value = analogRead(2);
  //pwm0 = value;
  DW1 = digitalRead(7);

  DW2 = digitalRead(8);

  DW3 = digitalRead(9);

  
  if (DW1 == HIGH)//默认状态
  {
    pwm0 = 2965;
    Serial.println(pwm0);
  }
  
  if (DW2 == HIGH)
  {
    pwm0 = map(value,400,1023,2900,3250);
    Serial.println(pwm0);
  }
  
  if (DW3 == HIGH)
  {
    
    if((value<=650)&&(Auto_Speed==0))//停止模式
    {
      pwm0 = 2965;//停止值
    }
    
   if((value>650)&&(value<980)&&(Auto_Speed==0))//启动模式
   {
      pwm0 = 3145;//启动值
   }
   
   if(value>=999)//加速模式
   {
      Auto_Speed=1;
      Keep_Speed=1;
        if(XNAdd==1)
        {
            pwm0 = pwm0+1;
            XNAdd = 0;
        }
        else
        {
            XNAdd = XNAdd+1;
        }
        if(pwm0>3155)//后半段超快加速
        {
          pwm0 = pwm0+1;
        }
        if(pwm0>3400)//后半段超快加速
        {
          pwm0 = pwm0+2;
        }
   }

   if((Auto_Speed==1)&&(Keep_Speed==1)&&(value>650)&&(value<985))//匀速
   {
    pwm0=pwm0;
   }



   
   if((Auto_Speed==1)&&(value<680))//减速
   {
    Keep_Speed=0;
    if(pwm0<3165)
    {
      Auto_Speed=0;
    }
    
    if(pwm0>3250)
    {
      pwm0 = pwm0-5;
    }
    
    if(pwm0>3500)
    {
      pwm0 = pwm0-3;
    }
    
    if(pwm0<=3250)
    {
        if(XNSub==1)
        {
            pwm0 = pwm0-8;
            XNSub = 0;
        }
        else
        {
            XNSub = XNSub+1;
        }
    }
    
   }
   if(value<320)
   {
    pwm0=2965;
   }
   if(value<15)
   {
    pwm0=2860;
   }

  
   
   Serial.println(pwm0);
   
    //pwm0 = map(value,400,1023,2820,3600);
   //Serial.println(value);

    //3120 启动电压
  }
  
  
  //Serial.println(Power);

  
  if(Power<780)//低电量3.759V=0.0048828125*770
  {
    digitalWrite(13, HIGH);
  }
  else
  {
    digitalWrite(13, LOW);
  }
  
  delay(150);
}
