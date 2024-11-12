#include <WiFiNINA.h>                // Include WiFiNINA library for Wi-Fi connectivity
#include <Firebase_Arduino_WiFiNINA.h> // Include Firebase Arduino library for Firebase integration

// WiFi credentials
#define WIFI_SSID "Free"               // Wi-Fi SSID (network name)
#define WIFI_PASSWORD "12345678"       // Wi-Fi password

// Firebase credentials
#define FIREBASE_HOST "task7-807a2-default-rtdb.firebaseio.com"  // Firebase Realtime Database URL (host)
#define FIREBASE_AUTH "S1YLnWlLHBWvXpl4Txfc6Lg3xuXC4sOlgbrXDGNN" // Firebase Database secret key (authentication)

// LED pins for RGB LEDs connected to Arduino
const int redPin = 2;      // Pin connected to the Red LED
const int greenPin = 3;    // Pin connected to the Green LED
const int bluePin = 4;     // Pin connected to the Blue LED

// Firebase reference for retrieving data from Firebase
FirebaseData firebaseData;

// WiFi connection status
int status = WL_IDLE_STATUS;

void setup() {
  Serial.begin(9600);               // Start the serial communication at 9600 baud rate for debugging
  initializeLEDs();                  // Initialize LED pins as output

  // Connect to WiFi
  connectToWiFi();                   // Connect to the Wi-Fi network

  // Initialize Firebase
  initializeFirebase();              // Initialize Firebase with credentials
}

void loop() {
  // Fetch color data from Firebase and control LEDs
  fetchAndControlLEDs();

  delay(100);  // Small delay before the next loop iteration
}

// Function to initialize LED pins as output
void initializeLEDs() {
  pinMode(redPin, OUTPUT);          // Set Red LED pin as OUTPUT
  pinMode(greenPin, OUTPUT);        // Set Green LED pin as OUTPUT
  pinMode(bluePin, OUTPUT);         // Set Blue LED pin as OUTPUT
}

// Function to connect to Wi-Fi
void connectToWiFi() {
  Serial.print("Connecting to WiFi");  // Print message indicating the start of Wi-Fi connection
  while (status != WL_CONNECTED) {     // Loop until Wi-Fi is connected
    status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);  // Try to connect to Wi-Fi
    Serial.print(".");                  // Print a dot to indicate progress
    delay(300);                         // Wait for 300ms before trying again
  }
  Serial.println();                     // Move to the next line in serial monitor
  Serial.print("Connected with IP: ");  // Print the local IP address
  Serial.println(WiFi.localIP());       // Display the local IP address assigned by Wi-Fi
}

// Function to initialize Firebase
void initializeFirebase() {
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH, WIFI_SSID, WIFI_PASSWORD);  // Initialize Firebase with credentials
  Firebase.reconnectWiFi(true);  // Enable automatic reconnection if Wi-Fi is lost
  Serial.println("Connected to Firebase");  // Print confirmation of Firebase connection
}

// Function to fetch color data from Firebase and control the LEDs
void fetchAndControlLEDs() {
  if (Firebase.getString(firebaseData, "/ledControl/color")) {  // Retrieve the "color" string from Firebase
    String color = firebaseData.stringData();  // Store the received color string
    Serial.print("Received color: ");          // Print the received color
    Serial.println(color);                     // Display the received color
    controlLED(color);                         // Call function to control LED based on the received color
  } else {
    // If there's an error getting the data from Firebase
    Serial.println("Failed to get color from Firebase");  // Print failure message
    Serial.println(firebaseData.errorReason());          // Print the error reason
  }
}

// Function to control LEDs based on received color
void controlLED(String color) {
  // Turn off all LEDs initially
  digitalWrite(redPin, LOW);    // Ensure the Red LED is off
  digitalWrite(greenPin, LOW);  // Ensure the Green LED is off
  digitalWrite(bluePin, LOW);   // Ensure the Blue LED is off

  // Turn on the LED according to the color received
  if (color == "red") {         // If the received color is "red"
    digitalWrite(redPin, HIGH); // Turn on the Red LED
  } else if (color == "green") { // If the received color is "green"
    digitalWrite(greenPin, HIGH); // Turn on the Green LED
  } else if (color == "blue") {  // If the received color is "blue"
    digitalWrite(bluePin, HIGH);  // Turn on the Blue LED
  } else if (color == "off") {  // If the received color is "off"
    // Turn off all LEDs if the color is "off"
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
    Serial.println("All LEDs turned off");  // Print that all LEDs are turned off
  }
}
