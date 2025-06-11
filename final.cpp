#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// DHT22 Temperature and Humidity Sensor
#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// Gas Sensors
#define MQ135_PIN 34
#define MQ7_PIN   32 // <<< CHANGED: Assigned MQ7 to a different pin (32). Both sensors cannot use the same pin (34).
                     // Please make sure to connect your MQ-7 sensor to pin 32 on your board.

// GP2Y1014AU Dust Sensor
#define DUST_LED_PIN 2
#define DUST_SENSOR_PIN 35

// LCD Display (20x4 I2C)
// Note: Common I2C addresses are 0x27 and 0x3F. If 0x27 doesn't work, try 0x3F.
LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
  // Start serial communication for debugging
  Serial.begin(115200);
  
  // Initialize DHT sensor
  dht.begin();
  
  // Set up Dust Sensor LED pin
  pinMode(DUST_LED_PIN, OUTPUT);

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Air Quality Monitor");
  lcd.setCursor(0, 1);
  lcd.print("   Initializing...  ");
  delay(2000);
  lcd.clear(); // Clear the screen for sensor readings
}

void loop() {
  // --- Read All Sensor Values ---

  // Read Temperature and Humidity from DHT22
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Read Gas Sensors
  int mq135Value = analogRead(MQ135_PIN);
  int mq7Value = analogRead(MQ7_PIN);
  
  // Read Dust Sensor
  int dustRaw = readDustSensor();

  // --- Check for Sensor Read Errors (Good Practice) ---
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("DHT Sensor Error");
    delay(2000);
    return; // Skip this loop iteration if DHT fails
  }

  // --- Print to Serial Monitor for Debugging ---
  Serial.println("===== SENSOR READINGS =====");
  Serial.print("Temperature: "); Serial.print(temperature); Serial.println(" C");
  Serial.print("Humidity: "); Serial.print(humidity); Serial.println(" %");
  Serial.print("MQ135 (Air Quality): "); Serial.println(mq135Value);
  Serial.print("MQ7 (Carbon Monoxide): "); Serial.println(mq7Value);
  Serial.print("Dust Raw: "); Serial.println(dustRaw);
  Serial.println("===========================\n");

  // --- Display Values on LCD Screen ---
  // ADDED: Clear the LCD at the start of the loop. This prevents "garbage" characters
  // from being left over when a new value has fewer digits than the old one.
  lcd.clear();

  // Display Temperature and Humidity on the first row
  lcd.setCursor(0, 0);
  lcd.print("T: ");
  lcd.print(temperature, 1); // Print with 1 decimal place
  lcd.print((char)223);      // Print the degree symbol
  lcd.print("C");
  
  lcd.setCursor(10, 0);
  lcd.print(" H: ");
  lcd.print(humidity, 1);    // Print with 1 decimal place
  lcd.print("%");

  // Display Air Quality (MQ135) on the second row
  lcd.setCursor(0, 1);
  lcd.print("Air Quality: ");
  lcd.print(mq135Value);

  // Display Carbon Monoxide (MQ7) on the third row
  lcd.setCursor(0, 2);
  lcd.print("CO Level   : ");
  lcd.print(mq7Value);

  // Display Dust on the fourth row
  lcd.setCursor(0, 3);
  lcd.print("Dust Level : ");
  lcd.print(dustRaw);

  // Wait for 2 seconds before the next reading
  delay(2000);
}

/**
 * @brief Reads the raw value from the GP2Y1014AU dust sensor.
 * This function handles the timing required to power the sensor's IR LED.
 * @return The raw analog reading from the dust sensor.
 */
int readDustSensor() {
  // Power the IR LED on the dust sensor
  digitalWrite(DUST_LED_PIN, LOW);
  delayMicroseconds(280);
  
  // Read the analog value from the sensor's output
  int rawValue = analogRead(DUST_SENSOR_PIN);
  
  // Turn the IR LED off to save power
  delayMicroseconds(40);
  digitalWrite(DUST_LED_PIN, HIGH);
  
  // Wait for the remainder of the 10ms cycle
  delayMicroseconds(9680);
  
  return rawValue;
}

// <<< REMOVED: There was an extra closing brace '}' here which would cause a compilation error.

