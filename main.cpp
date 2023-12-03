#include <SFML/Graphics.hpp>
#include "math.h"


int main()
{
    // Visina i širina prozora
    int screenWidth = 1000;
    int screenHeight = 800;

    // Sat za delta time
    sf::Clock deltaClock;

    // Renderiranje prozora
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Window text");

    // Učitamo privremnu teksturu stavimo "setSmooth" na true za anti-aliasing (Josipe guglaj to)
    // Čekamo da Martin pošalje teksture
    sf::Texture privermenaTekstura;
    privermenaTekstura.loadFromFile("PrivermenaTextura.png");
    privermenaTekstura.setSmooth(true);

    // S ovime centriramo kameru na igraća
    sf::View center;
    
    // Novi sprite igrac ako ti Mihelec zatreba negdje drugdje u programu samo mo mi reci da ga globaliziram ;) 
    sf::Sprite igrac;
    igrac.setOrigin(100.f,100.f);
    igrac.setTexture(privermenaTekstura);
    igrac.setPosition(screenHeight/2, screenWidth/2);
    igrac.setRotation(0);

    // Sprite file to ćemo morati zaštititi od virusa
    sf::Sprite file;
    file.setTexture(privermenaTekstura);
    file.setOrigin(100.f,100.f);
    file.setPosition(screenHeight/2, screenWidth/2);
    file.setColor(sf::Color::Yellow);   


    sf::Vector2i pozicijaMisa; // Vektor 2 int
    sf::Vector2f pozicijaIgraca; // Vektor 2 float
    float kut;
    double misX, misB;

    while (window.isOpen())
    {
        sf::Event event;
        
        // Dobivamo vrijeme između slićica po sekundi
        float dt = deltaClock.restart().asSeconds();

        // Kod za kretanje
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            igrac.move(0.f,-500.f * dt);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            igrac.move(0.f,500.f * dt);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            igrac.move(-500.f * dt,0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            igrac.move(500.f * dt,0.f);
        }

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        // Ovaj kod sam shvatio 1/10 ali radi!!! hip hip hura!
        float dX = window.mapPixelToCoords(sf::Mouse::getPosition(window)).x - igrac.getPosition().x;
        float dY = window.mapPixelToCoords(sf::Mouse::getPosition(window)).y - igrac.getPosition().y;

        float angle = (atan2(dY, dX)*180)/3.14159;
        igrac.setRotation(angle + 90);

        center.setCenter(igrac.getPosition());
        window.clear(sf::Color::Blue);
        window.setView(center);
        window.draw(file);
        window.draw(igrac);
        window.display();
    }

    return 0;
}