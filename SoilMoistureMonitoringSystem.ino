#include <Adafruit_LiquidCrystal.h>

Adafruit_LiquidCrystal lcd_1(0);
int previousValue = -1;

void setup() {
    Serial.begin(9600);           // Start serial communication for debugging
    lcd_1.begin(16, 2);           // Initialize the LCD
    pinMode(A0, OUTPUT);          // Set A0 as an output pin to control power to the sensor
}

void loop() {
    digitalWrite(A0, HIGH);       // Power on the sensor
    delay(10);                    // Short delay to stabilize sensor output

    int rawValue = analogRead(A1); // Read the moisture level from sensor connected to A1
    int currentValue = readMoisturePercentage(rawValue); // Convert rawValue to percentage

    digitalWrite(A0, LOW);        // Power off the sensor

    if (currentValue != previousValue) {
        lcd_1.clear();
        lcd_1.print("Wilgotnosc Gleby");
        lcd_1.setCursor(0, 1);
        lcd_1.print(currentValue);
        lcd_1.print("%");

        previousValue = currentValue;
    }

    debug(rawValue, currentValue);

    delay(1000);
}

int readMoisturePercentage(int rawValue) {
    int minValue = 0;   // Minimum raw value expected from the sensor
    int maxValue = 150; // Maximum raw value expected from the sensor

    int percentage = map(rawValue, minValue, maxValue, 0, 100);
    percentage = constrain(percentage, 0, 100);

    return percentage;
}

void debug(int rawValue, int percentage) {
    Serial.print("Raw Value: ");
    Serial.println(rawValue);
    Serial.print("Mapped Percentage: ");
    Serial.println(percentage);
}
