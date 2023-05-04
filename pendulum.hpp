#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>

constexpr float g = 2.0f ; 

struct Pendulum
{ 
    float length ; 
    float angle ; 
    float velocity ; 
    float mass ;
    sf :: Vector2f pos ; 
    sf :: Vertex line[2]; 
    sf :: CircleShape circle ; 

    Pendulum(sf :: Vector2f pos, float length, float angle , float mass); 
    void draw(sf :: RenderWindow & window);
    
    sf :: Vector2f get_pos();
};

sf :: Vector2f update(Pendulum & p1 , Pendulum & p2 , float t);