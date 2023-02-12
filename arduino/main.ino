#include <TFT.h>
#include <SPI.h>
#define CS 10
#define DC 9
#define RST 8
#define BKLIGHT 6           // Backlight control pin
#define BRIGHTNESS 204      // Backlight intensity (0-255)
#define RANGE 100           // Vertical size of the graph in pixels
#define WIDTH 128           // Horizontal size of Display in pixels
#define HEIGHT 160          // Vertical size of Display in pixels
#define PERSIST 500         // persistence of the graph (milliseconds)
#define peakThreshold 100   // R peak of an actual heartbeat
#define window 10000        // time window for heartRateVariability

// Initializing the TFT Object
TFT TFTscreen = TFT(CS, DC, RST);

// Variables required for the ECG Reading
long firstHeartBeat = 0, heartRateTimer;
double heartRateVariability = 0, defaultHeartRate = 72, heartInterval = 0;
int ECGReading = 0, holdRPeak = 0, graphReading;  
bool preventNearbyRs = 0;

// Variables required for the Buzzing
const byte buzzer = 7;
unsigned long lastPeriodStart;
const int periodDuration = 800, onDuration = 100, zeroSignal = 2000;
unsigned long currentMillis = millis();
unsigned long previousMillis = 500;

// Variables required for the LED
const long interval = 500; 
const int blueLedPin = 6;
const int redLedPin = 5;
int ledState = LOW;

// Initializing the values for the grapj
int value;         // Intial Point Drawn
int last_value;    // Last Point Drawn
int x_pos = 0;     // Graph cursor position
int offset = 20;   // Vertical graph displacement in pixels.

void setup() {
  Serial.begin(9600);               // Initializing Serial Port
  TFTscreen.begin();                // Initializing the KMR-1.8 SPI Display
  TFTscreen.setRotation(0);         // KMR-1.8 Screen Rotation
  TFTscreen.background(180,0,0);    // KMR-1.8 Blue Background
  TFTscreen.stroke(255,255,255);    // KMR-1.8 White Rectangle
  analogWrite(BKLIGHT,BRIGHTNESS);  // KMR-1.8 Brightness 
  TFTscreen.setTextSize(1);         // KMR-1.8 Text Size
  drawFrame();                      // Initializing the draw frame on KMR-1.8
  clearGraph();                     // Clearing the graph
  pinMode(3, INPUT);                // Electrode 1
  pinMode(2, INPUT);                // Electrode 2      
  pinMode(blueLedPin, OUTPUT);      // Blinks along the BPM
  pinMode(redLedPin, OUTPUT);       // Blinks when there is no signal
  pinMode(buzzer, OUTPUT);          // Buzzing along the BPM
}

void drawFrame()
{
  TFTscreen.stroke(255,255,255);    // KMR-1.8 White Title Rectangle
  TFTscreen.fill(255,255,255);      // Filling the screen  
  TFTscreen.rect(0, 0, WIDTH, 21);  // Max Upper Width  
  TFTscreen.setTextSize(1);         // Text Size
  TFTscreen.stroke(0,0,0);          // Black text
  TFTscreen.text("BPM:",2,2);       // BPM Text
  TFTscreen.text("Test",2,12);      // Actual BPM Reading
}

void clearGraph(){
  TFTscreen.stroke(127,127,127);    // Grey color for the border
  TFTscreen.fill( 180, 0, 0 );      // Dark Blue for the background
  TFTscreen.rect(0, 22, 128, 128);
  TFTscreen.line(65, 23, 65, 151);  // Vertical line
  TFTscreen.line(1, 85,127, 85);    // Horizontal line
  TFTscreen.stroke(0,0,255);        // Red plot
}

void plotLine(int last,int actual){
  
  if(x_pos==0) last= actual; // first value is a dot.
  TFTscreen.line(x_pos-1, last, x_pos, actual); // draw line.
  x_pos++;
  if(x_pos > WIDTH){
  x_pos=0;
  delay(PERSIST);
  clearGraph();
  }
}

void loop()
{

  if(defaultHeartRate < 23)
  {
    
    tone(buzzer, 1300, zeroSignal);

    if (currentMillis - previousMillis >= interval) 
      {
      previousMillis = currentMillis;
      if (ledState == LOW) 
      {
        ledState = HIGH;
      } 
      else 
      {
        ledState = LOW;
      }
      digitalWrite(redLedPin, ledState);
    }
  }

  // Reading the AD8226 Sensor
  ECGReading = analogRead(0);

  // Mapping the graph on the serial plotter
  ECGReading = map(ECGReading, 250, 400, 0, 100);
  
  // If we detect an 'R' peak and we are preventing an nearby a 'R'
  if((ECGReading > peakThreshold) && (!preventNearbyRs)) 
  {
    // Increase the value of the 'R' quantity
    holdRPeak++;  

    // Serial.println("Heartbeat Division");

    // Preventing nearby 'Rs'
    preventNearbyRs = 1;

    // Decreasing the interval of the first heart beat
    // substracting while the Arduino stills runs
    heartInterval = micros() - firstHeartBeat; 

    // Resetting the firstHeartBeat value
    firstHeartBeat = micros(); 
  }

  if ((defaultHeartRate >= 30) && (millis()-lastPeriodStart>=periodDuration))
    {
      lastPeriodStart+=periodDuration;
      tone(buzzer, 550, onDuration);

      if (currentMillis - previousMillis >= interval) 
      {
      
      previousMillis += currentMillis;

      if (ledState == LOW) 
      {
        ledState = HIGH;
      } 
      else 
      {
        ledState = LOW;
      }
    }
    digitalWrite(blueLedPin, ledState);
  }

  else if((ECGReading < peakThreshold)) 
  {
    // Avoiding P Peaks
    preventNearbyRs = 0;
  }

  if ((millis() - heartRateTimer) > 10000) 
  {
    // Heart Rate = (RR peaks in a window of 10 seconds) * 6;
    defaultHeartRate = holdRPeak * 6;
    heartRateTimer = millis();
    holdRPeak = 0; 
  }

  // HRV = (HR/60 - RR interval)
  heartRateVariability = defaultHeartRate / 60 - heartInterval / 1000000;

  // Serial Monitor Outputs
  Serial.print("BPM: ");
  Serial.print(defaultHeartRate);
  Serial.print(",");
  Serial.print("HRV: ");
  Serial.print(heartRateVariability);
  Serial.print(",");
  Serial.print("ECG Value: ");
  Serial.println(ECGReading);
  
  last_value = value;

  // value = To the ECG reading graph
  value = ECGReading;
  value= map(value,0,1023,149,23);
  value -= offset;
  if(value <= 100) value = 100; //truncate off screen values.
  plotLine(last_value , value);
  delay(50);
}
