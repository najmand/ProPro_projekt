//cheap controls 67
int potPin = 35;
int delayLength = 200;
long currentMilli = 0;
int radianCount = 0;
int upCount = 1;
String endChar = String(char(0xff)) + String(char(0xff)) + String(char(0xff));
String dataFromDisplay = "";
int lastPotValue = -1; // Variable to track last potentiometer value
int memoryLocation = 10;

void setup() {
  Serial.begin(9600);
  //Serial.begin(9600);
  currentMilli = millis();
}

void loop() {
  if (millis() > currentMilli + delayLength){
    currentMilli = millis();
    radianCount = radianCount + upCount;

    if (radianCount > 63) {
      radianCount = 0;
    }

    float radianFloat = float (radianCount)/10; //vytvori skalu 0,0 do 6,2 //float y = float(x)/10
    int sineWaveValue = (sin(radianFloat) * 100) + 120; //sinus akceptuje pouze radiany //chceme rozumnou škálu v kladných hodnotách, normálně by šel -1 do 1
    Serial.print("wepo " + String(sineWaveValue) + "," + String(memoryLocation)); //poslání hodnoty do nextionu
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
    currentMilli = millis();
    
    Serial.println("Mem = " + String(memoryLocation) + " : " + "Value = " + String(sineWaveValue));
    memoryLocation+=4;
    if(memoryLocation > 800) 
    {memoryLocation = 10;}
    Serial.print("wepo 0," + String(memoryLocation)); //poslání hodnoty do nextionu
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
    
  }

     // Read potentiometer value and map it to slider range (1-100 for example)
    int potValue = analogRead(potPin);
    upCount = map(potValue, 0, 1023, 0, 255); // Adjust range as needed

    // Update the slider value only if it has changed significantly
    if (potValue != lastPotValue) {
      Serial.print("add 4,1," + String(upCount)); // Update slider with potentiometer value
      Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);
      lastPotValue = potValue; // Update lastPotValue to current
      Serial.print("h0.val=" + String(potValue));
      Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);
      
    }
    
    currentMilli = millis();


   // Čtení dat z displeje (pokud je potřeba ovlivnit upCount)
  if (Serial.available()){
    dataFromDisplay += char(Serial.read());
    upCount = dataFromDisplay.toInt();
    if (dataFromDisplay = "1")
    {memoryLocation = 10;}
    Serial.println(dataFromDisplay);
    dataFromDisplay = ""; // Reset stringu pro další čtení
    }
   
 

 // Změna barvy pozadí a textu na základě hodnoty upCount
  if (upCount >= 1 && upCount <= 4) {
    // Zelená pro hodnoty 1-4
    Serial.print("h0.bco=2016");  // Nastav barvu na zelenou (h0)
    Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);
    Serial.print("t0.pco=2016");  // Nastav barvu textu na zelenou (t0)
    Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);
  } 
  else if (upCount >= 5 && upCount <= 7) {
    // Žlutá pro hodnoty 5-7
    Serial.print("h0.bco=65504");  // Nastav barvu na žlutou (h0)
    Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);
    Serial.print("t0.pco=65504");  // Nastav barvu textu na žlutou (t0)
    Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);
  } 
  else if (upCount >= 8 && upCount <= 9) {
    // Červená pro hodnoty 8-9
    Serial.print("h0.bco=63488");  // Nastav barvu na červenou (h0)
    Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);
    Serial.print("t0.pco=63488");  // Nastav barvu textu na červenou (t0)
    Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);
  }

}

//void draw() {
//    if (mySerial.available() > 0 ) {
//         String value = mySerial.readString();
//         if ( value != null ) {
//              output.println( value );
//         }
//    }
//}
//
//void keyPressed() {
//    output.flush();  // Writes the remaining data to the file
//    output.close();  // Finishes the file
//    exit();  // Stops the program
//}

/*
void setup() {
  Serial.begin(9600);
  Serial.begin(9600);  // Používáte správný sériový port?
}

void loop() {
  // Testovací posílání hodnoty 100 do grafu s ID 4
  Serial.print("add 4,0,200");
  Serial.write(0xff); 
  Serial.write(0xff); 
  Serial.write(0xff); 

  delay(1000);  // Posílá každou sekundu
}
*/
