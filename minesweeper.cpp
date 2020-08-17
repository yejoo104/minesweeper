#include <iostream>
#include <vector>
#include <random>
using namespace std;

vector <vector <bool> > makeboard(int width, int height, int mines);
void printboard (vector <vector <bool> > &board);

int main (int argc, char** argv)
{
  vector <vector <bool> > board = makeboard(4, 5, 3);
  printboard(board);
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

void printboard (vector <vector <bool> > &board)
{
  for (int i = 0; i < board.size(); i++)
  {
    for (int j = 0; j < board[i].size(); j++)
    {
      cout << board[i][j] << " ";
    }
    cout << "\n";
  }
}
