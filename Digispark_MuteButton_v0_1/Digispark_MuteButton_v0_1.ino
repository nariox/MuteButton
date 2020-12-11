#include <DigiKeyboard.h>

const int buttonPin = 2;
const int builtinledPin = 1;
const int ledPin = 0;

bool muteState = false; //start unmuted
bool buttonState;             // the current reading from the input pin
bool lastButtonState = LOW;   // the previous reading from the input pin

unsigned long CurTime = 0;
unsigned long ledPreTime = 0;
int ledState = LOW;

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup()
{
    pinMode(ledPin, OUTPUT);
    pinMode(buttonPin, INPUT_PULLUP);

    digitalWrite(ledPin, LOW);
}

void loop()
{
    bool reading = digitalRead(buttonPin);

    // If the switch changed, due to noise or pressing:
    if (reading != lastButtonState) {
        // reset the debouncing timer
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {
        if (reading != buttonState) {
          buttonState = reading;
          DigiKeyboard.sendKeyStroke(0); //to clear buffer
          // if the change is because button is pressed, change LED and press Ctrl+D
          if (buttonState == LOW) {
            muteState = !muteState;
            
            //Google Meet - Windows 
            DigiKeyboard.sendKeyStroke(KEY_D, MOD_CONTROL_LEFT );

            //Zoom - Chromebook/Linux
            //DigiKeyboard.sendKeyStroke(KEY_A, MOD_ALT_LEFT);
            
            // set the LED:
            digitalWrite(ledPin, muteState);
          }
        }

    }

    lastButtonState = reading;
    DigiKeyboard.delay(5);
}
