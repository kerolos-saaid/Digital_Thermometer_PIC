#include "Lcd_i2c.h"

#define LM35_CONVERSION_FACTOR 500.0
#define LM35_RESOLUTION 1023.5
#define HIGH_TEMPERATURE_THRESHOLD 40

// Function prototypes
float convert_adc_to_temperature(int adc_value);
void handle_temperature(float temperature);
void update_lcd_display(float temperature);

// Global variables
float temperature = 0;
unsigned char temperature_text[16] = "Temperature:";

void main() {
    // Initialize ports
    TRISA = 1;   // Set Port A as input
    TRISB = 0;   // Set Port B as output
    PORTA = 0x00;
    PORTB = 0x00;

    // Initialize peripherals
    ADC_Init();
    I2C1_Init(100000);
    I2C_LCD_Init();
    I2C_LCD_Cmd(_LCD_CURSOR_OFF);
    I2C_LCD_Cmd(_LCD_CLEAR);

    // Display initial temperature text on LCD
    I2C_Lcd_Out(1, 1, temperature_text);

    // Main loop
    while(1) {
        // Read temperature from ADC
        temperature = ADC_Read(0);
        // Convert ADC value to temperature
        temperature = convert_adc_to_temperature(temperature);
        // Handle temperature events
        handle_temperature(temperature);
        // Update temperature display on LCD
        update_lcd_display(temperature);
    }
}

// Convert ADC value to temperature
float convert_adc_to_temperature(int adc_value) {
    return (adc_value * LM35_CONVERSION_FACTOR) / LM35_RESOLUTION;
}

// Handle temperature events
void handle_temperature(float temperature) {
    // Check if temperature is above the high threshold
    if (temperature >= HIGH_TEMPERATURE_THRESHOLD) {
        // Handle high temperature event
        PORTB = 0b00000110;
    } else {
        // Handle low temperature event
        PORTB = 0b00000001;
    }
}

// Update temperature display on LCD
void update_lcd_display(float temperature) {
    unsigned char temperature_str[7]; // Maximum of 6 characters for the temperature
    // Convert temperature to string
    FloatToStr(temperature, temperature_str);
    // Limit the temperature to 5 digits (6 character in total: the decimal point and the 5 digits)
    temperature_str[6] = '\0';
    // Display temperature on LCD
    I2C_Lcd_Out(2, 1, temperature_str);
}