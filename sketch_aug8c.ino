const int ledPins[5] = {2, 3, 4, 5, 6};
const int buttonPin1 = 8;
const int buttonPin2 = 9;

// Button state variables for toggle method
int button1_current = 0;
int button1_last = 0;
int button2_current = 0;
int button2_last = 0;

int counter = 0;

void setup() {
  // Initialize LED pins
  for (int i = 0; i < 5; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }

  // Initialize button pins with internal pull-up resistors
  pinMode(buttonPin1, INPUT_PULLUP); 
  pinMode(buttonPin2, INPUT_PULLUP);
  
  // Initialize button states
  button1_last = digitalRead(buttonPin1);
  button2_last = digitalRead(buttonPin2);
}

void loop() {
  buttonControl();
  showBinary(counter);
  delay(10); // Small delay to stabilize readings
}

void buttonControl() {
  // Read current button states
  button1_current = digitalRead(buttonPin1);
  button2_current = digitalRead(buttonPin2);
  
  // Check for button1 press (increment counter)
  // Detect falling edge: button was HIGH (not pressed) and now LOW (pressed)
  if (button1_last == HIGH && button1_current == LOW) {
    counter++;
    if (counter > 31) {
      counter = 0;
    }
  }
  
  // Check for button2 press (decrement counter)  
  // Detect falling edge: button was HIGH (not pressed) and now LOW (pressed)
  if (button2_last == HIGH && button2_current == LOW) {
    counter--;
    if (counter < 0) {
      counter = 31;
    }
  }
  
  // Update last button states for next iteration
  button1_last = button1_current;
  button2_last = button2_current;
}

void showBinary(int value) {
  // Display the 5-bit binary representation on LEDs
  for (int i = 0; i < 5; i++) {
    digitalWrite(ledPins[i], (value >> i) & 0x01);
  }
}