#include <iostream>
#include <vector>
#include <random>
using namespace std;

vector <vector <bool> > makeboard(int width, int height, int mines);
void printboard (vector <vector <int> > &board);

int main (int argc, char** argv)
{
  vector <vector <int> > board = { {-1, -1, -1}, {0, 4, 3}, {2, 3, 2} };
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
