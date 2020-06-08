// Read the full tutorial at prusaprinters.org


#include <HID-Project.h>

#define REDUZIR_RESOLUCAO 2

// constants won't change. They're used here to set pin numbers:
const int BUTTON_PIN = 7;  // the number of the pushbutton pin
const int LED_PIN =  3;   // the number of the LED pin

// variables will change:
int buttonState = 0;   // variable for reading the pushbutton status
boolean ledState = false;
//

int lastValPot = 0;

void setup() {
  Serial.begin(9600); // Opens the serial connection used for communication with the PC. 
  Consumer.begin(); // Initializes the media keyboard
  // initialize the LED pin as an output:
  pinMode(LED_PIN, OUTPUT);
  // initialize the pushbutton pin as an pull-up input:
  // the pull-up input pin will be HIGH when the switch is open and LOW when the switch is closed.
  pinMode(BUTTON_PIN, INPUT_PULLUP);
} 

void loop() {  
  //Logica dos botoes e leds

  
  
  buttonState = digitalRead(BUTTON_PIN);

  if(buttonState == LOW){
    if(ledState == false){
      digitalWrite(LED_PIN, HIGH);
      ledState = true;
    }else{
      digitalWrite(LED_PIN, LOW);
      ledState = false;
    }
  }


  //Logica do volume
  int valPot = analogRead(5)>>REDUZIR_RESOLUCAO;
  valPot = map(valPot, 0, 1023>>REDUZIR_RESOLUCAO, 0, 300);
  analogWrite(9, valPot);
  if(valPot != lastValPot){
    if(valPot > lastValPot)
    Consumer.write(MEDIA_VOLUME_UP);
    else
    Consumer.write(MEDIA_VOLUME_DOWN);
    lastValPot = valPot;
    Serial.print("Encoder Value: "); // Text output of the rotation value used manily for debugging (open Tools - Serial Monitor to see it)
    Serial.println(valPot);
    
  }
  delay(10); // Wait 10 milliseconds, we definitely don't need to detect the rotary encoder any faster than that
  // The end of the loop() function, it will start again from the beggining (the begginging of the loop function, not the whole document)
  
}

  
