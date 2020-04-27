#ifndef GAME_HPP
#define GAME_HPP

#include "Rooms.hpp"
#include <functional>
#include <map>
#include <string>
#include <vector>

using namespace std;

class GameWumpus;
class Room;
class Item;

enum game_txt { TITLE_SCREEN, INTRO_YOU, INTRO_ARE, INTRO_TDM,
  DIE, DANCE, GET, GET_DAGGER, GO, LOOK, UNKNOWN, TALK, GIVE, SMELL
};

class Game {
  public:
    Game();
    //~Game();  // Soon...

    inline vector<string> getArgs();  // Canst this be thy way?
    inline void sayArgs(vector<string> &args) const;
    inline void sayArgs(vector<string> &args, int start, int end) const;
    void sayCmd(int cmd) const;
    void sayTxt(const string *_txt) const;
    inline int getScore() const;

    void lc(string *io);

    bool play(void);

    void addToScore(int amt);
    void Over();

  private:
    int score;
    bool over = false;

    enum room_key { MAIN_ROOM, NORTH, SOUTH, DENNIS };
    vector<Room *> rooms = { new MainRoom(), new NorthRoom() };
    Room *room = rooms.at(0);  // Current room

    const string txt[14] = {
      // Title screen
      " \"#\" # # # #   #\"= # # #\"# #\"\" #\"\" #\"# #\"# #=# #\"# #\"#  .   .\n"
      "  #  #\"#  #    # # # # # # # # #\"\" # # # # # # #\"# # # =#= =#=\n"
      "  \"  \" \"  \"    \"\"  \"\"\" \" \" \"\"\" \"\"\" \"\"\" \" \" \" \" \" \" \" \"  \"   \"\n"
      "\n"
      "                    /\\      /\\      /\\\n"
      "                    ||/----\\||      ||\n"
      "                    \\_------_/      ||\n"
      "                     / o  o \\       ||\n"
      "                     /  ||  \\    o__||__o\n"
      "                     / ---- \\     \\____/\n"
      "                     /\\/\\/\\/\\       ||\n"
      "                                    oo\n"
      "\n"
      "         ~=Press the ENTER key to enter yon dungeon=~\n",
      // Intro sequence
      "░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n"
      "░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n"
      "░░░░░░░░░░░░░░░  m   m   mmm   m   m  ░░░░░░░░░░░░░░░\n"
      "░░░░░░░░░░░░░░░  \"m m\"  #\" \"#  #   #  ░░░░░░░░░░░░░░░\n"
      "░░░░░░░░░░░░░░░   #m#   #   #  #   #  ░░░░░░░░░░░░░░░\n"
      "░░░░░░░░░░░░░░░   \"#    \"#m#\"  \"mm\"#  ░░░░░░░░░░░░░░░\n"
      "░░░░░░░░░░░░░░░   m\"                  ░░░░░░░░░░░░░░░\n"
      "░░░░░░░░░░░░░░░ \"\"                    ░░░░░░░░░░░░░░░\n"
      "░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n"
      "░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░",

      "░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n"
      "░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n"
      "░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n"
      "░░░░░░░░░░░░░░░   mmm    m mm   mmm   ░░░░░░░░░░░░░░░\n"
      "░░░░░░░░░░░░░░░  \"   #   #\"  \" #\"  #  ░░░░░░░░░░░░░░░\n"
      "░░░░░░░░░░░░░░░  m\"\"\"#   #     #\"\"\"\"  ░░░░░░░░░░░░░░░"
      "\n░░░░░░░░░░░░░░░  \"mm\"#   #     \"#mm\"  ░░░░░░░░░░░░░░░"
      "\n░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n"
      "░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n"
      "░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░",

      "░░░░░░░░░░░░░░░░░░░░░░\"#\"░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n"
      "░░░░░░░░░░░░░░░░░░░░░░░#░░#░#░░░░░░░░░░░░░░░░░░░░░░░░\n"
      "░░░░░░░░░░░░░░░░░░░░░░░\"░░#\"#░#░#░░░░░░░░░░░░░░░░░░░░\n"
      "░░░░░░░░░░░░░░░░░░░░░░░░░░\"░\"░░#░░░░░░░░░░░░░░░░░░░░░\n"
      "░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\"░░░░░░░░░░░░░░░░░░░░░\n"
      "░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n"
      "░#\"=░░░░░#\"#░░░░░#\"\"░░░░░░#\"#░░░░░░░░░░#\"#░░░░░#░"
      "░░#░\n░#░#░#░#░#░#░#\"\"░#\"\"░░#\"#░#░#░░░░░░#=#░#\"#░#\"#░"
      "\"░#░\"░\n░\"\"░░#░#░\"░\"░#░#░\"\"\"░░#░#░\"░\"░░░░░░#░#░\""
      "░\"░#░#░\"░\"░\"░\n░░░░░\"\"\"░░░░░\"\"\"░░░░░░\"\"\"░░░░░░░"
      "░░░\"░\"░░░░░\"░\"░░░\"░░░",
      // General commands
      "That wasn't very smart. Your score was: %s. \n"
      "Play again? [Y/N] ",

      "Thou shaketh it a little, and it feeleth all right.",

      "Thou cannotst get that. Quit making stuffeth up!",

      "Yeah, okay",

      "Thou cannotst go there. Who do you think thou art?\n"
      "A magistrate?!",

      "It looketh pretty awesome.",
      "That does not computeth. Type HELP is thou needs of it.",

      "Who is %n? Your new boyfriend? Somebody from work you\n"
      "don't want me to meeteth?",

      "Thou don'tst have %AN %ARGS to give. Go back to your\n"
      "tiny life.",

      "You smell a Wumpus."
    };
};

#endif  // GAME_HPP
