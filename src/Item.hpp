#ifndef ITEM_HPP
#define ITEM_HPP

//#include "Game.hpp"
#include "Rooms.hpp"
#include <string>
#include <vector>

using namespace std;

class Game;

class GameWumpus {
  public:
    void gg(Game *);

  protected:
    Game *game;
};

class Item : public GameWumpus {
  public:
    Item();
    Item(const string item_fmt, ...);

    bool itm_get(void);
    void itm_look(void);

    int getIdx(char ikey) const;
    bool getOof() const;

  protected:
    int got_idx = -1;  // When a get gives your inventory an item
    int got_amt = 0;
    int kill_idx = -1;
    int kill_amt = 0;
    int score_mod_idx = -1;
    int score_mod_amt = 0;

    int get_idx = 0;
    int look_idx = 0;

    int look_type = 0;
    bool oof = false;

    vector<string> get_txt;
    vector<string> look_txt;
};

// Main dungeon room
class Scroll: public Item {
  public:
    Scroll();

    bool itm_get(void);
    void itm_look(void);

  private:
    bool zap = false;
};

class Flask: public Item {
  public:
    Flask();

    bool itm_get(void);
    void itm_look(void);
};

// North of main dungeon room
class Parapets: public Item {
  public:
    Parapets();

    bool itm_get(void);
    void itm_look(void);
};

class Rope: public Item {
  public:
    Rope();

    bool itm_get(void);
    void itm_look(void);
};

// South of main dungeon room
class Trinket: public Item {
  public:
    Trinket();

    bool itm_get(void);
    void itm_look(void);
};

// Dennis

#endif  // ITEM_HPP
