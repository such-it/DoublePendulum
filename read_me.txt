// ream_me

Path = where sfml graphics lib exist

// compile
g++ -c main.cpp -I"Path\SFML-2.5.1\include"

// link
g++ main.o -o main -L"Path\SFML-2.5.1\lib" -lsfml-graphics -lsfml-window -lsfml-system
