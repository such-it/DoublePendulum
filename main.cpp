#include<iostream>
#include<SFML/Graphics.hpp>

#include "pendulum.hpp"
#include "pendulum.cpp"

int main()
{
    sf :: RenderWindow window(sf :: VideoMode(600,450) , "Double Pendulum" , sf :: Style :: Close);
    window.setFramerateLimit(60);

    sf :: Clock clock ; 
    sf :: VertexArray lines ; 

    sf :: CircleShape bob_point(5);
    bob_point.setFillColor(sf :: Color(255,100,0));
    bob_point.setPosition(sf :: Vector2f(300 - bob_point.getRadius(), 120 - bob_point.getRadius()));

    Pendulum p1(sf :: Vector2f(300 , 120) , 100 , M_PI/2 , 20);
    Pendulum p2(p1.get_pos() , 100 , M_PI , 20);

    while( window.isOpen() == true )
    {
        for ( sf :: Event event ; window.pollEvent(event) ; )
        {
            if ( event.type == sf :: Event :: Closed )
            {
                window.close() ; 
                break ; 
            }
        }
        window.setTitle(std :: to_string(static_cast<int>(1000.f/clock.getElapsedTime().asMilliseconds())));
        clock.restart();

        window.clear(sf :: Color(80,80,80));

        sf :: Vector2f point = update(p1 , p2 , 0.4);
        /*
        this can be used to draw the lines , but i'm concerned that it will overflow the memory, maybe there is a better way 
        which i dont know.
        */
        lines.append(sf :: Vertex(point , sf :: Color :: Black));        
        window.draw(&lines[0] , lines.getVertexCount() , sf :: LineStrip);
        
        window.draw(bob_point);
        p1.draw(window);
        p2.draw(window);
        
        window.display();
        
    }

    return 0 ; 
}
