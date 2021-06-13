#include "board.hh"

#include <iostream>
#include <math.h>
#include <limits>
#include <bits/stdc++.h>

using namespace std;

#define ascii 41

Checker_board::Checker_board(void){

}

/* Wyświetlenie zasad gry */
void Checker_board::print_rules(void){
   
    if(size_board < 3){
        cout << endl << "Tworzone są tylko plansze większe lub równe 3x3, ponieważ mniejsze warianty ciżęko jest nazwać grami, jeżeli zwycięstwo determinowane jest tylko przez wybór osoby zaczynającej" << endl;
        cout << endl << "----------------------------" << endl;
        
        if(size_board < 3){
            while(size_board < 3){
                pick_starting_piece();
                cout << "_'WYGRYWA'_" << main_player << endl;
                 cout << "Podaj wielkość planszy (size x size)" << endl;
                 cin >> size_board;
            }
        }
        
    }

    cout << endl << "----------------------------" << endl;
    cout << endl << "      ZASADY GRY   " << endl;
    cout << endl << "----------------------------" << endl;


    if(size_board >= 3 && size_board < 5){
        cout << endl << "1. Celem gry jest zdobycie " << size_board << " znaków w lini pionowo, poziomo lub na skos" << endl;
    }
    if(size_board >= 5){
        cout << endl << "1. Celem gry jest zdobycie 5 znaków w lini pionowo, poziomo lub na skos" << endl;
    }
    
    cout << endl << "2. Zaczyna gracz, który losowo otrzyma możliwość gry znakiem 'X'" << endl;
    cout << endl << "3. Dla uproszczenia każde pola opatrzone jest znakiem specjalnym, przez którego wciśniecie umieszczamy w nim SWÓJ znak" << endl;
    cout << endl << "4. Gracz, który wygrywa otrzymuje 1pkt" << endl;

    if(size_board == 3 ){
       cout << endl << "5. Wypełnienie całej planszy bez wyłonienia zwycięzcy oznacza remis i liczony jest jako 0pkt" << endl;
    }

    else if(size_board >= 4){
        cout << endl << "5. Wypełnienie całej planszy bez wyłonienia zwycięzcy oznacza zwycięstwo komputera 1pkt" << endl;
    }

    cout << endl << "----------------------------" << endl;
    
    cout << endl << "Naciśnij r, aby potwierdzić, że zasady zostały zrozumiane." << endl;
    char START;
    cin >> START;
    if(START != 'r') print_rules();
    cout << "\n\n\n\n\n\n";
}

/* Stworzenie pustej planszy */
void Checker_board::init_board(void){\
    
    pick_starting_piece();

    for(int i = 0; i < size_board; i++){
        for(int j = 0; j < size_board; j++){
            if(((i + j + 1) % 2) == 0){
                 board[i][j] = ' ';
            }
            else{
                board[i][j] = ' ';
            }

        }
    }
}

/* Wyświetlenie sytuacji na planszy max 9x9 */
/* Wypełnienie planszy max 9x9, znakami ASCII oraz stworzenie tablicy odrębnej z rzeczywistym
    wypełnieniem tablicy (tzn. tylko 'X', 'O', ' '). */
void Checker_board::first_board(void){

    int simplify = 41; // od tej wartości znaki ASII wyświetlane są poprawnie

    for(int i = 0; i < size_board; i++){
        for(int j = 0; j < size_board; j++){
            if((char)simplify == 79 || (char)simplify == 88) simplify++;
            board[i][j] = (char)simplify;
            board_vis[i][j] = ' ';
            //board_AI[i][j] = ' ';
            cout << "| " << (char)simplify++ << " |";
        }

        cout << endl;  

        if(i == size_board - 1){
            break;
        }

            for(int size = 0; size < size_board; size++){
                cout << "-----";
            } cout << endl;


    }

}

/* Wyświetlenie sytuacji na planszy max 9x9 */
/* Ograniczenie jest nałożone wyłącznie ze względu na wygodę użytkowania,
    która wynika z tego, że ilość dostępnych znaków ASCII używanych od ozaczania pól
        wynosi 85 */
