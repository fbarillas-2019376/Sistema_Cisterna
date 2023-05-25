/*
   Fundacion Kinal
   Centro Educativo Tecnico Laboral KINAL
   Quinto electronica
   Codigo Tecnico: EB5AM 
   Curso: Taller de electronica digital 
   Proyecto: Sisterna
   Nombre de los integrantes
   Cristian Estuardo Orellana Dieguez - 2022030
   Francisco Javier Barillas Velasquez - 2019376
   Juan David Tejada Peñuela - 2022454
   Landon Francisco Alexander Reyes Baten - 2022012
*/
//Incluyo las librerias necesarias para la LCD
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//directivas de preprocesador
//defino los pines que se utilizaran en el arduino
#define trig A0
#define echo A1
#define rele A3
#define buzz 5
#define led1 2
#define led2 3
#define led3 4
#define led4 6
#define led5 7
#define led6 8
#define led7 9
#define led8 10
#define led9 11
#define led10 12
//modifico funciones de arduino
#define in(pin); pinMode(pin, INPUT);    //Definir un pin como entrada
#define out(pin); pinMode(pin, OUTPUT);  //Definir un pin como salida
#define h(pin); digitalWrite(pin, HIGH); //Mandar un pulso en HIGH o 1
#define l(pin); digitalWrite(pin, LOW);  //Mandar un pulso en LOW o 0

//defino funciones
void pines();           //Definir modo de pines
int ultrasonico();      //Lectura de Distancia
void sistera();         //Procesos de ejecutacion
void Activacion_LCD();  //Crea los Caracteres e inicia la comunicacion Serial

//configuro la LCD(Direccion, Columnas, Filas, Contructor)
#define Direccion_LCD 0x27
int COLUMNAS = 16;
int FILAS = 2;
LiquidCrystal_I2C LCD_CISTERNA(Direccion_LCD, COLUMNAS, FILAS);

//defino una nota para el buzzer
int sol  = 493;
int si  = 200;

//defino los caracteres de vaso vacio y vaso lleno
byte vaso[] = {
  B00000,
  B11111,
  B10001,
  B10001,
  B01010,
  B01010,
  B01110,
  B00000
};
byte vaso_lleno[] = {
  B00000,
  B11111,
  B11111,
  B11111,
  B01110,
  B01110,
  B01110,
  B00000
};

//Activo las Funciones de LCD y declaracion del modo de Pines 
void setup() {
Activacion_LCD();
pines();
}

//Ejecuto los procesos que se realizaran de manera simultanea
void loop() {
  ultrasonico();
  Cisterna();
  Serial.begin(9600);
  Serial.println(ultrasonico());
}

//Creo los caracteres para la LCD
void Activacion_LCD()
{
  LCD_CISTERNA.init();
  LCD_CISTERNA.backlight();
  LCD_CISTERNA.createChar(1,vaso);
  LCD_CISTERNA.write(1);
  LCD_CISTERNA.createChar(2,vaso_lleno);
  LCD_CISTERNA.write(2);
}

//Defino el modo de Pines
void pines(){
  in(echo);
  out(trig);
  out(rele);
  out(buzz);
  out(led1);
  out(led2);
  out(led3);
  out(led4);
  out(led5);
  out(led6);
  out(led7);
  out(led8);
  out(led9);
  out(led10);
  }

//Realizo la lectura con el Ultrasonico  
int ultrasonico(){
  long distancia, T; 
  digitalWrite(trig, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trig, LOW);
  T = pulseIn(echo, HIGH);
  distancia = T/59;
  delay(50);
  return distancia;
}

