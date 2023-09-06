/*----------------------------------------------------------------------------------
Implementazione della classe Enemy ("Nemico"), sottoclasse di Character, 
e classe base delle altre classi che definiscono gli altri tipi di nemici
----------------------------------------------------------------------------------*/

#include <ncurses/ncurses.h>
#include <string.h>
#include "Hero.h"

class Enemy: public Character{

    public:
        int money_released; //soldi rilasciati dal nemico sconfitto
        int score_released; //punteggio rilasciato dal nemico sconfitto
        int enemy_type; //ogni tipo di nemico viene identificato da un numero

        const int DEF_SCORE = 25;
        const int DEF_MONEY = 10;
        const int DEF_HP = 40;
        const int DEF_ST = 15;
        const int DEF_DF = 0;

        const char* enemy_shape_right[2]= {
                "  ( )( )",
                "_( _'w')_"
        };
        const char* enemy_shape_left[2]= {
                " ( )( )  ",
                "_('w'_ )_"
        };

        const char* enemy_shape_right_hit[2]= {
                "  ( )( )",
                "_( _@.@)_"
        };
        const char* enemy_shape_left_hit[2]= {
                " ( )( )  ",
                "_(@.@_ )_"
        };

        const char* enemy_shape_dead[2]= {
                "/  X X  \\",
                "VVVVVVVVV"
        };

        //costruttore dei nemici. Richiama il costruttore della classe Character.
        Enemy(WINDOW * win, int y, int x, int type, int bRight, MapManager* map, bool isL, int hp = 40, int st = 15, int df = 0, int r = 2, int score_rel = 25, int money_rel = 10):Character(win, y, x, bRight, map, isL, hp, st, df, r){
                enemy_type = type;
                money_released = money_rel;
                score_released = score_rel;
        }
        void mv_left_right();
        void check_enemy_player_collision(Hero *p);
        Hero::p_bullet check_enemy_bullet_collision(Hero *p, Hero::p_bullet h);
};