/*
If you want to learn how to use an OLED display, then watch my video on how to use them, connect them, and write code!
Video: https://www.youtube.com/watch?v=ee7MyGsxqqI

If you use this information anywhere, please cite the source. 
Sourse: https://www.youtube.com/@HuHamster
My GitHub: https://www.github.com/HuHamster
*/

// Required libraries for working with Adafruit OLED
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

// --- DISPLAY CONFIGURATION ---

// Defining screen size
#define SCREEN_WIDTH 128 // OLED display width in pixels
#define SCREEN_HEIGHT 64 // OLED display height in pixels

// Adafruit_SSD1306 object.
// SCREEN_ADDRESS - is the typical I2C address for SSD1306 (can be 0x3C or 0x3D)
#define OLED_RESET -1 // Reset Pin, use -1 if not connected (typical for I2C)
#define SCREEN_ADDRESS 0x3C 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// --- PIN AND GRAPH SETTINGS ---
const int ANALOG_PIN = A0; // Analog pin from which data is read (e.g., potentiometer)

// Graph width (128 pixels)
const int GRAPH_WIDTH = SCREEN_WIDTH;
// Graph area height (64 - 20 = 44 pixels. 20 pixels reserved for the value)
const int GRAPH_HEIGHT = 44; 
// Initial Y coordinate for the graph (top edge of the graph area)
const int GRAPH_Y_OFFSET = 20; 

// Array to store 128 history points
int history[GRAPH_WIDTH];

// --- SETUP ---
void setup() {
  // Initialize the display
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    // If the display is not found, a message can be output to Serial
    Serial.begin(9600);
    Serial.println(F("SSD1306 initialization error"));
    for(;;); // Infinite loop if the display is not working
  }

  // Set initial display parameters
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE); // Text color
  display.display();

  // Clear the history array
  for (int i = 0; i < GRAPH_WIDTH; i++) {
    history[i] = 0;
  }
}

// --- LOOP ---
void loop() {
  // 1. Read analog value
  int rawValue = analogRead(ANALOG_PIN); // Value from 0 to 1023

  // 2. Scale the value for the graph
  // Map 0-1023 to the range 0-GRAPH_HEIGHT (0-44)
  int mappedValue = map(rawValue, 0, 1023, 0, GRAPH_HEIGHT);

  // 3. Shift history: move all old points 1 position to the left
  for (int i = 0; i < GRAPH_WIDTH - 1; i++) {
    history[i] = history[i + 1];
  }

  // 4. Add the new (scaled) value to the end of the array
  history[GRAPH_WIDTH - 1] = mappedValue;

  // --- DISPLAY ON SCREEN (START) ---
  display.clearDisplay(); 

  // --- 1. DISPLAY CURRENT VALUE (TOP) ---


  // Output the numerical value
  display.setTextSize(2); 
  display.setCursor(0, 0); // Shift slightly lower for the number itself
  display.print(rawValue);
  
  // --- 2. DRAWING FRAME AND FILLED GRAPH (BOTTOM) ---

  // Drawing the frame to visualize the graph area
  display.drawRect(0, GRAPH_Y_OFFSET, GRAPH_WIDTH, GRAPH_HEIGHT, SSD1306_WHITE);

  for (int i = 0; i < GRAPH_WIDTH; i++) {
    int barHeight = history[i];
    
    // Calculate the starting Y coordinate for the filled part
    // GRAPH_Y_OFFSET (top of graph) + GRAPH_HEIGHT (full height) - barHeight (fill height)
    int startY = GRAPH_Y_OFFSET + GRAPH_HEIGHT - barHeight;
    
    // Drawing the filled vertical bar (column)
    // fillRect(X, Y, Width, Height, Color)
    display.fillRect(i, startY, 1, barHeight, SSD1306_WHITE);
  }

  // Update the display
  display.display(); 

  // Delay between updates
  delay(50); 
}
