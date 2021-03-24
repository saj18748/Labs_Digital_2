//-----------------------------------------
// Laboratorio #4
// Elctronica Digital 2
// Yefry Sajquiy - 18748
//----------------------------------------

#include <stdint.h>
#include <TM4C123GH6PM.h>

// Definicion de los estados de los leds
#define LEDR RED_LED
#define LEDG GREEN_LED
#define LEDB BLUE_LED


#define PUSHA PUSH1
#define PUSHB PUSH2
#define PUSHS PA_2

//puertos
int PORTA[] = {PB_0, PB_1, PE_4, PE_5, PB_4, PA_5, PA_6, PA_7};
int PORTB[] = {PD_0, PD_1, PD_2, PD_3, PE_1, PE_2, PE_3, PD_7};

//Banderas 
uint8_t FLAG_1 = 0;
uint8_t FLAG_2 = 0;
uint8_t FLAG_3 = 0;
uint8_t START = 0;

uint8_t i = 0;
uint8_t j = 0;

//prototipados
void semaforo(void);
void J1(void);
void J2(void);


//Configuracion de cada puerto, entrada y salida 
void setup() {
  Serial.begin(9600);
  
  //semaforo
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
  //pushes
  pinMode(PUSHA, INPUT_PULLUP);
  pinMode(PUSHB, INPUT_PULLUP);
  pinMode(PUSHS, INPUT_PULLUP);
  
  //puertos
  //PUERTO A
  pinMode(PB_0, OUTPUT);
  pinMode(PB_1, OUTPUT);
  pinMode(PE_4, OUTPUT);
  pinMode(PE_5, OUTPUT);
  pinMode(PB_4, OUTPUT);
  pinMode(PA_5, OUTPUT);
  pinMode(PA_6, OUTPUT);
  pinMode(PA_7, OUTPUT);

  //PUERTO B
  pinMode(PD_0, OUTPUT);
  pinMode(PD_1, OUTPUT);
  pinMode(PD_2, OUTPUT);
  pinMode(PD_3, OUTPUT);
  pinMode(PE_1, OUTPUT);
  pinMode(PE_2, OUTPUT);
  pinMode(PE_3, OUTPUT);
  pinMode(PD_7, OUTPUT);

}

// Inicio del programa princiapal
void loop() {

  
  if (digitalRead(PUSHS) == 0) {
    FLAG_1 = 1;
    delay(50);
  }
  else {
    if (FLAG_1 == 1) {
      FLAG_1 = 0;
      semaforo();
      delay(50);
    }
  }
  // JUGADOR 1
  if (digitalRead(PUSHA) == 0 && START == 1) {
    FLAG_2 = 1;
    delay(50);
  }
  else {
    if (FLAG_2 == 1) {
      FLAG_2 = 0;
      J1();
      delay(50);
    }
  }
  
  // JUGADOR 2
  //MISMA LOGICA QUE PARA EL JUGADOR 1
  if (digitalRead(PUSHB) == 0 && START == 1) {
    FLAG_3 = 1;
    delay(50);
  }
  else {
    if (FLAG_3 == 1) {
      FLAG_3 = 0;
      J2();
      delay(50);
    }
  }
}

void semaforo(void) {
  //inicio
  
  i = 0;
  j = 0;
  
  START = 1;
  for (int n = 0; n < 8; n++) {
    digitalWrite(PORTA[n], LOW);
    digitalWrite(PORTB[n], LOW);
  }
  //luces
  digitalWrite(LEDR, HIGH);  
  digitalWrite(LEDG, LOW);   
  digitalWrite(LEDB, LOW);  
   
  delay(1000);        
         
  digitalWrite(LEDR, HIGH);   
  digitalWrite(LEDG, HIGH);   
  digitalWrite(LEDB, LOW);  
   
  delay(1000);        
       
  digitalWrite(LEDR, LOW);   
  digitalWrite(LEDG, HIGH);   
  digitalWrite(LEDB, LOW);   
  delay(1000);              
  digitalWrite(LEDR, LOW);   
  digitalWrite(LEDG, LOW);  
  digitalWrite(LEDB, LOW);   
  delay(1000);               
}

void J1(void) {
  if (i < 8) {
    if (i > 0) {
      digitalWrite(PORTA[i - 1], LOW);
    }
    digitalWrite(PORTA[i], HIGH);
    i++;
  }
  else {
    digitalWrite(PORTA[7], LOW);
    digitalWrite(LEDB, HIGH);
    digitalWrite(LEDG, HIGH);
    START = 0;
    i = 0;
  }
}

void J2(void) {
  if (j < 8) {
    if (j > 0) {
      digitalWrite(PORTB[j - 1], LOW);
    }
    digitalWrite(PORTB[j], HIGH);
    j++;
  }
  else {
    digitalWrite(PORTB[7], LOW);
    digitalWrite(LEDB, HIGH);
    digitalWrite(LEDR, HIGH);
    START = 0;
    j = 0;
  }
}

// ------------ FIN    XD --------------------------
