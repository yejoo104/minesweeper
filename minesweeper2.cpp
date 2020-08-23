#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <queue>
using namespace sf;
using namespace std;

vector <vector <bool> > makeboard(int width, int height, int mines, int row, int column);
vector <vector <int> > updatetracker(vector < vector <int> > tracker, vector <vector <bool> > mineboard, int row, int column);
int around(vector <vector <bool> > mineboard, int row, int column);
void printarray (vector <vector <bool> > board);
void printarray (vector <vector <int> > board);

int main()
{
  string level;
  int width = 30;
  int height = 16;
  int mines = 99;

  int w = 32;
  Texture t;
  t.loadFromFile("tiles.jpg");
  Sprite s(t);

  RenderWindow app(VideoMode(w * width, w * height), "Minesweeper");

  // Display Board before Game Starts
  int firstrow;
  int firstcol;
  while (app.isOpen())
  {
    Vector2i pos = Mouse::getPosition(app);
    int x = pos.x / w;
    int y = pos.y / w;

    Event e;
    while (app.pollEvent(e))
    {
      if (e.type == Event::Closed) app.close();
    }

    // First Click
    if (e.type == Event::MouseButtonPressed)
      if (e.key.code == Mouse::Left)
        {
          firstcol = x;
          firstrow = y;
          break;
        }

    for (int i = 0; i <= height;i++)
      for (int j = 0; j <= width; j++)
      {
        s.setTextureRect(IntRect(10 * w, 0, w, w));
        s.setPosition(j * w, i * w);
        app.draw(s);
      }

    app.display();
  }

  // Initialize Board & Tracker after First Click
  vector <vector <int> > tracker(height, vector<int>(width, -1));
  vector <vector <bool> > mineboard = makeboard(width, height, mines, firstrow, firstcol);
  tracker = updatetracker(tracker, mineboard, firstrow, firstcol);

  // Game runs while in loop
  while (app.isOpen())
  {
    Vector2i pos = Mouse::getPosition(app);
    int x = pos.x / w;
    int y = pos.y / w;

    bool gameover = false;

    Event e;
    while (app.pollEvent(e))
    {
      if (e.type == Event::Closed) app.close();

      if (e.type == Event::MouseButtonPressed)
        if (e.key.code == Mouse::Left)
          if (mineboard[y][x]) gameover = true;
          else tracker = updatetracker(tracker, mineboard, y, x);
    }

    if (gameover) break;
    
    app.clear(Color::White);
    for (int i = 0; i < tracker.size(); i++)
      for (int j = 0; j < tracker[i].size(); j++)
      {
        if (tracker[i][j] == -1) s.setTextureRect(IntRect(10 * w, 0, w, w));
        else s.setTextureRect(IntRect(tracker[i][j] * w, 0, w, w));
        s.setPosition (j * w, i * w);
        app.draw(s);
      }

    app.display();
  }

  // Print Final Board
  while (app.isOpen())
  {
    Event e;
    while (app.pollEvent(e))
    {
      if (e.type == Event::Closed) app.close();
    }

    app.clear(Color::White);
    for (int i = 0; i < tracker.size(); i++)
      for (int j = 0; j < tracker[i].size(); j++)
      {
        if (mineboard[i][j]) s.setTextureRect(IntRect(9 * w, 0, w, w));
        else if (tracker[i][j] == -1) s.setTextureRect(IntRect(10 * w, 0, w, w));
        else if (tracker[i][j] == 0) s.setTextureRect(IntRect(0, 0, w, w));
        else s.setTextureRect(IntRect(tracker[i][j] * w, 0, w, w));
        s.setPosition (j * w, i * w);
        app.draw(s);
      }

    app.display();
  }
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
