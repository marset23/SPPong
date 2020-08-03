#ifndef TEXT_H
#define TEXT_H
#include <QGraphicsTextItem>


class Text:public QGraphicsTextItem
{
public:
    Text(QString wiadomosc);
    Text(int wynik);
    void textUpdate(int wynik);
};

#endif // TEXT_H
