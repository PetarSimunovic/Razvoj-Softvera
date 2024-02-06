#include <SFML/Graphics.hpp>
#include <list>
#include <vector>
#include <string>
#include "math.h"

// Visina i širina prozora
int screenWidth = 1000;
int screenHeight = 800;

// Stvaranje prozora
sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Virus Destroyer");

// Definiramo globalnu teksturu jer nam treba u funkicji
sf::Texture virusTexture;

// Array di se nalaze svi virusi u igrici
sf::Sprite virusi[5];

// array za level 1 gdje sadrži koji svi virusi u levlu
// Jedan predstavalja normalog virusa
int level1[3] = {0,1,1};

int toDraw;

// Funkcija kreira virus
int createVirus(){
    for (int i = 1;i < sizeof(level1)/sizeof(int);i++){
        if (level1[i] == 1){
            virusi[i] = sf::Sprite(virusTexture);
            virusi[i].setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
            toDraw = i;
        }
        else {
            toDraw = 0;
        }
    }
}

// Gornja funkcija krira viruse u "Kompjuteru" a ovo ih crta
int drawVirus(){
    int ifDraw = toDraw ;
    if (ifDraw != 0){
        window.draw(virusi[toDraw]);
    }
    else{
        return 0;
    }
    
}

int main()
{

    // Sat za delta time
    sf::Clock deltaClock;
   
    // Učitamo teksturu igraca stavimo "setSmooth" na true za anti-aliasing (Josipe guglaj to)
    sf::Texture igracTekstura;
    igracTekstura.loadFromFile("igrac.jpg");
    igracTekstura.setSmooth(true);

    // Učitamo teksturu file stavimo 
    sf::Texture fileTekstura;
    fileTekstura.loadFromFile("file.JPG");
    fileTekstura.setSmooth(true);


    // S ovime centriramo kameru na igraća
    sf::View center;
    
    // Novi sprite igrac ako ti Mihelec zatreba negdje drugdje u programu samo mo mi reci da ga globaliziram ;) 
    sf::Sprite igrac;
    igrac.setOrigin(32.f,32.f);
    igrac.setTexture(igracTekstura);
    igrac.setPosition(screenHeight/2, screenWidth/2);
    igrac.setRotation(0);

    // Sprite file to ćemo morati zaštititi od virusa
    sf::Sprite file;
    file.setTexture(fileTekstura);
    file.setOrigin(100.f,100.f);
    file.setPosition(screenHeight/2, screenWidth/2);

    sf::Vector2i pozicijaMisa; // Vektor 2 int
    sf::Vector2f pozicijaIgraca; // Vektor 2 float
    float kut;
    double misX, misB;

    // Ovdje defiiramo stvari za funkciju
    virusTexture.loadFromFile("virus.jpg");
    virusTexture.setSmooth(true);

    while (window.isOpen())
    {
        window.clear(sf::Color::Blue);
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
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            createVirus();
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
        drawVirus();
        window.setView(center);
        window.draw(file);
        window.draw(igrac);
        window.display();
    }

    return 0;
}