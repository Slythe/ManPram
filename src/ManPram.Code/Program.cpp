#include <Arduino.h>


//potentiometer pin
const uint8_t potPin = A0;
const uint8_t tempPin = 1;


//pins the RGB LED is hooked up to on the Arduino
const int redPin = 6;
const int greenPin = 3;
const int bluePin = 5;


//structure to hold RGB values for colours
struct colourValues {
	int redValue;
	int greenValue;
	int blueValue;
} yellow, orange, blue, red, green;


//current colour of the LED
colourValues currentColour;


int lastPotVal = 0;



void defineColours()
{

	red.redValue = 255;
	red.greenValue = 0;
	red.blueValue = 0;

	green.redValue = 0;
	green.greenValue = 255;
	green.blueValue = 0;

	blue.redValue = 0;
	blue.greenValue = 0;
	blue.blueValue = 255;

	yellow.redValue = 255;
	yellow.greenValue = 255;
	yellow.blueValue = 0;

	orange.redValue = 255;
	orange.greenValue = 165;
	orange.blueValue = 0;
	
}




int adjustColourValue(int currentValue, int requiredValue)
{

	if (currentValue > requiredValue){
		currentValue = currentValue--;
	}
	else if (currentValue < requiredValue){
		currentValue = currentValue++;
	};

	return currentValue;

}



void moveToColour(colourValues newColour, colourValues previousColour){


	for (int i = 0; i < 255; i++){


		//adjust values accordingly
		previousColour.redValue = adjustColourValue(previousColour.redValue, newColour.redValue);
		previousColour.greenValue = adjustColourValue(previousColour.greenValue, newColour.greenValue);
		previousColour.blueValue = adjustColourValue(previousColour.blueValue, newColour.blueValue);

		//set the values
		analogWrite(redPin, constrain(previousColour.redValue, 0, 255));
		analogWrite(greenPin, constrain(previousColour.greenValue, 0, 255));
		analogWrite(bluePin, constrain(previousColour.blueValue, 0, 255));
		
		//wait a little so the effect can be seen
		delay(10);

	};

	//keep track of the current colour values
	currentColour = newColour;

}



void flashIgnitionStart()
{

	for (int i = 0; i < 5; i++) {

		analogWrite(redPin, 0);
		analogWrite(greenPin, 255);
		analogWrite(bluePin, 0);

		delay(250);

		analogWrite(greenPin, 0);

		delay(125);

	}
	
	moveToColour(blue, green);

	currentColour = blue;

}



float readTemprature(){

	int sensorReading = analogRead(1);

	float voltage = sensorReading * 5.0;
	voltage /= 1024.0;

	float tempC = (voltage - 0.5) * 100;

	return tempC;

}



void setup()
{

	Serial.begin(9600);

	defineColours();

	flashIgnitionStart();

	
}


void loop()
{
	
	
	//Lights
	int potVal = map(analogRead(potPin), 0, 1023, 0, 4);


	if (potVal != lastPotVal)
	{

		lastPotVal = potVal;

		if (potVal == 0) moveToColour(blue, currentColour);
		else if (potVal == 1) moveToColour(yellow, currentColour);
		else if (potVal == 2) moveToColour(orange, currentColour);
		else moveToColour(red, currentColour);

	};


	analogRead(tempPin);
	delay(10);
	float tempC = (3.3 * analogRead(tempPin) * 100.0) / 1024;

	Serial.println(tempC);

	delay(1000);

}