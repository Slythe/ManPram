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


void moveToOrange(int currentRed, int currentGreen, int currentBlue)
{
	//255, 165, 0

	for (int i = 0; i < 255; i++){

		//cycle red up to 255
		currentRed = currentRed++;

		//cycle blue down to 0
		currentBlue = currentBlue--;

		//cycle green to the correct value
		if (currentGreen > 165)
		{
			currentGreen = currentGreen--;
		}
		else
		{
			currentGreen = currentGreen++;
		};

		//set the values
		analogWrite(redPin, constrain(currentRed, 0, 255));
		analogWrite(greenPin, constrain(currentGreen, 0, 255));
		analogWrite(bluePin, constrain(currentBlue, 0, 255));

		//wait a little so you can see the effect
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

	delay(2000);

	moveToYellow(0, 0, 255);

	delay(2000);

	moveToOrange(255, 255, 0);

	delay(2000);


}