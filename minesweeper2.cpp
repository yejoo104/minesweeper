#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
using namespace sf;
using namespace std;

int main()
{
  string level;
  int width = 10;
  int height = 10;
  int mines = 10;

  int w = 32;
  Texture t;
  t.loadFromFile("tiles.jpg");
  Sprite s(t);

  RenderWindow app(VideoMode(w * width, w * height), "Minesweeper");

  // Display Board before Game Starts
  while (app.isOpen())
  {
    Event e;
    while (app.pollEvent(e))
    {
      if (e.type == Event::Closed) app.close();
    }

    for (int i = 0; i <= height;i++)
      for (int j = 0; j <= width; j++)
      {
        s.setTextureRect(IntRect(10 * w, 0, w, w));
        s.setPosition(i * w, j * w);
        app.draw(s);
      }

    app.display();
  }

  // First Click
}
