#include <iostream>
#include <curses.h>
#include <unistd.h>


using namespace std;


class Player {

    public:
    int _score = 0;
};

class Ball {

    public:
    int _dx;
    int _dy;
    int _posx;
    int _posy;
    Ball(int t_dx, int t_dy, int t_posx, int t_posy) 
    : _dx(t_dx), _dy(t_dy),_posx(t_posx),_posy(t_posy)
    {
    }
    void updateBall(){
        if(_dx == 1 && _dy == 1){
            _posx++;
            _posy++;
        }
        else if(_dx == 1 && _dy == -1){
            _posx++;
            _posy--;
        }
        else if(_dx == -1 && _dy == 1){
            _posx--;
            _posy++;
        }
        else if(_dx == -1 && _dy == -1){
            _posx--;
            _posy--;
        }
    }

    void drawBall(){
        mvaddch(_posy, _posx, ACS_DIAMOND);
    }

};

class Paddle {

    public:
    int _posx;
    int _posy;
    int _height;
    Paddle(int t_posx, int t_posy, int t_height)
    : _posx(t_posx), _posy(t_posy), _height(t_height)
    {    
    }

    void drawPaddle(){
        for(int size = 0; size < _height; size++){
            mvaddch(_posy+size, _posx, ACS_VLINE);
        }
    }
};

class Board {
    // Columns and Rows
    int COLUMNS = 60;
    int LINES = 12;

    public:
    // Y = Rows, X = Columns
    // mvwaddch(win, y, x, ch)
    Board()
    {
    }

    void DrawBoard(){
        for(int y = 0; y < LINES; y++){
            for(int x = 0; x < COLUMNS; x++){
                if (x == COLUMNS-1) {
                    mvaddch(y, x, ACS_CKBOARD);
                }
                else if (y == 0 || x == 0){
                    mvaddch(y, x, ACS_CKBOARD);
                }
                else if (y == LINES-1) {
                    mvaddch(y, x, ACS_CKBOARD);
                }
                else {
                    mvaddch(y, x, ' ');
                }
            }
        }
    }



};

class Game {

    // Remember Columns = X/ Lines/Rows = Y
    const int boardWidth = 60;
    const int boardHeight = 12;
    Ball ball = Ball(-1,1,(boardWidth/2+5),(boardHeight/2-2));
    Paddle paddle1 = Paddle{4,(boardHeight/2),3};
    Paddle paddle2 = Paddle{(boardWidth-4), (boardHeight/2),3};
    Player player1, player2;
    Board board; 

    public:

    Game(){

    }



    void checkWallCollision(Ball &ball, Player &player1, Player &player2){
        if(ball._posy > boardHeight-3){
            ball._dy = -1;
            printw("one");
        }
        else if(ball._posy < 0+2){
            ball._dy = 1;
            printw("two");
        }
        else if(ball._posx > boardWidth-3){
            ball._dx = -1;
            printw("three");
            player1._score++;
            ball._posx = boardWidth/2+3;
            ball._posy = boardHeight/2;
            usleep(100000);
        }
        else if(ball._posx < 0+2){
            ball._dx = 1;
            printw("four");
            player2._score++;
            ball._posx = boardWidth/2-2;
            ball._posy = boardHeight/2;
            usleep(100000);
        }
    }



    void checkPaddleCollision(Ball &ball, Paddle &paddle1, Paddle &paddle2){
        if(ball._posx < paddle1._posx+2 && ball._posy > paddle1._posy && ball._posy < paddle1._posy+paddle1._height){
            ball._dx = 1;
            printw("paddleL");

        }
        else if(ball._posx > paddle2._posx-2 && ball._posy > paddle2._posy && ball._posy < paddle2._posy+paddle2._height){
            ball._dx = -1;
            printw("paddleR");
        }
    }

    void PlayGame(){
        for(int i=0;i < 5000000;i++){
        usleep(100000);
        erase();
        board.DrawBoard();
        paddle1.drawPaddle();
        paddle2.drawPaddle();
        checkPaddleCollision(ball, paddle1, paddle2);
        checkWallCollision(ball, player1, player2);
        ball.updateBall();
        ball.drawBall();
        mvprintw(15,0,"Player 1 score is %d",player1._score);
        mvprintw(15,40,"Player 2 score is %d",player2._score);
        refresh();
        }
    }
    
};



int main()
{

    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    erase();
    Game game;
    game.PlayGame();
    //endwin();

    return 0;
}




