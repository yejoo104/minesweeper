#include <iostream>
#include <vector>
using namespace std;

vector <vector <bool> > makeboard(int width, int height);
void printboard (vector <vector <bool> > &board);

int main (int argc, char** argv)
{
  srand(time(0));
  vector <vector <bool> > board = makeboard(5, 5);
  printboard(board);
}

vector <vector <bool> > makeboard(int width, int height)
{
  vector <vector <bool> > board(width, vector<bool>(height));
  for (int i = 0; i < width; i++)
  {
    for (int j = 0; j < height; j++)
    {
      board[i][j] = rand() % 2;
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
