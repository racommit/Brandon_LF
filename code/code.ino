//int s2,s3,s5,in1,in2,in3,in4,enA,enB;
//int s1;

//sensor
int s1 = A0;
int s2 = A1;
int s3 = A2;
int s4 = A3;
int s5 = A4;
int s6 = A5;
int s7 = 4;

// pembacaan sensor
int kiri2,kiri1,tengah,kanan1,kanan2, klik, near;


int tahan1 = 0;

// menu
int menu = 1;
int tekan = 0;
bool mulai = false;

//motor driver
int in1 = 12; //ban kanan
int in2 = 13;
int enA = 11;

int in3 = 9;  //ban kiri
int in4 = 8;
int enB = 10;

int led=2;
int led1=3;
int led2=6;
int led3=7;

int speedT = 1000;
int speedR = 500;
int bagi = 8;
int pwma;
int pwmb;



void setup() {
  // put your setup code here, to run once:
//  sensor
  pinMode(s1,INPUT);
  pinMode(s2,INPUT);
  pinMode(s3,INPUT);
  pinMode(s4,INPUT);
  pinMode(s5,INPUT);
  pinMode(s6,INPUT);
  pinMode(s7,INPUT);


// Motor driver
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(enA,OUTPUT);

  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(enB,OUTPUT);

//led
  pinMode(led,OUTPUT);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);

//strobo
  strobo();
  strobo1();


//tes motor 
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  analogWrite(enA,65);

  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  analogWrite(enB,65);
  delay(500);

  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  analogWrite(enA,65);

  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  analogWrite(enB,65);
  delay(500);

  digitalWrite(in1,HIGH); //ban kiri maju
  digitalWrite(in2,LOW);
  analogWrite(enA,65);

  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH); // ban kanan mundur
  analogWrite(enB,65);
  delay(500);

  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  analogWrite(enA,65);

  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  analogWrite(enB,65);
  delay(500);


  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  analogWrite(enA,0);

  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  analogWrite(enB,0);
  delay(500);


  digitalWrite(s1,LOW);
  digitalWrite(s2,LOW);
  digitalWrite(s3,LOW);
  digitalWrite(s4,LOW);
  digitalWrite(s5,LOW);
  Serial.begin(9600);
}

void bacasensor(){
  kiri2 = digitalRead(s1); //paling kiri 
  kiri1 = digitalRead(s2); //kiri1
  tengah = digitalRead(s3); //tengah
  kanan1 = digitalRead(s4); //kanan2
  kanan2 = digitalRead(s5); //paling kanan

  near = digitalRead(s6); //near
  klik = digitalRead(s7);
}

void tombol(){
  if(klik == HIGH){
  
    tekan = millis();
    if(menu == 1){
      menu = 2;
    }else if(menu == 2){
      menu = 1;
    }

      tekan = tekan / 1000;
      if(tekan >= 3){
      mulai = true;
      }else{
      mulai = false;
      }

  }

 
  Serial.print(tekan);



}