void Checker_board::print_board(void){


    for(int i = 0; i < size_board; i++){
        for(int j = 0; j < size_board; j++)
            cout << "| " << board[i][j] << " |";
        cout << endl;  

        if(i == size_board - 1){
            break;
        }

            for(int size = 0; size < size_board; size++){
                cout << "-----";
            } cout << endl;


    }cout << endl;

}

void Checker_board::print_board_vis(void){


    for(int i = 0; i < size_board; i++){
        for(int j = 0; j < size_board; j++)
            cout << "| " << board_vis[i][j] << " |";
        cout << endl;  

        if(i == size_board - 1){
            break;
        }

            for(int size = 0; size < size_board; size++){
                cout << "-----";
            } cout << endl;


    }cout << endl;

}


/* Wybór gracza zaczynającego i przydzielenie mu odpowiedniego znaku */
void Checker_board::pick_starting_piece(void){
    srand(time(NULL));

    int mark = rand() % 2 + 1;// losowy wybór koloru gracza

    if(mark == 1){ main_player = player1; AI_player = player2;} // gracz gra 'X'

    if(mark == 2){ main_player = player2; AI_player = player1;} // gracz gra 'O'

}

/* Wykonanie PRAWIDŁOWEGO ruchu */
void Checker_board::move(void){

    char place;
    int place_int;

    cout << "Miejsce ruchu:  " << endl;

    cin >> place;
    
    place_int = (char)place - ascii;
  
    int i = (place_int/size_board);
    int j = (place_int - i*size_board);

    /* Ruch wykracza poza zakres tablicy, miejsce jest już zajęte lub jest sytuacja remisowa */
    if(!allowed_move(place_int, i, j)){
        invalid_p1++;
        if(invalid_p1 <= 2){
            cout << "Niepoprawny ruch  " << invalid_p1 << endl;
            cout << "Miejsce ruchu:  " << endl;
            cin >> place;
        }  
    }

    //if(who_won() == 10) {cout << "wygrałeś" << endl;}

    if(allowed_move(place, i, j)) {board[i][j] = main_player; board_vis[i][j] = main_player; cout << "allowed " << endl;}
}

/* Sprawdzenie czy ruch jest dozwolony */
bool Checker_board::allowed_move(int place, int i, int j){

    if(!is_move_left()) { cout << "REMIS" << endl; return false;} // sytuacja remisowa

    else if(i > (size_board - 1) || j > (size_board - 1) ) return false; // ruch jest w zakresie tablicy

    else if(board_vis[i][j] != 'X' && board_vis[i][j] != 'O') return true; // pole ruchu nie jest zajęte przez inny znak

    return false;
}

/* Sprawdzenie czy nie doszło do remisu */
/* Zwrócona wartość +10 ozanacza zwycięstowo gracza, natomiast -10 komputra */
bool Checker_board::is_move_left(void){
    //if( ( turn < 9 && size_board >= 5 ) || ( size_board <= 4 && turn < ( size_board + size_board - 1 ) ) ) return true; // ilość ruchów jest zbyt mała na możliwość zwycięstwa

    //else{
        for(int i = 0; i < size_board; i++){
            for(int j = 0; j < size_board; j++)
                if(board_vis[i][j] == ' ') return true; // istnieją jeszcze niezajęte pola
        }
        return false;
    //}
}

