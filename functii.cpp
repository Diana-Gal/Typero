#include<iostream>
#include <cstdlib>
#include<iomanip>
#include <string.h>
#include <chrono>

using namespace std::chrono;
using namespace std;

// Variabile globale
string errorChars = "";
string currentGeneratedText = "";
char topMistakenChar = '*';

//functia pt generare cuvinte aleatorii
void GenerateText() {
  currentGeneratedText = "";
  int textLength = 25;
  const char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
  srand(time(0)); // Pornim generatorul de sir de caractere
  for (int i = 0; i < textLength; i++) {
    //imparte sirul de caractere in siruri de caractere de cate 5
    if (i != 0 && i % 5 == 0) {
      currentGeneratedText += " "; //adauga spatiu la fiecare 5 caractere
    }

    if (topMistakenChar != '*' && i % 3 == 0) {
      currentGeneratedText += topMistakenChar;
    } else {
      //adaugare caracter random la sirul actual
      currentGeneratedText += alphabet[rand() % (sizeof(alphabet) - 1)];
    }
  }
}
//afisare primul text
void GenerateFirstText() {
  GenerateText();
  cout << currentGeneratedText << endl;
  cout << "Va rog tastati:" << endl;
}

void MostWrongChar() {
  const char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
  int topMistakesCounter = 0;

  if (errorChars.length() == 1 || errorChars.length() == 2)
    topMistakenChar = errorChars[0];
  else if (errorChars.length() > 2) {
    for (int i = 0; i < sizeof(alphabet); i++) {
      int currentMistakesCounter = 0;
      for (int j = 0; j < errorChars.length(); j++) {
        if (alphabet[i] == errorChars[j])
          currentMistakesCounter++;
      }

      if (currentMistakesCounter > topMistakesCounter) {
        topMistakesCounter = currentMistakesCounter;
        topMistakenChar = alphabet[i];
      }
    }
  }
}

//verifica acuratetea, viteza, cuv/minut, char/minut
void CheckAccuracy() {
  //atribuire valoare initiala
  errorChars = "";
  topMistakenChar = '*';

  double wpm, cpm;
  string textInserted;

  // returneaza timpul de start
  auto start = system_clock::now();
  cin >> ws; 
  getline(cin, textInserted);
  //returneaza timpul de la momentul opririi
  auto end = system_clock::now();
  cout << "\nAti tastat: " << textInserted << endl;

  // am folosit fct duration_cast din libraria chrono care calculeaza timpul in secunde
  long duration = duration_cast < seconds > (end - start).count();
  int textt= textInserted.length();
  cpm = textInserted.length() * 60 / duration ;
  wpm = cpm / 5;
  if (currentGeneratedText < textInserted) {
    //reduce numarul de caractere
    textInserted.resize(currentGeneratedText.length());
  } else if (currentGeneratedText > textInserted) {
    int noOfMissingChar = currentGeneratedText.length() - textInserted.length();
    for (int i = 0; i < noOfMissingChar; i++) {
      textInserted += "_";
    }
  }


  //verifica erorile din textul scris de user
  int errors = 0;
  for (int i = 0; i < currentGeneratedText.length(); i++) {
    if (currentGeneratedText[i] != ' ' && currentGeneratedText[i] != textInserted[i]) {
      errors++;
      errorChars += currentGeneratedText[i];
    }
  }

  cout << "Ati facut " << errors << " erori. " << endl;
  cout << "Timpul de tastare a fost de: " << setprecision(0) << duration << "s";
  printf(" (%.0fcpm sau %.0f cuvinte/min) \n", cpm, wpm);
  
  if (errors > 0) {
    MostWrongChar();
    cout << "Cel mai gresit caracter: " << topMistakenChar << endl << endl;
  }
}

void Meniu() {
  cout << "Selectati o optiune:" << endl;
  cout << "1. Afisati un nou text;" << endl;
  cout << "2. Exit." << endl;
}

void ProcessOption(int selectedOption) {
  switch (selectedOption) {
  case 1: {
    GenerateText();
    cout << currentGeneratedText << endl;
    cout << "Va rog tastati:" << endl;
    CheckAccuracy();
    cout << "Alegeti o alta optiune" << endl;
  }
  break;
  case 2:
    cout << "La revedere!";
    break;
  default:
    cout << "Ati ales o optiune gresita. Alegeti din nou" << endl;
    break;
  }
}