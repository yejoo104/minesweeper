#include <iostream>
#include <vector>
using namespace std;

void printboard (vector <vector <int> > &board);

int main (int argc, char** argv)
{
  vector <vector <int> > board{ {2, 3},
                                {3, 1} };
  printboard(board);
}

void printboard (vector <vector <int> > &board)
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
