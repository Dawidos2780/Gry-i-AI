/* Dawid Szymczyna 252920 10.06.2021 Projekt 3 "Gry i AI" */
/* Program pozwala na grę w "kółko i krzyżyk" gracza i komputera.
AI zrealizowane jest przy pomocy funckji MinMax, oraz pewnych jej modyfikacji w zależności od wielkośći planszy. */

#include <iostream>
#include <iomanip>
#include <cstring>
#include <cassert>
#include <math.h>
 
#include "board.hh"
#include "AI.hh"

using namespace std;

/* Test gry */
void graj(Checker_board Checker_board, int wygrana, int reset, int rules){

    int old_size = Checker_board.size_board;
    Checker_board.turn = 0;

    while(wygrana = 1){

        /* Włączenie gry po raz pierwszy lub zmiana wielkości planszy */
        if(reset == 0){
            cout << "Podaj rozmiar planszy" << endl;
            cin >> Checker_board.size_board;

            if(rules == 0 || old_size != Checker_board.size_board){ // wyświetlenie zasad przy każdorazowej zmianie wielkości planszy
                Checker_board.print_rules();
                rules++;
            }
            
            reset++;
            Checker_board.init_board(); // generowanie planszy
            Checker_board.first_board(); // wypełnienie planszy znakiami upraszczającymi grę
            
        }

        /* Zaczynał gracz */
        if(Checker_board.main_player == 'X'){
            Checker_board.move();
            Checker_board.turn++;

            Checker_board.print_board_vis();
            Checker_board.print_board();

            if(Checker_board.who_won() == 10){
                reset = 0;

                Checker_board.pkt_player++;
                Checker_board.tab_winners[Checker_board.pkt_player + Checker_board.pkt_ai] = Checker_board.main_player;

                cout << "Wygrał gracz '" << Checker_board.main_player << "' " << endl;
                Checker_board.show_results();
                
                graj(Checker_board, wygrana, reset, rules);
            }

            if(Checker_board.turn >= Checker_board.size_board * Checker_board.size_board){
                reset = 0;
                
                Checker_board.tab_winners[Checker_board.pkt_player + Checker_board.pkt_ai] = Checker_board.AI_player;
                
                cout << "Remis" << endl;
                Checker_board.show_results();
                
                graj(Checker_board, wygrana, reset, rules);
            }

            Checker_board.bestmove();
            Checker_board.turn++;

            Checker_board.print_board_vis();
            Checker_board.print_board();

            if(Checker_board.who_won() == -10){
                reset = 0;
                
                Checker_board.pkt_ai++;
                Checker_board.tab_winners[Checker_board.pkt_player + Checker_board.pkt_ai] = Checker_board.AI_player;
                
                cout << "Wygrał komputer '" << Checker_board.AI_player << "' " << endl;
                Checker_board.show_results();
                
                graj(Checker_board, wygrana, reset, rules);
            }

            if(Checker_board.turn >= Checker_board.size_board * Checker_board.size_board){
                reset = 0;
                
                Checker_board.pkt_ai++;
                Checker_board.tab_winners[Checker_board.pkt_player + Checker_board.pkt_ai] = Checker_board.AI_player;
                
                cout << "Remis" << endl;
                Checker_board.show_results();
                
                graj(Checker_board, wygrana, reset, rules);
            }

        }

        /* Zaczynał komputer */
        else{
           
            Checker_board.bestmove();
            Checker_board.turn++;

            Checker_board.print_board_vis();
            Checker_board.print_board();

            if(Checker_board.who_won() == -10){ // wygrało AI
                reset = 0;
                
                Checker_board.pkt_ai++;
                Checker_board.tab_winners[Checker_board.pkt_player + Checker_board.pkt_ai] = Checker_board.AI_player;
                
                cout << "Wygrał komputer '" << Checker_board.AI_player << "' " << endl;
                Checker_board.show_results();
                
                graj(Checker_board, wygrana, reset, rules);
            }

            if(Checker_board.turn >= Checker_board.size_board * Checker_board.size_board){ // remis
                reset = 0;
                
                Checker_board.pkt_ai++;
                
                Checker_board.tab_winners[Checker_board.pkt_player + Checker_board.pkt_ai] = Checker_board.AI_player;
                
                cout << "Remis" << endl;
                Checker_board.show_results();
                
                graj(Checker_board, wygrana, reset, rules);
            }


           

             Checker_board.move();
            Checker_board.turn++;

            Checker_board.print_board_vis();
            Checker_board.print_board();

            if(Checker_board.who_won() == 10){ // wygrał gracz
                reset = 0;

                Checker_board.pkt_player++;
                Checker_board.tab_winners[Checker_board.pkt_player + Checker_board.pkt_ai] = Checker_board.main_player;

                cout << "Wygrał gracz '" << Checker_board.main_player << "' " << endl;
                Checker_board.show_results();
                
                graj(Checker_board, wygrana, reset, rules);
            }

            if(Checker_board.turn >= Checker_board.size_board * Checker_board.size_board){ // remis
                reset = 0;
                
                Checker_board.tab_winners[Checker_board.pkt_player + Checker_board.pkt_ai] = Checker_board.AI_player;
                
                cout << "Remis" << endl;
                Checker_board.show_results();
                
                graj(Checker_board, wygrana, reset, rules);
            }


        }
            
              
    }

}

int main()
{
    Checker_board Checker_board;

    int wygrana = 1, reset = 0, rules = 0;

    graj(Checker_board, wygrana, reset, rules);

    return 0;
}
