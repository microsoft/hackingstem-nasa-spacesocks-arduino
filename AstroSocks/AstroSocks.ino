//===----------------__ Hacking STEM Astro Socks Arduino __------------===//
// For use with the Astro Socks lesson plan available from Microsoft 
// Education Workshop at http://aka.ms/hackingSTEM
//
// Overview:
// Project detects analog voltage levels which correspond to deformation 
// of velostat flex sensors attached to a sock. These values help us 
// understand pressure points on the top part of the foot.
//
// Pins:
// A0 Phalanges Sensor
// A1 Metatarsals Sensor
// A2 Tarsals Sensor
// A3 Ankle Sensor
//
// This project uses an Arduino UNO microcontroller board, information at:
// https://www.arduino.cc/en/main/arduinoBoardUno
//
// Comments, contributions, suggestions, bug reports, and feature requests
// are welcome! For source code and bug reports see:
// http://github.com/[TODO: github path to Hacking STEM]
//
// Copyright 2019 Jeremy Franklin-Ross & Adi Azulay Microsoft EDU 
// Workshop - HackingSTEM
// MIT License terms detailed in LICENSE.txt 
//===----------------------------------------------------------------------===//

const String kDelimiter = ",";    // Data Streamer expects a comma delimeter

// SETUP ----------------------------------------------------------------------
void setup() {
  // Initializations occur here
  Serial.begin(9600);  
}

// START OF MAIN LOOP --------------------------------------------------------- 
void loop()
{
  // Read sensor values
  int toeReading = analogRead(A0);
  int firstMidReading = analogRead(A1);
  int secondMidReading = analogRead(A2);
  int ankleReading = analogRead(A3);

  // Send data out separated by a comma (kDelimiter)
  Serial.print(kDelimiter); //first column reserved for commands

  Serial.print(toeReading);
  Serial.print(kDelimiter);

  Serial.print(firstMidReading);
  Serial.print(kDelimiter);

  Serial.print(secondMidReading);
  Serial.print(kDelimiter);

  Serial.print(ankleReading);
  Serial.print(kDelimiter);

  Serial.println(); // Add final line ending character only once

  delay(10); //delay 10 millisecond before looping again
}

