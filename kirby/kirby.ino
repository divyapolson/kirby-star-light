// KIRBY STAR LIGHT
// An Arduino project by Divya Polson and Zara Abraham
// Prototyping Studio Winter 2020 
// A5: Nightlight 

int redPin = 3;
int greenPin = 5;
int bluePin = 6;
int speakerPin = 12;

int lightSensor = A0;
int pressureSensor = A2;
int lightValue = 0;
int pressureValue = 0;
int currentPressure = 0;

int partyMode = 0;

long previousMillis = 0;
int stopTime = 0;

// SUPER MARIO THEME credit: https://gist.github.com/internalbuffer/749273f46309a83ddc5d17703392616c

int delays[] = {150, 300, 300, 100, 300, 550, 575, 450, 400, 500, 300, 330, 150, 300, 200, 200, 150, 300, 150, 350, 300, 150, 150, 500, 450, 400, 500, 300, 330, 150, 300, 200, 200, 150, 300, 150, 350, 300, 150, 150, 500, 300, 100, 150, 150, 300, 300, 150, 150, 300, 150, 100, 220, 300, 100, 150, 150, 300, 300, 300, 150, 300, 300, 300, 100, 150, 150, 300, 300, 150, 150, 300, 150, 100, 420, 450, 420, 360, 300, 300, 150, 300, 300, 100, 150, 150, 300, 300, 150, 150, 300, 150, 100, 220, 300, 100, 150, 150, 300, 300, 300, 150, 300, 300, 300, 100, 150, 150, 300, 300, 150, 150, 300, 150, 100, 420, 450, 420, 360, 300, 300, 150, 300, 150, 300, 350, 150, 350, 150, 300, 150, 600, 150, 300, 350, 150, 150, 550, 325, 600, 150, 300, 350, 150, 350, 150, 300, 150, 600, 150, 300, 300, 100, 300, 550, 575};
int tone1[] = {660, 660, 660, 510, 660, 770, 380, 510, 380, 320, 440, 480, 450, 430, 380, 660, 760, 860, 700, 760, 660, 520, 580, 480, 510, 380, 320, 440, 480, 450, 430, 380, 660, 760, 860, 700, 760, 660, 520, 580, 480, 500, 760, 720, 680, 620, 650, 380, 430, 500, 430, 500, 570, 500, 760, 720, 680, 620, 650, 1020, 1020, 1020, 380, 500, 760, 720, 680, 620, 650, 380, 430, 500, 430, 500, 570, 585, 550, 500, 380, 500, 500, 500, 500, 760, 720, 680, 620, 650, 380, 430, 500, 430, 500, 570, 500, 760, 720, 680, 620, 650, 1020, 1020, 1020, 380, 500, 760, 720, 680, 620, 650, 380, 430, 500, 430, 500, 570, 585, 550, 500, 380, 500, 500, 500, 500, 500, 500, 500, 580, 660, 500, 430, 380, 500, 500, 500, 500, 580, 660, 870, 760, 500, 500, 500, 500, 580, 660, 500, 430, 380, 660, 660, 660, 510, 660, 770, 380};
int tone2[] = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 80, 100, 100, 100, 80, 50, 100, 80, 50, 80, 80, 80, 80, 100, 100, 100, 100, 80, 100, 100, 100, 80, 50, 100, 80, 50, 80, 80, 80, 80, 100, 100, 100, 100, 150, 150, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 150, 200, 80, 80, 80, 100, 100, 100, 100, 100, 150, 150, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 150, 150, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 150, 200, 80, 80, 80, 100, 100, 100, 100, 100, 150, 150, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 60, 80, 60, 80, 80, 80, 80, 80, 80, 60, 80, 60, 80, 80, 80, 80, 80, 60, 80, 60, 80, 80, 80, 80, 80, 80, 100, 100, 100, 100, 100, 100, 100};

//RED: 0, 255, 255, ORANGE: 0, 165, 255
//YELLOW: 0, 0, 255, GREEN: 255, 0, 255
//TEAL: 255, 0, 0, BLUE: 255, 255, 0
//PURPLE: 165, 255, 0, WHITE: 0, 0, 0

int redVal[] = {0, 0, 0, 255, 255, 255, 165, 0};
int greenVal[] = {255, 165, 0, 0, 0, 255, 255, 0};
int blueVal[] = {255, 255, 255, 255, 0, 0, 0, 0};

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  Serial.begin(9600);
  pinMode(speakerPin, OUTPUT);
}

void loop() {
  lightValue = analogRead(lightSensor);
  pressureValue = analogRead(pressureSensor);

  unsigned long currentMillis = millis();

  Serial.println(lightValue);

  // turns light on once room is dark
  if (lightValue <= 1000) {
    setColor(255,255,255);
  } else {
    setColor(0, 0, 0); 
  }

  // activates party mode when force sensitive resistor is pressed
  if (pressureValue > 500 && currentMillis > stopTime) {
    partyMode = 1;
  }

  // plays mario theme song and cycles through rainbow LEDs
  if (partyMode == 1) {
    for (int i = 0; i < 155; i++) {
      currentPressure = analogRead(pressureSensor);
      // toggles out of party mode if input sensor is pressed again
      if (i > 1) {
        if (currentPressure > 500) {
          stopTime = millis() + 500;
          partyMode = 0;
          break;
        }
      }
      setColor(redVal[i % 9], greenVal[i % 9], blueVal[i % 9]);
      tone(speakerPin, tone1[i], tone2[i]);
      delay(delays[i]);
      setColor(255, 255, 255);
    }
    noTone(speakerPin);
  }
}


void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}
