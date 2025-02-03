#ifndef MYTRAINER_H
#define MYTRAINER_H

#include "config.h"

#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTime>
#include <QTimer>
#include <QSoundEffect>
#include <QUrl>

class MyTrainer : public QWidget
{
    Q_OBJECT



public:
    MyTrainer(QWidget *parent = nullptr);
    ~MyTrainer();

private:


    struct StatusWidget {
        int secTimer;
        int shortSecTimer;
        int nowNumberElement;

        enum longWorkStatus{
            itWork,
            itRest,
        } longWorkStatus_e;

        enum shortWorkStatus{
            itPress,
            itUnPress,
        } shortWorkStatus_e;

        enum pauseStatus{
            itNotPaused,
            itPaused,
        }pauseStatus_e;

    } myTrainerStatus;

    QSoundEffect startPressSound;
    QSoundEffect stopPressSound;

    QPushButton *startBtn;
    QPushButton *pauseBtn;
    QPushButton *stopBtn;

    QHBoxLayout *hbox;
    QVBoxLayout *vbox;

    QLabel *warnLbl;
    QLabel *verticalLabel[2*WORKCYCLES - 1];

    QTimer *secTmr;

    QTime workTime;

    QTime intToQTime(int );

    void labelsStartInit();

private slots:
    void on_startBtnClicked();
    void on_stopBtnClicked();
    void on_pauseBtnClicked();
    void bigTimerIsOut();
    void showTimeScore();

};
#endif // MYTRAINER_H
