#ifndef PLAYER_H
#define PLAYER_H
#include <QObject>
#include <QGraphicsRectItem>
#include <QTimer>

class Player:public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
        Player();
        void keyPressEvent(QKeyEvent * event);
        void keyReleaseEvent(QKeyEvent * event);
        QTimer * timer = new QTimer();
        int flag = 0;
        float speed=1.5;
public slots:
        void move();
};

#endif // PLAYER_H
