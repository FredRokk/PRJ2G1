#include "idle.h"
#include "mapselect.h"
#include "practice.h"
#include "versus.h"
#include <QApplication>
#include <QListWidget>
#include <QLabel>
#include <QTimer>
#include <QLCDNumber>
#include <unistd.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    idle wIdle1;
    idle wIdle2;
    idle wIdle3;
    mapSelect wMapSelect;
    practice wPractice;
    versus wVersus;


    wIdle1.centralWidget()->findChild<QLabel*>("nameLabel")->setText("Tipping Templars");
    wIdle2.centralWidget()->findChild<QLabel*>("nameLabel")->setText("Breakwater Brigade");
    wIdle3.centralWidget()->findChild<QLabel*>("nameLabel")->setText("Randomized Map");

    wIdle1.centralWidget()->findChild<QListWidget*>("allTimeList")->addItem("CAT      999");
    wIdle2.centralWidget()->findChild<QListWidget*>("allTimeList")->addItem("CAT      999");
    wIdle3.centralWidget()->findChild<QListWidget*>("allTimeList")->addItem("CAT      999");

    wMapSelect.centralWidget()->findChild<QLabel*>("map1")->setFrameStyle(QFrame::NoFrame | QFrame::Plain);
    wMapSelect.centralWidget()->findChild<QLabel*>("map2")->setFrameStyle(QFrame::WinPanel | QFrame::Plain);

    wVersus.centralWidget()->findChild<QLCDNumber*>("player1Score")->display("000");
    wVersus.centralWidget()->findChild<QLCDNumber*>("player2Score")->display("000");
    wVersus.centralWidget()->findChild<QLCDNumber*>("player1Shots")->display("4");
    wVersus.centralWidget()->findChild<QLCDNumber*>("player2Shots")->display("4");

    wIdle1.show();
    wMapSelect.show();
    wPractice.show();
    wVersus.show();

    QTimer::singleShot(3000, [&](){wPractice.centralWidget()->findChild<QLabel*>("missLabel")->hide();});
    QTimer::singleShot(2000, [&](){wIdle2.show(); wIdle1.hide();});
    QTimer::singleShot(4000, [&](){wIdle3.show(); wIdle2.hide();});
    QTimer::singleShot(6000, [&](){wIdle1.show(); wIdle3.hide();});

    return a.exec();
}
