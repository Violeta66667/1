#include <SFML/Graphics.hpp>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <SFML/Audio.hpp>

using namespace sf;
using namespace std;
int level = 1;
int akt = 1;
int ekran = 0;
int viborlevel = 1;
int savehp = -1;
const int w = 8;
const int h = 8;
bool persunlock[4] = { false,true,false,false };
Font font;
struct Level {
    bool unlock;
    bool winn;
    int enemyid;
};

Level act1lvl[11] = {{false,false,0}, {true,false,1}, {false,false,2} , {false,false,0},{false,false,1}, {false,false,3}, {false,false,1},
    {false,false,1}, {false,false,5},{false,false,1}, {false,false,4} };

int cursellevel = 1;
extern int music;
extern int sound;
extern void loadnastr();
void savgame(int viborperss) {
    ofstream out("save.txt");
    if (out.is_open()) {
        if (out.is_open()) {
            out << level << "\n" << akt << "\n" << viborperss << "\n" << savehp << "\n" << persunlock[2] << "\n" << persunlock[3] << "\n";
            for (int i = 1; i < 11; i++) {
                out << act1lvl[i].unlock << " " << act1lvl[i].winn << " " << act1lvl[i].enemyid<< "\n";
            }
            out.close();
        }
    }

}
bool loadgam(int& viborperss) {
    ifstream in("save.txt");
    int per;
    if (!in.is_open()) {
        return false;
    }
    in >> level >> akt >> viborperss >> savehp >> persunlock[2] >> persunlock[3];
    for (int i = 1; i < 11; i++) {
        in >> act1lvl[i].unlock >> act1lvl[i].winn >> act1lvl[i].enemyid;
    }
    in.close();
    return true;
}
class Player {
private:
    int id;
    int maxhp;
    int hp;
    int uron;
    int defense;
    int maxulta;
    int curulta;
    bool voskr = false;
    bool bonusdamage = false;
    bool bonusdef = false;

public:
    Player(int cid) {
        id = cid;
        curulta = 0;
        defense = 0;
        if (id == 1) {
            maxhp = 50;
            hp = 50;
            uron = 7;
            maxulta = 15;
        }
        else if (id == 2) {
            maxhp = 45;
            hp = 45;
            uron = 8;
            maxulta = 12;


        }
        else  {
            id = 3;
            maxhp = 45;
            hp = 45;
            uron = 6;
            maxulta = 18;
        }

    }
    

    void ispolskill() {
        
        if (id == 1) {
            if (hp <= 25 && hp > 0) {
                defense += 5;
                bonusdef = true;
            }
        }
        else if (id == 2) {
            if (hp <=15 && hp > 0) {
                uron = 10;
                bonusdamage = true;
            }

        }
        else if (id == 3) {
            if (hp <= 0 && !voskr) {
                hp = 10;
                voskr = true;
            }

        }
        
        }
    void sethp(int v) {
        hp = v;
        if (hp < 0) hp = 0;
        if (hp > maxhp) hp = maxhp;

        
    }
    void resetdef() {
        defense = 0;
        voskr = false;
        bonusdamage = false;
        bonusdef = false;
        if (id == 2) uron = 8;
    }
    int getmaxhp() const {
        return maxhp;
    }
    int gethp() const {
        return hp;
    }
    int geturon() const {
        return uron;
    }
    int getdefense()const {
        return defense;
    }
    int getulta() const {
        return curulta;
    }
    int getmaxulta() const {
        return maxulta;

    }
    void useulta() {
        curulta = 0;
    }
    void poluron(int uronvrag) {
        if (defense >= uronvrag) {
            defense -= uronvrag;
            
      }
        else {
            int finaluron = uronvrag - defense;
            defense = 0;
            hp -= finaluron;
        }
        ispolskill();
        if (hp <= 0) {
         
            if (hp < 0) hp = 0;
        }
    }
    void heal(int kol) {
        hp += kol;
        if (hp > maxhp) hp = maxhp;

    }

    void poldefense(int kol) {
        defense += kol;
    }

    bool nakoplenieulta(int kol) {
        curulta += kol;
        if (curulta >= maxulta) {
            curulta = maxulta;
        }
        return false;

    }
   
};
class Enemy {
private:
    int id;
    int  maxhp;
    int hp;
    int uron;
    int defense;
    bool oglushen;
    int urron;
    int deff;
public:
    Enemy(int cid) {
        id = cid;
        oglushen = false;


        if (id == 1) {
            maxhp = 20;
            hp = 20;
            uron = 5;
            defense = 0;
        }
        if (id == 2) {
            maxhp = 35;
            hp = 35;
            uron = 6;
            defense = 0;
        }
        if (id == 3) {
            maxhp = 50;
            hp = 50;
            uron = 10;
            defense = 0;
        }
        if (id == 4) {
            maxhp = 65;
            hp = 65;
            uron = 8;
            defense = 0;
            

        }
        if (id == 5) {
            maxhp = 55;
            hp = 55;
            uron = 8;
            defense = 0;
        }
    }
    void action() {
        if (id == 1) {
            urron = 5 + (rand() % 10);

            deff = 5 + (rand() % 6);

        }
        if (id == 2) {
            urron = 8 + (rand() % 10);
            deff = 5 + (rand() % 7);
        }
        if (id == 3) {
            urron = 10 + (rand() & 11);
            deff = 5 + (rand() % 9);
        }
        if (id == 4) {
            urron = 12 + (rand() % 19);
            deff = 8 + (rand() % 9);
        }
        if (id == 5) {
            urron = 11 + (rand() % 13);
            deff = 6 + (rand() % 9);

        }
    }
        void poluron(int playeruron) {
            if (defense >= playeruron) {
                defense -= playeruron;
               
            }
            else {
                int finaluron = playeruron - defense;
                defense = 0;
                hp -= finaluron;
            }
            if (hp < 0)
                hp = 0;
        }
        void ogl() {
            oglushen = true;
    }
        void removeogl() {
            oglushen = false;
        }
        void resetdef() {
            defense = 0;
        }
        void adddefense(int v) {
            defense += v;
        }
        void sethp(int v) {
            hp = v;
        }
        int getid() const {
            return id;
        }
        int gethp() const {
            return hp;
        }
        int getmaxhp() const {
            return maxhp;
        }
        int getdefense() const {
            return defense;
        }
        int getogl() const {
            return oglushen;
        }
        int geturron() const {
            return urron;

        }
        int getdeff() const {
            return deff;
        }
        
};


struct Crystal {
    int tip;
    Sprite sprite;
    float currentY;
    float targetY;  
    bool isFalling;
};
struct Anim {
    int fx, fy;
    int tx, ty;
    float pr;
    bool activ;
    Anim() : fx(0), fy(0), tx(0), ty(0), pr(0.0f), activ(false) {}
};

void ñrystalåffect(int tip, int count, Player& player, Enemy& vrag) {
    if (count < 3) return;
    int multiplier = (count >= 4) ? 2 : 1;

    switch (tip) {
    case 0: 
        vrag.poluron(player.geturon() * multiplier);
        break;
    case 1: 
        player.poldefense(5 * multiplier);
        break;
    case 2:
        player.heal(4 * multiplier);
        break;
    case 3:
        player.nakoplenieulta(3 * multiplier);
        break;
    case 4: 
        player.poluron(4 * multiplier);
        break;
    default:
        break;
    }
}

void generatepola(Crystal polle[w][h], Texture crystaltex[], int vidcrystal, int poleY, int c) {
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            int t;
            do {
                t = rand() % vidcrystal;
                polle[i][j].tip = t; 
            } while ((i >= 2 && polle[i - 1][j].tip == t && polle[i - 2][j].tip == t) ||
                (j >= 2 && polle[i][j - 1].tip == t && polle[i][j - 2].tip == t));

            polle[i][j].tip = t;
            polle[i][j].sprite.setTexture(crystaltex[t]);
            polle[i][j].targetY = poleY + j * c;
            polle[i][j].currentY = polle[i][j].targetY;
            polle[i][j].isFalling = false;
        }
    }
}

