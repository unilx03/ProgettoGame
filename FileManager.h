#include <ncurses/ncurses.h>
#include <string>
#include <fstream>
using namespace std;

class Menu {
  protected:
      int a;
      int b;
      int xM;
      int yM;
      WINDOW *twin;

  public:
       void seta(int x){
            a = x;
        }
        int geta(){
            return a;
        }
        void setb(int y){
            b = y;
        }
        int getb(){
            return b;
        }
        void setxM(int xMx){
            xM = xMx;
        }
        int getxM(){
            return xM;
        }
        void setyM(int yMx){
            yM = yMx;
        }
        int getyM(){
            return yM;
        }
        WINDOW *getW(){
            return twin;
        }

    Menu(int x, int y, int xMx, int yMy){
          a=x;
          b=y;
          xM=xMx;
          yM=yMy;
          twin=newwin(yMy, xMx-1, x,y);
      }

    void wrW();

};

void creaFileStat();
void stampaConiglio(WINDOW *f, int n);
void selezionoScore(string v[]);
int create_menu();
void creaFinestra();
void perdita();
string inseriscinome();