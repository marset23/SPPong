#include <QApplication>
#include "button.h"

extern Game * game;

Button::Button(int value)
{
    //Zależnie od rodzaju przycisku, nadawany jest mu obrazek
    switch (value){
    case 0:
        setPixmap(QPixmap(":/images/newGame.png"));
        break;
    case 1:
        setPixmap(QPixmap(":/images/quitGame.png"));
        break;
    case 2:
        setPixmap(QPixmap(":/images/return.png"));
        break;
    }
type=value;
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event){
    switch (type){
    case 0:
        //Rozpoczęcie nowej gry
        game->start();
        break;
    case 1:
        //Wyłączenie gry
        qApp->quit();
        break;
    case 2:
        //Powrót do menu głównego
        game->setScene(game->menu);
        game->gameOverScreen->removeItem(game->wynikValue);
        break;
    }
}
