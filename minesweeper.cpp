#include <iostream>
#include <vector>
#include <random>
#include <string>
using namespace std;

vector <vector <bool> > makeboard(int width, int height, int mines, int row, int column);
void printboard (vector <vector <int> > &board);
vector <vector <int> > updatetracker(vector < vector <int> > tracker, vector <vector <bool> > mineboard, int row, int column);
int around(vector <vector <bool> > mineboard, int row, int column);
void printarray (vector <vector <bool> > board);

int main (int argc, char** argv)
{
  vector <vector <bool> > board = makeboard(6, 7, 8, 3, 2);
  printarray(board);
  cout << around(board, 2, 4) << endl;

  /*
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

  string firstcoordinates;
  cout << "Input coordinates, row first and then space and then column. (ex: 4 2)" << endl;
  cin >> firstcoordinates;
  int firstrow = firstcoordinates[0] - '0' - 1;
  int firstcolumn = firstcoordinates[0] - '0' - 1;

  vector <vector <bool> > mineboard = makeboard(width, height, mines, firstrow, firstcolumn);
  vector <vector <int> > tracker(height, vector<int>(width, -1));
  printboard(tracker);
  */
}

vector <vector <bool> > makeboard(int width, int height, int mines, int row, int column)
{
  random_device device;
  mt19937 generator(device());
  uniform_int_distribution<> widthdis(0, width - 1);
  uniform_int_distribution<> heightdis(0, height - 1);

  int count = 0;
  float remaining = width * height;

  vector <vector <bool> > board(height, vector<bool>(width));

  while (count < mines)
  {
    int thisrow = heightdis(generator);
    int thiscolumn = widthdis(generator);

    if (thisrow == row && thiscolumn == column) continue;

    if (!board[thisrow][thiscolumn])
    {
      board[thisrow][thiscolumn] = true;
      count++;
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

vector <vector <int> > updatetracker(vector < vector <int> > tracker, vector <vector <bool> > mineboard, int row, int column)
{

}

int around(vector <vector <bool> > mineboard, int row, int column)
{
  int count = 0;
  for (int i = -1; i <= 1; i++)
  {
    if (row + i >= 0 && row + i < mineboard.size())
    {
      for (int j = -1; j <= 1; j++)
      {
        if (column + j >= 0 && column + j < mineboard[0].size())
        {
          if (mineboard[row + i][column + j]) count++;
        }
      }
    }
  }

  return count - mineboard[row][column];
}

void printarray (vector <vector <bool> > board)
{
  for (int i = 0; i < board.size(); i++)
  {
    for(int j = 0; j < board[i].size(); j++)
    {
      cout << board[i][j] << " ";
    }
    cout << endl;
  }
}