/* Znaleznienie ewentualnego zwycięzcy */
int Checker_board::who_won(){

    if(size_board == 3){ // wywołana tablica 3x3
            return board_size_3();        
      }
    else if(size_board == 4){ // wywołana tablica 4x4
        {
           return board_size_4();
        
      }
    }

    else if(size_board >= 5){ // wywołana tablica 5x5 lub większa

        /* Sprawdzenie kolumn */
        for(int row = 0; row < size_board; row++){
            for(int col = 0; col < (size_board-4); col++){

                if(board_vis[row][col] == main_player && board_vis[row][col+1] == main_player && board_vis[row][col+2] == main_player && board_vis[row][col+3] == main_player && board_vis[row][col+4] == main_player) return +10;
                else if(board_vis[row][col] == AI_player && board_vis[row][col+1] == AI_player && board_vis[row][col+2] == AI_player && board_vis[row][col+3] == AI_player && board_vis[row][col+4] == AI_player) return -10;
            }
        }

        /* Sprawdzanie wierszy */
        for(int col = 0; col < size_board; col++){
            for(int row = 0; row < (size_board-4); row++){

                if(board_vis[row][col] == main_player && board_vis[row+1][col] == main_player && board_vis[row+2][col] == main_player && board_vis[row+3][col] == main_player && board_vis[row+4][col] == main_player) return +10;
                else if(board_vis[row][col] == main_player && board_vis[row+1][col] == main_player && board_vis[row+2][col] == main_player && board_vis[row+3][col] == main_player && board_vis[row+4][col] == main_player) return -10;
            }
        }

        /* Sprawdzenie przekątnych (z lewej do prawej)*/
        for(int row = 0; row < (size_board - 4); row++){
            for(int col = 0; col < (size_board - 4); col++){

                if(board_vis[row][col] == main_player && board_vis[row+1][col+1] == main_player && board_vis[row+2][col+2] == main_player && board_vis[row+3][col+3] == main_player && board_vis[row+4][col+4] == main_player) return +10;
                else if(board_vis[row][col] == AI_player && board_vis[row+1][col+1] == AI_player && board_vis[row+2][col+2] == AI_player && board_vis[row+3][col+3] == AI_player && board_vis[row+4][col+4] == AI_player) return -10;
            }
        }

        /* Sprawdzenie przekątnych (z prawej do lewej)*/
        for(int row = 0; row < (size_board - 4); row++){
            for(int col = (size_board - 1); col >= 0; col--){

                if(board_vis[row][col] == main_player && board_vis[row+1][col-1] == main_player && board_vis[row+2][col-2] == main_player && board_vis[row+3][col-3] == main_player && board_vis[row+4][col-4] == main_player) return +10;
                else if(board_vis[row][col] == AI_player && board_vis[row+1][col-1] == AI_player && board_vis[row+2][col-2] == AI_player && board_vis[row+3][col-3] == AI_player && board_vis[row+4][col-4] == AI_player) return -10;
            }
        }
    }
    return 0;
}

/* Sprawdzenie zwycięstwa dla tablicy 3x3 */
int Checker_board::board_size_3(){

    /* Sprawdzenie kolumn */
    for (int row = 0; row<3; row++)
    {
        if (board_vis[row][0]==board_vis[row][1] &&
            board_vis[row][1]==board_vis[row][2])
        {
            if (board_vis[row][0]== main_player)
                return +10;
            else if (board_vis[row][0]== AI_player)
                return -10;
        }
    }

    /* Sprawdzenie wierszy */
    for (int col = 0; col<3; col++)
    {
        if (board_vis[0][col]==board_vis[1][col] &&
            board_vis[1][col]==board_vis[2][col])
        {
            if (board_vis[0][col]==main_player){
                return +10;
            }
                
 
            else if (board_vis[0][col]==AI_player)
                return -10;
        }
    }

    /* Sprawdzenie przekątej (z lewej do prawej) */
    if (board_vis[0][0]== board_vis[1][1] && board_vis[1][1]==board_vis[2][2])
    {
        if (board_vis[0][0]==main_player)
            return +10;
        else if (board_vis[0][0]==AI_player)
            return -10;
    }

    /* Sprawdzenie przekątej (z prawej do lewej) */
    if (board_vis[0][2]==board_vis[1][1] && board_vis[1][1]==board_vis[2][0])
    {
        if (board_vis[0][2]==main_player)
            return +10;
        else if (board_vis[0][2]==AI_player)
            return -10;
    }
    return 0;
}

