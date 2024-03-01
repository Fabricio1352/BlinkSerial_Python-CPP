#include <Arduino.h>
#include <string.h>
#include <nodelay.h>
noDelay delayTimer;

/*
 * blinkSerial2.ino
 *
 * Este programa hace que el LED de status del microcontrolador
 * ESP32 DEVKIT DOIT de 30 pines o un LED conectado al pin 2,
 * se encienda o apague controlado por comandos recibidos por
 * el puerto serie
 */
// Pin a la que esta conectado el LED, GPIO2
const unsigned int PIN_LED1 = 2;
const unsigned int PIN_LED2 = 4;
const unsigned int PIN_LED3 = 18;
const unsigned int PIN_LED4 = 19;
// Velocidad de transmisión del puerto serie
const unsigned int BAUD_RATE = 115200;
// Define los posibles estados del LED
void mensajeError(char *comando);
void apagarEncender(int accion);
void sideToSide(int accion);
void setup()
{
  // Establece el pin PIN_LED (GPIO2) como de salida.
  pinMode(PIN_LED1, OUTPUT);
  pinMode(PIN_LED2, OUTPUT);
  pinMode(PIN_LED3, OUTPUT);
  pinMode(PIN_LED4, OUTPUT);
  // Establece la velocidad de transmisión del puerto
  // serie al valor BAUD_RATE
  Serial.begin(BAUD_RATE);
  // Establece el estado inicial del LED
  apagarEncender(1);
}

void loop()
{
  apagarEncender(2);
  char comando[6];
  // Si hay caracteres disponibles para lectura en el puerto
  // serie
  if (Serial.available() > 0)
  {
    // Lee a lo mas 5 caracteres del puero serie o hasta que se
    // presione la tecla Enter y los guarda en el arreglo
    // comando.
    int n = Serial.readBytesUntil('\n', comando, 6);
    // Todas las cadenas en C/C++ terminan en el carácter de
    // fin de cadena, ‘\n’.
    comando[n] = '\0';
    // Escribe el comando al puerto serie
    Serial.print("Comando: ");
    Serial.println(comando);
    // Prender/apagar el LED
    //     Compara las cadenas s1 y s2 lexicográficamente.
    // La función regresa un entero que es menor que 0 si s1 es menor que s2; Regresa 0 si
    // s1 es igual a s2 y regresa un número que es mayor que 0 si s1 es mayor que s2.

    if (strcmp(comando, "off") == 0)
      apagarEncender(2);
    else
    {
      mensajeError(comando);
    }

    if (strcmp(comando, "ltr") == 0)
      sideToSide(1);
      if(strcmp(comando, "off") == 0){
        sideToSide(0);
      }
    else
    {
      mensajeError(comando);
    }
    if (strcmp(comando, "rtl") == 0)
      sideToSide(2);
    else
    {
      mensajeError(comando);
    }
    if (strcmp(comando, "flash") == 0)
      apagarEncender(3);
    else
    {
      mensajeError(comando);
    }
  }
}

void apagarEncender(int accion)
{
  if (accion == 1)
  {
    digitalWrite(PIN_LED1, HIGH);
    digitalWrite(PIN_LED2, HIGH);
    digitalWrite(PIN_LED3, HIGH);
    digitalWrite(PIN_LED4, HIGH);
  }
  else if (accion == 2)
  {
    digitalWrite(PIN_LED1, LOW);
    digitalWrite(PIN_LED2, LOW);
    digitalWrite(PIN_LED3, LOW);
    digitalWrite(PIN_LED4, LOW);
  }
  else if (accion == 3)
  {
    for (int i = 0; i <= 5; i++)
    {
      apagarEncender(1);
      delayTimer.setdelay(1000);
      while (!delayTimer.update())
        ;
      apagarEncender(2);
      delayTimer.setdelay(1000);
      while (!delayTimer.update())
        ;
    }
  }
}
void mensajeError(char *comando)
{
  Serial.print("Comando no valido: ");
  Serial.println(comando);
}
void sideToSide(int accion)
{
  apagarEncender(2);
  switch (accion)
  {
  case 1:
    digitalWrite(PIN_LED1, HIGH);
    delayTimer.setdelay(5000);
    while (!delayTimer.update())
      ;
    digitalWrite(PIN_LED1, LOW);

    digitalWrite(PIN_LED2, HIGH);
    delayTimer.setdelay(5000);
    while (!delayTimer.update())
      ;
    digitalWrite(PIN_LED2, LOW);

    digitalWrite(PIN_LED3, HIGH);
    delayTimer.setdelay(5000);
    while (!delayTimer.update())
      ;
    digitalWrite(PIN_LED3, LOW);

    digitalWrite(PIN_LED4, HIGH);
    delayTimer.setdelay(5000);
    while (!delayTimer.update())
      ;
    digitalWrite(PIN_LED4, LOW);
    break;
  case 2:
    digitalWrite(PIN_LED4, HIGH);
    delayTimer.setdelay(5000);
    while (!delayTimer.update())
      ;
    digitalWrite(PIN_LED4, LOW);

    digitalWrite(PIN_LED3, HIGH);
    delayTimer.setdelay(5000);
    while (!delayTimer.update())
      ;
    digitalWrite(PIN_LED3, LOW);

    digitalWrite(PIN_LED2, HIGH);
    delayTimer.setdelay(5000);
    while (!delayTimer.update())
      ;
    digitalWrite(PIN_LED2, LOW);

    digitalWrite(PIN_LED1, HIGH);
    delayTimer.setdelay(5000);
    while (!delayTimer.update())
      ;
    digitalWrite(PIN_LED1, LOW);
  case 0:
     apagarEncender(2);
    break;
  }
 
}