//
void Cisterna(){
  long medida = ultrasonico(); //Le asigno el valor de la lectura del ultrasonico a la variable medida
  if(medida == 12 || medida == 13){ 
  LCD_CISTERNA.setCursor(0,0);
  LCD_CISTERNA.print("ESTADO VACIO    ");
  LCD_CISTERNA.setCursor(0,1);  //Muestro Caracteres en la LCD
  LCD_CISTERNA.write(1);
  LCD_CISTERNA.setCursor(1,1);
  LCD_CISTERNA.write(1);
  LCD_CISTERNA.setCursor(2,1);
  LCD_CISTERNA.write(1);
  LCD_CISTERNA.setCursor(3,1);
  LCD_CISTERNA.write(1);
  LCD_CISTERNA.setCursor(4,1);
  LCD_CISTERNA.write(1);
  LCD_CISTERNA.setCursor(5,1);
  LCD_CISTERNA.write(1);
  LCD_CISTERNA.setCursor(6,1);
  LCD_CISTERNA.write(1);
  LCD_CISTERNA.setCursor(7,1);
  LCD_CISTERNA.write(1);
  LCD_CISTERNA.setCursor(8,1);
  LCD_CISTERNA.write(1);
  LCD_CISTERNA.setCursor(9,1);
  LCD_CISTERNA.write(1);
  l(rele);                //Activo el Rele
  tone(buzz, sol*2, 100); //Mando una nota al Buzzer
  delay(100);
  noTone(buzz);           //Apago el Buzzer
  l(led1);                //Defino el estado del Display de acuerdo al Nivel de la Cisterna
  l(led2);
  l(led3);
  l(led4);
  l(led5);
  l(led6);
  l(led7);
  l(led8);
  l(led9);
  l(led10);
    }
  if(medida == 11){
  LCD_CISTERNA.setCursor(0,0);
  LCD_CISTERNA.print("ESTADO 1cm LLENO");
  LCD_CISTERNA.setCursor(0,1);          //Muestro Caracteres en la LCD
  LCD_CISTERNA.write(2);
  LCD_CISTERNA.setCursor(1,1);
  LCD_CISTERNA.write(1);
  LCD_CISTERNA.setCursor(2,1);
  LCD_CISTERNA.write(1);
  LCD_CISTERNA.setCursor(3,1);
  LCD_CISTERNA.write(1);
  LCD_CISTERNA.setCursor(4,1);
  LCD_CISTERNA.write(1);
  LCD_CISTERNA.setCursor(5,1);
  LCD_CISTERNA.write(1);
  LCD_CISTERNA.setCursor(6,1);
  LCD_CISTERNA.write(1);
  LCD_CISTERNA.setCursor(7,1);
  LCD_CISTERNA.write(1);
  LCD_CISTERNA.setCursor(8,1);
  LCD_CISTERNA.write(1);
  LCD_CISTERNA.setCursor(9,1);
  LCD_CISTERNA.write(1);
  tone(buzz, sol*2, 100);  //Activo la nota sol en el buzzer
  delay(100);              //Le agrego un delay de 100ms
  noTone(buzz);            //desactivo el tono del buzzer
  l(rele);                 //Activo el rele
  h(led1);                 //Activo la barra LED
  l(led2);
  l(led3);
  l(led4);
  l(led5);
  l(led6);
  l(led7);
  l(led8);
  l(led9);
  l(led10);
  }
  if(medida == 10){ //Agregamos una distancia al ultrasonico
  LCD_CISTERNA.setCursor(0,0);
  LCD_CISTERNA.print("ESTADO 2cm LLENO");
  LCD_CISTERNA.setCursor(0,1); //Muestro Caracteres en la LCD
  LCD_CISTERNA.write(2);
  LCD_CISTERNA.setCursor(1,1);
  LCD_CISTERNA.write(2);
  LCD_CISTERNA.setCursor(2,1);
  LCD_CISTERNA.write(1);
  LCD_CISTERNA.setCursor(3,1);
  LCD_CISTERNA.write(1);
  LCD_CISTERNA.setCursor(4,1);
  LCD_CISTERNA.write(1);
  LCD_CISTERNA.setCursor(5,1);
  LCD_CISTERNA.write(1);
  LCD_CISTERNA.setCursor(6,1);
  LCD_CISTERNA.write(1);
  LCD_CISTERNA.setCursor(7,1);
  LCD_CISTERNA.write(1);
  LCD_CISTERNA.setCursor(8,1);
  LCD_CISTERNA.write(1);
  LCD_CISTERNA.setCursor(9,1);
  LCD_CISTERNA.write(1);
  tone(buzz, sol*2, 100);  //Agrego la nota sol al buzzer mientras esta en HIGH o 1
  delay(100);              //Agregamos en un delay de 100ms
  noTone(buzz); //Ponemos el buzzer en LOW o 0
  l(rele); //Activo el rele
  h(led1);  //Activamos la barra LED
  h(led2);
  l(led3);
  l(led4);
  l(led5);
  l(led6);
  l(led7);
  l(led8);
  l(led9);
  l(led10);
  }
  if(medida ==    9){ //Agregamos la medida de en el ultrasonico
  LCD_CISTERNA.setCursor(0,0);
  LCD_CISTERNA.print("ESTADO 3cm LLENO"); 
  LCD_CISTERNA.setCursor(0,1); //Muestra el caracter en la LCD
  LCD_CISTERNA.write(2);
  LCD_CISTERNA.setCursor(1,1);
  LCD_CISTERNA.write(2);
  LCD_CISTERNA.setCursor(2,1);
  LCD_CISTERNA.write(2);
  LCD_CISTERNA.setCursor(3,1);
  LCD_CISTERNA.write(1);
  LCD_CISTERNA.setCursor(4,1);
  LCD_CISTERNA.write(1);
  LCD_CISTERNA.setCursor(5,1);
  LCD_CISTERNA.write(1);
  LCD_CISTERNA.setCursor(6,1);
  LCD_CISTERNA.write(1);
  LCD_CISTERNA.setCursor(7,1);
  LCD_CISTERNA.write(1);
  LCD_CISTERNA.setCursor(8,1);
  LCD_CISTERNA.write(1);
  LCD_CISTERNA.setCursor(9,1);
  LCD_CISTERNA.write(1);
  l(rele);   //Activa el rele
  h(led1);   //Activamos la barra LED
  h(led2);
  h(led3);
  l(led4);
  l(led5);
  l(led6);
  l(led7);
  l(led8);
  l(led9);
  l(led10);
  }
  if(medida == 8){ //Agregamos la medida en el ultrasonico
  LCD_CISTERNA.setCursor(0,0);
  LCD_CISTERNA.print("ESTADO 4cm LLENO"); 
  LCD_CISTERNA.setCursor(0,1); //Muestra el caracter en la LCD
  LCD_CISTERNA.write(2);
  LCD_CISTERNA.setCursor(1,1);
  LCD_CISTERNA.write(2);
  LCD_CISTERNA.setCursor(2,1);
  LCD_CISTERNA.write(2);
  LCD_CISTERNA.setCursor(3,1);
  LCD_CISTERNA.write(2);
  LCD_CISTERNA.setCursor(4,1);
  LCD_CISTERNA.write(1);
  LCD_CISTERNA.setCursor(5,1);
  LCD_CISTERNA.write(1);
  LCD_CISTERNA.setCursor(6,1);
  LCD_CISTERNA.write(1);
  LCD_CISTERNA.setCursor(7,1);
  LCD_CISTERNA.write(1);
  LCD_CISTERNA.setCursor(8,1);
  LCD_CISTERNA.write(1);
  LCD_CISTERNA.setCursor(9,1);
  LCD_CISTERNA.write(1);
  tone(buzz, sol, 100); //Agregamos la nota sol en el buzzer
  noTone(buzz); //Apagamos el buzzer
  l(rele);  //Activa el rele
  h(led1);  //Activamos la barra LED
  h(led2);
  h(led3);
  h(led4);
  l(led5);
  l(led6);
  l(led7);
  l(led8);
  l(led9);
  l(led10);
  }
  if(medida == 7){ //Agregamos la medida en el ultrasonico
  LCD_CISTERNA.setCursor(0,0);
  LCD_CISTERNA.print("ESTADO 5cm LLENO"); 
  LCD_CISTERNA.setCursor(0,1);  //Muestra el caracter en la LCD
  LCD_CISTERNA.write(2);
  LCD_CISTERNA.setCursor(1,1);
  LCD_CISTERNA.write(2);
  LCD_CISTERNA.setCursor(2,1);
  LCD_CISTERNA.write(2);
  LCD_CISTERNA.setCursor(3,1);
  LCD_CISTERNA.write(2);
  LCD_CISTERNA.setCursor(4,1);
  LCD_CISTERNA.write(2);
  LCD_CISTERNA.setCursor(5,1);
  LCD_CISTERNA.write(1);
  LCD_CISTERNA.setCursor(6,1);
  LCD_CISTERNA.write(1);
  LCD_CISTERNA.setCursor(7,1);
  LCD_CISTERNA.write(1);
  LCD_CISTERNA.setCursor(8,1);
  LCD_CISTERNA.write(1);
  LCD_CISTERNA.setCursor(9,1);
  LCD_CISTERNA.write(1);
  l(rele);   //Activa el rele
  h(led1);   //Activamos la barra LED
  h(led2);
  h(led3);
  h(led4);
  h(led5);
  l(led6);
  l(led7);
  l(led8);
  l(led9);
  l(led10);
  }
  if(medida == 6){ //Agregamos la medida en el ultrasonico
  LCD_CISTERNA.setCursor(0,0);
  LCD_CISTERNA.print("ESTADO 6cm LLENO"); 
  LCD_CISTERNA.setCursor(0,1);   //Muestra el caracter en la LCD
  LCD_CISTERNA.write(2);
  LCD_CISTERNA.setCursor(1,1);
  LCD_CISTERNA.write(2);
  LCD_CISTERNA.setCursor(2,1);
  LCD_CISTERNA.write(2);
  LCD_CISTERNA.setCursor(3,1);
  LCD_CISTERNA.write(2);
  LCD_CISTERNA.setCursor(4,1);
  LCD_CISTERNA.write(2);
  LCD_CISTERNA.setCursor(5,1);
  LCD_CISTERNA.write(2);
  LCD_CISTERNA.setCursor(6,1);
  LCD_CISTERNA.write(1);
  LCD_CISTERNA.setCursor(7,1);
  LCD_CISTERNA.write(1);
  LCD_CISTERNA.setCursor(8,1);
  LCD_CISTERNA.write(1);
  LCD_CISTERNA.setCursor(9,1);
  LCD_CISTERNA.write(1);
  l(rele);  //Activa el rele
  h(led1);  //Activamos la barra LED
  h(led2);
  h(led3);
  h(led4);
  h(led5);
  h(led6);
  l(led7);
  l(led8);
  l(led9);
  l(led10);
  }
  if(medida == 5){  //Agregamos la medida en el ultrasonico
  LCD_CISTERNA.setCursor(0,0);
  LCD_CISTERNA.print("ESTADO 7cm LLENO"); 
  LCD_CISTERNA.setCursor(0,1);   //Muestra el caracter en la LCD
  LCD_CISTERNA.write(2);
  LCD_CISTERNA.setCursor(1,1);
  LCD_CISTERNA.write(2);
  LCD_CISTERNA.setCursor(2,1);
  LCD_CISTERNA.write(2);
  LCD_CISTERNA.setCursor(3,1);
  LCD_CISTERNA.write(2);
  LCD_CISTERNA.setCursor(4,1);
  LCD_CISTERNA.write(2);
  LCD_CISTERNA.setCursor(5,1);
  LCD_CISTERNA.write(2);
  LCD_CISTERNA.setCursor(6,1);
  LCD_CISTERNA.write(2);
  LCD_CISTERNA.setCursor(7,1);
  LCD_CISTERNA.write(1);
  LCD_CISTERNA.setCursor(8,1);
  LCD_CISTERNA.write(1);
  LCD_CISTERNA.setCursor(9,1);
  LCD_CISTERNA.write(1);
  l(rele);  //Activa el rele
  h(led1);  //Activa la barra LED
  h(led2);
  h(led3);
  h(led4);
  h(led5);
  h(led6);
  h(led7);
  l(led8);
  l(led9);
  l(led10);
  }
  if(medida == 4){  //Agregamos la medida en el ultrasonico
  LCD_CISTERNA.setCursor(0,0);
  LCD_CISTERNA.print("ESTADO 8cm LLENO");
  LCD_CISTERNA.setCursor(0,1);    //Muestra el caracter en la LCD
  LCD_CISTERNA.write(2);
  LCD_CISTERNA.setCursor(1,1);
  LCD_CISTERNA.write(2);
  LCD_CISTERNA.setCursor(2,1);
  LCD_CISTERNA.write(2);
  LCD_CISTERNA.setCursor(3,1);
  LCD_CISTERNA.write(2);
  LCD_CISTERNA.setCursor(4,1);
  LCD_CISTERNA.write(2);
  LCD_CISTERNA.setCursor(5,1);
  LCD_CISTERNA.write(2);
  LCD_CISTERNA.setCursor(6,1);
  LCD_CISTERNA.write(2);
  LCD_CISTERNA.setCursor(7,1);
  LCD_CISTERNA.write(2);
  LCD_CISTERNA.setCursor(8,1);
  LCD_CISTERNA.write(1);
  LCD_CISTERNA.setCursor(9,1);
  LCD_CISTERNA.write(1);
  l(rele); //Activamos el rele
  h(led1);  //Activa la barra LED
  h(led2);
  h(led3);
  h(led4);
  h(led5);
  h(led6);
  h(led7);
  h(led8);
  l(led9);
  l(led10);
  }
  if(medida == 3){  //Agregamos la medida en el ultrasonico
  LCD_CISTERNA.setCursor(0,0);
  LCD_CISTERNA.print("ESTADO 9cm LLENO"); 
  LCD_CISTERNA.setCursor(0,1);   //Muestra el caracter en la LCD
  LCD_CISTERNA.write(2);
  LCD_CISTERNA.setCursor(1,1);
  LCD_CISTERNA.write(2);
  LCD_CISTERNA.setCursor(2,1);
  LCD_CISTERNA.write(2);
  LCD_CISTERNA.setCursor(3,1);
  LCD_CISTERNA.write(2);
  LCD_CISTERNA.setCursor(4,1);
  LCD_CISTERNA.write(2);
  LCD_CISTERNA.setCursor(5,1);
  LCD_CISTERNA.write(2);
  LCD_CISTERNA.setCursor(6,1);
  LCD_CISTERNA.write(2);
  LCD_CISTERNA.setCursor(7,1);
  LCD_CISTERNA.write(2);
  LCD_CISTERNA.setCursor(8,1);
  LCD_CISTERNA.write(2);
  LCD_CISTERNA.setCursor(9,1);
  LCD_CISTERNA.write(1);
  l(rele);  //Activa el rele
  h(led1);  //Activa la Barra LED
  h(led2);
  h(led3);
  h(led4);
  h(led5);
  h(led6);
  h(led7);
  h(led8);
  h(led9);
  l(led10);
  }
  if(medida == 2){  //Agregamos la medida en el ultrasonico
  LCD_CISTERNA.setCursor(0,0);
  LCD_CISTERNA.print("ESTADO 10cmLLENO"); 
  LCD_CISTERNA.setCursor(0,1);   //Muestra el caracter en la LCD
  LCD_CISTERNA.write(2);
  LCD_CISTERNA.setCursor(1,1);
  LCD_CISTERNA.write(2);
  LCD_CISTERNA.setCursor(2,1);
  LCD_CISTERNA.write(2);
  
 LCD_CISTERNA.setCursor(3,1);
  LCD_CISTERNA.write(2);
  LCD_CISTERNA.setCursor(4,1);
  LCD_CISTERNA.write(2);
  LCD_CISTERNA.setCursor(5,1);
  LCD_CISTERNA.write(2);
  LCD_CISTERNA.setCursor(6,1);
  LCD_CISTERNA.write(2);
  LCD_CISTERNA.setCursor(7,1);
  LCD_CISTERNA.write(2);
  LCD_CISTERNA.setCursor(8,1);
  LCD_CISTERNA.write(2);
  LCD_CISTERNA.setCursor(9,1);
  LCD_CISTERNA.write(2);
  tone(buzz, si*2,100);  //Activa la nota si en el buzzer
  delay(100);            //Agregamos un delay de 100ms
  noTone(buzz);          //Desactivamos el buzzer
  h(rele);               //Desactivamos el rele
  h(led1);               //Activamos la barra LED
  h(led2);
  h(led3);
  h(led4);
  h(led5);
  h(led6);
  h(led7);
  h(led8);
  h(led9);
  h(led10);
  }//
  }
