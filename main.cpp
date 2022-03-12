#include<iostream>
#include "functii.h"

using namespace std;

int main() {
  int selectedOption;
  int startingOption = 1;
 
  cout << "Welcome to Speed Writer-Typero!!" << endl;
  GenerateFirstText();
  CheckAccuracy();
   Meniu();
   do {
     cin >> selectedOption;
     ProcessOption(selectedOption);
   }
   while (selectedOption != 2);
   return 0;
}