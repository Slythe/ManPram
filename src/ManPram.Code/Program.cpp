#include <Arduino.h>

const int redPin = 6;
const int greenPin = 3;
const int bluePin = 5;


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



void moveToYellow(int currentRed, int currentGreen, int currentBlue)
{


	for (int i = 0; i < 255; i++){

		//values for red and green both need to go to 255
		currentRed = currentRed++;
		currentGreen = currentGreen++;

		//value for blue needs to be cycled down to 0
		currentBlue = currentBlue--;


		//set the values
		analogWrite(redPin, constrain(currentRed, 0, 255));
		analogWrite(greenPin, constrain(currentGreen, 0, 255));
		analogWrite(bluePin, constrain(currentBlue, 0, 255));
		
		delay(10);

		
	};

	
}


void setup()
{
	Serial.begin(9600);
	flashIgnitionStart();
}

void loop()
{

	analogWrite(redPin, 0);
	analogWrite(greenPin, 0);
	analogWrite(bluePin, 255);

	delay(1000);

	moveToYellow(0, 0, 255);

}