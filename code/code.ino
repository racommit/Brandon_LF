//int s2,s3,s5,in1,in2,in3,in4,enA,enB;
//int s1;

//sensor
int s1 = A0;
int s2 = A1;
int s3 = A2;
int s4 = A3;
int s5 = A4;
int s6 = A5;


// pembacaan sensor
int kiri2,kiri1,tengah,kanan1,kanan2, klik, near;

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
  analogWrite(enA,150);

  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  analogWrite(enB,150);
  delay(500);

  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  analogWrite(enA,150);

  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  analogWrite(enB,150);
  delay(500);

  digitalWrite(in1,HIGH); //ban kiri maju
  digitalWrite(in2,LOW);
  analogWrite(enA,150);

  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH); // ban kanan mundur
  analogWrite(enB,150);
  delay(500);

  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  analogWrite(enA,150);

  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  analogWrite(enB,150);
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
  tombol();
  bacasensor();
  Serial.print(kiri2);
  Serial.print(kiri1);
  Serial.print(tengah);
  Serial.print(kanan1);
  Serial.print(kanan2);
  Serial.print("  ");
  Serial.print(near);
  Serial.print(klik);
  Serial.println(' ');


  Serial.print(" menu ke");
  Serial.print(menu);
  if(mulai == true){
    Serial.print(" siap jalan ");
  }else{
    Serial.print(" tidak siap ");
  }
  
  Serial.print("  ");
  delay(10);
  // put your main code here, to run repeatedly:
//  cek sensor
if(menu == 1 && mulai == true){
  if(near == LOW){
    if(kiri2 == HIGH && kiri1 == HIGH && tengah == HIGH && kanan1 == HIGH  && kanan2 == HIGH || kiri2 == LOW && kiri1 == LOW && tengah == LOW && kanan1 == LOW && kanan2 == LOW){
      lurusdikit();
      Serial.print("lurus dikit");
      Serial.println(' ');
    }else if(kiri2 == HIGH && kiri1 == HIGH && tengah == LOW && kanan1 == HIGH  && kanan2 == HIGH){ //11011
    lurus();
    Serial.print("lurus");
    Serial.println(' ');
    }else if(kiri2 == HIGH && kiri1 == HIGH && tengah == LOW && kanan1 == LOW  && kanan2 == LOW){//11000
     mati();
     kanantajam();
     Serial.print("kanan tajam");
     Serial.println(' ');
    }else if(kiri2 == LOW && kiri1 == LOW && tengah == LOW && kanan1 == HIGH  && kanan2 == HIGH){//00011
      mati();
     kiritajam();
     Serial.print("kiri tajam");
     Serial.println(' ');
    }else if(kiri2 == HIGH && kiri1 == HIGH && tengah == HIGH && kanan1 == LOW && kanan2 == HIGH){//11101
     serongkanan();
     Serial.print("serong kanan");
     Serial.println(' ');
    }else if(kiri2 == HIGH && kiri1 == LOW && tengah == HIGH && kanan1 == HIGH && kanan2 == HIGH){//10111
      serongkiri();
      Serial.print("serong kiri");
      Serial.println(' ');
    }else if(kiri2 == HIGH && kiri1 == HIGH && tengah == HIGH && kanan1 == LOW && kanan2 == LOW){//11100
      mati();
      kanantajam();
      Serial.print("kanan tajam");
      Serial.println(' ');
    }else if(kiri2 == LOW && kiri1 == LOW && tengah == HIGH && kanan1 == HIGH && kanan2 == HIGH){//00111
      mati();
      kiritajam();
      Serial.print("kiri tajam");
      Serial.println(' ');
    }else if(kiri2 == HIGH && kiri1 == HIGH && tengah == HIGH && kanan1 == HIGH && kanan2 == LOW){//11110
      kanantajam();
      Serial.print("kanan tajam");
      Serial.println(' ');
    }else if(kiri2 == LOW && kiri1 == HIGH && tengah == HIGH && kanan1 == HIGH && kanan2 == HIGH){//01111
      kiritajam();
      Serial.print("kiri tajam");
      Serial.println(' ');
    }else if(kiri2 == HIGH && kiri1 == HIGH && tengah == LOW && kanan1 == LOW && kanan2 == HIGH){//11001
      kanantajam();
      Serial.print("kanan tajam");
      Serial.println(' ');
    }else if(kiri2 == HIGH && kiri1 == LOW && tengah == LOW && kanan1 == HIGH && kanan2 == HIGH){//10011
      kiritajam();
      Serial.print("kiri tajam");
      Serial.println(' ');
    }else if(kiri2 == HIGH && kiri1 == LOW && tengah == LOW && kanan1 == LOW && kanan2 == LOW){//10000
      mati();
      kanantajam();
      Serial.print("kanan tajam");
      Serial.println(' ');
    }else if(kiri2 == LOW && kiri1 == LOW && tengah == LOW && kanan1 == LOW && kanan2 == HIGH){//00001
      mati();
      kiritajam();
      Serial.print("kiri tajam");
      Serial.println(' ');
    }else if(kiri2 == HIGH && kiri1 == HIGH && tengah == LOW && kanan1 == HIGH && kanan2 == LOW){//11010
      kanantajam();
      Serial.print("kanan tajam");
      Serial.println(' ');
    }else if(kiri2 == LOW && kiri1 == HIGH && tengah == LOW && kanan1 == HIGH && kanan2 == HIGH){//01011
      kiritajam();
      Serial.print("kiri tajam");
      Serial.println(' ');
    }else if(kiri2 == HIGH && kiri1 == LOW && tengah == LOW && kanan1 == HIGH && kanan2 == LOW){//10010
      kanantajam();
      Serial.print("kanan tajam");
      Serial.println(' ');
    }else if(kiri2 == LOW && kiri1 == HIGH && tengah == LOW && kanan1 == LOW && kanan2 == HIGH){//01001
      kiritajam();
      Serial.print("kiri tajam");
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
      kiritajam();
      Serial.print("kiri tajam");
      Serial.println(' ');
    }else if(kiri2 == HIGH && kiri1 == LOW && tengah == HIGH && kanan1 == LOW && kanan2 == LOW){//10100
      kanantajam();
      Serial.print("kanan tajam");
      Serial.println(' ');
    }else if(kiri2 == LOW && kiri1 == HIGH && tengah == LOW && kanan1 == LOW && kanan2 == LOW){//01000
      kanantajam();
      Serial.print("kanan tajam");
      Serial.println(' ');
    }else if(kiri2 == LOW && kiri1 == LOW && tengah == LOW && kanan1 == HIGH && kanan2 == LOW){//00010
      kiritajam();
      Serial.print("kiri tajam");
      Serial.println(' ');    
    }else if(kiri2 == LOW && kiri1 == LOW && tengah == HIGH && kanan1 == LOW && kanan2 == LOW){//00100
      mundurdikit();
      Serial.print("mundur dikit");
      Serial.println(' ');    
    }
    else {
      mati();    
    }
  }else if(near == HIGH){
    mati();
  }

}
//
//

   
}


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
  analogWrite(enA,150);

  digitalWrite(in3,HIGH); //ban kanan
  digitalWrite(in4,LOW);
  analogWrite(enB,150);

  digitalWrite(led,HIGH);
  digitalWrite(led1,HIGH);
  digitalWrite(led2,LOW);
  digitalWrite(led3,LOW);
}