/* Sprawdzenie zwycięstwa dla tablicy 4x4 */
int Checker_board::board_size_4(){

       /* Sprawdzenie kolumn */
        for(int row = 0; row < size_board; row++){
            for(int col = 0; col < (size_board-3); col++){

                if(board_vis[row][col] == main_player && board_vis[row][col+1] == main_player && board_vis[row][col+2] == main_player && board_vis[row][col+3] == main_player) return +10;

                else if(board_vis[row][col] == AI_player && board_vis[row][col+1] == AI_player && board_vis[row][col+2] == AI_player && board_vis[row][col+3] == AI_player) return -10;
            }
        }

        /* Sprawdzanie wierszy */
        for(int col = 0; col < size_board; col++){
            for(int row = 0; row < (size_board-3); row++){

                if(board_vis[row][col] == main_player && board_vis[row+1][col] == main_player && board_vis[row+2][col] == main_player && board_vis[row+3][col] == main_player) return +10;
                else if(board_vis[row][col] == AI_player && board_vis[row+1][col] == AI_player && board_vis[row+2][col] == AI_player && board_vis[row+3][col] == AI_player) return -10;
            }
        }

        /* Sprawdzenie przekątnej (z lewej do prawej)*/
        for(int row = 0; row < (size_board - 3); row++){
            for(int col = 0; col < (size_board - 3); col++){

                if(board_vis[row][col] == main_player && board_vis[row+1][col+1] == main_player && board_vis[row+2][col+2] == main_player && board_vis[row+3][col+3] == main_player) return +10;
                else if(board_vis[row][col] == AI_player && board_vis[row+1][col+1] == AI_player && board_vis[row+2][col+2] == AI_player && board_vis[row+3][col+3] == AI_player) return -10;
            }
        }

        /* Sprawdzenie przekątnej (z prawej do lewej)*/
        for(int row = 0; row < (size_board - 3); row++){
            for(int col = (size_board - 1); col >= 0; col--){

                if(board_vis[row][col] == main_player && board_vis[row+1][col-1] == main_player && board_vis[row+2][col-2] == main_player && board_vis[row+3][col-3] == main_player) return +10;
                else if(board_vis[row][col] == AI_player && board_vis[row+1][col-1] == AI_player && board_vis[row+2][col-2] == AI_player && board_vis[row+3][col-3] == AI_player) return -10;
            }
        }
        return 0;
}

void Checker_board::show_results(void){

    int size = pkt_ai + pkt_player;

    cout << endl << "----------------------------" << endl;
    cout << endl << "      GRACZ|VS|KOMPUTER     " << endl;
    cout << endl << "----------------------------" << endl;
    for(int i = 1; i < size + 1; i++){
        cout << "-----" << tab_winners[i];
        cout << "-----|";
        if(tab_winners[i] == main_player) cout << "G";
        else if(tab_winners[i] == AI_player) cout << "K"; 
        cout << "|-----";
        if(tab_winners[i] == 'X') cout << "O";
        else if(tab_winners[i] == 'O') cout << "X";
        cout << "--------" << endl;
    }

}



/* Znajdz najlepszy możliwy ruch dla AI */
void Checker_board::bestmove(){

    int bestScore = -INFINITY; // początkowo najlepsza wartość ustawiona tak żeby zawsze móc ją zamienić na rzeczywisty ruch
    int col = -1, row = -1;
    int turn_c = turn;

    for(int i = 0; i < size_board; i++){
        for(int j = 0; j < size_board; j++){
            if(board_vis[i][j] == ' '){ // jeżeli miejsce na planszy jest wolne

                board_vis[i][j] = AI_player; // wykonanie ruchu przez AI

                int score = minimax(0, false, turn_c); // wartość ustawiana na najlepszą możliwą przy założeniu że postawiono znak w wybranym polu

                board_vis[i][j] = ' '; // cofnięcie ruchu

                if(score > bestScore){ // jeżeli zwycięstwo następuje szybciej - zapisz ruch
                    row = i; col = j;
                    bestScore = score;
                }
            }
        }
    }
    //cout << bestScore << "- best move" << endl;
     board[row][col] = AI_player; board_vis[row][col] = AI_player; // wykonaj najlepszy ruch

}

