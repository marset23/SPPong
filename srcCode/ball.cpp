#include "ball.h"
#include "game.h"
#include "player.h"

extern Game * game;

Ball::Ball()
{
    //Nadanie obietkowi Ball obrazka i ustawienie pozycji początkowej
    setPixmap(QPixmap(":/images/ball2.png"));
    setPos(400,(rand()%569)+1);

    //Obliczanie prędkości nowej piłki na podstawie uzyskanych punktów
    if(game->score>0){
        ydir+=original*game->score*0.01;
        xdir-=original*game->score*0.01;
    }
    //Nadanie piłce przypadkowego zwrotu w pionie
    int zwrot=rand()%2;
    if(zwrot){
        ydir*=-1;
    }

    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(5);
}

void Ball::move(){
setPos(x()+xdir,y()+ydir);
//Wykrywanie kolizji pomiędzy obiektem Player a obiektem Ball
QList<QGraphicsItem *> collidingitems = collidingItems();
    for(int i = 0, n = collidingitems.size(); i<n;i++){
        if(typeid(*(collidingitems[i])) == typeid(Player)){
            //Kolizje z górą lub dołem obiektu Player
            if((y()+27<=game->gracz->y()||y()>=game->gracz->y()+97)&&x()<game->gracz->x()+29){
                ydir*=-1;
                ydir-=game->gracz->speed*game->gracz->flag;
                setPos(x(),y()-game->gracz->flag);
                //Niszczenie obiektu Ball gdy zostanie zgnieciony pomiędzy obiektem Player a brzegiem ekranu
                if(y()<=3||y()>=567){
                    setX(-1);
                }
            }
            else{
                xdir*=-1;
            }
            //W przypadku uderzenia piłki poruszającą się paletką, piłka przyśpiesza lub zwalnia w górę lub w dół
            if(game->gracz->flag){
                ydir-=original*game->gracz->flag*0.3;
            }
        }
    }
    //Jeśli piłka uderza o górną lub dolną krawędź ekranu, zostaje odbita
    if(y()<=0||y()>570){
        ydir=-ydir;
    }
    //Jeśli piłka uderza w prawą ścianę, zostaje odbita oraz przyśpiesza, przyznając przy tym punkt
    if(x()>=770&&xdir>0){
        xdir*=-1;
        xdir-=0.01*original;
        if(ydir>0){
            ydir+=0.01*original;
        }
        else if(ydir<0){
            ydir-=0.01*original;
        }
        game->score++;
        game->wynikValue->textUpdate(game->score);
    }
    //Jeśli piłka zetknie się z lewą krawędzią ekranu, zostaje usunięta
    if(x()<0){
        deleteBall();
    }
}

//Usunięcie piłki powoduje utratę życia, a w przypadku stracenia wszystkich żyć, przenosi gracza do ekranu końca gry

void Ball::deleteBall(){
    game->lives-=1;
    game->livesDisplay->textUpdate(game->lives);
    if(game->lives<=0){
        delete this;
        game->gameOver();
    }
    else{
        game->newBall();
        delete this;
    }
}
