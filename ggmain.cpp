#include <iostream>
#include <list>
#include <stack>
#include <iterator>

using namespace std;

//čvor u drvu - sazdrži listu, evaluation value, alpha, beta
struct node
{
    list<int> lista;
    int nodedepth;
    int turn; //TKO VUČE POTEZ U TOM TRENU, 1 je kompjuter, 0 je čovjek
    int evaluation; // EVALUATION JE 1 AKO KOMP POBJEĐUJE, -1 AKO ČOVJEK POBJEĐUJE, 0 AKO SE IGRA NASTAVLJA
    int alpha;
    int beta;
    node* parent;
    list<node> children;

    //default konstuktor
    node(){
        nodedepth=0;
        turn=1;
        lista.clear();
        children.clear();
        evaluation=0;
        alpha=-1;
        beta=1;
        parent=nullptr;
    };

    //konstruktor s listom
    node(list<int> L){
        list<int>::iterator li;
        lista.clear();
        for (li=L.begin(); li!=L.end(); li++){
            int element=*li;
            lista.push_front(element);
        };

        nodedepth=0;
        turn=1;
        children.clear();
        evaluation=0;
        alpha=-1;
        beta=1;
        parent=nullptr;
    };

    //kopira listu u node
    void input_list(list<int> L){
        list<int>::iterator li;
        lista.clear();
        for (li=L.begin(); li!=L.end(); li++){
            int element=*li;
            lista.push_front(element);
        };
    };


    void copy(node zakopirati){
          nodedepth=zakopirati.nodedepth;
          turn=zakopirati.turn;
          evaluation=zakopirati.evaluation;
          alpha=zakopirati.alpha;
          beta=zakopirati.beta;
          this->input_list(zakopirati.lista);
          parent=zakopirati.parent;

          list<node>::iterator it;
          children.clear();
          for (it=zakopirati.children.begin(); it!=zakopirati.children.end(); it++){
              children.push_back(*it);
          };
        };


    bool gameover(node temp){
        list<int>::iterator li;
        for (li=temp.lista.begin(); li!=temp.lista.end(); li++){
            int element=*li;
            if (element>2)return false;
        };
        return true;
    };

    void expand(){
         list<int>::iterator li;
         //IDEM PO HRPAMA
         for(li=lista.begin(); li!=lista.end(); li++){
           int element=*li;
           int i;
           for (i=1; i<element; i++){
               //NE SMIJEM DIJELITI NA JEDNAKE HRPE
                int ostatak=element-i;
                if (ostatak!=i){
                     //RADIM NOVI CHILDLIST
                    list<int> tmplist;
                    list<int>::iterator ti;
                    for(ti=lista.begin(); ti!=lista.end(); ti++){
                        if(ti!=li){int tmpelement=*ti; tmplist.push_back(tmpelement);}else{tmplist.push_back(i);tmplist.push_back(ostatak);};
                        };
                    //RADIM NOVI CHILDNODE I APPENDAM MU MAMU
                    node tmpnode(tmplist);
                    tmpnode.nodedepth=nodedepth+1;
                    if (turn==1){tmpnode.turn=0;}else{tmpnode.turn=0;}
                    if (this->gameover(tmpnode)==1){
                        if (tmpnode.turn==0){tmpnode.evaluation=-1;}else{tmpnode.evaluation=1;};
                    };
                    tmpnode.parent=this;
                    //APPENDAM CHILDNODE NA MAMU
                    children.push_back(tmpnode);
                     ;}
                };
           };

    };

    bool gameover(){
        list<int>::iterator li;
        for (li=lista.begin(); li!=lista.end(); li++){
            int element=*li;
            if (element>2)return false;
        };
        return true;};

};

int alphabeta(node *presentstate){

    //AKO JE PRESENTSTATE LIST
    if(presentstate->gameover()==1){
        if(presentstate->turn==0){
            //MINPLAYER LOST -> MAXPLAYER WON
            presentstate->evaluation=1;
            return presentstate->evaluation;
        }else{
            //MAXPLAYER LOST -> MINPLAYER WON
            presentstate->evaluation=-1;
            return presentstate->evaluation;
        };
    };

    //AKO PRESENTSTATE NIJE LIST, GLEDAM MU DJECU I BACAM REKURZIJU NA NJIH
    presentstate->expand();
    list<node>::iterator li;
    for (li=presentstate->children.begin(); li!=presentstate->children.end(); li++){
        node childnode(*li);
        if(presentstate->turn==1){
            //MAXPLAYER
            presentstate->alpha=max(presentstate->alpha, alphabeta(&childnode));
            if(presentstate->beta<=presentstate->alpha){break;};
            return presentstate->alpha;
        }else{
            //MINPLAYER
            presentstate->beta=min(presentstate->beta, alphabeta(&childnode));
            if(presentstate->beta<=presentstate->alpha){break;};
            return presentstate->beta;
        };
    };
    return -100; //DO OVDJE FUNKCIJA NE BI SMJELA DOCI, ERROR CONTROL
  };


