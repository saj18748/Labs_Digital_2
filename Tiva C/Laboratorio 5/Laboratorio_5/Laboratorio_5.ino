//----------------------------------------------------------------------------------------
//             Laboratorio #5
//          Elctronica Digital 2
//          Yefry Sajquiy - 18748
//-----------------------------------------------------------------------------------------

// se utilizo como base la libreria de listfiles y ReadWrite para leer los archivos de la SD
/*
  Listfiles
*/

// se incluyen las librerias para la comunicancion de a TIVA C con la SD
#include <SPI.h>
#include <SD.h>

int input = 0;
File root;    // rutas de lectura 
File myfile;

// -------------------------------  SETUP -----------------------------------------------------

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);     // Frecuencia de trabaj0
  SPI.setModule(0);

  Serial.print(" Initializing SD card...");
  
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output
  // or the SD library functions will not work.
  
  pinMode(PA_3, OUTPUT);

  if (!SD.begin(PA_3)) {
    Serial.println(" Initialization failed!"); // se muestsra cuando no lee una SD
    return;
  }
  Serial.println(); 
  Serial.println(" Initialization done.");    // se muestra cuando se lee la SD
  Serial.println(); 
  Serial.println("----------------- BIENVENIDO -------------------");
  Serial.println(); 
  Serial.println(" Archivos de la SD "); 
  Serial.println(); 
  root = SD.open("/");  // se muestran los archivos de la SD

  printDirectory(root, 0);

  Serial.println("done!");    
  Serial.println(); 

// se inicia con el menu de lectura de archivos 
  Serial.println(" Elige el numero de imagen que deseas ver");
  Serial.println(); 
  Serial.println(" 1. Batman.txt");
  Serial.println(" 2. Arbol.txt");
  Serial.println(" 3. SP85D7~1.txt");

  
}

// ---------------------- PROGRAMA PRINCIPAL -----------------------------------------

void loop()
{
  // ------------------------------------ Imagen 1 ------------------------------------
  
    input = Serial.read();
  if(input == 49){
    myfile = SD.open("Batman.txt");   // si le elige el la imagen 1, se muestra la imagen del archivo batman
    if (myfile) {
      Serial.println("Batman.txt:");

      // read from the file until there's nothing else in it:
      while (myfile.available()) {
        Serial.write(myfile.read());
      }
      // close the file:
      myfile.close();
    } else {
      // if the file didn't open, print an error:
      Serial.println(" Error opening .txt");  // si no encuentra el archivo, muestra el error
    }

    // Vuelve a mistrar el menu de eleccion de imagenes 
        Serial.println(" Elige el numero de imagen que deseas ver ");
        Serial.println(" 1. Batman.txt");
        Serial.println(" 2. Arbol.txt");
        Serial.println(" 3. SP85D7~1.txt");
  } 

// ------------------------------------ Imagen 2 --------------------------------------

  if(input == 50){
    myfile = SD.open("Arbol.txt");    //si le elige el la imagen 2, se muestra la imagen del archivo arbol
    if (myfile) {
      Serial.println("Arbol.txt:");

      // read from the file until there's nothing else in it:
      while (myfile.available()) {
        Serial.write(myfile.read());
      }
      // close the file:
      myfile.close();
    } else {
      // if the file didn't open, print an error:
      Serial.println("Error opening .txt");   // si no encuentra el archivo, muestra el error
    }

    // Vuelve a mistrar el menu de eleccion de imagenes 
    
        Serial.println(" Elige el numero de imagen que deseas ver ");
        Serial.println(" 1. Batman.txt");
        Serial.println(" 2. Arbol.txt");
        Serial.println(" 3. SP85D7~1.txt");
  } 

// ---------------------------------- Imagen 3 ------------------------------------
  if(input == 51){
    myfile = SD.open("SP85D7~1.txt");    //si le elige el la imagen 3, se muestra la imagen del archivo SP85D7~ ( es un logo de Spiderman )
    if (myfile) {
      Serial.println("SP85D7~1.txt:");

      // read from the file until there's nothing else in it:
      while (myfile.available()) {
        Serial.write(myfile.read());
      }
      // close the file:
      myfile.close();
    } else {
      // if the file didn't open, print an error:
      Serial.println("error opening .txt");      // si no encuentra el archivo, muestra el error
    }

    // Vuelve a mistrar el menu de eleccion de imagenes 
        Serial.println(" Elige el numero de imagen que deseas ver ");
        Serial.println(" 1. Batman.txt");
        Serial.println(" 2. Arbol.txt");
        Serial.println(" 3. SP85D7~1.txt");
  } 
}

// 
void printDirectory(File dir, int numTabs) {
  dir.rewindDirectory();
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {  
        Serial.println("");
        //printDirectory(entry, numTabs+1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}