void dropandspawn(Crystal polle[w][h], Texture crystaltex[], int vidcrystal, int poleY, int c, Player& player, Enemy& vrag) {
    for (int i = 0; i < w; i++) {
        int emptySpaces = 0;

        for (int j = h - 1; j >= 0; j--) {
            if (polle[i][j].tip == -1) {
                emptySpaces++;
            }
            else if (emptySpaces > 0) {
                polle[i][j + emptySpaces] = polle[i][j];
                polle[i][j + emptySpaces].targetY = poleY + (j + emptySpaces) * c;
                polle[i][j + emptySpaces].isFalling = true;
                polle[i][j].tip = -1;
            }
        }

        for (int j = emptySpaces - 1; j >= 0; j--) {
            int t;
            int kk = 0;
            do {
                t = rand() % vidcrystal;
                kk++;
            } while (((j + 1 < h && polle[i][j + 1].tip == t && j + 2 < h && polle[i][j + 2].tip == t) ||
                (i >= 2 && polle[i - 1][j].tip == t && polle[i - 2][j].tip == t) ||
                (i + 2 < w && polle[i + 1][j].tip == t && polle[i + 2][j].tip == t)) && kk < 15);

            polle[i][j].tip = t;
            polle[i][j].sprite.setTexture(crystaltex[t]);
            polle[i][j].currentY = poleY - (emptySpaces - j) * c;
            polle[i][j].targetY = poleY + j * c;
            polle[i][j].isFalling = true;
        }
    }
}

bool proverksovpada(Crystal polle[w][h], Player& player, Enemy& vrag, Sound crystalsound[3], int sound) {
    bool found = false;

    bool todelete[w][h];
    for (int i = 0; i < w; i++)
        for (int j = 0; j < h; j++)
            todelete[i][j] = false;

    
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w - 2; i++) {
            int t = polle[i][j].tip;
            if (t != -1 && t == polle[i + 1][j].tip && t == polle[i + 2][j].tip) {
                int count = 1;
                while (i + count < w && polle[i + count][j].tip == t) {
                    count++;
                }

                ñrystalåffect(t, count, player, vrag);

                for (int k = 0; k < count; k++) {
                    todelete[i + k][j] = true;
                }
                found = true;
                i += (count - 1);
            }
        }
    }

    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h - 2; j++) {
            int t = polle[i][j].tip;
            if (t != -1 && t == polle[i][j + 1].tip && t == polle[i][j + 2].tip) {
                int count = 3;
                if (j + 3 < h && polle[i][j + 3].tip == t) count = 4;
                if (count == 4 && j + 4 < h && polle[i][j + 4].tip == t) count = 5;

                ñrystalåffect(t, count, player, vrag);

                for (int k = 0; k < count; k++) {
                    todelete[i][j + k] = true;
                }
                found = true;
                j += (count - 1);
            }
        }
    }
    if (found) {
        int randd = rand() % 3;
        crystalsound[randd].setVolume(static_cast<float>(sound)); crystalsound[randd].play();
    }

 
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            if (todelete[i][j]) {
                polle[i][j].tip = -1;
            }
        }
    }

    return found;
}
void drop(Crystal polle[w][h]) {
    for (int i = 0; i < w; i++) {
        for (int j = h - 1; j >= 0; j--) {
            if (polle[i][j].tip == -1) {
                for (int k = j - 1; k >= 0; k--) {
                    if (polle[i][k].tip != -1) {
                        polle[i][j].tip = polle[i][k].tip;
                        polle[i][j].sprite = polle[i][k].sprite;
                        polle[i][k].tip = -1;
                        break;
                    }
                }
            }
        }
    }
}
void zapolnenie(Crystal polle[w][h], Texture crystaltex[], int vidcrystal) {
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            if (polle[i][j].tip == -1) {
                int t = rand() % vidcrystal;
                polle[i][j].tip = t;
                polle[i][j].sprite.setTexture(crystaltex[t]);
            }
        }
    }
}

void obmen(Crystal polle[w][h], int x1, int y1, int x2, int y2) {
    Crystal tt = polle[x1][y1];
    polle[x1][y1] = polle[x2][y2];
    polle[x2][y2] = tt;
    swap(polle[x1][y1].currentY, polle[x2][y2].currentY);
    swap(polle[x1][y1].targetY, polle[x2][y2].targetY);


}
bool updateFalling(Crystal polle[w][h], float dt) {
    float fallSpeed = 450.0f; 
    bool anyFalling = false;

    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            if (polle[i][j].isFalling) {
                anyFalling = true;
                if (polle[i][j].currentY < polle[i][j].targetY) {
                    polle[i][j].currentY += fallSpeed * dt;
                 
                    if (polle[i][j].currentY >= polle[i][j].targetY) {
                        polle[i][j].currentY = polle[i][j].targetY;
                        polle[i][j].isFalling = false;
                    }
                }
            }
        }
    }
    return anyFalling; 
}