void loop() {
  // tombol();
  bacasensor();
  Serial.print(kiri2);
  Serial.print(kiri1);
  Serial.print(tengah);
  Serial.print(kanan1);
  Serial.print(kanan2);
  Serial.print("  ");
//  Serial.print(near);
//  Serial.print(klik);
  Serial.print(enA);
    Serial.print("  ");
  Serial.print(enB);
//  Serial.println(' ');


  // Serial.print(" menu ke");
  // Serial.print(menu);
  // if(mulai == true){
  //   Serial.print(" siap jalan ");
  // }else{
  //   Serial.print(" tidak siap ");
  // }
  
  Serial.print("  ");
  delay(10);
  // put your main code here, to run repeatedly:
//  cek sensor
// if(menu == 1 && mulai == true){
//  if(near == LOW){
    if(kiri2 == HIGH && kiri1 == HIGH && tengah == HIGH && kanan1 == HIGH  && kanan2 == HIGH){
      if(tahan1 == 1){
        kanan();
        speedR;
        pwma = speedR / bagi;
        analogWrite(enA,pwma);
        analogWrite(enB,0);
      }else if(tahan1 == 2){
        kiri();
      speedR;
      pwmb = speedR / bagi;
      analogWrite(enA,0);
      analogWrite(enB,pwmb); //ban kanan
      }
      Serial.print("lurus dikit");
      Serial.println(' ');
    }else if(kiri2 == LOW && kiri1 == LOW && tengah == LOW && kanan1 == LOW && kanan2 == LOW){//00000
      int waktu = millis();
      waktu = waktu /1000;
      if(waktu >= 2){
        mati();
        for(int i =0;i<=3;i++){
              digitalWrite(led,HIGH);
              digitalWrite(led2,LOW);
              digitalWrite(led1,HIGH);
              digitalWrite(led3,LOW);
              delay(100);
              digitalWrite(led,LOW);
              digitalWrite(led2,HIGH);
              digitalWrite(led1,LOW);
              digitalWrite(led3,HIGH);
              delay(100);
          }
      }else{
        lurusdikit();
      }
      }
    else if(kiri2 == HIGH && kiri1 == HIGH && tengah == LOW && kanan1 == HIGH  && kanan2 == HIGH){ //11011
    lurus();
    tahan1 =0;
    Serial.print("lurus");
    Serial.println(' ');
    }else if(kiri2 == HIGH && kiri1 == HIGH && tengah == LOW && kanan1 == LOW  && kanan2 == LOW){//11000
     
     tahan1 = 1;
     kanan();

      pwma = speedR / bagi;
      analogWrite(enA,pwma);
      analogWrite(enB,0);
     Serial.print("kanan");
     Serial.println(' ');
    }else if(kiri2 == LOW && kiri1 == LOW && tengah == LOW && kanan1 == HIGH  && kanan2 == HIGH){//00011
      // mati();
      tahan1=2;
     kiri();
      analogWrite(enA,0);

      pwmb = speedR / bagi;
      analogWrite(enB,pwmb);
     Serial.print("kiri");
     Serial.println(' ');
    }else if(kiri2 == HIGH && kiri1 == HIGH && tengah == HIGH && kanan1 == LOW && kanan2 == HIGH){//11101
     tahan1=0;
     serongkanan();
     Serial.print("serong kanan");
     Serial.println(' ');
    }else if(kiri2 == HIGH && kiri1 == LOW && tengah == HIGH && kanan1 == HIGH && kanan2 == HIGH){//10111
      tahan1=0;
      serongkiri();
      Serial.print("serong kiri");
      Serial.println(' ');
    }else if(kiri2 == HIGH && kiri1 == HIGH && tengah == HIGH && kanan1 == LOW && kanan2 == LOW){//11100
      // mati();
      tahan1 = 1;
      serongkanan();
      analogWrite(enA,pwma); //ban kiri
        analogWrite(enB,0);
      Serial.print("kanan");
      Serial.println(' ');
    }else if(kiri2 == LOW && kiri1 == LOW && tengah == HIGH && kanan1 == HIGH && kanan2 == HIGH){//00111
      // mati();
      tahan1 = 2;
    
      analogWrite(enA,0);
  
      serongkiri();
        Serial.print("kiri");
      Serial.println(' ');
    }else if(kiri2 == HIGH && kiri1 == HIGH && tengah == HIGH && kanan1 == HIGH && kanan2 == LOW){//11110
      tahan1 = 1;
      serongkanan();
      Serial.print("kanan tajam");
      Serial.println(' ');
    }else if(kiri2 == LOW && kiri1 == HIGH && tengah == HIGH && kanan1 == HIGH && kanan2 == HIGH){//01111
      tahan1 = 2;
      serongkiri();
      Serial.print("kiri tajam");
      Serial.println(' ');
      
    }else if(kiri2 == HIGH && kiri1 == HIGH && tengah == LOW && kanan1 == LOW && kanan2 == HIGH){//11001
      tahan1=0;
      lurusdikit();
      Serial.print("lurus");
      Serial.println(' ');
    }else if(kiri2 == HIGH && kiri1 == LOW && tengah == LOW && kanan1 == HIGH && kanan2 == HIGH){//10011
      tahan1=0;
      lurusdikit();
      Serial.print("lurus");
      Serial.println(' ');
    }else if(kiri2 == HIGH && kiri1 == LOW && tengah == LOW && kanan1 == LOW && kanan2 == LOW){//10000
      tahan1 =1;
      kanan();
      //tinggi
    
      pwma = speedR / bagi;
      analogWrite(enA,pwma); //ban kiri
        analogWrite(enB,0);
      Serial.print("kanan");
      Serial.println(' ');
    }else if(kiri2 == LOW && kiri1 == LOW && tengah == LOW && kanan1 == LOW && kanan2 == HIGH){//00001
      tahan1 =2;
      kiri();
        analogWrite(enA,0);

 
      pwmb = speedR / bagi;
      analogWrite(enB,pwmb); //ban kanan
      
      Serial.print("kiri");
      Serial.println(' ');
    }else if(kiri2 == HIGH && kiri1 == HIGH && tengah == LOW && kanan1 == HIGH && kanan2 == LOW){//11010
      serongkanan();
      Serial.print("kanan");
      Serial.println(' ');
    }else if(kiri2 == LOW && kiri1 == HIGH && tengah == LOW && kanan1 == HIGH && kanan2 == HIGH){//01011
      serongkiri();
      Serial.print("kiri");
      Serial.println(' ');
    }else if(kiri2 == HIGH && kiri1 == LOW && tengah == LOW && kanan1 == HIGH && kanan2 == LOW){//10010
      serongkanan();
      Serial.print("kanan");
      Serial.println(' ');
    }else if(kiri2 == LOW && kiri1 == HIGH && tengah == LOW && kanan1 == LOW && kanan2 == HIGH){//01001
      serongkiri();
      Serial.print("kiri");
      Serial.println(' ');
    }else if(kiri2 == HIGH && kiri1 == LOW && tengah == LOW && kanan1 == LOW && kanan2 == HIGH){//10001
      serongkanan();
      Serial.print("serong kanan");
      Serial.println(' ');
    }else if(kiri2 == HIGH && kiri1 == LOW && tengah == HIGH && kanan1 == LOW && kanan2 == HIGH){//10101
      lurusdikit();
      Serial.print("lurus dikit");
      Serial.println(' ');
    }else if(kiri2 == LOW && kiri1 == LOW && tengah == HIGH && kanan1 == LOW && kanan2 == HIGH){//00101
      serongkiri();
      Serial.print("kiri");
      Serial.println(' ');
    }
    else if(kiri2 == HIGH && kiri1 == LOW && tengah == HIGH && kanan1 == LOW && kanan2 == LOW){//10100
      serongkanan();
      Serial.print("kanan");
      Serial.println(' ');
    }else if(kiri2 == LOW && kiri1 == HIGH && tengah == LOW && kanan1 == LOW && kanan2 == LOW){//01000
      tahan1 = 1;
      kanan();
      //tinggi
      
      pwma = speedR / bagi;
      analogWrite(enA,pwma); //ban kiri
        analogWrite(enB,0);
      Serial.print("kanan");
      Serial.println(' ');
    }else if(kiri2 == LOW && kiri1 == LOW && tengah == LOW && kanan1 == HIGH && kanan2 == LOW){//00010
      tahan1= 2;
      kiri();
      analogWrite(enA,0);
    
      pwmb = speedR / bagi;
      analogWrite(enB,pwmb); //ban kanan

      Serial.print("kiri");
      Serial.println(' ');    
    }else if(kiri2 == LOW && kiri1 == LOW && tengah == HIGH && kanan1 == LOW && kanan2 == LOW){//00100
      mundurdikit();
      Serial.print("mundur dikit");
      Serial.println(' ');    
    }
    else {
      mati();    
    }
  // }else if(near == HIGH){
  //   mati();
  // }

}
//
//

   



