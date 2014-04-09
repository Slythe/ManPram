#include <Arduino.h>

const int redPin = 6;
const int greenPin = 3;
const int bluePin = 5;



struct colourValues {
	int redValue;
	int greenValue;
	int blueValue;
} yellow, orange;



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

}



void defineColours()
{

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


void moveToColour(colourValues colour, int currentRed, int currentGreen, int currentBlue){


	for (int i = 0; i < 255; i++){


		//adjust values accordingly
		currentRed = adjustColourValue(currentRed, colour.redValue);
		currentGreen = adjustColourValue(currentGreen, colour.greenValue);
		currentBlue = adjustColourValue(currentBlue, colour.blueValue);

		//set the values
		analogWrite(redPin, constrain(currentRed, 0, 255));
		analogWrite(greenPin, constrain(currentGreen, 0, 255));
		analogWrite(bluePin, constrain(currentBlue, 0, 255));


		//wait a little so the effect can be seen
		delay(10);

	};


}


void setup()
{

	Serial.begin(9600);
	defineColours();
	flashIgnitionStart();
	
}


void loop()
{

	analogWrite(redPin, 0);
	analogWrite(greenPin, 0);
	analogWrite(bluePin, 255);

	delay(2000);

	moveToColour(yellow, 0, 0, 255);

	delay(2000);

	moveToColour(orange, 255, 255, 0);

	delay(2000);


}