void gamewin(bool prodgame, int viborpers){
    int idpers = viborpers;
    bool finalwin = false;
    srand(static_cast<unsigned int>(time(NULL)));
    Enemy vrag = Enemy(vrag.getid());
    Player player = Player(idpers);
    loadnastr();
    Music gamemusic;
    if (gamemusic.openFromFile("audio/03.ogg")) {
        gamemusic.setLoop(true);
        gamemusic.setVolume(static_cast<float>(music));
        gamemusic.play();
    }
    SoundBuffer clickbufer;
    Sound click;
    if (clickbufer.loadFromFile("audio/click.ogg")) {
        click.setBuffer(clickbufer);
    }

    SoundBuffer ultbuffer;
    Sound ultas;
    if (ultbuffer.loadFromFile("audio/ultimate.ogg")) {
        ultas.setBuffer(ultbuffer);
    }
    SoundBuffer crystalbuf1, crystalbuf2, crystalbuf3;
    Sound crystalsounds[3];
    if (crystalbuf1.loadFromFile("audio/s.ogg")) crystalsounds[0].setBuffer(crystalbuf1);
    if (crystalbuf2.loadFromFile("audio/ssss.ogg")) crystalsounds[1].setBuffer(crystalbuf2);
    if (crystalbuf3.loadFromFile("audio/sc.ogg")) crystalsounds[2].setBuffer(crystalbuf3);

    SoundBuffer nobuf;
    Sound no;
    if (nobuf.loadFromFile("audio/ne.ogg")) {
        no.setBuffer(nobuf);
    }
    ekran = 0;
    bool load = false;
    if (prodgame) {
        load = loadgam(idpers);
        if (savehp > 0) {
            player.sethp(savehp);
        }
        

    }
    else {
        ifstream in("save.txt");
        if (in.is_open()) {
            int tlevel, takt, tpers, th;
            if (in >> tlevel >> takt >> tpers >> th >> persunlock[2] >> persunlock[3]) {
            }
            in.close();
        }
        level = 1;
        akt = 1;
        savehp = -1;
        act1lvl[0] = { false, false, 0 };
        act1lvl[1] = { true, false, 1 };
        act1lvl[2] = { false, false, 2 };
        act1lvl[3] = { false, false, 1 };
        act1lvl[4] = { false, false, 1 };
        act1lvl[5] = { false, false, 3 };
        act1lvl[6] = { false, false, 2 };
        act1lvl[7] = { false, false, 1 };
        act1lvl[8] = { false, false, 5 };
        act1lvl[9] = { false, false, 0 };
        act1lvl[10] = { false, false,4 };
        player.sethp(player.getmaxhp());

        savehp = player.gethp();
        savgame(idpers);
    }
    bool boardStable = true;
    bool pauza = false;
    if (prodgame && savehp > 0) {
        player.sethp(savehp);
    }
    bool peremeshenie = false;
    int starthp = player.gethp();
    int sx = -1;
    int sy = -1;
    int tx = -1;
    int ty = -1;
    Anim anim1, anim2;
    Clock animclock;
    float animspid = 5.0f;
    int animfase = 0;
    int hodovv = 5;
    int roundd = 1;
    bool levelwin = false;
    bool vraghodit = false;
    Texture poletex;
    poletex.loadFromFile("img/pole.png");
    Sprite pole;
    pole.setTexture(poletex);
    pole.setPosition(570, 300);
    const int c = 83;
    int poleX = pole.getPosition().x + 59;
    int poleY = pole.getPosition().y + 40;
    Texture crystaltex[5];
    crystaltex[0].loadFromFile("img/attack.png");
    crystaltex[1].loadFromFile("img/defense.png");
    crystaltex[2].loadFromFile("img/health.png");
    crystaltex[3].loadFromFile("img/ultimate.png");
    crystaltex[4].loadFromFile("img/uron.png");
    const int vidcrystal = 5;
    Crystal polle[w][h];
    generatepola(polle, crystaltex, vidcrystal, poleY, c);
    vrag.action();
    Text hodtext;
    hodtext.setFont(font);
    hodtext.setCharacterSize(36);
    hodtext.setFillColor(Color::White);
    hodtext.setOutlineColor(Color::Black);
    hodtext.setOutlineThickness(2.0f);
    Text raundtext;
    raundtext.setFont(font);
    raundtext.setCharacterSize(36);
    raundtext.setFillColor(Color::White);
    raundtext.setOutlineColor(Color::Black);
    raundtext.setOutlineThickness(2.0f);
    Text ataktext;
    ataktext.setFont(font);
    ataktext.setCharacterSize(30);
    ataktext.setFillColor(Color::White);
    ataktext.setOutlineColor(Color::Black);
    ataktext.setOutlineThickness(2.0f);
    Text deftext;
    deftext.setFont(font);
    deftext.setCharacterSize(30);
    deftext.setFillColor(Color::White);
    deftext.setOutlineColor(Color::Black);
    deftext.setOutlineThickness(2.0f);
    Texture oknvost;
    oknvost.loadFromFile("img/109.png");
    Sprite okvost;
    okvost.setTexture(oknvost);
    okvost.setPosition(565, 300);


    bool vernuts = false;
    Texture pausetex;
    pausetex.loadFromFile("img/paus.png");
    Texture plosulttex;
    plosulttex.loadFromFile("img/ulta.png");
    Texture plostex;
    plostex.loadFromFile("img/0pl.png");
    Sprite plos;
    plos.setTexture(plostex);
    plos.setPosition(170, 870);
    Texture hptex;
    hptex.loadFromFile("img/hpp.png");
    Texture pusttex;
    pusttex.loadFromFile("img/pust.png");
    Texture ultttex;
    ultttex.loadFromFile("img/ultimate.png");
    Texture ultpltex;
    ultpltex.loadFromFile("img/ultpl.png");
    Texture ultptex;
    ultptex.loadFromFile("img/ultimatep.png");
    Texture defenssetex;
    defenssetex.loadFromFile("img/def.png");
    Texture atacktex;
    atacktex.loadFromFile("img/atak.png");
    Texture hodtex;
    hodtex.loadFromFile("img/hodov.png");
    Texture raundtex;
    raundtex.loadFromFile("img/raund.png");
    Texture elitvrag;
    elitvrag.loadFromFile("img/02.png");
    Texture elitvragd;
    elitvragd.loadFromFile("img/02d.png");

    Sprite pause;
    pause.setTexture(pausetex);
    pause.setPosition(15, 10);
    Sprite raund;
    raund.setTexture(raundtex);
    raund.setPosition(1600, 30);
    Sprite hodov;
    hodov.setTexture(hodtex);
    hodov.setPosition(740, 30);
    Sprite deffen;
    deffen.setTexture(defenssetex);
    //deffen.setPosition(1630, 294);
    Sprite atak;
    atak.setTexture(atacktex);
    //atak.setPosition(1630, 300);

    Sprite ultpl;
    ultpl.setTexture(ultpltex);
    ultpl.setPosition(250, 960);
    Sprite ult;
   
    ult.setPosition(170, 930);
    Sprite pustulta;
    pustulta.setTexture(pusttex);
    pustulta.setPosition(270, 960);
    Sprite plosulta;
    plosulta.setTexture(plosulttex);
    plosulta.setPosition(170, 950);
    Sprite pust;
    pust.setTexture(pusttex);
    pust.setPosition(200, 885);
    Sprite pustvrag;
    pustvrag.setTexture(pusttex);
    pustvrag.setPosition(1490,875);
    Sprite playerhp;
    playerhp.setTexture(hptex);
    playerhp.setPosition(200, 885);
    Sprite vraghp;
    vraghp.setTexture(hptex);
    vraghp.setPosition(1490, 875);
    int maxhpwidth = hptex.getSize().x;
    int hpheight = hptex.getSize().y;
  

    Sprite enemy;
    if (!font.loadFromFile("font/BestTen-DOT.otf")) {

    }
    Text playerhptext;
    playerhptext.setFont(font);
    playerhptext.setCharacterSize(30);
    playerhptext.setFillColor(Color::White);
    playerhptext.setOutlineColor(Color::Black);
    playerhptext.setOutlineThickness(2.0f);

    Text enemyhptext;
    enemyhptext.setFont(font);
    enemyhptext.setCharacterSize(30);
    enemyhptext.setFillColor(Color::White);
    enemyhptext.setOutlineColor(Color::Black);
    enemyhptext.setOutlineThickness(2.0f);
    
    Text playerdeftext;
    playerdeftext.setFont(font);
    playerdeftext.setCharacterSize(30);
    playerdeftext.setFillColor(Color::White);
    playerdeftext.setOutlineColor(Color::Black);
    playerdeftext.setOutlineThickness(2.0f);
    
    Text enemydeftext;
    enemydeftext.setFont(font);
    enemydeftext.setCharacterSize(30);
    enemydeftext.setFillColor(Color::White);
    enemydeftext.setOutlineColor(Color::Black);
    enemydeftext.setOutlineThickness(2.0f);

    Text ulttext;
    ulttext.setFont(font);
    ulttext.setCharacterSize(30);
    ulttext.setFillColor(Color::White);
    ulttext.setOutlineColor(Color::Black);
    ulttext.setOutlineThickness(2.0f);

    Sprite plosvrag;
    plosvrag.setTexture(plostex);
    plosvrag.setPosition(1450, 865);
    


    Texture fonntex;
    fonntex.loadFromFile("img/fonn.png");
    Texture venrtex;
    venrtex.loadFromFile("img/12.png");
    Texture obichvragtex;
    obichvragtex.loadFromFile("img/01.png");
    RectangleShape kvadr(Vector2f(15.0f, 15.0f));
    kvadr.setFillColor(Color::Black);
    kvadr.setPosition(230, 640);
    RectangleShape kvadr1(Vector2f(15.0f, 15.0f));
    kvadr1.setFillColor(Color::Black);
    kvadr1.setPosition(280, 640);
    RectangleShape kvadr2(Vector2f(15.0f, 15.0f));
    kvadr2.setFillColor(Color::Black);
    kvadr2.setPosition(410, 610);
    RectangleShape kvadr3(Vector2f(15.0f, 15.0f));
    kvadr3.setFillColor(Color::Black);
    kvadr3.setPosition(450, 580);
    Texture vosttex;
    vosttex.loadFromFile("img/vost.png");
    RectangleShape kvadr4(Vector2f(15.0f, 15.0f));
    kvadr4.setFillColor(Color::Black);
    kvadr4.setPosition(586, 582);
    RectangleShape kvadr5(Vector2f(15.0f, 15.0f));
    kvadr5.setFillColor(Color::Black);
    kvadr5.setPosition(634, 615);
    RectangleShape kvadr6(Vector2f(15.0f, 15.0f));
    kvadr6.setFillColor(Color::Black);
    kvadr6.setPosition(756, 642);
    RectangleShape kvadr7(Vector2f(15.0f, 15.0f));
    kvadr7.setFillColor(Color::Black);
    kvadr7.setPosition(806, 642);
    RectangleShape kvadr8(Vector2f(15.0f, 15.0f));
    kvadr8.setFillColor(Color::Black);
    kvadr8.setPosition(956, 642);
    RectangleShape kvadr9(Vector2f(15.0f, 15.0f));
    kvadr9.setFillColor(Color::Black);
    kvadr9.setPosition(1006, 642);
    RectangleShape kvadr10(Vector2f(15.0f, 15.0f));
    kvadr10.setFillColor(Color::Black);
    kvadr10.setPosition(1136, 642);
    RectangleShape kvadr11(Vector2f(15.0f, 15.0f));
    kvadr11.setFillColor(Color::Black);
    kvadr11.setPosition(1190, 642);
    RectangleShape kvadr12(Vector2f(15.0f, 15.0f));
    kvadr12.setFillColor(Color::Black);
    kvadr12.setPosition(1310, 602);
    RectangleShape kvadr13(Vector2f(15.0f, 15.0f));
    kvadr13.setFillColor(Color::Black);
    kvadr13.setPosition(1350, 572);
    RectangleShape kvadr14(Vector2f(15.0f, 15.0f));
    kvadr14.setFillColor(Color::Black);
    kvadr14.setPosition(1460, 575);
    RectangleShape kvadr15(Vector2f(15.0f, 15.0f));
    kvadr15.setFillColor(Color::Black);
    kvadr15.setPosition(1495, 606);
    RectangleShape kvadr16(Vector2f(15.0f, 15.0f));
    kvadr16.setFillColor(Color::Black);
    kvadr16.setPosition(1595, 642);
    RectangleShape kvadr17(Vector2f(15.0f, 15.0f));
    kvadr17.setFillColor(Color::Black);
    kvadr17.setPosition(1650, 642);

    Texture fnot;
    fnot.loadFromFile("img/fonur.png");
    Texture pers1tex;
    pers1tex.loadFromFile("img/pess1.png");
    Texture pers2tex;
    pers2tex.loadFromFile("img/pers2.png");
    Texture pers3tex;
    pers3tex.loadFromFile("img/pers3.png");
    Texture slimetex;
    slimetex.loadFromFile("img/vrag1.png");
    Texture vra2t;
    vra2t.loadFromFile("img/vrag2.png");
    Texture elit2t;
    elit2t.loadFromFile("img/elitvr2.png");
    Texture vragdtex;
    vragdtex.loadFromFile("img/01d.png");
    Texture elitvrag1t;
    elitvrag1t.loadFromFile("img/elitvrag1.png");
    Texture bosstex;
    bosstex.loadFromFile("img/boss.png");
    Texture poltex;
    poltex.loadFromFile("img/p.png");
    Texture boss;
    boss.loadFromFile("img/03.png");
    Sprite elitvrag1;
    elitvrag1.setTexture(elitvrag1t);
    Sprite vrag2;
    vrag2.setTexture(vra2t);
   
    Sprite bosss;
    bosss.setTexture(bosstex);

    Texture bossd;
    bossd.loadFromFile("img/03d.png");
    Texture podebatex;
    podebatex.loadFromFile("img/podeba1.png");
    Texture oktex;
    oktex.loadFromFile("img/11.png");
    Texture podev;
    podev.loadFromFile("img/podebaa.png");
    Sprite pobedaa;
    pobedaa.setTexture(podev);
    pobedaa.setPosition(565, 300);
    Sprite podebba;
    Texture past;
    past.loadFromFile("img/09.png");
    podebba.setTexture(podebatex);
    podebba.setPosition(565, 300);
    Sprite okknopka;
    okknopka.setTexture(oktex);
    okknopka.setPosition(800, 650);
    Sprite okonp;
    okonp.setTexture(oktex);
    okonp.setPosition(780, 600);
    RectangleShape zatemn(Vector2f(1920.f, 1080.f)); 
    zatemn.setFillColor(Color(0, 0, 0, 150));
    zatemn.setPosition(0.f, 0.f);

    Sprite pausse;
    pausse.setTexture(past);
    pausse.setPosition(600, 300);
    Texture prodlst;
    prodlst.loadFromFile("img/7pause.png");
    Sprite prodolmen;
    prodolmen.setTexture(prodlst);
    prodolmen.setPosition(800, 400);
    Texture vixxodt;
    vixxodt.loadFromFile("img/111pause.png");
    Sprite vixxod;
    vixxod.setTexture(vixxodt);
    vixxod.setPosition(800, 600);
    Sprite fno;
    fno.setTexture(fnot);
    Texture proigt;
    proigt.loadFromFile("img/proigr.png");
    Sprite proigr;
    proigr.setTexture(proigt);
    proigr.setPosition(605, 330);
    pole.setTexture(poletex);
    Sprite fonn;
    fonn.setTexture(fonntex);
    Sprite venr;
    venr.setTexture(venrtex);
    venr.setPosition(0, 100);
    Sprite obichvrag;
    obichvrag.setTexture(obichvragtex);
    obichvrag.setPosition(130, 600);
    Sprite obichvrag1;
    obichvrag1.setTexture(obichvragtex);
    obichvrag1.setPosition(320, 600);
    Sprite vost;
    vost.setTexture(vosttex);
    vost.setPosition(498, 500);
    Sprite obichvrag2;
    obichvrag2.setTexture(obichvragtex);
    obichvrag2.setPosition(660, 610);
    Sprite obichvrag3;
    obichvrag3.setTexture(elitvrag);
    obichvrag3.setPosition(840, 615);
    Sprite obichvrag4;
    obichvrag4.setTexture(obichvragtex);
    obichvrag4.setPosition(1035, 610);
    Sprite obichvrag5;
    obichvrag5.setTexture(obichvragtex);
    obichvrag5.setPosition(1225, 610);
    Sprite obichvrag6;
    obichvrag6.setTexture(elitvrag);
    obichvrag6.setPosition(1360, 520);
    Sprite vost1;
    vost1.setTexture(vosttex);
    vost1.setPosition(1500, 610);
    Sprite obichvrag7;
    obichvrag7.setTexture(boss);
    obichvrag7.setPosition(1690, 600);
    Texture vostpt;
    vostpt.loadFromFile("img/vostp.png");
    Texture oglt;
    oglt.loadFromFile("img/oglush.png");
    Sprite ogl;
    ogl.setTexture(oglt);
    ogl.setPosition(1570, 300);
    Sprite elit2vr;
    elit2vr.setTexture(elit2t);

  
    Sprite pers;
    if (idpers == 1) pers.setTexture(pers1tex);
    if (idpers == 2) pers.setTexture(pers2tex);
    if (idpers == 3)pers.setTexture(pers3tex);
    pers.setPosition(200, 405);
    Sprite p;
    p.setTexture(poltex);
    p.setPosition(0, 0);
    Vector2f baseperspoz(200.f, 545.f);
    Vector2f baseememypoz(1490.f, 605.f);
    Vector2f baseenemy2poz(1490.f, 525.f);
    Vector2f baseelitvrag(1440.f, 515.f);
    Vector2f baseelitvrag2(1440.f, 405.f);
    Vector2f baseboss(1420.f, 490.f);

    float perst = 0.0f;
    float enemyt = 0.0f;
    float elitt = 0.0f;
    float elitt2 = 0.0f;
    float enemy2t = 0.0f;
    float bost = 0.0f;

    const float hitd = 0.15f;
    const float maxoffset = 35.0f;
    bool proigrh = false;
    Sprite(okknopkaa);
    okknopkaa.setTexture(oktex);
    okknopkaa.setPosition(800,650);
    Sprite(okknopk);
    okknopk.setTexture(oktex);
    okknopk.setPosition(800, 650);
    RenderWindow window(VideoMode::getDesktopMode(), "kursovaya");
    ShowWindow(window.getSystemHandle(), SW_SHOWMAXIMIZED);
    View gameView(FloatRect(0.f, 0.f, 1920.f, 1080.f));
    window.setView(gameView);
    Image icon;
    icon.loadFromFile("img/0.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr()
    );
    bool vostoknoo = false;
    int lplhp = player.gethp();
    int lenmhp= vrag.gethp();
    while (window.isOpen())
    {
        View gameplayView(FloatRect(0.f, 0.f, 1920.f, 1080.f));
        window.setView(gameplayView);
        float dt = animclock.restart().asSeconds();
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) {
                if (ekran == 1) {
                    savehp = starthp;
                    player.ispolskill();
                }
                else {
                    savehp = player.gethp();
                }
                savgame(idpers);
                gamemusic.stop();
                window.close();

            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                if (ekran == 1 && !proigrh && !finalwin) {
                    pauza = !pauza;
                    click.setVolume(static_cast<float>(sound));
                    click.play();
                }
                continue;
            }

       
            if (anim1.activ || anim2.activ || !boardStable) continue;

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window), window.getView());
                if (ekran == 0 && venr.getGlobalBounds().contains(mouse)) {
                    savehp = player.gethp();
                    savgame(idpers);
                    gamemusic.stop();
                    window.close();
                }   
                if (levelwin) {
                    if (okknopk.getGlobalBounds().contains(mouse)) {
                        click.setVolume(static_cast<float>(sound));
                        click.play();
                        act1lvl[cursellevel].winn = true;
                        if (cursellevel + 1 < 11) {
                            act1lvl[cursellevel + 1].unlock = true;
                        }


                        savehp = player.gethp();
                        savgame(idpers);

                        ekran = 0;
                        levelwin = false;
                    }
                    continue;
                }
              
                if (proigrh) {
                    if (okknopka.getGlobalBounds().contains(mouse)) {
                        click.setVolume(static_cast<float>(sound)); click.play();
                        ekran = 0;
                        level = 1;
                        akt = 1;

                        act1lvl[0] = { false, false, 0 };
                        act1lvl[1] = { true, false, 1 };
                        act1lvl[2] = { false, false, 2 };
                        act1lvl[3] = { false, false, 1 };
                        act1lvl[4] = { false, false, 1 };
                        act1lvl[5] = { false, false, 3 };
                        act1lvl[6] = { false, false, 2 };
                        act1lvl[7] = { false, false, 1 };
                        act1lvl[8] = { false, false, 5 };
                        act1lvl[9] = { false, false, 0 };
                        act1lvl[10] = { false, false, 4 };

                        player.sethp(player.getmaxhp()); 
                        savehp = player.gethp();
                        cursellevel = 1;

                        obichvrag.setTexture(obichvragtex);
                        obichvrag1.setTexture(obichvragtex);
                        obichvrag2.setTexture(obichvragtex);
                        obichvrag3.setTexture(elitvrag);
                        obichvrag4.setTexture(obichvragtex);
                        obichvrag5.setTexture(obichvragtex);
                        obichvrag6.setTexture(elitvrag);
                        obichvrag7.setTexture(boss);
                        vost.setTexture(vosttex);
                        vost1.setTexture(vosttex);

                        savgame(idpers);

                        proigrh = false; 
                    }
                    continue; 
                }
                       
                
                

                if (pauza) {
                    if (prodolmen.getGlobalBounds().contains(mouse)) {
                        pauza = false;
                        click.setVolume(static_cast<float>(sound)); click.play();
                    }
                    else if (vixxod.getGlobalBounds().contains(mouse)) {
                        pauza = false;
                        click.setVolume(static_cast<float>(sound)); click.play();
                        ekran = 0;
                        savehp = (starthp);
                        player.sethp(starthp);
                        savgame(idpers);
                    }
                    continue;
                }
                if (vostoknoo) {
                    if (okonp.getGlobalBounds().contains(mouse)) {
                        click.setVolume(static_cast<float>(sound));
                        click.play();
                        player.heal(15);
                        act1lvl[cursellevel].winn = true;
                        if (cursellevel + 1 < 11) {
                            act1lvl[cursellevel + 1].unlock = true;
                        }

                        savehp = player.gethp();
                        savgame(idpers);
                        vostoknoo = false;
                    }
                    continue;
                }
                if (ekran == 1) {
                    if (pause.getGlobalBounds().contains(mouse)) {
                        pauza = true;
                        click.setVolume(static_cast<float>(sound)); click.play();
                        continue;
                    }
                }
              
                if (finalwin) {
                    if (okknopka.getGlobalBounds().contains(mouse)) {
                        click.setVolume(static_cast<float>(sound)); click.play();
                        level = 1;
                        savehp = -1;
                        act1lvl[10].winn = true;
                        if (idpers == 1) {
                            persunlock[2] = true;
                        }
                        else if (idpers == 2) {
                            persunlock[3] = true;
                        }
                        savgame(idpers);
                        ekran = 0;     
                        finalwin = false;
                        return;          
                    }
                    continue;
                }

                

                if (ekran == 0 && obichvrag.getGlobalBounds().contains(mouse) && act1lvl[1].unlock && !act1lvl[1].winn) {
                    cursellevel = 1;
                    vrag = Enemy(act1lvl[1].enemyid);
                    player.resetdef();
                    vrag.resetdef();
                    player.ispolskill();
                    vrag.action();
                    player.useulta();
                    click.setVolume(static_cast<float>(sound)); click.play();
                    generatepola(polle, crystaltex, vidcrystal, poleY, c);
                    hodovv = 5;
                    roundd = 1;
                    starthp = player.gethp();
            
                    if (vrag.getid() == 1) {
                        enemy.setTexture(slimetex);
                    }
                    if (vrag.getid() == 2) {
                        vrag2.setTexture(vra2t);
                    }
                    if (vrag.getid() == 3) {
                        elitvrag1.setTexture(elitvrag1t);
                    }
                    if (vrag.getid() == 4) {
                        bosss.setTexture(bosstex);
                    }
                    if (vrag.getid() == 5) {
                        elit2vr.setTexture(elit2t);
                    }
                    ekran = 1;
                }
                if (ekran == 0 && obichvrag1.getGlobalBounds().contains(mouse) && act1lvl[2].unlock && !act1lvl[2].winn) {
                    cursellevel = 2;
                    vrag = Enemy(act1lvl[2].enemyid);
                    click.setVolume(static_cast<float>(sound)); click.play();
                    player.resetdef();
                    generatepola(polle, crystaltex, vidcrystal, poleY, c);
                    vrag.resetdef();
                    player.ispolskill();
                    vrag.action();
                    player.useulta();
                    hodovv = 5;
                    roundd = 1;
                    starthp = player.gethp();
         

                    if (vrag.getid() == 1) {
                        enemy.setTexture(slimetex);
                    }
                    if (vrag.getid() == 2) {
                        vrag2.setTexture(vra2t);
                    }
                    if (vrag.getid() == 3) {
                        elitvrag1.setTexture(elitvrag1t);
                    }
                    if (vrag.getid() == 4) {
                        bosss.setTexture(bosstex);
                    }
                    if (vrag.getid() == 5) {
                        elit2vr.setTexture(elit2t);
                    }
                    ekran = 1;
                }
                if (ekran == 0 && vost.getGlobalBounds().contains(mouse) && act1lvl[3].unlock && !act1lvl[3].winn) {
                    cursellevel = 3;
                    click.setVolume(static_cast<float>(sound)); click.play();
                    vostoknoo = true;
                }
                if (ekran == 0 && obichvrag2.getGlobalBounds().contains(mouse) && act1lvl[4].unlock && !act1lvl[4].winn) {
                    cursellevel = 4;
                    vrag = Enemy(act1lvl[4].enemyid);
                    player.resetdef();
                    vrag.resetdef();
                    player.ispolskill();
                    generatepola(polle, crystaltex, vidcrystal, poleY, c);
                    player.useulta();
                    vrag.action();
                    click.setVolume(static_cast<float>(sound)); click.play();
                    hodovv = 5;
                    roundd = 1;
                    starthp = player.gethp();
                 

                    if (vrag.getid() == 1) {
                        enemy.setTexture(slimetex);
                    }
                    if (vrag.getid() == 2) {
                        vrag2.setTexture(vra2t);
                    }
                    if (vrag.getid() == 3) {
                        elitvrag1.setTexture(elitvrag1t);
                    }
                    if (vrag.getid() == 4) {
                        bosss.setTexture(bosstex);
                    }
                    if (vrag.getid() == 5) {
                        elit2vr.setTexture(elit2t);
                    }
                    ekran = 1;
                }
                if (ekran == 0 && obichvrag3.getGlobalBounds().contains(mouse) && act1lvl[5].unlock && !act1lvl[5].winn) {
                    cursellevel = 5;
                    click.setVolume(static_cast<float>(sound)); click.play();
                    vrag = Enemy(act1lvl[5].enemyid);
                    player.resetdef();
                    vrag.resetdef();
                    player.ispolskill();
                    generatepola(polle, crystaltex, vidcrystal, poleY, c);
                    player.useulta();
                    vrag.action();
                    click.setVolume(static_cast<float>(sound)); click.play();
                    hodovv = 5;
                    roundd = 1;
                    starthp = player.gethp();

                    if (vrag.getid() == 1) {
                        enemy.setTexture(slimetex);
                    }
                    if (vrag.getid() == 2) {
                        vrag2.setTexture(vra2t);
                    }
                    if (vrag.getid() == 3) {
                        elitvrag1.setTexture(elitvrag1t);
                    }
                    if (vrag.getid() == 4) {
                        bosss.setTexture(bosstex);
                    }
                    if (vrag.getid() == 5) {
                        elit2vr.setTexture(elit2t);
                    }
                    ekran = 1;
                }
                if (ekran == 0 && obichvrag4.getGlobalBounds().contains(mouse) && act1lvl[6].unlock && !act1lvl[6].winn) {
                    cursellevel = 6;
                   
                    vrag = Enemy(act1lvl[6].enemyid);
                    player.resetdef();
                    vrag.resetdef();
                    player.ispolskill();
                    generatepola(polle, crystaltex, vidcrystal, poleY, c);
                    player.useulta();
                    vrag.action();
                    click.setVolume(static_cast<float>(sound)); click.play();
                    hodovv = 5;
                    roundd = 1;
                    starthp = player.gethp();

                    if (vrag.getid() == 1) {
                        enemy.setTexture(slimetex);
                    }
                    if (vrag.getid() == 2) {
                        vrag2.setTexture(vra2t);
                    }
                    if (vrag.getid() == 3) {
                        elitvrag1.setTexture(elitvrag1t);
                    }
                    if (vrag.getid() == 4) {
                        bosss.setTexture(bosstex);
                    }
                    if (vrag.getid() == 5) {
                        elit2vr.setTexture(elit2t);
                    }
                    ekran = 1;
                }
                if (ekran == 0 && obichvrag5.getGlobalBounds().contains(mouse) && act1lvl[7].unlock && !act1lvl[7].winn) {
                    cursellevel = 7;
                    vrag = Enemy(act1lvl[7].enemyid);
                    
                    player.resetdef();
                    vrag.resetdef();
                    player.ispolskill();
                    generatepola(polle, crystaltex, vidcrystal, poleY, c);
                    player.useulta();
                    vrag.action();
                    click.setVolume(static_cast<float>(sound)); click.play();
                    hodovv = 5;
                    roundd = 1;
                    starthp = player.gethp();
                    if (vrag.getid() == 1) {
                        enemy.setTexture(slimetex);
                    }
                    if (vrag.getid() == 2) {
                        vrag2.setTexture(vra2t);
                    }
                    if (vrag.getid() == 3) {
                        elitvrag1.setTexture(elitvrag1t);
                    }
                    if (vrag.getid() == 4) {
                        bosss.setTexture(bosstex);
                    }
                    if (vrag.getid() == 5) {
                        elit2vr.setTexture(elit2t);
                    }
                    ekran = 1;
                }
                if (ekran == 0 && obichvrag6.getGlobalBounds().contains(mouse) && act1lvl[8].unlock && !act1lvl[8].winn) {
                    cursellevel = 8;
                    click.setVolume(static_cast<float>(sound)); click.play();
                    vrag = Enemy(act1lvl[8].enemyid);
                    player.resetdef();
                    vrag.resetdef();
                    player.ispolskill();
                    generatepola(polle, crystaltex, vidcrystal, poleY, c);
                    player.useulta();
                    vrag.action();
                    hodovv = 5;
                    roundd = 1;
                    starthp = player.gethp();
                 
                    if (vrag.getid() == 1) {
                        enemy.setTexture(slimetex);
                    }
                    if (vrag.getid() == 2) {
                        vrag2.setTexture(vra2t);
                    }
                    if (vrag.getid() == 3) {
                        elitvrag1.setTexture(elitvrag1t);
                    }
                    if (vrag.getid() == 4) {
                        bosss.setTexture(bosstex);
                    }
                    if (vrag.getid() == 5) {
                        elit2vr.setTexture(elit2t);
                    }
                    ekran = 1;
                }
                if (ekran == 0 && vost1.getGlobalBounds().contains(mouse) && act1lvl[9].unlock && !act1lvl[9].winn) {
                    cursellevel = 9;
                    click.setVolume(static_cast<float>(sound)); click.play();
                    vostoknoo = true;
               

                    if (vrag.getid() == 1) {
                        enemy.setTexture(slimetex);
                    }
                    if (vrag.getid() == 2) {
                        vrag2.setTexture(vra2t);
                    }
                    if (vrag.getid() == 3) {
                        elitvrag1.setTexture(elitvrag1t);
                    }
                    if (vrag.getid() == 4) {
                        bosss.setTexture(bosstex);
                    }
                    if (vrag.getid() == 5) {
                        elit2vr.setTexture(elit2t);
                    }
                    savgame(idpers);
                }
                if (ekran == 0 && obichvrag7.getGlobalBounds().contains(mouse) && act1lvl[10].unlock && !act1lvl[10].winn) {
                    cursellevel = 10;
                    vrag = Enemy(act1lvl[10].enemyid);
                    click.setVolume(static_cast<float>(sound)); click.play();
                    player.resetdef();
                    vrag.resetdef();
                    player.ispolskill();
                    generatepola(polle, crystaltex, vidcrystal, poleY, c);
                    player.useulta();
                    vrag.action();
                    hodovv = 5;
                    roundd = 1;
                    starthp = player.gethp();
                  
                    if (vrag.getid() == 1) {
                        enemy.setTexture(slimetex);
                    }
                    if (vrag.getid() == 2) {
                        vrag2.setTexture(vra2t);
                    }
                    if (vrag.getid() == 3) {
                        elitvrag1.setTexture(elitvrag1t);
                    }
                    if (vrag.getid() == 4) {
                        bosss.setTexture(bosstex);
                    }
                    if (vrag.getid() == 5) {
                        elit2vr.setTexture(elit2t);
                    }
                    ekran = 1;
                }

                if (ekran == 1 && !proigrh)
                {
                    Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window), window.getView());
                    if (ult.getGlobalBounds().contains(mouse)) {
                        if (player.getulta() >= player.getmaxulta()) {
                            ultas.setVolume(static_cast<float>(sound)); ultas.play();
                            if (viborpers == 1) {
                                vrag.ogl();
                                player.useulta();
                            }
                            else if (viborpers == 2) {
                                hodovv += 1;
                                player.useulta();
                            }
                            else if (viborpers == 3) {
                                player.heal(10);
                                player.useulta();
                            }
                        }
                    }

                    for (int i = 0; i < w; i++) {
                        for (int j = 0; j < h; j++) {
                            polle[i][j].sprite.setPosition(poleX + i * c, polle[i][j].currentY);
                            if (polle[i][j].sprite.getGlobalBounds().contains(mouse)) {
                                peremeshenie = true;
                                sx = i; sy = j;
                            }
                        }
                    }
                }
            }
            


            if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
            {
                if (pauza) continue;

                if (ekran == 1 && peremeshenie)
                {
                    peremeshenie = false;
                    Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window), window.getView());

                    for (int i = 0; i < w; i++) {
                        for (int j = 0; j < h; j++) {
                            polle[i][j].sprite.setPosition(poleX + i * c, polle[i][j].currentY);
                            if (polle[i][j].sprite.getGlobalBounds().contains(mouse)) {

                                if ((abs(i - sx) == 1 && abs(j - sy) == 0) || (abs(j - sy) == 1 && abs(i - sx) == 0)) {
                                    tx = i; ty = j;


                                    anim1.fx = sx; anim1.fy = sy; anim1.tx = tx; anim1.ty = ty;
                                    anim1.pr = 0.0f; anim1.activ = true;

                                    anim2.fx = tx; anim2.fy = ty; anim2.tx = sx; anim2.ty = sy;
                                    anim2.pr = 0.0f; anim2.activ = true;

                                    animfase = 1;
                                }
                            }
                        }
                    }
                }
            }
        }
        if (ekran == 1 && player.gethp() <= 0 && !proigrh) {
            proigrh = true;

        }
        if (!proigrh) {
            if (anim1.activ && anim2.activ) {
                anim1.pr += dt * animspid;
                anim2.pr += dt * animspid;

                if (anim1.pr >= 1.0f) {
                    anim1.pr = 1.0f;

                    if (animfase == 1) {

                        obmen(polle, sx, sy, tx, ty);
                        no.setVolume(static_cast<float>(sound));
                        no.play();
                        if (!proverksovpada(polle, player, vrag, crystalsounds,sound)) {
                          
                            animfase = 2;
                            anim1.pr = 0.0f;
                            anim2.pr = 0.0f;
                            anim1.fx = tx; anim1.fy = ty; anim1.tx = sx; anim1.ty = sy;
                            anim2.fx = sx; anim2.fy = sy; anim2.tx = tx; anim2.ty = ty;


                        }
                        else {
                            hodovv--;


                            dropandspawn(polle, crystaltex, vidcrystal, poleY, c, player, vrag);
                            boardStable = false;

                            anim1.activ = false;
                            anim2.activ = false;
                            animfase = 0;

                        }
                    }
                    else if (animfase == 2) {

                        obmen(polle, sx, sy, tx, ty);


                        anim1.activ = false;
                        anim2.activ = false;
                        animfase = 0;
                    }
                }
            }
        }
        if (!boardStable) {

            bool elementsAreFalling = updateFalling(polle, dt);


            if (!elementsAreFalling) {

                if (proverksovpada(polle, player, vrag, crystalsounds,sound)) {

                    dropandspawn(polle, crystaltex, vidcrystal, poleY, c, player, vrag);
                }
                else {

                    boardStable = true;
                }
            }
        }
        if (ekran == 1 && hodovv <= 0 && boardStable && !anim1.activ && !anim2.activ) {


            if (!vrag.getogl()) {
                if (vrag.geturron() > 0) {
                    player.poluron(vrag.geturron());
                }
                if (vrag.getdeff() > 0) {
                    vrag.adddefense(vrag.getdeff());
                }
            }
            else {
                vrag.removeogl();
            }
            roundd++;
            hodovv = 5;
            vrag.action();

        }
       
        
        if (ekran == 1 && vrag.gethp() <= 0) {
       
            act1lvl[cursellevel].winn = true;
            savehp = player.gethp();

            if (cursellevel == 10) {
                finalwin = true; 

                if (idpers == 1) {
                    persunlock[2] = true;
                }
                else if (idpers == 2) {
                    persunlock[3] = true;
                }
  
            }
            else {
                if (cursellevel != 3 && cursellevel != 9) {
                    act1lvl[cursellevel + 1].unlock = true;
                }
                levelwin = true;
            }
            savgame(idpers); 
        }
        if (ekran == 1) {

            if (player.gethp() < lplhp) {
                perst = hitd;
            }
            lplhp = player.gethp();

         
            if (vrag.gethp() < lenmhp) {
                if (vrag.getid() == 1) {
                    enemyt = hitd;
                }
                else if (vrag.getid() == 2) {
                    enemy2t = hitd;
                }
                else if (vrag.getid() == 3) {
                    elitt = hitd;
                }
                else if (vrag.getid() == 4) {
                    bost = hitd;
                }
                else if (vrag.getid() == 5) {
                    elitt2 = hitd;
                }
            }
            lenmhp = vrag.gethp();

          
            if (perst > 0.0f) {
                perst -= dt;
                if (perst < 0.0f) perst = 0.0f;

                float progress = (hitd - perst) / hitd;
                float offset = 0.0f;

                if (progress < 0.25f) {
                    offset = (progress / 0.25f) * maxoffset;
                }
                else {
                    offset = maxoffset * (1.0f - (progress - 0.25f) / 0.75f);
                }

                Vector2f curperspoz = baseperspoz;
                curperspoz.x -= offset;
                pers.setPosition(curperspoz); 
            }

         
            if (enemyt > 0.0f) {
                enemyt -= dt;
                if (enemyt < 0.0f) enemyt = 0.0f;

                float progress = (hitd - enemyt) / hitd;
                float offset = 0.0f;

                if (progress < 0.25f) {
                    offset = (progress / 0.25f) * maxoffset;
                }
                else {
                    offset = maxoffset * (1.0f - (progress - 0.25f) / 0.75f);
                }

                Vector2f currentEnemyPos = baseememypoz;
                currentEnemyPos.x -= offset;
                enemy.setPosition(currentEnemyPos); 
            }
            if (enemy2t > 0.0f) {
                enemy2t -= dt;
                if (enemy2t < 0.0f) enemy2t = 0.0f;

                float progress = (hitd - enemy2t) / hitd;
                float offset = 0.0f;

                if (progress < 0.25f) {
                    offset = (progress / 0.25f) * maxoffset;
                }
                else {
                    offset = maxoffset * (1.0f - (progress - 0.25f) / 0.75f);
                }

                Vector2f currentEnemy2Pos = baseenemy2poz;
                currentEnemy2Pos.x -= offset;
                vrag2.setPosition(currentEnemy2Pos);
            }

          
            if (elitt > 0.0f) {
                elitt -= dt;
                if (elitt < 0.0f) elitt = 0.0f;

                float progress = (hitd - elitt) / hitd;
                float offset = 0.0f;

                if (progress < 0.25f) {
                    offset = (progress / 0.25f) * maxoffset;
                }
                else {
                    offset = maxoffset * (1.0f - (progress - 0.25f) / 0.75f);
                }

                Vector2f currelitpoz = baseelitvrag;
                currelitpoz.x -= offset;
                elitvrag1.setPosition(currelitpoz); 
            }
            if (elitt2 > 0.0f) {
                elitt2 -= dt;
                if (elitt2 < 0.0f) elitt2 = 0.0f;

                float progress = (hitd - elitt2) / hitd;
                float offset = 0.0f;

                if (progress < 0.25f) {
                    offset = (progress / 0.25f) * maxoffset;
                }
                else {
                    offset = maxoffset * (1.0f - (progress - 0.25f) / 0.75f);
                }

                Vector2f currelit2poz = baseelitvrag2;
                currelit2poz.x -= offset;
                elit2vr.setPosition(currelit2poz);
            }

          
            if (bost > 0.0f) {
                bost -= dt;
                if (bost < 0.0f) bost = 0.0f;

                float progress = (hitd - bost) / hitd;
                float offset = 0.0f;

                if (progress < 0.25f) {
                    offset = (progress / 0.25f) * maxoffset;
                }
                else {
                    offset = maxoffset * (1.0f - (progress - 0.25f) / 0.75f);
                }

                Vector2f currbospoz = baseboss;
                currbospoz.x -= offset;
                bosss.setPosition(currbospoz); 
            }
        }
        if (perst == 0.0f) pers.setPosition(200.f, 545.f);
        if (enemyt == 0.0f)enemy.setPosition(1490.f, 605.f);
        if (enemy2t == 0.0f)vrag2.setPosition(1490.f, 525.f);
        if (elitt == 0.0f) elitvrag1.setPosition(1440.f, 515.f);
        if(elitt2 == 0.0f) elit2vr.setPosition(1440.f, 405.f);
        if (bost == 0.0f) bosss.setPosition(1420.f, 490.f);
        
       
    
        

        Vector2f mous = window.mapPixelToCoords(Mouse::getPosition(window), window.getView());
        //Vector2f mous = window.mapPixelToCoords(pozic);

        venr.setScale(1.0f, 1.0f);
        obichvrag.setScale(1.0f, 1.0f);
        obichvrag1.setScale(1.0f, 1.0f);
        obichvrag2.setScale(1.0f, 1.0f);
        obichvrag3.setScale(1.0f, 1.0f);
        obichvrag4.setScale(1.0f, 1.0f);
        obichvrag5.setScale(1.0f, 1.0f);
        obichvrag6.setScale(1.0f, 1.0f);
        obichvrag7.setScale(1.0f, 1.0f);
        vost.setScale(1.0f, 1.0f);
        vost1.setScale(1.0f, 1.0f);
        okknopka.setScale(1.0f, 1.0f);
        prodolmen.setScale(1.0f, 1.0f);
        vixxod.setScale(1.0f, 1.0f);
        okknopk.setScale(1.0f, 1.0f);
        okonp.setScale(1.0f, 1.0f);
        if (levelwin) {
            if (okknopk.getGlobalBounds().contains(mous)) {
                okknopk.setScale(1.1f, 1.1f);
            }
        }
        if (finalwin) {
            if (okknopka.getGlobalBounds().contains(mous)) {
                okknopka.setScale(1.1f, 1.1f);
            }
        }
        if (pauza) {
            if (prodolmen.getGlobalBounds().contains(mous)) {
                prodolmen.setScale(1.1f, 1.1f);
            }
            if (vixxod.getGlobalBounds().contains(mous)) {
                vixxod.setScale(1.1f, 1.1f);
            }
        }
        if (levelwin || vostoknoo) {
            if (okonp.getGlobalBounds().contains(mous)) {
                okonp.setScale(1.1f, 1.1f);
            }
        }
        else {
            if (venr.getGlobalBounds().contains(mous))
                venr.setScale(1.1f, 1.1f);
            if (obichvrag.getGlobalBounds().contains(mous) && act1lvl[1].unlock && !act1lvl[1].winn)
                obichvrag.setScale(1.1f, 1.1f);
            if (obichvrag1.getGlobalBounds().contains(mous) && act1lvl[2].unlock && !act1lvl[2].winn)
                obichvrag1.setScale(1.1f, 1.1f);
            if (vost.getGlobalBounds().contains(mous) && act1lvl[3].unlock && !act1lvl[3].winn)
                vost.setScale(1.1f, 1.1f);
            if (obichvrag2.getGlobalBounds().contains(mous) && act1lvl[4].unlock && !act1lvl[4].winn)
                obichvrag2.setScale(1.1f, 1.1f);
            if (obichvrag3.getGlobalBounds().contains(mous) && act1lvl[5].unlock && !act1lvl[5].winn)
                obichvrag3.setScale(1.1f, 1.1f);
            if (obichvrag4.getGlobalBounds().contains(mous) && act1lvl[6].unlock && !act1lvl[6].winn)
                obichvrag4.setScale(1.1f, 1.1f);
            if (obichvrag5.getGlobalBounds().contains(mous) && act1lvl[7].unlock && !act1lvl[7].winn)
                obichvrag5.setScale(1.1f, 1.1f);
            if (obichvrag6.getGlobalBounds().contains(mous) && act1lvl[8].unlock && !act1lvl[8].winn)
                obichvrag6.setScale(1.1f, 1.1f);
            if (vost1.getGlobalBounds().contains(mous) && act1lvl[9].unlock && !act1lvl[9].winn)
                vost1.setScale(1.1f, 1.1f);
            if (obichvrag7.getGlobalBounds().contains(mous) && act1lvl[10].unlock && !act1lvl[10].winn)
                obichvrag7.setScale(1.1f, 1.1f);
        }





        

        float ultr = static_cast<float>(player.getulta()) / player.getmaxulta();
        if (ultr > 1.0f) ultr = 1.0f;
        int maxultwidth = ultpltex.getSize().x;
        int ultheight = ultpltex.getSize().y;
        int curvecultw = static_cast<int>(maxultwidth * ultr);
        ultpl.setTextureRect(IntRect(0, 0, curvecultw, ultheight));
        ulttext.setString(to_string(player.getulta()) + "/" + to_string(player.getmaxulta()));
        ulttext.setPosition(270.0f, 960.0f);
        if (player.getulta() >= player.getmaxulta()) {
            ult.setTexture(ultttex);
        }
        else {
            ult.setTexture(ultptex);
        }
        float playerhpr= static_cast<float>(player.gethp()) / player.getmaxhp();
        int curvecplayerw = static_cast<int>(maxhpwidth * playerhpr);
        playerhp.setTextureRect(IntRect(0, 0, curvecplayerw, hpheight));
        playerhptext.setString(to_string(player.gethp()) + "/" + to_string(player.getmaxhp()));
        playerhptext.setPosition(250.0f, 875.0f);
        float enemyhpr = static_cast<float>(vrag.gethp()) / vrag.getmaxhp();
        int curvecenemyw = static_cast<int> (maxhpwidth * enemyhpr);
        vraghp.setTextureRect(IntRect(0, 0, curvecenemyw, hpheight));
       enemyhptext.setString(to_string(vrag.gethp()) + "/" + to_string(vrag.getmaxhp()));
       enemyhptext.setPosition(1540.0f, 868.0f);
       playerdeftext.setString(to_string(player.getdefense()));
       playerdeftext.setPosition(438.0f, 875.0f);
       enemydeftext.setString(to_string(vrag.getdefense()));
       enemydeftext.setPosition(1718.0f, 872.0f);
       hodtext.setString(to_string(hodovv));
       hodtext.setPosition(980.0f, 27.0f);
       raundtext.setString(to_string(roundd));
       raundtext.setPosition(1845.0f, 25.0f);
       bool geturron = (vrag.geturron() > 0);
       bool getdeff = (vrag.getdeff() > 0);
       if (geturron && getdeff) {
           deffen.setPosition(1630, 294);
           atak.setPosition(1510, 300);
           ataktext.setString(to_string(vrag.geturron()));
           ataktext.setPosition(1460.0f, 300.0f);
           deftext.setString(to_string(vrag.getdeff()));
           deftext.setPosition(1580.0f, 294.0f);
       }
      
     
        window.clear();
        if (ekran == 0) {
            window.draw(fonn);
            window.draw(venr);
            if (act1lvl[1].winn) obichvrag.setTexture(vragdtex);
            window.draw(obichvrag);
            window.draw(kvadr);
            if (act1lvl[2].winn) obichvrag1.setTexture(vragdtex);
            window.draw(obichvrag1);
            window.draw(kvadr1);
            window.draw(kvadr2);
            window.draw(kvadr3);
            if (act1lvl[3].winn)vost.setTexture(vostpt);
            window.draw(vost);
            window.draw(kvadr4);
            window.draw(kvadr5);
            if (act1lvl[4].winn)obichvrag2.setTexture(vragdtex);
            window.draw(obichvrag2);
            window.draw(kvadr6);
            window.draw(kvadr7);
            if (act1lvl[5].winn)obichvrag3.setTexture(elitvragd);
            window.draw(obichvrag3);
            window.draw(kvadr8);
            window.draw(kvadr9);
            if (act1lvl[6].winn)obichvrag4.setTexture(vragdtex);
            window.draw(obichvrag4);
            window.draw(kvadr10);
            window.draw(kvadr11);
            if (act1lvl[7].winn)obichvrag5.setTexture(vragdtex);
            window.draw(obichvrag5);
            window.draw(kvadr12);
            window.draw(kvadr13);
            if (act1lvl[8].winn)obichvrag6.setTexture(elitvragd);
            window.draw(obichvrag6);
            window.draw(kvadr14);
            window.draw(kvadr15);
            if (act1lvl[9].winn)vost1.setTexture(vostpt);
            window.draw(vost1);
            window.draw(kvadr16);
            window.draw(kvadr17);
            if (act1lvl[10].winn)obichvrag7.setTexture(bossd);
            window.draw(obichvrag7);
          
        }
        else if (ekran == 1) {
            window.draw(fno);
            window.draw(p);
            window.draw(pause);
         
            if (idpers == 1) pers.setTexture(pers1tex);
            if (idpers == 2) pers.setTexture(pers2tex);
            if (idpers == 3) pers.setTexture(pers3tex);
            window.draw(pers);
            if (vrag.getid() == 1) {
                window.draw(enemy); 
            }
            if (vrag.getid() == 2) {
                window.draw(vrag2);
            }
            else if (vrag.getid() == 3) {
                window.draw(elitvrag1); 
            }
            else if (vrag.getid() == 4) {
                window.draw(bosss); 
            }
            else if (vrag.getid() == 5) {
                window.draw(elit2vr);
            }
           
            window.draw(pole);
          
            
        
            window.draw(pust);
            window.draw(playerhp);
            window.draw(plos);
            window.draw(playerhptext);
            window.draw(playerdeftext);
            window.draw(pustvrag);
            window.draw(vraghp);
            window.draw(plosvrag);
            window.draw(enemyhptext);
            window.draw(enemydeftext);
            window.draw(pustulta);
            window.draw(ultpl);
            window.draw(plosulta);
            window.draw(ulttext);
            window.draw(ult);
            window.draw(hodov);
            window.draw(raund);
            window.draw(hodtext);
            window.draw(raundtext);

            if (vrag.getogl()) {
                window.draw(ogl);
            }
            else {

                if (geturron) {
                    window.draw(atak);
                    window.draw(ataktext);
                }
                if (getdeff) {
                    window.draw(deffen);
                    window.draw(deftext);
                }
                
            }
           

            for (int i = 0; i < w; i++) {
                for (int j = 0; j < h; j++) {


                    float currentX = poleX + i * c;
                    float currentY = polle[i][j].currentY;

                    if (anim1.activ && anim2.activ) {
                     
                        if (i == anim1.fx && j == anim1.fy) {
                            currentX = (poleX + anim1.fx * c) + ((poleX + anim1.tx * c) - (poleX + anim1.fx * c)) * anim1.pr;
                            currentY = (poleY + anim1.fy * c) + ((poleY + anim1.ty * c) - (poleY + anim1.fy * c)) * anim1.pr;
                        }
                        
                        else if (i == anim2.fx && j == anim2.fy) {
                            currentX = (poleX + anim2.fx * c) + ((poleX + anim2.tx * c) - (poleX + anim2.fx * c)) * anim2.pr;
                            currentY = (poleY + anim2.fy * c) + ((poleY + anim2.ty * c) - (poleY + anim2.fy * c)) * anim2.pr;
                        }
                    }

                    polle[i][j].sprite.setPosition(currentX, currentY);
                    window.draw(polle[i][j].sprite);
                
                }
            }
        }
        if (vostoknoo) {
            window.draw(zatemn); 
            window.draw(okvost);  
            window.draw(okonp);
        }
        if (finalwin) {
            window.draw(zatemn);
            window.draw(podebba);
            window.draw(okknopka);
        }
        if (levelwin) {
            window.draw(zatemn);
            window.draw(pobedaa);
            window.draw(okknopk);
        }
        if (proigrh) {
            window.draw(zatemn);
            window.draw(proigr);
            window.draw(okknopkaa);
            window.display();
            continue;
        }
        if (pauza) {
            window.draw(zatemn);
            window.draw(pausse);
            window.draw(prodolmen);
            window.draw(vixxod);
        }
        window.display(); 
    }

}
