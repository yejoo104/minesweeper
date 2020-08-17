#include <iostream>
#include <vector>
#include <random>
#include <string>
using namespace std;

vector <vector <bool> > makeboard(int width, int height, int mines);
void printboard (vector <vector <int> > &board);

int main (int argc, char** argv)
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

vector <vector <bool> > makeboard(int width, int height, int mines)
{
  random_device device;
  mt19937 generator(device());
  uniform_real_distribution<> distribution(0.0, 1.0);

  int count = 0;
  float remaining = width * height;

  vector <vector <bool> > board(height, vector<bool>(width));
  for (int i = 0; i < board.size(); i++)
  {
    for (int j = 0; j < board[i].size(); j++)
    {
      if (distribution(generator) < (mines - count) / remaining)
      {
        board[i][j] = true;
        count++;
      }
      remaining--;
    }
  }
  return board;
}

void printboard (vector <vector <int> > &board)
{
  for (int i = 0; i < board.size(); i++)
  {
    for (int j = 0; j < board[i].size(); j++)
    {
      if (board[i][j] == -1)
      {
        cout << "? ";
      }
      else if (board[i][j] == 0)
      {
        cout << "_ ";
      }
      else
      {
        cout << board[i][j] << " ";
      }
    }
    cout << endl;
  }
}
