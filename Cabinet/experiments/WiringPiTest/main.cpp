#include <wiringPi.h>
#include <iostream>
using namespace std;
int main (void)
{
  wiringPiSetup() ;
  pinMode (0, INPUT) ;
  int i = 0;

  while(1)
  {
    if( digitalRead (0))
    {
        delay(20);
        if(digitalRead(0))
        {
            cout << "+" << flush;
        }
    }
    else
    {
        cout << "-"<< flush;
    }
    delay(125);
  }



  return 0 ;
}
