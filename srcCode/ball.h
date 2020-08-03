#ifndef BALL_H
#define BALL_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

class Ball:public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
        Ball();
        QTimer * timer = new QTimer();
        float original=1.5;
        float ydir=original;
        float xdir=-original;
        void deleteBall();
public slots:
        void move();
};

#endif // BALL_H
