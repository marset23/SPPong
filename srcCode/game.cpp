#include <fstream>
#include "game.h"
#include "player.h"
#include "ball.h"
#include "text.h"
#include "button.h"


Game::Game(QWidget *parent)
{
    srand(time(NULL));

    //Ustawienie okna rozgrywki
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,600);

    //Stworzenie sceny będącej menu głównym gry
    menu = new QGraphicsScene();
    menu->setSceneRect(0,0,800,600);
    menu->setBackgroundBrush(QBrush(Qt::black));

    //Stworzenie sceny będącej ekranem końca gry
    gameOverScreen = new QGraphicsScene();
    gameOverScreen->setSceneRect(0,0,800,600);
    gameOverScreen->setBackgroundBrush(QBrush(Qt::black));

    //Dodanie do ekranu końca gry, guzik powrotu do menu głównego
    Button * returnButton = new Button(2);
    returnButton->setPos(275,470);
    gameOverScreen->addItem(returnButton);

    //W przypadku istniejącego pliku z najelpszym winikiem, wynik wczytywany jest do zmiennej
    std::fstream plik;
    plik.open("wyniki.bin",std::ios::in|std::ios::binary);
    if(plik.is_open()){
        plik.read((char *) &hiscore, sizeof hiscore);
        plik.close();
    }

    //Utworzenie etykiet
    Text * hiscoreLabel=new Text("Hiscore: ");
    gameOverScreen->addItem(hiscoreLabel);

    Text * currentScoreLabel=new Text("Uzyskany wnik: ");
    currentScoreLabel->setX(200);
    gameOverScreen->addItem(currentScoreLabel);

    //Wyświetlanie na ekranie końca gry, wartości najelpszego wyniku
    hiscoreValue = new Text(hiscore);
    hiscoreValue->setX(55);
    gameOverScreen->addItem(hiscoreValue);

    //Dodanie do sceny menu głównego guzików rozpoczęcia nowej gry oraz wyjścia z gry
    Button * startButton = new Button();
    startButton->setPos(275,400);
    menu->addItem(startButton);

    Button * exitButton = new Button(1);
    exitButton->setPos(275,470);
    menu->addItem(exitButton);

    //Ustawienie sceny początkowej i otworzenie okna gry
    setScene(menu);
    show();
}

void Game::start(){
    //Utworzenie i ustawienie sceny rozgrywki
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600);
    scene->setBackgroundBrush(QBrush(Qt::black));
    setScene(scene);

    //Utworzenie paletki oraz nadanie jej możliwości przechwytywania danych z klawiatury
    gracz=new Player();
    scene->addItem(gracz);
    gracz->setFlag(QGraphicsItem::ItemIsFocusable);
    gracz->setFocus();

    //Dodanie do sceny piłki
    newBall();

    //Dodanie do sceny informacji o bierzącym wyniku i ilości pozostałych żyć
    Text * wynikLabel=new Text("Wynik: ");
    scene->addItem(wynikLabel);
    wynikValue=new Text(score);
    wynikValue->setX(50);
    scene->addItem(wynikValue);
    wynikLabel=new Text("Życia: ");
    wynikLabel->setX(725);
    scene->addItem(wynikLabel);
    livesDisplay=new Text(lives);
    livesDisplay->setX(775);
    scene->addItem(livesDisplay);
}

//Funkcja tworząca nową piłkę i dodająca ją do sceny rozgrywki
void Game::newBall(){
    pilka=new Ball();
    scene->addItem(pilka);
}

//Funkcj końca gry zerująca parametry rozgrywki oraz porównująca uzyskany wynik z najlepszym wynikiem i w razie potrzeby, zapisanie nowego najlepszego wyniku do pliku
void Game::gameOver(){
    std::fstream plik;
    if(score>hiscore){
        hiscore=score;
        plik.open("wyniki.bin",std::ios::out|std::ios::binary);
        if(plik.is_open()){
            plik.write((const char *) &score, sizeof score);
            plik.close();
        }
        hiscoreValue->textUpdate(hiscore);
    }
    //Dodanie do ekranu końca gry wartości uzyskanego wyniku
    wynikValue->setX(300);
    gameOverScreen->addItem(wynikValue);
    //Wyświetlenie sceny końca gry
    setScene(gameOverScreen);
    score=0;
    lives=3;
}
