#ifndef GAME_H
#define GAME_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include "text.h"
#include "ball.h"
#include "player.h"


class Game: public QGraphicsView
{
public:
    Game(QWidget * parent=0);
    void start();
    void gameOver();
    void newBall();
    QGraphicsScene * scene;
    QGraphicsScene * menu;
    QGraphicsScene * gameOverScreen;
    Text * wynikValue;
    Text * livesDisplay;
    Text * hiscoreValue;
    Player * gracz;
    Ball * pilka;
    int score=0;
    int hiscore=0;
    int lives=3;
};

#endif // GAME_H
