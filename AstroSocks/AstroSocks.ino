//===----------------__ Hacking STEM Astro Socks Arduino __------------===//
// For use with the TODO:[add lesson title] lesson plan 
// available from Microsoft Education Workshop at 
// http://aka.ms/hackingSTEM
//
// Overview:
// Project detects analog voltage levels which correspond to 
// deformation of velostat flex sensors attached to a sock. 
// These values help us understand pressure points on the top part of the foot.
//
// Pins:
// A0 Toe Sensor
// A1 First Mid-foot Sensor
// A2 Second Mid-foot Sensor
// A3 Ankle Sensor
//
// This project uses an Arduino UNO microcontroller board, information at:
// https://www.arduino.cc/en/main/arduinoBoardUno
//
// Comments, contributions, suggestions, bug reports, and feature requests
// are welcome! For source code and bug reports see:
// http://github.com/[TODO: github path to Hacking STEM]
//
// Copyright 2019 Adi Azulay Microsoft EDU Workshop - HackingSTEM
// MIT License terms detailed in LICENSE.txt 
//===----------------------------------------------------------------------===//

const int kToeSensorPin = A0;
const int kFirstMidSensorPin = A1;
const int kSecondMidSensorPin = A2;
const int kAnkleSensorPin = A3;

const byte kNumberOfChannelsFromExcel = 6; 
//Incoming Serial Data Array
String incomingSerialData[kNumberOfChannelsFromExcel];

const String kDelimiter = ",";    // Data Streamer expects a comma delimeter
String inputString = "";          // String variable to hold incoming data
boolean stringComplete = false;   // Indicates complete string (newline found)
const int kSerialInterval = 10;   // Interval between serial writes
unsigned long serialPreviousTime; // Timestamp to track serial interval

// SETUP ----------------------------------------------------------------------
void setup() {
  // Initializations occur here
  Serial.begin(9600);  
}

// START OF MAIN LOOP --------------------------------------------------------- 
void loop()
{

  // Read Excel variables from serial port (Data Streamer)
  ProcessIncomingSerial();

  if (incomingSerialData[0] != "#pause")
  {
    // Process and send data to Excel via serial port (Data Streamer)
    ProcessOutgoingSerial();  
  }

}

// INCOMING SERIAL DATA PROCESSING CODE----------------------------------------
// Process serial data inputString from Data Streamer
void ParseSerialData()
{
  if (stringComplete) {     
    //Build an array of values from comma delimited string from Data Streamer
    ParseLine(inputString);

    inputString = ""; // reset inputString
    stringComplete = false; // reset stringComplete flag
  }
}

// OUTGOING SERIAL DATA PROCESSING CODE----------------------------------------
void SendDataToSerial() {
  // Read sensor values
  int toeReading = analogRead(kToeSensorPin);
  int firstMidReading = analogRead(kFirstMidSensorPin);
  int secondMidReading = analogRead(kSecondMidSensorPin);
  int ankleReading = analogRead(kAnkleSensorPin);

  // Send data out separated by a comma (kDelimiter)
  // Repeat next 2 lines of code for each variable sent:
  Serial.print(toeReading);
  Serial.print(kDelimiter);

  Serial.print(firstMidReading);
  Serial.print(kDelimiter);

  Serial.print(secondMidReading);
  Serial.print(kDelimiter);

  Serial.print(ankleReading);
  Serial.print(kDelimiter);

  Serial.println(); // Add final line ending character only once
}

// OUTGOING SERIAL DATA PROCESSING CODE----------------------------------------
void ProcessOutgoingSerial()
{
   // Enter into this only when serial interval has elapsed
  if((millis() - serialPreviousTime) > kSerialInterval) 
  {
    serialPreviousTime = millis(); // Reset serial interval timestamp
    SendDataToSerial(); 
  }
}

// INCOMING SERIAL DATA PROCESSING CODE----------------------------------------
void ProcessIncomingSerial()
{
  GetSerialData();
  ParseSerialData();
}

// Gathers bits from serial port to build inputString
void GetSerialData()
{
  while (Serial.available()) {
    char inChar = (char)Serial.read();    // Read new character
    inputString += inChar;                // Add it to input string
    if (inChar == '\n') {                 // If we get a newline... 
      stringComplete = true;              // Then we have a complete string
    }
  }
}

// Parses a single string of comma delimited values with line ending character
void ParseLine(String data) 
{
    int charIndex = 0; // Tracks the character we are looking at
    int arrayIndex = 0; // Tracks the array index to set values into
    while(arrayIndex < kNumberOfChannelsFromExcel) // Loop until full
    {
        String field = ParseNextField(data, charIndex);  // Parse next field
        incomingSerialData[arrayIndex] = field; // Add field to array
        arrayIndex++;   // Increment index
    }
}

// Parses the next value field in between the comma delimiters
String ParseNextField(String data, int &charIndex)
{
    if (charIndex >= data.length() )
    {
      return ""; //end of data
    }
    
    String field = "";
    bool hitDelimiter = false; // flag for delimiter detection 
    while (hitDelimiter == false) // loop characters until next delimiter
    {
        if (charIndex >= data.length() )
        {
          break; //end of data
        }

        if (String(data[charIndex]) == "\n") // if character is a line break
        {
          break; // end of data
        }
        
       if(String(data[charIndex]) == kDelimiter) // if we hit a delimiter
        {
          hitDelimiter = true;  // flag the delimiter hit
          charIndex++; // set iterator after delimiter so we skip next comma
          break;
        }
        else
        {        
          field += data[charIndex]; // add character to field string
          charIndex++; // increment to next character in data
        }
    }
    return field;
}