void strobo(){
    for(int i = 0;i<=5;i++){
    digitalWrite(led,HIGH);
    digitalWrite(led2,HIGH);
    digitalWrite(led1,LOW);
    digitalWrite(led3,LOW);
    delay(100);
    digitalWrite(led,LOW);
    digitalWrite(led2,LOW);
    digitalWrite(led1,HIGH);
    digitalWrite(led3,HIGH);
    delay(100);
    }

    digitalWrite(led, LOW);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
  
  }

void strobo1(){
  for(int i=0;i<=3;i++){
    digitalWrite(led,HIGH);
    digitalWrite(led1,HIGH);
    delay(100);
    digitalWrite(led,LOW);
    digitalWrite(led1,LOW);
    delay(100);

    
    digitalWrite(led2,HIGH);
    digitalWrite(led3,HIGH);
    delay(100);
    digitalWrite(led2,LOW);
    digitalWrite(led3,LOW);
    delay(100);
  }
}

//logika perbelokan
void lurus(){
  digitalWrite(in1,HIGH); //ban kiri
  digitalWrite(in2,LOW);
      //tinggi
 
      pwma = speedT / bagi;
      analogWrite(enA,pwma); //ban kiri

  digitalWrite(in3,HIGH); //ban kanan
  digitalWrite(in4,LOW);
   
      pwmb = speedT / bagi;
      analogWrite(enB,pwmb); //ban kanan

  digitalWrite(led,HIGH);
  digitalWrite(led1,HIGH);
  digitalWrite(led2,LOW);
  digitalWrite(led3,LOW);
}

