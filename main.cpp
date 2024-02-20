#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <array>
#include <vector> 
#include <stdlib.h> 
#include "math.h"

// Definiramo globalnu teksturu jer nam treba u funkicji    
sf::Texture virusTexture;
sf::Texture virusGunnerTexture;

std::vector<sf::Sprite> virusi;
std::vector<int> virusHP;
int val=0;

int spawnVirus(){
    if (val % 3 == 0 && val != 0){
        virusi.push_back(sf::Sprite(virusGunnerTexture));
        virusHP.push_back(3);
        virusi.back().setOrigin(32,32);
        float x = rand() % 1500 + -500;
        float y = rand() % 1500 + -500;
        virusi.back().setPosition(x,y);
    }
    else{
        virusi.push_back(sf::Sprite(virusTexture));
        virusHP.push_back(3);
        virusi.back().setOrigin(32,32);
        float x = rand() % 1500 + -500;
        float y = rand() % 1500 + -500;
        virusi.back().setPosition(x,y);
    }
}

int main()
{

    // Visina i širina prozora
    int screenWidth = 1000;
    int screenHeight = 800;

    // Stvaranje prozora
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Virus Destroyer");
    window.setFramerateLimit(240);

    // Sat za delta time
    sf::Clock deltaClock;
    sf::Clock randomSpawn;

    sf::Clock respawn;

    sf::Clock firerate;
    sf::Time elapsed;
    bool firedFirstTime=0;
    bool controlCounter=0;

    sf::Clock virusFirerate;
    sf::Time virusElapsed;
    bool virusFiredFirstTime=0;
    bool virusControlCounter=0;
   
    sf::Clock invFrames;
   
    sf::Font font;
    font.loadFromFile("Arial.ttf");

    sf::Text umro;
    umro.setFont(font);
    umro.setString("Izgubio si sve svoje životne bodove");
    umro.setCharacterSize(24);
    umro.setFillColor(sf::Color::Red);

    int hp = 3;

    sf::Text health;
    health.setFont(font);
    health.setString(std::to_string(hp));
    health.setFillColor(sf::Color::Red);
    health.setCharacterSize(24);
    
    sf::Text kakoIgrati;
    kakoIgrati.setFont(font);
    kakoIgrati.setString(L"Sa tipkama w,a,s,d se krećeš gore,dolje\n,desno,lijevo, a sa lijevim tipkom miša igraš,\n imaš 3 života i ako ih izgubiš moraš ćekati pet\n sekundi da se ponovo stvoriš, moraš zaštititi \n file od zlih virusa");
    kakoIgrati.setFillColor(sf::Color::White);
    kakoIgrati.setCharacterSize(24);

    // Učitamo teksturu igraca stavimo "setSmooth" na true za anti-aliasing (Josipe guglaj to)
    sf::Texture igracTekstura;
    igracTekstura.loadFromFile("igrac.png");
    igracTekstura.setSmooth(true);

    // Učitamo teksturu file stavimo 
    sf::Texture fileTekstura;
    fileTekstura.loadFromFile("file.png");
    fileTekstura.setSmooth(true);
    
    // Tekstura za metak
    sf::Texture bulletTexture;
    bulletTexture.loadFromFile("metak.png");
    bulletTexture.setSmooth(true);

    // Tekstura za neprijateljski metak
    sf::Texture virusBulletTexture;
    virusBulletTexture.loadFromFile("virusMetak.png");
    virusBulletTexture.setSmooth(true);

    // Teksture za main menu
    sf::Texture playTexture;
    playTexture.loadFromFile("play.png");
    playTexture.setSmooth(true);

    sf::Texture settingsTexture;
    settingsTexture.loadFromFile("audio.png");
    settingsTexture.setSmooth(true);

    sf::Texture logoTexture;
    logoTexture.loadFromFile("logo.png");
    logoTexture.setSmooth(true);
    
    sf::Texture kakoTexture;
    kakoTexture.loadFromFile("kakoigrati.png");
    kakoTexture.setSmooth(true);

    sf::Texture resetTexture;
    resetTexture.loadFromFile("settings.png");
    resetTexture.setSmooth(true);

    // S ovime centriramo kameru na igraća
    sf::View center;
    
    // Definiramo igraca 
    sf::Sprite igrac;
    // za dodavanje igraca
    igrac.setOrigin(32.f,32.f);
    igrac.setTexture(igracTekstura);
    igrac.setPosition(screenHeight/2, screenWidth/2);
    igrac.setRotation(0);
    
    // Sprite file to ćemo morati zaštititi od virusa
    sf::Sprite file;
    file.setTexture(fileTekstura);
    file.setOrigin(35.f,35.f);
    file.setPosition(screenHeight/2, screenWidth/2);
    int fileHp = 10;

    sf::Sprite play;
    play.setTexture(playTexture);
    play.setScale(0.1f,0.1f);
    play.setOrigin(20.48f,20.48f);
    play.setPosition(screenHeight/2, screenWidth/2);

    sf::Sprite settings;
    settings.setTexture(settingsTexture);
    settings.setScale(0.1f,0.1f);
    settings.setOrigin(20.48f,20.48f);
    settings.setPosition(screenHeight/2-200, screenWidth/2);

    sf::Sprite logo;
    logo.setTexture(logoTexture);
    logo.setScale(0.3f,0.3f);
    logo.setOrigin(7.96f,5.56f);
    logo.setPosition(screenHeight/2 -250, (screenWidth/2) - 400);
    bool runOnce= 1;

    sf::Sprite kako;
    kako.setTexture(kakoTexture);
    kako.setScale(0.2f,0.2f);
    kako.setOrigin(5.12f,5.12f);
    kako.setPosition(screenHeight/2+200, screenWidth/2);

    sf::Sprite reset;
    reset.setTexture(resetTexture);
    reset.setScale(0.1f,0.1f);
    reset.setOrigin(20.48f,20.48f);
    reset.setPosition(screenHeight/2, screenWidth/2);

    sf::RectangleShape kvadrat(sf::Vector2f(500.f, 200.f));
    kvadrat.setFillColor(sf::Color::Black);
    
    float kut;

    virusTexture.loadFromFile("virus.png");
    virusTexture.setSmooth(true);

    virusGunnerTexture.loadFromFile("gunner.png");
    virusGunnerTexture.setSmooth(true);

    bool mainMenuActive = true;
    bool soundOn = true;
    bool drawKvadrat = false;
    int menuNum =0 ;

    sf::SoundBuffer pucBuffer;
    pucBuffer.loadFromFile("puc.wav");
    sf::Sound puc;
    puc.setBuffer(pucBuffer);


    sf::SoundBuffer udarenBuffer;
    udarenBuffer.loadFromFile("udaren.wav");
    sf::Sound udaren;
    udaren.setBuffer(udarenBuffer);


    // Vektor za sve metke
    std::vector<sf::Sprite> bullets;
    std::vector<sf::Clock> bulletTime;
    std::vector<float> kutovi;

    //Vektor za sve metke od virusa
    std::vector<sf::Sprite> virusBullets;
    std::vector<sf::Clock> virusBulletTime;
    std::vector<float> virusKutovi;

    while (window.isOpen())
    {
       
        window.clear(sf::Color::White);
        sf::Event event;
        
        // Dobivamo vrijeme između slićica po sekundi
        float dt = deltaClock.restart().asSeconds();

        if(mainMenuActive){
        
            while (window.pollEvent(event)){
                if (event.type == sf::Event::Closed){
                    window.close();
                }
                else if (event.type == sf::Event::MouseButtonReleased){
                    if (drawKvadrat && event.mouseButton.button == sf::Mouse::Left){
                        drawKvadrat = false;
                        menuNum = 0;
                    }
                    if (event.mouseButton.button == sf::Mouse::Left){
                    if (play.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))){
                        mainMenuActive = 0;
                    }
                    if (kako.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))){
                        drawKvadrat = true;
                        menuNum = 1;
                    }
                    if (settings.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))){
                        soundOn = false;
                    }
                }
            }
        }
        
        window.draw(play);
        window.draw(settings);
        window.draw(kako);
        window.draw(logo);
        if (drawKvadrat){
            kvadrat.setPosition(screenHeight/2-200, screenWidth/2-100);
            window.draw(kvadrat);
        }
        if (menuNum == 1){
            kakoIgrati.setPosition(kvadrat.getPosition().x,kvadrat.getPosition().y);
            window.draw(kakoIgrati);
        }
        }
        else{

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
            if (event.type == sf::Event::Closed){
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed){
                if (!firedFirstTime && !controlCounter){
                    firerate.restart();
                    firedFirstTime =1;
                }
                sf::Time elapsed = firerate.getElapsedTime();
                if (event.mouseButton.button == sf::Mouse::Left){
                    if (elapsed.asSeconds() > 0.000500 || firedFirstTime){
                        firedFirstTime = 0;
                        controlCounter = 1;
                        bullets.push_back(sf::Sprite(bulletTexture));
                        bullets.back().setOrigin(6.f,6.f);
                        bullets.back().setPosition(igrac.getPosition());
                        kutovi.push_back(atan2(window.mapPixelToCoords(sf::Mouse::getPosition(window)).y - igrac.getPosition().y,
                                                window.mapPixelToCoords(sf::Mouse::getPosition(window)).x - igrac.getPosition().x));
                        bulletTime.push_back(sf::Clock());
                        firerate.restart();
                        if(soundOn){
                                puc.play();
                        }
                    }
                }
            }
        }
        float dX = window.mapPixelToCoords(sf::Mouse::getPosition(window)).x - igrac.getPosition().x;
        float dY = window.mapPixelToCoords(sf::Mouse::getPosition(window)).y - igrac.getPosition().y;

        float angle = (atan2(dY, dX)*180)/3.14159;
        igrac.setRotation(angle + 90);

        health.setPosition(igrac.getPosition().x - 500.f ,igrac.getPosition().y - 500.f);
        health.setString(std::to_string(hp));
        
        float fr = firerate.restart().asSeconds();
        
        sf::Time getInvFrames = invFrames.getElapsedTime();

        // Ovjde crtamo i posataljamo sve stvari koje nam se žele updateati svaki loop
        window.draw(file);
        center.setCenter(igrac.getPosition());
        for (int i = 0; i < virusi.size(); i++) {
            window.draw(virusi[i]);
            float kutVirusa;
            float iX = igrac.getPosition().x - virusi[i].getPosition().x;
            float iY = igrac.getPosition().y - virusi[i].getPosition().y;
            float fX = file.getPosition().x - virusi[i].getPosition().x;
            float fY = file.getPosition().y - virusi[i].getPosition().y; 
            if (sqrt(pow(iX, 2.0) + pow(iY, 2.0)) < sqrt(pow(fX, 2.0) + pow(fY, 2.0))) {
                kutVirusa = (atan2(iY, iX) * 180) / 3.14159;
            }
            else {
                kutVirusa = (atan2(fY, fX) * 180) / 3.14159;
            }
            virusi[i].setRotation(kutVirusa + 90);
            if (!virusi[i].getGlobalBounds().intersects(igrac.getGlobalBounds()) || !virusi[i].getGlobalBounds().intersects(file.getGlobalBounds())){
                virusi[i].move((300 * cos(kutVirusa))*dt,(300 * sin(kutVirusa))*dt);
            }
            if(igrac.getGlobalBounds().intersects(virusi[i].getGlobalBounds()) && getInvFrames.asSeconds() > 1.000000){
                hp--;
                invFrames.restart();
                if(soundOn){
                    udaren.play();
                }

            }
            if(file.getGlobalBounds().intersects(virusi[i].getGlobalBounds()) && getInvFrames.asSeconds() > 1.000000){
                fileHp--;
                invFrames.restart();
                if(soundOn){
                    udaren.play();
                }
            }
            //&& sqrt(pow(fX, 2.0) + pow(fY, 2.0)) < 100)
            if (virusi[i].getTexture() == &virusGunnerTexture){
                if (sqrt(pow(iX, 2.0) + pow(iY, 2.0)) < 800 ) {
                    if (!virusFiredFirstTime && !virusControlCounter){
                    virusFirerate.restart();
                    virusFiredFirstTime =1;
                    }
                    sf::Time virusElapsed = virusFirerate.getElapsedTime();
                    if (event.mouseButton.button == sf::Mouse::Left){
                        if (virusElapsed.asSeconds() > 0.005000 || virusFiredFirstTime){
                            virusFiredFirstTime = 0;
                            virusControlCounter = 1;
                            virusBullets.push_back(sf::Sprite(virusBulletTexture));
                            virusBullets.back().setOrigin(6.f,6.f);
                            virusBullets.back().setPosition(virusi[i].getPosition());
                            virusKutovi.push_back(atan2(igrac.getPosition().y - virusi[i].getPosition().y,
                                                    igrac.getPosition().x - virusi[i].getPosition().x));
                            virusBulletTime.push_back(sf::Clock());
                            virusFirerate.restart();
                            
                        }
                    }
                }
                else if(sqrt(pow(fX, 2.0) + pow(fY, 2.0)) < 800 ){
                     if (!virusFiredFirstTime && !virusControlCounter){
                    virusFirerate.restart();
                    virusFiredFirstTime =1;
                    }
                    sf::Time virusElapsed = virusFirerate.getElapsedTime();
                    if (event.mouseButton.button == sf::Mouse::Left){
                        if (virusElapsed.asSeconds() > 0.005000 || virusFiredFirstTime){
                            virusFiredFirstTime = 0;
                            virusControlCounter = 1;
                            virusBullets.push_back(sf::Sprite(virusBulletTexture));
                            virusBullets.back().setOrigin(6.f,6.f);
                            virusBullets.back().setPosition(virusi[i].getPosition());
                            virusKutovi.push_back(atan2(file.getPosition().y - virusi[i].getPosition().y,
                                                    file.getPosition().x - virusi[i].getPosition().x));
                            virusBulletTime.push_back(sf::Clock());
                            virusFirerate.restart();
                            
                        }
                    }
                }
            }
        }   
        for (int i =0;i < bullets.size();i++){
            window.draw(bullets[i]);
            bullets[i].move((1000*cos(kutovi[i]))*dt,(1000*sin(kutovi[i]))*dt);
            for (int j=0;j < virusi.size();j++){
                if (bullets[i].getGlobalBounds().intersects(virusi[j].getGlobalBounds())){
                    bullets.erase(bullets.begin()+ i);
                    kutovi.erase(kutovi.begin()+ i);
                    bulletTime.erase(bulletTime.begin() + i);
                    virusHP[j]--;
                }
                    if (virusHP[j]==0){
                    virusi.erase(virusi.begin() + j);
                    virusHP.erase(virusHP.begin()+j);
                    }
                    if(bulletTime[i].getElapsedTime().asSeconds() ==  sf::seconds(10.f).asSeconds()){
                        bullets.erase(bullets.begin() + i);
                        bulletTime.erase(bulletTime.begin() + i);
                        kutovi.erase(kutovi.begin() + i);
                        
                    }
                }
            }
        for (int i =0;i < virusBullets.size();i++){
            window.draw(virusBullets[i]);
            virusBullets[i].move((800*cos(virusKutovi[i]))*dt,(800*sin(virusKutovi[i]))*dt);
                if(virusBulletTime[i].getElapsedTime().asSeconds() ==  0.50000){
                        virusBullets.erase(virusBullets.begin() + i);
                        virusBulletTime.erase(virusBulletTime.begin() + i);
                        virusKutovi.erase(virusKutovi.begin() + i);

                }
                if (virusBullets[i].getGlobalBounds().intersects(igrac.getGlobalBounds()) &&  getInvFrames.asSeconds() > 1.000000){
                    hp--;
                    invFrames.restart();
                    if(soundOn){
                    udaren.play();
                    }
                }
                if (virusBullets[i].getGlobalBounds().intersects(file.getGlobalBounds()) &&  getInvFrames.asSeconds() > 1.000000){
                    fileHp--;
                    invFrames.restart();
                    if(soundOn){
                        udaren.play();
                    }
                }
            }

        sf::Time rng = randomSpawn.getElapsedTime();
        float intensity = 3.0000;
        if (rng.asSeconds() > intensity){
            spawnVirus();
            randomSpawn.restart();
            intensity / 0.90;
            val++;
        }
        runOnce = 0;
        window.setView(center);
        if (hp == 0){
            respawn.restart();
            sf::Time respawnTime = respawn.getElapsedTime();
            if (respawnTime.asSeconds() < 5.000000){
                window.draw(umro);
            }
        }
        else{
            window.draw(igrac);
        }
        window.draw(health);
        if (fileHp == 0){
            window.draw(reset);
            if(reset.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))){
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    virusi.clear();
                    virusHP.clear();
                    bullets.clear();
                    kutovi.clear();
                    bulletTime.clear();
                    virusBullets.clear();
                    virusKutovi.clear();
                    virusBulletTime.clear();
                    hp = 3;
                    fileHp = 10;

                }
            }
        }
    }
    window.display();
    }
    return 0;
}