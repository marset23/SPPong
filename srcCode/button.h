#ifndef BUTTON_H
#define BUTTON_H
#include <QGraphicsPixmapItem>
#include "game.h"

class Button:public QGraphicsPixmapItem
{
public:
    Button(int value=0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    int type=0;
};

#endif // BUTTON_H
