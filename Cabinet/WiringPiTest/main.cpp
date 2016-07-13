#include <wiringPi.h>
#include <iostream>
using namespace std;
int main (void)
{
  wiringPiSetup() ;
  pinMode (0, INPUT) ;
  int i = 0;
 /* for (int i=0; i<20;i++)
  {
    digitalWrite (0, HIGH) ; delay (500) ;
    digitalWrite (0,  LOW) ; delay (500) ;
  }*/

  while(1)
  {
    if( digitalRead (0))
    {
        cout << "+" << flush;
        i++;
    }
    else
        cout << "-"<< flush;
    delay(1);
    cout << i << flush;
  }



  return 0 ;
}
