#include <wiringPi.h>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

class Pi {
public:
    Pi();

    Pi(string message);

    //void blink(int delay);
    void transmit(unsigned int delay, bool state);

    void transmit2(unsigned int delay, bool state);

};

void blink(int del) {
    for (int i = 0; i < 10; i++) {
        digitalWrite(0, HIGH);
        delay(500);
        digitalWrite(0, LOW);
        delay(500);
    }

}

void Pi::transmit(unsigned int del, bool state) {
    digitalWrite(0, 0;
    delay(del);
    digitalWrite(0, state);
    delay(del);
}

Pi::Pi() {
    wiringPiSetup();
    pinMode(0, OUTPUT);
}

/*
int main() {
	wiringPiSetup();
	pinMode(0, OUTPUT);
	Pi pi;
	cout<<"lol";
	return 0;
}

*/
