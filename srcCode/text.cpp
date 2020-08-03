#include "text.h"

Text::Text(QString wiadomosc)
{
    setPlainText(wiadomosc);
    setDefaultTextColor(QColor(Qt::red));
}

Text::Text(int wynik){
    setPlainText(QString::number(wynik));
    setDefaultTextColor(QColor(Qt::green));
}

void Text::textUpdate(int wynik){
    setPlainText(QString::number(wynik));
}
