
#include <SFML/Graphics.hpp>
#include <windows.h>
#include "game.h"
#include <iostream>
#include <fstream>
#include <SFML/Audio.hpp>


using namespace sf;
using namespace std;
extern int savehp;
int music = 50;
int sound = 50;
struct Level {
    bool unlock;
    bool winn;
    int enemyid;
};
void savenastr() {
    ofstream out("config.txt");
    if (out.is_open()) {
        out << music << "\n" << sound;
        out.close();

    }
}
void loadnastr() {
    ifstream in("config.txt");
    if (in.is_open()) {
        in>> music >> sound;
    }
}
bool persunlockk[4] = { false,true,false,false };
void savegame(int level, int akt, int viborpers, Level levels[], int q, int savhp) {
    ofstream out("save.txt");
    if (out.is_open()) {
       
        out << level << "\n" << akt << "\n" << viborpers << "\n" << savhp << "\n" << persunlockk[2] << "\n " << persunlockk[3] << "\n";
        for (int i = 1; i < 11; i++) {
            out << levels[i].unlock << " " << levels[i].winn << " " << levels[i].enemyid;
        }
        out.close();
    }
}

bool loadgame(int& level, int& akt, int& viborpers, Level levels[], int q, int& savhp) {
    ifstream in("save.txt");
    if (!in.is_open()) {
        return false;
    }
   
    in >> level >> akt >> viborpers >> savhp >> persunlockk[2] >> persunlockk[3];
    for (int i = 1; i < 11; i++) {
        in >> levels[i].unlock >> levels[i].winn >> levels[i].enemyid;
    }
    in.close();
    return true;
}