void lurusdikit(){
  digitalWrite(in1,HIGH); //ban kiri
  digitalWrite(in2,LOW);
  analogWrite(enA,95);

  digitalWrite(in3,HIGH); //ban kanan
  digitalWrite(in4,LOW);
  analogWrite(enB,95);
  delay(10);

  digitalWrite(in1,LOW); //ban kiri
  digitalWrite(in2,LOW);
  analogWrite(enA,0);

  digitalWrite(in3,LOW); //ban kanan
  digitalWrite(in4,LOW);
  analogWrite(enB,0);

  digitalWrite(led,HIGH);
  digitalWrite(led1,HIGH);
  digitalWrite(led2,LOW);
  digitalWrite(led3,LOW);
}


void kiritajam(){
  digitalWrite(in1,LOW); //ban kiri
  digitalWrite(in2,HIGH);
  analogWrite(enA,150);

  digitalWrite(in3,HIGH); //ban ban kanan
  digitalWrite(in4,LOW);
  analogWrite(enB,150);

  digitalWrite(led,HIGH);
  digitalWrite(led1,LOW);
  digitalWrite(led2,HIGH);
  digitalWrite(led3,LOW);
}


void kanantajam(){
  digitalWrite(in1,HIGH); //ban kiri
  digitalWrite(in2,LOW);
  analogWrite(enA,150);

  digitalWrite(in3,LOW); //ban kanan
  digitalWrite(in4,HIGH);
  analogWrite(enB,150);

  digitalWrite(led,LOW);
  digitalWrite(led1,HIGH);
  digitalWrite(led2,LOW);
  digitalWrite(led3,HIGH);
}

void mati(){
   digitalWrite(in1, LOW); //ban kanan
   digitalWrite(in2, LOW);
   analogWrite(enA, 0);


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
  analogWrite(enA,150);

  digitalWrite(in3,LOW); //ban kanan
  digitalWrite(in4,HIGH);
  analogWrite(enB,100);
}

void serongkiri(){
  digitalWrite(in1,LOW); //ban kiri
  digitalWrite(in2,HIGH);
  analogWrite(enA,100);

  digitalWrite(in3,HIGH); //ban kanan
  digitalWrite(in4,LOW);
  analogWrite(enB,150);
}


void mundurdikit(){
   digitalWrite(in1, LOW); //ban kanan
   digitalWrite(in2, HIGH);
   analogWrite(enA, 150);


   digitalWrite(in3, LOW); //ban kiri
   digitalWrite(in4, HIGH);
   analogWrite(enB, 100);


   digitalWrite(led,LOW);
   digitalWrite(led1,LOW);
   digitalWrite(led2,HIGH);
   digitalWrite(led3,HIGH);
  
  }
