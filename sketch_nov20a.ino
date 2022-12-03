int ledR = 2;
int ledV =9 ;
int buz = 3;
int echo = 7;
int trig = 8;
int duree;
int dis;
char data;
void setup(){
  Serial.begin(9600);
  pinMode(ledR, OUTPUT);
  pinMode(ledV, OUTPUT);
  pinMode(buz, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT); 
}
void loop(){
  
  digitalWrite(trig, HIGH);
  delayMicroseconds(2);
  data=Serial.read();
  digitalWrite(trig, LOW);
  long duree = pulseIn(echo,HIGH);

  float dis = duree/2.0*360/1000;

  if ((dis <= 200)||(data=='1')){
   
    digitalWrite(ledR, HIGH);
    digitalWrite(ledV, LOW);
    digitalWrite(buz, HIGH);
    Serial.println("1");
    
  }
  else if ((dis >= 200)||(data=='0')){

    digitalWrite(ledV, HIGH);
    digitalWrite(ledR, LOW);
    digitalWrite(buz, LOW);
    Serial.println("0");
  }
}