int main()
{   
    
    loadnastr();
    Music menumusic;
    if (menumusic.openFromFile("audio/01.ogg")) {
        menumusic.setLoop(true);
        menumusic.setVolume(static_cast<float>(music));
        menumusic.play();
    }
    SoundBuffer clickbufer;
    Sound click;
    if (clickbufer.loadFromFile("audio/click.ogg")) {
        click.setBuffer(clickbufer);
    }
    int tmusic = music;
    int tsound = sound;
    int currhp = -1;
    bool viborm = false;
    bool nastrm = false;
    int viborpers = 0;
    int level = 1;
    int akt = 1;
    Level levelss[11] = { {false,false,0}, {true,false,1}, {false,false,1} , {false,false,0},{false,false,1}, {false,false,1}, {false,false,1},
    {false,false,1}, {false,false,1},{false,false,1}, {false,false,1} };
    bool savve = loadgame(level, akt, viborpers, levelss, 11, currhp);

    RenderWindow window(VideoMode::getDesktopMode(), "kursovaya");
    ShowWindow(window.getSystemHandle(), SW_SHOWMAXIMIZED);
    View gameView(FloatRect(0.f, 0.f, 1920.f, 1080.f));
    window.setView(gameView);
    Texture fontex;
    fontex.loadFromFile("img/00.png");
    Texture ntex;
    ntex.loadFromFile("img/0.png");
    Texture playtex;
    playtex.loadFromFile("img/1.png");
    Texture prodoltex;
    prodoltex.loadFromFile("img/2.png");
    Texture nastrtex;
    nastrtex.loadFromFile("img/3.png");
    Texture pers02t;
    pers02t.loadFromFile("img/pers02.png");
    Texture pers03t;
    pers03t.loadFromFile("img/pers03.png");
    Texture pravilatex;
    pravilatex.loadFromFile("img/5.png");
    Texture vixodtex;
    vixodtex.loadFromFile("img/6.png");
    Texture vibortex;
    vibortex.loadFromFile("img/09.png");
    Texture play1tex;
    play1tex.loadFromFile("img/08.png");
    Texture vibor1tex;
    vibor1tex.loadFromFile("img/pe1.png");
    Texture vibor2tex;
    vibor2tex.loadFromFile("img/pe2.png"); 
    Texture viborunlock;
    viborunlock.loadFromFile("img/10unl.png");
    Texture vibor3tex;
    vibor3tex.loadFromFile("img/pe3.png");
    Texture viborpersatext;
    viborpersatext.loadFromFile("img/7.png");
    Texture vernutstex;
    vernutstex.loadFromFile("img/111.png");
    Texture pers01t;
    pers01t.loadFromFile("img/pers01.png");
    Texture prodolntex;
    prodolntex.loadFromFile("img/2n.png");
    Texture nastrr;
    nastrr.loadFromFile("img/nastroika.png");
    Sprite nastroika;
    nastroika.setTexture(nastrr);
    nastroika.setPosition(560, 240);
    Texture plust;
    plust.loadFromFile("img/plus.png");
    Texture minust;
    minust.loadFromFile("img/minus.png");
    Texture prt;
    prt.loadFromFile("img/jn.png");
    Texture vrt;
    vrt.loadFromFile("img/jk.png");
    Texture muzt;
    muzt.loadFromFile("img/mus.png");
    Texture zvt;
    zvt.loadFromFile("img/zv.png");
    Texture soxrtex;
    soxrtex.loadFromFile("img/soxr.png");
    Texture delsoxrtex;
    delsoxrtex.loadFromFile("img/delsohr.png");
    Texture vixdtex;
    vixdtex.loadFromFile("img/vih.png");
    Sprite pluss;
    pluss.setTexture(plust);
    pluss.setPosition(1220, 320);
    Sprite minuss;
    minuss.setTexture(minust);
    minuss.setPosition(820, 330);
    Sprite ple;
    ple.setTexture(prt);
    Sprite pli;
    pli.setTexture(vrt);
    Sprite muzz;
    muzz.setTexture(muzt);
    muzz.setPosition(620, 320);
    Sprite zvv;
    zvv.setPosition(620, 440);
    zvv.setTexture(zvt);
    Sprite soxr;
    soxr.setTexture(soxrtex);
    soxr.setPosition(610, 680);
    Sprite deletsoxr;
    deletsoxr.setTexture(delsoxrtex);
    deletsoxr.setPosition(762, 530);
    Sprite vihodd;
    vihodd.setTexture(vixdtex);
    vihodd.setPosition(970, 680);
    Sprite pluss2;
    pluss2.setTexture(plust);
    pluss2.setPosition(1220, 440);
    Sprite minuss2;
    minuss2.setTexture(minust);
    minuss2.setPosition(820, 445);
   
    Sprite fon;
    fon.setTexture(fontex);
    Sprite n;
    n.setTexture(ntex);
    n.setPosition(770, 0);
    Sprite play;
    play.setTexture(playtex);
    play.setPosition(740, 300);
    bool prodoll = savve && !levelss[10].winn;
    Sprite prodol;
    if (prodoll) {
        prodol.setTexture(prodoltex);
    }
    else {
        prodol.setTexture(prodolntex);
    }
    prodol.setPosition(740,400 );
    Sprite nastr;
    nastr.setTexture(nastrtex);
    nastr.setPosition(740, 510);
    
    Sprite pravila;
    pravila.setTexture(pravilatex);
    pravila.setPosition(740, 620);
    Sprite vixod;
    vixod.setTexture(vixodtex);
    vixod.setPosition(740, 730);
    Sprite vibor;
    vibor.setTexture(vibortex);
    vibor.setPosition(1070, 290);
    Sprite vibor1;
    vibor1.setTexture(vibor1tex);
    vibor1.setPosition(360, 250);
    Sprite vibor2;
    if (persunlockk[2]) vibor2.setTexture(vibor2tex);
    else vibor2.setTexture(viborunlock);
    vibor2.setPosition(360, 405);
    Sprite vibor3;
    if (persunlockk[3]) vibor3.setTexture(vibor3tex);
    else vibor3.setTexture(viborunlock);
    vibor3.setPosition(360, 560);
    Sprite play1;
    play1.setTexture(play1tex);
    play1.setPosition(735, 300);
    Sprite viborpersa;
    viborpersa.setTexture(viborpersatext);
    viborpersa.setPosition(1470, 625);
    Sprite vernuts;
    vernuts.setTexture(vernutstex);
    vernuts.setPosition(1115, 625);
    
    RectangleShape zatemnenie;
    zatemnenie.setSize(Vector2f(1920.f, 1080.f));
    zatemnenie.setFillColor(Color(0, 0, 0, 150));
    zatemnenie.setPosition(0.f, 0.f);


    
    
    
    Image icon;
    icon.loadFromFile("img/0.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr()
    );
    while (window.isOpen())
    {
        View gameplayView(FloatRect(0.f, 0.f, 1920.f, 1080.f));
        window.setView(gameplayView);
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                
                window.close();

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window), window.getView());
                if (nastrm) {
                    if (minuss.getGlobalBounds().contains(mouse)) {
                        if (music > 0) music -= 25;
                        menumusic.setVolume(static_cast<float>(music));
                        click.setVolume(static_cast<float>(sound)); click.play();
                    }
                    if (pluss.getGlobalBounds().contains(mouse)) {
                        if (music < 100) music += 25;
                        menumusic.setVolume(static_cast<float>(music));
                        click.setVolume(static_cast<float>(sound)); click.play();
                    }
                    if (minuss2.getGlobalBounds().contains(mouse)) {
                        if (sound > 0) sound -= 25;
                        click.setVolume(static_cast<float>(sound));
                        click.setVolume(static_cast<float>(sound)); click.play();
                    }
                    if (pluss2.getGlobalBounds().contains(mouse)) {
                        if (sound < 100) sound += 25;
                        click.setVolume(static_cast<float>(sound));
                        click.setVolume(static_cast<float>(sound)); click.play();
                    }
                    if (deletsoxr.getGlobalBounds().contains(mouse)) {
                        remove("save.txt");
                        prodoll = false;

                        prodol.setTexture(prodolntex);
                        savve = false;

                        persunlockk[2] = false;
                        persunlockk[3] = false;

                        vibor2.setTexture(viborunlock);
                        vibor3.setTexture(viborunlock);

                        if (viborpers == 2 || viborpers == 3) {
                            viborpers = 0;
                            vibor.setTexture(vibortex); 
                        }

                        click.setVolume(static_cast<float>(sound)); click.play();
                    }
                    if (soxr.getGlobalBounds().contains(mouse)) {
                        savenastr();
                        tmusic = music;
                        tsound = sound;
                        nastrm = false;
                        click.setVolume(static_cast<float>(sound)); click.play();
                    }
                    if (vihodd.getGlobalBounds().contains(mouse)) {
                        music = tmusic;
                        sound = tsound;
                        menumusic.setVolume(static_cast<float>(music));
                        nastrm = false;
                        click.setVolume(static_cast<float>(sound)); click.play();
                    }
               }
                else if (!viborm) {
                    if (play.getGlobalBounds().contains(mouse)) {
                        viborm = true;
                        viborpers = 0;
                        click.setVolume(static_cast<float>(sound)); click.play();
                    }
                   

                  
                    if (prodoll &&prodol.getGlobalBounds().contains(mouse.x, mouse.y)) {
                        if (loadgame(level, akt, viborpers, levelss, 11,currhp)) {
                            extern Level act1lvl[11];
                            for (int i =1; i < 11; i++) {
                                act1lvl[i] = levelss[i];
                            }
                            if (persunlockk[2]) vibor2.setTexture(vibor2tex);
                            else vibor2.setTexture(viborunlock);

                            if (persunlockk[3]) vibor3.setTexture(vibor3tex);
                            else vibor3.setTexture(viborunlock);
                            click.setVolume(static_cast<float>(sound)); click.play();
                            menumusic.stop();
                            window.setVisible(false);
                            gamewin(true, viborpers);
                            window.setVisible(true);
                            extern bool persunlock[4];
                            persunlockk[2] = persunlock[2];
                            persunlockk[3] = persunlock[3];
                            if (persunlockk[2]) vibor2.setTexture(vibor2tex);
                            else vibor2.setTexture(viborunlock);

                            if (persunlockk[3]) vibor3.setTexture(vibor3tex);
                            else vibor3.setTexture(viborunlock);
                            savve = loadgame(level, akt, viborpers, levelss, 11, currhp);
                            prodoll = savve && !levelss[10].winn;

                            if (prodoll) {
                                prodol.setTexture(prodoltex);
                            }
                            else {
                                prodol.setTexture(prodolntex);
                            }
                            loadnastr();
                            tmusic = music;
                            tsound = sound;
                            savve = loadgame(level, akt, viborpers, levelss, 11, currhp);
                            loadnastr();
                            menumusic.setVolume(static_cast<float>(music));
                            menumusic.play();
                            prodoll = savve &&!levelss[10].winn;
                            if (prodoll) prodol.setTexture(prodoltex);
                            else prodol.setTexture(prodolntex);
                            click.setVolume(static_cast<float>(sound)); click.play();
                        }
                        viborm = false;
                    }

                    if (nastr.getGlobalBounds().contains(mouse.x, mouse.y)) {
                        nastrm = true;
                        click.setVolume(static_cast<float>(sound)); click.play();
                    }
                    if (pravila.getGlobalBounds().contains(mouse.x, mouse.y)) {
                        click.setVolume(static_cast<float>(sound)); click.play();
                        ShellExecuteA(NULL, "open", "pr.chm", NULL, NULL, SW_SHOWNORMAL);
                    }

                    
                    if (vixod.getGlobalBounds().contains(mouse.x, mouse.y))
                    {
                        click.setVolume(static_cast<float>(sound)); click.play();
                        window.close();
                    }
                }
                else {
                    
                    if (vibor1.getGlobalBounds().contains(mouse)) {
                        viborpers = 1;
                        vibor.setTexture(pers01t);
                        click.setVolume(static_cast<float>(sound)); click.play();
                    }
                    if (vibor2.getGlobalBounds().contains(mouse)&& persunlockk[2]) {
                        viborpers = 2;
                        vibor.setTexture(pers02t);
                        click.setVolume(static_cast<float>(sound)); click.play();
                    }
                        
                    if (vibor3.getGlobalBounds().contains(mouse)&& persunlockk[3]) {
                        viborpers = 3;
                        vibor.setTexture(pers03t);
                        click.setVolume(static_cast<float>(sound)); click.play();

                    }
                        if (viborpersa.getGlobalBounds().contains(mouse.x, mouse.y)) {
                            if (viborpers != 0) {
                                level = 1;
                                akt = 1;
                                currhp = -1;
                                levelss[1] = { true,false,1 };
                                for (int i = 1; i < 11; i++) {
                                    levelss[i] = { false,false,1 };
                                }
                                savegame(level, akt, viborpers, levelss, 11,currhp);
                                menumusic.stop();
                                window.setVisible(false);
                                gamewin(false,viborpers);
                                window.setVisible(true);
                                extern bool persunlock[4];
                                persunlockk[2] = persunlock[2];
                                persunlockk[3] = persunlock[3];
                                if (persunlockk[2]) vibor2.setTexture(vibor2tex);
                                else vibor2.setTexture(viborunlock);

                                if (persunlockk[3]) vibor3.setTexture(vibor3tex);
                                else vibor3.setTexture(viborunlock);
                                savve = loadgame(level, akt, viborpers, levelss, 11, currhp);
                                prodoll = savve && !levelss[10].winn;

                                if (prodoll) {
                                    prodol.setTexture(prodoltex);
                                }
                                else {
                                    prodol.setTexture(prodolntex); 
                                }
                                click.setVolume(static_cast<float>(sound)); click.play();
                          
                                loadnastr();
                                menumusic.setVolume(static_cast<float>(music));
                                menumusic.play();
                                tmusic = music;
                                tsound = sound;
                                viborm = false;
                                prodoll = true;
                                prodol.setTexture(prodoltex);
                              
                                vibor.setTexture(vibortex);
                              
                            }
                        }
                    



                    if (vernuts.getGlobalBounds().contains(mouse.x, mouse.y)) {
                        viborm = false;
                        vibor.setTexture(vibortex);
                        click.setVolume(static_cast<float>(sound)); click.play();
                    }
                }
                
            
               
            }
        }
           

        Vector2f mous = window.mapPixelToCoords(Mouse::getPosition(window), window.getView());
      
  
        play.setScale(1.0f, 1.0f);
        prodol.setScale(1.0f, 1.0f);
        nastr.setScale(1.0f, 1.0f);
        
        pravila.setScale(1.0f, 1.0f);
        vixod.setScale(1.0f, 1.0f);
        viborpersa.setScale(1.0f, 1.0f);
        vibor1.setScale(1.0f, 1.0f);
        vibor2.setScale(1.0f, 1.0f);
        vibor3.setScale(1.0f, 1.0f);
        vernuts.setScale(1.0f, 1.0f);
        vibor1.setScale(1.0f, 1.0f);
        vibor2.setScale(1.0f, 1.0f);
        vibor3.setScale(1.0f, 1.0f);
        soxr.setScale(1.0f, 1.0f);
        deletsoxr.setScale(1.0f, 1.0f);
        vihodd.setScale(1.0f, 1.0f);
            if (!viborm && !nastrm) {
            if (play.getGlobalBounds().contains(mous))
                play.setScale(1.2f,1.2f);
            if (prodoll &&prodol.getGlobalBounds().contains(mous))
                prodol.setScale(1.2f, 1.2f);
            if (nastr.getGlobalBounds().contains(mous))
                nastr.setScale(1.2f, 1.2f);
         
            if (pravila.getGlobalBounds().contains(mous))
                pravila.setScale(1.2f, 1.2f);
            if (vixod.getGlobalBounds().contains(mous))
                vixod.setScale(1.2f, 1.2f);
            
        }
        if (viborpersa.getGlobalBounds().contains(mous))
            viborpersa.setScale(1.1f, 1.1f);
        if (vernuts.getGlobalBounds().contains(mous))
            vernuts.setScale(1.1f, 1.1f);
        if (vibor1.getGlobalBounds().contains(mous))
            vibor1.setScale(1.1f, 1.1f);
        if (vibor2.getGlobalBounds().contains(mous)&& persunlockk[2])
            vibor2.setScale(1.1f, 1.1f);
        if (vibor3.getGlobalBounds().contains(mous)&& persunlockk[3])
            vibor3.setScale(1.1f, 1.1f);
        if (nastrm) {
            if (soxr.getGlobalBounds().contains(mous))
                soxr.setScale(1.1f, 1.1f);
            if (deletsoxr.getGlobalBounds().contains(mous))
                deletsoxr.setScale(1.1f, 1.1f);
            if (vihodd.getGlobalBounds().contains(mous))
                vihodd.setScale(1.1f, 1.1f);
     }

        window.clear();
        window.draw(fon);
        window.draw(n);
        if (!viborm && !nastrm) {
            window.draw(play);
            window.draw(prodol);
            window.draw(nastr);
            window.draw(pravila);
            window.draw(vixod);
        }
        else if (viborm) {
            window.draw(prodol);
            window.draw(nastr);
            window.draw(pravila);
            window.draw(vixod);
            window.draw(zatemnenie);
            window.draw(play1);
            window.draw(vibor);
            window.draw(vibor1);
            window.draw(vibor2);
            window.draw(vibor3);
            window.draw(viborpersa);
            window.draw(vernuts);
      

       
        }
        else if (nastrm) {
            window.draw(play);
            window.draw(prodol);
            window.draw(nastr);
            window.draw(pravila);
            window.draw(vixod);
            window.draw(zatemnenie);
            window.draw(nastroika);
            window.draw(muzz);
            window.draw(zvv);
            window.draw(minuss);
            window.draw(pluss);
            window.draw(minuss2);
            window.draw(pluss2);
            window.draw(deletsoxr);
            window.draw(soxr);
            window.draw(vihodd);
            int muzsteps = music / 25;
            for (int i = 0; i < 4; i++) {
                if (i < muzsteps) {
                    ple.setPosition(895 + i * 55, 320);
                    window.draw(ple);
                }
                else {
                    pli.setPosition(895 + i * 55, 320);
                    window.draw(pli);
                }
            }
            int zvsteps = sound / 25;
            for (int i = 0; i < 4; i++) {
                if (i < zvsteps) {
                    ple.setPosition(895 + i * 55, 440);
                    window.draw(ple);
                }
                else {
                    pli.setPosition(895 + i * 55, 440);
                    window.draw(pli);
                }
            }

        }
            window.display();
        
    }

    return 0;
}
