minesweeper: minesweeper.cpp
	g++ -std=c++17 -o minesweeper minesweeper.cpp
minesweeper2: minesweeper2.cpp
	g++ -std=c++17 -o minesweeper2 minesweeper2.cpp -lsfml-graphics -lsfml-window -lsfml-system
