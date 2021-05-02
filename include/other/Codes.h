#ifndef KEYCODES_H
#define KEYCODES_H

#include <map>
#include <string>

/** Usage:
*    key::codes_{ \type }.at(`string key name`)
*    -- returns int key code
*
*    lang::lang.at({ \language }).at({ \textIndex })
**/
namespace key{
    // KeyCodes Map Used In OnKeyDown Event
    const std::map< std::string, int > codes_misc = {
        {"enter", 13},
        {"space", 32},
        {"esc",   27},
    };

    const std::map< std::string, std::map <std::string, int> > codes_move = {
        // Arrow Key Codes
        {"Arrows",{
            {"down",  317},
            {"right", 316},
            {"up",    315},
            {"left",  314},}
        },
        // WSAD Key Codes
        {"WSAD",{
            {"down",  83},
            {"right", 68},
            {"up",    87},
            {"left",  65},}
        }
        //
    };
}

// Language Map for Translations
///TODO Options uising int indexes
namespace lang {
    const std::map< std::string , std::map <std::string, std::string>> lang {
        {"Polski", {
            {"info_text_stop",       "\'Esc\' By Zatrzymac Gre"},
            {"info_text_start",      "\'Esc\' By Rozpoczac Gre"},
            {"info_text_move_arrow", "Uzyj Strzalek Do Ruszania"},
            {"info_text_move_wsad",  "Uzyj WSAD DO Ruszania"},
            {"time_left",            "Pozostalo:"},
            {"language_pick",        "Jezyk"},
            {"movement_pick",        "Metoda\nRuszania"},
            {"save_options",         "Zapisz Opcje"},
            {"score",                "Wynik:"},
            {"high_score",           "Rekord:"},
            {"game_paused",          "WSTRZYMANO"},
            {"author",               "Autor"},
            {"space_button",         "Nacisnij \'Spacje\' By Strzelic Pocisk"},
            {"close_button",         "Zakoncz"},
            {"again_button",         "Od Nowa"},
            {"end_text",             "Zwyciestwo!"},
            }
        },
        {"English", {
            {"info_text_stop",       "Press \'Esc\' To Pause Game"},
            {"info_text_start",      "Press \'Esc\' To Release"},
            {"info_text_move_arrow", "Use Arrows To Move"},
            {"info_text_move_wsad",  "Use WSAD To Move"},
            {"time_left",            "Time Left:"},
            {"language_pick",        "Language"},
            {"movement_pick",        "Movement\nKeys"},
            {"save_options",         "Save Options"},
            {"score",                "Score:"},
            {"high_score",           "High Score:"},
            {"game_paused",          "GAME PAUSED"},
            {"author",               "Created By"},
            {"space_button",         "Press \'Space\' To Shoot Bullet"},
            {"close_button",         "Exit"},
            {"again_button",         "Play Again"},
            {"end_text",             "Victory!"},
            }
        }
    };
}

// key::codes -> simple good looking statement
// why {namespace}? -> why not?
#endif