int Checker_board::minimax(int depth, bool isMax, int turn_c){
    
    if(size_board >= 4 && size_board < 6 && depth == 4){
        int score = board_state(turn_c);
        return score;
    }

    /*if(size_board >= 6 && depth == 3){
        int score = board_state(turn_c);
        return score;
    }*/

    else{
        int score = who_won(); // wytypowanie ewentualnego zwycięzcy lub remisu

        if(score == -10) {score = 10; return score;} // wygrał komputer

        if(score == 10) {score = -10; return score;} // wygrał gracz

        if(is_move_left() == false) {return score;} // remis
    }

    turn_c++;
    
    if(isMax){ // tura AI

        int best_score = -INFINITY; // podobnie jak w bestmove

         for(int i = 0; i < size_board; i++){
        for(int j = 0; j < size_board; j++){
            if(board_vis[i][j] == ' '){ // jeżeli miejsce na planszy jest wolne

                board_vis[i][j] = AI_player; // wykonanie ruchu przez AI

                int score = minimax(depth + 1, false, turn_c); // wartość ustawiana na najlepszą możliwą przy założeniu że postawiono znak w wybranym polu

                best_score = max(score, best_score); 

                board_vis[i][j] = ' '; // wycofaj ruch
                
                }
            }
        }
        return best_score; // zwróć najlepszy możliwy ruch dla danego przejśćia
    }
    else{
        int best_score = INFINITY;

         for(int i = 0; i < size_board; i++){
        for(int j = 0; j < size_board; j++){
            if(board_vis[i][j] == ' '){

                board_vis[i][j] = main_player; // wykonanie ruchu przez gracza

                int score = minimax(depth + 1, true, turn_c);

                best_score = min(score, best_score);

                board_vis[i][j] = ' ';
                
                }
            }
        }
        return best_score;
    }

}

