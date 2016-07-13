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
