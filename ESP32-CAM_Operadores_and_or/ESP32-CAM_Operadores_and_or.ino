
/* Ejemplo Operadores and y or en C
 * Además se utiliza el sensor de temperatura DHT11
 * Enecender un led y leer un botón.
 * Este programa enciende un led cuando se presiona un botón
 * Por: JMC
 * 18 de abril de 2022 
 * Actualizado: 20 de abril de 2022
 */ 

// Bibliotecas
#include "DHT.h"

#define DHTPIN 14     // Digital pin connected to the DHT sensor 

#define DHTTYPE    DHT11     // DHT 11



// Constantes
const int Led1 = 4; // led flash pin - Indica estado de la Refrigeración manual
const int Led2 = 2; // led pin - Indica estado de la Refrigeración Automática

const int Boton1 = 12; // IO12 Activa la refrigeración manual
const int Boton2 = 13; // IO12 Alta demanda
const int Boton3 = 15; // IO12 Sobrecarga de funcionamiento

// Variables
unsigned long delayMS = 1000;
int dato1;  // Almacena el estado del Boton1
int dato2;  // Almacena el estado del Boton2
int dato3;  // Almacena el estado del Boton3
unsigned long tiempo_inicio = 0, tiempo_actual;
float t;
 
// Definicion de objetos
DHT dht(DHTPIN, DHTTYPE);

// Condiciones iniciales
void setup() {// Inicio Void setup()
  Serial.begin(115200);
  // Configurar pines
  pinMode (Boton1, INPUT_PULLUP); // Se activa la resistencia de PULLUP
  pinMode (Boton2, INPUT_PULLUP); // Se activa la resistencia de PULLUP
  pinMode (Boton3, INPUT_PULLUP); // Se activa la resistencia de PULLUP
  pinMode (Led1, OUTPUT);  
  pinMode (Led2, OUTPUT);  
  digitalWrite (Led1, LOW);
  digitalWrite (Led2, LOW);
  
  // Initialize device.
  dht.begin();
}// Fin Void setup()

// Cuerpo del programa
void loop() { // Inicio void loop()
  tiempo_actual = millis();
  
  if (tiempo_actual - tiempo_inicio > delayMS){
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    // Read temperature as Celsius (the default)
    t = dht.readTemperature();
    
    // Check if any reads failed and exit early (to try again).
    if (isnan(t)) {
      Serial.println(F("Error de lectura del sensor DHT11!"));
      return;
    }
    Serial.print(F("Temperatura: "));
    Serial.print(t);
    Serial.println(F("°C "));
    
    tiempo_inicio = tiempo_actual;
  }
  
  dato1 = digitalRead (Boton1);
  dato2 = digitalRead (Boton2);
  dato3 = digitalRead (Boton3);
  if (!dato1 || (!dato3 && (t > 30)) || (!dato2 && (t > 30))) {
    digitalWrite (Led1, HIGH); 
  }
  else {
    digitalWrite (Led1, LOW); 
  }
  if ((!dato3 && (t > 30)) || (!dato2 && (t > 30)) || (dato1 && (t > 30)) || (dato1 && !dato2) || (dato1 && !dato3)) {
    digitalWrite (Led2, HIGH); 
  }
  else {
    digitalWrite (Led2, LOW); 
  }
  
        
} //Fin loop()

// Funciones del usuario
