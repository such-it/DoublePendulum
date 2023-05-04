#include <iostream> 
#include <SFML/Graphics.hpp> 
#include <math.h>

#include "pendulum.hpp"

Pendulum :: Pendulum(sf :: Vector2f pos , float length , float angle , float mass)
: pos(pos) , length(length) , angle(angle) , mass(mass)

{
    velocity = 0.f;

    line[0].color = sf :: Color(20,20,20);
    line[1].color = sf :: Color(60,60,60);

    line[0].position = pos ; 
    pos = line[1].position = pos + sf :: Vector2f( length*-sin(angle) , length*cos(angle));

    circle.setRadius(15);
    circle.setFillColor(sf :: Color(255,165,0));
    circle.setPosition(sf :: Vector2f(pos.x - circle.getRadius() , pos.y - circle.getRadius()));
}

void Pendulum :: draw(sf :: RenderWindow & window)
{
    window.draw(line , 2 , sf :: Lines);
    window.draw(circle);
}

sf :: Vector2f Pendulum :: get_pos()
{
    return line[1].position ;
}


sf :: Vector2f update(Pendulum & p1 , Pendulum & p2 , float t)
{
    /*this is the article i have used to do the physics = https://www.myphysicslab.com/pendulum/double-pendulum-en.html */
    float m1 = p1.mass;
    float l1 = p1.length;
    float O1 = p1.angle ; 
    float v1 = p1.velocity ; 

    float m2 = p2.mass;
    float l2 = p2.length;
    float O2 = p2.angle ;
    float v2 = p2.velocity ; 

    float x1 = -g*(2*m1 + m2 )*sin(O1) ; 
    float x2 = -m2*g*sin(O1 - 2*O2)    ; 
    float x3 = -2*sin(O1 - O2)*m2      ; 
    float x4 = (v2*v2*l2 + v1*v1*l1*cos(O1 - O2));
    float y  = l1*(2*m1 + m2 - m2*cos(2*O1 - 2*O2));

    p1.velocity += ( x1 + x2 + (x3*x4))/(y) *t;
    p1.angle += p1.velocity *t ; 
    

    x1 = 2*sin(O1 - O2)      ;
    x2 = v1*v1*l1*(m1 + m2)  ;
    x3 = g*(m1 + m2)*cos(O1) ;
    x4 = v2*v2*l2*m2*cos(O1 - O2) ; 
    y = l2*(2*m1 + m2 - m2*cos(2*O1 - 2*O2));

    p2.velocity += (x1*(x2 + x3 + x4))/(y) *t; 
    p2.angle += p2.velocity*t ; 
    
    p1.angle = fmodf(p1.angle , 2*M_PI);
    p2.angle = fmodf(p2.angle , 2*M_PI);


    p1.pos = p1.line[1].position = p1.line[0].position + sf :: Vector2f( p1.length*-sin(p1.angle) , p1.length*cos(p1.angle));
    p1.circle.setPosition(sf :: Vector2f(p1.pos.x - p1.circle.getRadius() , p1.pos.y - p1.circle.getRadius()));

    p2.line[0].position = p1.get_pos() ; 
    p2.pos = p2.line[1].position = p2.line[0].position + sf :: Vector2f( p2.length*-sin(p2.angle) , p2.length*cos(p2.angle));
    p2.circle.setPosition(sf :: Vector2f(p2.pos.x - p2.circle.getRadius() , p2.pos.y - p2.circle.getRadius()));

    return p2.pos ; 
}
