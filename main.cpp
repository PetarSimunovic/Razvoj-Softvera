#include <SFML/Graphics.hpp>
#include "kretanje.cpp"

int main()
{
    // Visina i širina prozora
    int screenWidth = 1000;
    int screenHeight = 800;

    // Renderiranje prozora
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Window text");

    // Učitamo privremnu teksturu stavimo "setSmooth" na true za anti-aliasing (Josipe guglaj to)
    // Čekamo da Martin pošalje teksture
    sf::Texture privermenaTekstura;
    privermenaTekstura.loadFromFile("PrivermenaTextura.png");
    privermenaTekstura.setSmooth(true);

    // Novi sprite igrac ako ti Mihelec zatreba negdje drugdje u programu samo mo mi reci da ga globaliziram ;) 
    sf::Sprite igrac;
    igrac.setTexture(privermenaTekstura);
    igrac.setOrigin(100.f,100.f);
    igrac.setPosition(screenHeight/2, screenWidth/2);
    

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // TODO: Dodaj delta time (ako iz nekog razloga nas lik ubrzava delta time ce nam to rijesiti)
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
                igrac.move(0.f,-5.f);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
                igrac.move(0.f,5.f);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                igrac.move(-5.f,0.f);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
                igrac.move(5.f,0.f);
            }

            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(igrac);
        window.display();
    }

    return 0;
}