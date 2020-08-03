#include "player.h"
#include <QKeyEvent>
#include <QGraphicsView>

Player::Player()
{
    //Ustawienie kształtu i pozycji paletki
    setRect(0,0,30,100);
    setPos(0,250);
    setBrush(QBrush(Qt::white));
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(5);
}

//Zczytywanie wciśnięcia przycisku
void Player::keyPressEvent(QKeyEvent *event){
    if(event->isAutoRepeat()==false){
        if(event->key()==Qt::Key_W){
            flag=1;
        }
        if(event->key()==Qt::Key_S){
            flag=-1;
        }


    }
}

//Zczytywanie puszczenia przycisku
void Player::keyReleaseEvent(QKeyEvent * event){
    if(event->isAutoRepeat()==false){
        if((event->key()==Qt::Key_W)&&(flag==1)){
            flag=0;
        }
        if((event->key()==Qt::Key_S)&&(flag==-1)){
            flag=0;
        }
    }
}

//Gdy przycisk jest wciśnięty, a paletka znajduje się pomiędzy krawędziam ekranu, paletka porusza się
void Player::move(){
    if((flag==1&&y()>0)||(flag==-1&&y()<500)){
        setPos(x(),y()-speed*flag);
    }
}