/* Minmax dla plansz większych lub równych 4. */
/* Sprawdzenie jest tylko dla jednego kroku w przód. Komputer podejmuje decyzje w zależności od tego, ile jest u każdego z graczy 4 i 3.
Nie jest to w żadnym wypadku optymalny system, przez co komputer ma szanse, w przeciwieństwie do 3x3, przegrać. */
int Checker_board::board_state(int turn_c){
    
    if( (size_board == 4 && turn_c >= ( size_board + size_board - 1 ) ) || (size_board > 4 && turn_c >= 9)){
        int score = who_won(); // wytypowanie ewentualnego zwycięzcy lub remisu

        if(score == -10) {score = 11; return score;} // wygrał komputer

        if(score == 10) {score = -11; return score;} // wygrał gracz

        if(is_move_left() == false) {return score;} // remis
    }

    int nr_of_ai_4 = 0;
    int nr_of_ai_3 = 0;

    int nr_of_p_4 = 0;
    int nr_of_p_3 = 0;

/* Kto ma więcej 4 */
    /* Sprawdzenie kolumn */
        for(int row = 0; row < size_board; row++){
            for(int col = 0; col < (size_board-3); col++){

                if(board_vis[row][col] == main_player && board_vis[row][col+1] == main_player && board_vis[row][col+2] == main_player && board_vis[row][col+3] == main_player){
                    nr_of_p_4++;
                    if( ( (col > 0) && board_vis[row][col - 1] != AI_player ) || ( (col < size_board) && board_vis[row][col+4] != AI_player )) {return -10;} 
                } 

                else if(board_vis[row][col] == AI_player && board_vis[row][col+1] == AI_player && board_vis[row][col+2] == AI_player && board_vis[row][col+3] == AI_player)  nr_of_ai_4++;
            }
        }

        /* Sprawdzanie wierszy */
        for(int col = 0; col < size_board; col++){
            for(int row = 0; row < (size_board-3); row++){

                if(board_vis[row][col] == main_player && board_vis[row+1][col] == main_player && board_vis[row+2][col] == main_player && board_vis[row+3][col] == main_player) {
                    nr_of_p_4++;
                    if( ( (row > 0) && board_vis[row-1][col] != AI_player ) || ( (row < size_board) && board_vis[row+4][col] != AI_player )) return -10;
                }
                else if(board_vis[row][col] == main_player && board_vis[row+1][col] == main_player && board_vis[row+2][col] == main_player && board_vis[row+3][col] == main_player) nr_of_ai_4++;
            }
        }

        /* Sprawdzenie przekątnej (z lewej do prawej)*/
        for(int row = 0; row < (size_board - 3); row++){
            for(int col = 0; col < (size_board - 3); col++){

                if(board_vis[row][col] == main_player && board_vis[row+1][col+1] == main_player && board_vis[row+2][col+2] == main_player && board_vis[row+3][col+3] == main_player){
                    nr_of_p_4++;
                    if( ( (row > 0) && (col > 0) && board_vis[row-1][col-1] != AI_player ) || ( (row < size_board) && (col < size_board) && board_vis[row+4][col+4] != AI_player )) return -10;
                } 
                else if(board_vis[row][col] == AI_player && board_vis[row+1][col+1] == AI_player && board_vis[row+2][col+2] == AI_player && board_vis[row+3][col+3] == main_player) nr_of_ai_4++;
            }
        }

        /* Sprawdzenie przekątnej (z prawej do lewej)*/
        for(int row = 0; row < (size_board - 3); row++){
            for(int col = (size_board - 1); col >= 0; col--){

                if(board_vis[row][col] == main_player && board_vis[row+1][col-1] == main_player && board_vis[row+2][col-2] == main_player && board_vis[row+3][col-3] == main_player){
                    nr_of_p_4++;
                    if( ( (row < size_board) && (col > 0) && board_vis[row-1][col-2] != AI_player ) || ( (row < size_board) && (col < 0) && board_vis[row+4][col-4] != AI_player )) return -10;
                } 
                else if(board_vis[row][col] == AI_player && board_vis[row+1][col-1] == AI_player && board_vis[row+2][col-2] == AI_player && board_vis[row+3][col-3] == AI_player) nr_of_ai_4++;

            }
        }
    /* Kto ma więcej 3 */
    /* Sprawdzenie kolumn */
        for(int row = 0; row < size_board; row++){
            for(int col = 0; col < (size_board-2); col++){

                if(board_vis[row][col] == main_player && board_vis[row][col+1] == main_player && board_vis[row][col+2] == main_player)
                    nr_of_p_3++;
                   
                else if(board_vis[row][col] == AI_player && board_vis[row][col+1] == AI_player && board_vis[row][col+2] == AI_player)  nr_of_ai_3++;
            }
        }

        /* Sprawdzanie wierszy */
        for(int col = 0; col < size_board; col++){
            for(int row = 0; row < (size_board-2); row++){

                if(board_vis[row][col] == main_player && board_vis[row+1][col] == main_player && board_vis[row+2][col] == main_player)
                    nr_of_p_3++;

                else if(board_vis[row][col] == main_player && board_vis[row+1][col] == main_player && board_vis[row+2][col] == main_player) nr_of_ai_3++;
            }
        }

        /* Sprawdzenie przekątnej (z lewej do prawej)*/
        for(int row = 0; row < (size_board - 2); row++){
            for(int col = 0; col < (size_board - 2); col++){

                if(board_vis[row][col] == main_player && board_vis[row+1][col+1] == main_player && board_vis[row+2][col+2] == main_player)
                    nr_of_p_3++;

                else if(board_vis[row][col] == AI_player && board_vis[row+1][col+1] == AI_player && board_vis[row+2][col+2] == AI_player) nr_of_ai_3++;
            }
        }

        /* Sprawdzenie przekątnej (z prawej do lewej)*/
        for(int row = 0; row < (size_board - 2); row++){
            for(int col = (size_board - 1); col >= 0; col--){

                if(board_vis[row][col] == main_player && board_vis[row+1][col-1] == main_player && board_vis[row+2][col-2] == main_player)
                    nr_of_p_3++;
 
                else if(board_vis[row][col] == AI_player && board_vis[row+1][col-1] == AI_player && board_vis[row+2][col-2] == AI_player) nr_of_ai_3++;
            }
        }
    
    if(nr_of_ai_4 > nr_of_p_4) return 10;

    if(nr_of_p_4 > nr_of_ai_4) return -10;

    if(nr_of_ai_4 == nr_of_p_4 && nr_of_ai_3 > nr_of_p_3) return 8; // Mają po tyle samo 4, ale AI ma więcej 3
    
    if(nr_of_ai_4 == nr_of_p_4 && nr_of_ai_3 < nr_of_p_3)  return -8; // Mają po tyle samo 4, ale Gracz ma więcej 3
    
    if(nr_of_ai_4 != 0 && nr_of_ai_3 != 0 && nr_of_ai_4 == nr_of_p_4 && nr_of_ai_3 == nr_of_p_3) return -10;
    
    else return 0;
}
