#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
  string level;
  int width;
  int height;
  int mines;

  while (true)
  {
    cout << "Type in B for Beginner (10x10 with 10 mines), I for Intermediate(16x16 with 40 mines), E for Expert(30x16 with 99 mines), and C for Custom Size." << endl;
    cin >> level;
    if (level == "B")
    {
      width = 10;
      height = 10;
      mines = 10;
      break;
    }
    if (level == "I")
    {
      width = 16;
      height = 16;
      mines = 40;
      break;
    }
    if (level == "E")
    {
      width = 30;
      height = 16;
      mines = 99;
      break;
    }
    if (level == "C")
    {
      cout << "Type in custom width." << endl;
      cin >> width;
      cout << "Type in custom height." << endl;
      cin >> height;
      cout << "Type in custom number of mines." << endl;
      cin >> mines;
      break;
    }
  }
}
