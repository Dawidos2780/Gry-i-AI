#ifndef BOARD_HH
#define BOARD_HH

#include <iostream>
#include <stdlib.h>
#include <time.h>


class Checker_board{ 
    public:
        int size_board = 0;

        char board[100][100];
        char board_vis[100][100];
        
        char tab_winners[30];

        char main_player;
        char AI_player;

        int turn = 0;
        int invalid_p1 = 0;
        int pkt_player = 0, pkt_ai = 0;
        
        Checker_board(void);

        void print_rules();

        void init_board();
        void first_board();
        void print_board();

        void pick_starting_piece();

        bool is_move_left();
        int who_won();
        int board_size_3();
        int board_size_4();

        void move();
        bool allowed_move(int place, int i, int j);

        int find_in_array(int place);

        void show_results();

        void bestmove();
        int minimax(int depth, bool isMax, int turn_c);
        int board_state(int turn_c);

        void print_board_vis();

    private:
    char player1 = 'X';
    char player2 = 'O';

};


#endif