void lurusdikit(){
  digitalWrite(in1,HIGH); //ban kiri
  digitalWrite(in2,LOW);
      speedR = 500;
      pwma = speedR / bagi;
      analogWrite(enA,pwma);

  digitalWrite(in3,HIGH); //ban kanan
  digitalWrite(in4,LOW);
      speedR = 500;
      pwmb = speedR / bagi;
      analogWrite(enB,pwmb);




  digitalWrite(led,HIGH);
  digitalWrite(led1,HIGH);
  digitalWrite(led2,LOW);
  digitalWrite(led3,LOW);
}


void kiri(){
  digitalWrite(in1,LOW); //ban kiri
  digitalWrite(in2,HIGH);
  analogWrite(enA,0);

  digitalWrite(in3,HIGH); //ban ban kanan
  digitalWrite(in4,LOW);



  digitalWrite(led,HIGH);
  digitalWrite(led1,LOW);
  digitalWrite(led2,HIGH);
  digitalWrite(led3,LOW);
 
}


void kanan(){
  digitalWrite(in1,HIGH); //ban kiri
  digitalWrite(in2,LOW);
  

  digitalWrite(in3,LOW); //ban kanan
  digitalWrite(in4,HIGH);
  analogWrite(enB,0);




  digitalWrite(led,LOW);
  digitalWrite(led1,HIGH);
  digitalWrite(led2,LOW);
  digitalWrite(led3,HIGH);
  
}

void kanantajam(){
  digitalWrite(in1,HIGH); //ban kiri
  digitalWrite(in2,LOW);
  analogWrite(enA,100);

  digitalWrite(in3,LOW); //ban kanan
  digitalWrite(in4,HIGH);
  analogWrite(enB,0);


  digitalWrite(led,LOW);
  digitalWrite(led1,HIGH);
  digitalWrite(led2,LOW);
  digitalWrite(led3,HIGH);
  
}

void kiritajam(){
  digitalWrite(in1,LOW); //ban kiri
  digitalWrite(in2,HIGH);
  

  digitalWrite(in3,HIGH); //ban kanan
  digitalWrite(in4,LOW);


  analogWrite(enA,0);
  analogWrite(enB,100);


  digitalWrite(led,LOW);
  digitalWrite(led1,HIGH);
  digitalWrite(led2,LOW);
  digitalWrite(led3,HIGH);
  
}

void mati(){
   digitalWrite(in1, LOW); //ban kanan
   digitalWrite(in2, LOW);
   analogWrite(enA,0);


   digitalWrite(in3, LOW); //ban kiri
   digitalWrite(in4, LOW);
   analogWrite(enB, 0);


   digitalWrite(led,LOW);
   digitalWrite(led1,LOW);
   digitalWrite(led2,HIGH);
   digitalWrite(led3,HIGH);
}

void serongkanan(){
  digitalWrite(in1,HIGH); //ban kiri
  digitalWrite(in2,LOW);
      speedR = 500;
      pwma = speedR / bagi;
      analogWrite(enA,pwma);
  

  digitalWrite(in3,LOW); //ban kanan
  digitalWrite(in4,HIGH);
  analogWrite(enB,0);
}

void serongkiri(){
  digitalWrite(in1,LOW); //ban kiri
  digitalWrite(in2,HIGH);
  analogWrite(enA,0);

  digitalWrite(in3,HIGH); //ban kanan
  digitalWrite(in4,LOW);
      speedR = 500;
      pwmb = speedR / bagi;
      analogWrite(enB,pwmb);
}


void mundurdikit(){
   digitalWrite(in1, LOW); //ban kanan
   digitalWrite(in2, HIGH);
   analogWrite(enA,100);


   digitalWrite(in3, LOW); //ban kiri
   digitalWrite(in4, HIGH);
   analogWrite(enB, 150);


   digitalWrite(led,LOW);
   digitalWrite(led1,LOW);
   digitalWrite(led2,HIGH);
   digitalWrite(led3,HIGH);
  
  }
