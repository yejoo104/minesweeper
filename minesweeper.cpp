#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <queue>
using namespace std;

vector <vector <bool> > makeboard(int width, int height, int mines, int row, int column);
bool printboard (vector <vector <int> > &board, int mines = 0);
vector <vector <int> > updatetracker(vector < vector <int> > tracker, vector <vector <bool> > mineboard, int row, int column);
int around(vector <vector <bool> > mineboard, int row, int column);
void printfinal (vector <vector <bool> > board, vector <vector <int> > tracker);
void printarray (vector <vector <bool> > board);
void printarray (vector <vector <int> > board);

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

  vector <vector <int> > tracker(height, vector<int>(width, -1));
  printboard(tracker);

  int row;
  int col;
  cout << "Input coordinates, row first and then space and then column. (ex: 4 2)" << endl;
  cin >> row >> col;
  row--;
  col--;

  vector <vector <bool> > mineboard = makeboard(width, height, mines, row, col);

  tracker = updatetracker(tracker, mineboard, row, col);

  while(!printboard(tracker, mines))
  {
    cout << "Input coordinates, row first and then space and then column. (ex: 4 2)" << endl;
    cin >> row >> col;
    row--;
    col--;

    if (mineboard[row][col])
    {
      cout << "That's a mine!" << endl;
      printfinal(mineboard, tracker);
      return 0;
    }

    if (tracker[row][col] != -1)
    {
      cout << "You've already revealed that grid!" << endl;
      continue;
    }

    tracker = updatetracker(tracker, mineboard, row, col);
  }
  cout << "You won!" << endl;
  printfinal(mineboard, tracker);
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

bool printboard (vector <vector <int> > &board, int mines)
{
  cout << "Board:\n";
  int count = 0;
  for (int i = 0; i < board.size(); i++)
  {
    for (int j = 0; j < board[i].size(); j++)
    {
      if (board[i][j] == -1)
      {
        cout << "? ";
        count++;
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

  return count == mines;
}

vector <vector <int> > updatetracker(vector < vector <int> > tracker, vector <vector <bool> > mineboard, int row, int column)
{
  queue <vector <int> > myqueue;
  myqueue.push({row, column});
  while (!myqueue.empty())
  {
    vector <int> coordinates = myqueue.front();
    myqueue.pop();
    int minesnearby = around(mineboard, coordinates[0], coordinates[1]);
    tracker[coordinates[0]][coordinates[1]] = minesnearby;

    if (minesnearby == 0)
    {
      for (int i = -1; i <= 1; i++)
      {
        if(coordinates[0] + i >= 0 && coordinates[0] + i < mineboard.size())
        {
          for (int j = -1; j <= 1; j++)
          {
            if(coordinates[1] + j >= 0 && coordinates[1] + j < mineboard[0].size() && tracker[coordinates[0] + i][coordinates[1] + j] == -1)
            {
              myqueue.push({coordinates[0] + i, coordinates[1] + j});
            }
          }
        }
      }
    }
  }

  return tracker;
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

void printfinal (vector <vector <bool> > board, vector <vector <int> > tracker)
{
  cout << "Mine Locations:\n";
  for (int i = 0; i < board.size(); i++)
  {
    for (int j = 0; j < board[i].size(); j++)
    {
      if (board[i][j]) cout << "* ";
      else if (tracker[i][j] == -1) cout << "? ";
      else if (tracker[i][j] == 0) cout << "_ ";
      else cout << tracker[i][j] << " ";
    }
    cout << endl;
  }
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

void printarray (vector <vector <int> > board)
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
