const int power1 = 5;
const int power2 = 6;
const int input = 7;
const int pot = A0;

unsigned long pulse;
int vprev = 183;
int value;
int pos;

void setup(){
  pinMode(power1,OUTPUT);
  pinMode(power2,OUTPUT);
  pinMode(input,INPUT);
  pinMode(pot,INPUT);
  Serial.begin(9600);
  pulse = pulseIn(input,HIGH);
  pos = map(analogRead(pot),37,737,0,180);
}

void loop(){
  while(pulse < 500){
    digitalWrite(power1,LOW);
    digitalWrite(power2,LOW);
    pulse = pulseIn(input,HIGH,6000);
  }
  value = map(pulse,540,2385,0,180);
  while(vprev <= value+1 && vprev >= value-1){
    pulse = pulseIn(input,HIGH,6000);
    while(pulse < 500){
      pulse = pulseIn(input,HIGH,6000);
    }
    value = map(pulse,540,2385,0,180);
  }
  Serial.println(value);
  while(value != pos){
    if(value > pos){
      digitalWrite(power1,LOW);
      digitalWrite(power2,HIGH);
    }
    else if(value < pos){
      digitalWrite(power1,HIGH);
      digitalWrite(power2,LOW);
    }
    pos = map(analogRead(pot),37,737,0,180);
  }
  digitalWrite(power1,LOW);
  digitalWrite(power2,LOW);
  vprev = value;
  pulse = pulseIn(input,HIGH);
}