// Klasa koja predstavljaigru između kompjutera i čovjeka
class Game{
public:

    //inicijalizator
    Game(int n){
        startingsizeheap=n;
        winflag=0;
        turn=0; //mi igramo prvi
        L.push_front(n);
    };
    //DONE

    //funkcija koja vrti igru i ispisuje niz novih hrpi u svakom potezu
    void run(){
        if(startingsizeheap<=2){
            if (turn==1){winflag=-1; cout << "Kompjuter je pobjedio" << endl; }
            else{winflag=1; cout << "Vi ste pobjedili" << endl;};
        };

        while (winflag==0){
            if (turn==1){this->computerPlayer();}else{this->personPlayer();};
           // this->printHeaps();

            //AKO JE IGRA GOTOVA OKIDA WINFLAG, AKO NIJE MIJENJA TURN
            if (this->gameover()==1){
                if(turn==0){winflag=1; cout << "Vi ste pobjedili" << endl;}
                else{winflag=-1; cout << "Kompjuter je pobjedio" << endl;};
            }else{
                if(turn==1){turn=0;}else{turn=1;};
            };
         };
    };
    //DONE

private:
    //provjerava je li igra gotova;
    bool gameover(){
        list<int>::iterator li;
        for (li=L.begin(); li!=L.end(); li++){
            int element=*li;
            if (element>2)return false;
        };
        return true;};
    //DONE

    // Ako kompjuter igra - radi bestmove
    void computerPlayer(){
        cout << "Kompjuter vuce potez:" << endl;
        //RADI NODE OD TRENUTNE SITUACIJE I VRŠI APLHABETA PRUNING/RAZVIJA DRVO NAD NJIM
        node root(L);
        alphabeta(&root);

        //ROOT NE MOŽE BITI LIST JER INAČE KOMPJUTER NE DOLAZI NA RED, TRAŽIM MU BESTMOVE DIJETE
        if(root.gameover()==0){

            //TRAŽIM NAJBOLJE DIJETE KOJE IMA NAJVEĆI BETA
            list<node>::iterator li;
            node bestchildnode(*root.children.begin());
            for(li=root.children.begin(); li!=root.children.end(); li++){
                node childnode(*li);
                if(childnode.beta>bestchildnode.beta)bestchildnode.copy(childnode);
                };

            //PREPISUJEM BESTCHILD LISTU U GAME LISTU, TJ RADIM BEST MOVE
            L.clear();
            list<int>::iterator ti;
            for (ti=bestchildnode.lista.begin(); ti!=bestchildnode.lista.end(); ti++){
                int element=*ti;
                L.push_back(element);
                };

        };
    };
    //DONE

    //Ako mi igramo - učitava move igrača
    void personPlayer(){
        //Pita za broj hrpe od [1,100]
        int flag1=0;
        int brojhrpe;
        while (flag1==0){
           cout<< "Koju hrpu po redu zelite dijeliti? Napisite broj! (od 1 do 100) ";
           cin >> brojhrpe;
           cout <<endl;
           int velicina=L.size();
           if (brojhrpe<=velicina && brojhrpe>0){flag1=1;}else{cout<< "Pogresan unos! Probajte opet. ";};
             };
        //Pita koliko zelimo uzeti novcica s te hrpe, iterator stavljam na mjesto
        int flag2=0;
        list<int>::iterator li;
        int counter=1;
        for (li=L.begin(); li!=L.end(); li++){if (counter==brojhrpe)break;};
        int nahrpi=*li;
        int uzeto=0;
        int ostalo=0;

        while (flag2==0){
           cout<< "Koliko novcica zelite uzeti sa nje i odijeliti u novu hrpu? Napisite broj! ";
           cin >> uzeto;

           ostalo=nahrpi-uzeto;
           if (nahrpi>uzeto && ostalo!=uzeto && uzeto>0){flag2=1;}else{cout<< "Pogresan unos! Probajte opet. ";};
        };
        //Brišem stari element iz liste i ubacujem nove
        L.erase(li);
        L.push_front(uzeto);
        L.push_front(ostalo);
    };
    //DONE

    //Printa sve hrpe
    void printHeaps(){
        list<int>::iterator li;
        for (li=L.begin(); li!=L.end(); li++){
            int element=*li;
            cout << element << " ";
        };
        cout << endl;
    };
    //DONE

private:
    int startingsizeheap;
    int winflag; //winflag==1 mi pobjedili, winflag==-1 komp pobjedio, winflag=0 igra se nastavlja
    int turn; //turn=0 mi igramo, turn=1 komp igra
    list<int> L;
};

int main()
{
    cout << "Upisite pocetni broj nocica na hrpi (izmedju 1 i 100): ";
    int n;
    cin >> n;
    if (n<=0 || n>100)throw "Unesen broj veci od 100 ili manji od 1!";

    Game Grundy(n);
    Grundy.run();

    return 0;
}
