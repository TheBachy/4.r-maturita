//Pridani knihovny pro motor driver
#include <AFMotor.h>

//Definice pinu pro IR sensory
#define IR_L A5
#define IR_R A4

//Definice konektoru na motor driveru
AF_DCMotor motor1(3, MOTOR34_1KHZ); //levy motor
AF_DCMotor motor2(4, MOTOR34_1KHZ); //pravy motor

void setup() {  
  //Definice pin modu
  pinMode(IR_L,INPUT); //Infra cerveny sensor vlevo
  pinMode(IR_R,INPUT); //Infra cerveny sensor vpravo

  Serial.begin(9600);
}

void loop() {
  Serial.println(digitalRead(IR_L)); //OUTPUT sensoru do serial monitoru pro debug
  
  Serial.println(digitalRead(IR_R)); //OUTPUT sensoru do serial monitoru pro debug

  if(digitalRead(IR_L)==0 && digitalRead(IR_R)==0){
    //Jede dopredu
    //setSpeed - 0 az 255
    motor1.run(FORWARD);
    motor1.setSpeed(95);
    motor2.run(FORWARD);
    motor2.setSpeed(95);
    //Kvuli moznosti ze sensory nezareaguji na caru dost rychle, jede auticko jen na ~ 1/3 plne rychlosti
  }
  else if(digitalRead(IR_L)==1 && digitalRead(IR_R)==0){
    //Levy sensor narazi na caru -> auticko se otoci do leva
    motor1.run(BACKWARD);
    motor1.setSpeed(150);
    motor2.run(FORWARD);
    motor2.setSpeed(100); 
  }
  else if(digitalRead(IR_L)==0 && digitalRead(IR_R)==1){
    //Pravy sensor narazi na caru -> auticko se otoci do prava
    motor1.run(FORWARD);
    motor1.setSpeed(100);
    motor2.run(BACKWARD);
    motor2.setSpeed(150); 
  }
  else{
    //Sensory nesnimaji nic -> motory se vypnou
    motor1.run(RELEASE);
    motor1.setSpeed(0);
    motor2.run(RELEASE);
    motor2.setSpeed(0); 
  }
}