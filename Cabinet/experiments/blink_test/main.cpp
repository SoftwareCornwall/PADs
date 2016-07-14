#include <iostream>
#include <wiringPi.h>

using namespace std;

int example_led()
{
    if ( wiringPiSetup() == -1)
        return -1;
    pinMode(0, OUTPUT);
    for (;;)
    {
        digitalWrite(0, LOW); delay(500);
        digitalWrite(0, HIGH); delay(500);
    }
    digitalWrite(0, LOW);
    return 0;
}

int main()
{
    example_led();
}
