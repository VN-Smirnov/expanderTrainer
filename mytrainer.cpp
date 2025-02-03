#include "mytrainer.h"

MyTrainer::MyTrainer(QWidget *parent)
    : QWidget(parent)
{

    //startPressSound.setSource(QUrl::fromLocalFile("C:\\Users\\bobby\\projects\\Qt\\expanderTrainer\\media\\pressUp.wav"));
    //stopPressSound.setSource(QUrl::fromLocalFile("C:\\Users\\bobby\\projects\\Qt\\expanderTrainer\\media\\pressDown.wav"));



    startPressSound.setSource(QUrl::fromLocalFile("media\\pressUp.wav"));
    stopPressSound.setSource(QUrl::fromLocalFile("media\\pressDown.wav"));


    secTmr = new QTimer(this);

    startBtn = new QPushButton("Старт");
    pauseBtn = new QPushButton("На паузу");
    stopBtn = new QPushButton("Стоп");

    pauseBtn->setEnabled(false);
    stopBtn->setEnabled(false);

    hbox = new QHBoxLayout();
    hbox->addWidget(startBtn);
    hbox->addWidget(pauseBtn);
    hbox->addWidget(stopBtn);

    vbox = new QVBoxLayout();
    vbox->addLayout(hbox);

    /*Start Labels init*/
    verticalLabel[0] = new QLabel("");
    vbox->addWidget(verticalLabel[0]);

    for(int i=1; i < 2*WORKCYCLES-1; i++){
        if(i%2){
            verticalLabel[i] = new QLabel("");
        } else {
            verticalLabel[i] = new QLabel("");
        }
        vbox->addWidget(verticalLabel[i]);
    }

    labelsStartInit();
    /*End Labels init*/

    setLayout(vbox);

    connect(startBtn, SIGNAL(clicked()),
            this, SLOT(on_startBtnClicked())
            );

    connect(pauseBtn, SIGNAL(clicked()),
            this, SLOT(on_pauseBtnClicked())
            );

    connect(stopBtn, SIGNAL(clicked()),
            this, SLOT(on_stopBtnClicked())
            );

    connect(secTmr, SIGNAL(timeout()),
            this, SLOT(showTimeScore())
            );

}

void MyTrainer::on_startBtnClicked(){
    startBtn->setEnabled(false);
    pauseBtn->setEnabled(true);
    stopBtn->setEnabled(true);

    labelsStartInit();

    secTmr->start(SECDELAY);

    myTrainerStatus.longWorkStatus_e = StatusWidget::itWork;
    myTrainerStatus.shortWorkStatus_e = StatusWidget::itPress;
    myTrainerStatus.pauseStatus_e = StatusWidget::itNotPaused;
    myTrainerStatus.secTimer = WORKDELAY/1000;
    myTrainerStatus.nowNumberElement=0;
    myTrainerStatus.shortSecTimer = PRESSDELAY/1000;

    verticalLabel[myTrainerStatus.nowNumberElement]->setStyleSheet("background-color: green");

    startPressSound.play();

}

void MyTrainer::on_pauseBtnClicked(){
    startBtn->setEnabled(false);
    pauseBtn->setEnabled(true);
    stopBtn->setEnabled(true);

    if(myTrainerStatus.pauseStatus_e == StatusWidget::itPaused){
        pauseBtn->setText("На паузу");
        myTrainerStatus.pauseStatus_e = StatusWidget::itNotPaused;
        secTmr->start(SECDELAY);
    } else if(myTrainerStatus.pauseStatus_e == StatusWidget::itNotPaused) {
        pauseBtn->setText("Продолжить");
        secTmr->stop();
        myTrainerStatus.pauseStatus_e = StatusWidget::itPaused;
    }
}

void MyTrainer::on_stopBtnClicked(){
    startBtn->setEnabled(true);
    pauseBtn->setEnabled(false);
    stopBtn->setEnabled(false);

    secTmr->stop();

    myTrainerStatus.longWorkStatus_e = StatusWidget::itRest;
    myTrainerStatus.secTimer=WORKDELAY/1000;
    myTrainerStatus.nowNumberElement=0;

    labelsStartInit();
    pauseBtn->setText("На паузу");

}

void MyTrainer::bigTimerIsOut() {

    verticalLabel[myTrainerStatus.nowNumberElement]->setStyleSheet("background-color: green");
    verticalLabel[myTrainerStatus.nowNumberElement]->setText("<b>Done!</b>");
    stopPressSound.play();

    myTrainerStatus.shortWorkStatus_e = StatusWidget::itPress;
    myTrainerStatus.shortSecTimer = PRESSDELAY/1000;

    if(myTrainerStatus.longWorkStatus_e == StatusWidget::itWork){
        myTrainerStatus.longWorkStatus_e = StatusWidget::itRest;
        myTrainerStatus.secTimer=PAUSEDELAY/1000;
    } else if(myTrainerStatus.longWorkStatus_e == StatusWidget::itRest){
        myTrainerStatus.longWorkStatus_e = StatusWidget::itWork;
        myTrainerStatus.secTimer=WORKDELAY/1000;
    }

    if(myTrainerStatus.nowNumberElement > 2*WORKCYCLES-3){
        stopBtn->click();
    } else {
        myTrainerStatus.nowNumberElement++;
        if(myTrainerStatus.longWorkStatus_e == StatusWidget::itWork) {
            verticalLabel[myTrainerStatus.nowNumberElement]->setStyleSheet("background-color: green");
        }
    }
}

void MyTrainer::showTimeScore(){
    verticalLabel[myTrainerStatus.nowNumberElement]->setText(intToQTime(myTrainerStatus.secTimer).toString("mm:ss"));

    if(intToQTime(myTrainerStatus.secTimer) == QTime(0,0,0)){
        MyTrainer::bigTimerIsOut();
    } else {
        myTrainerStatus.secTimer--;
        myTrainerStatus.shortSecTimer--;
    }

    if((myTrainerStatus.longWorkStatus_e == StatusWidget::itWork) & (myTrainerStatus.shortSecTimer == 0)){
        if(myTrainerStatus.shortWorkStatus_e == StatusWidget::itPress) {
            myTrainerStatus.shortSecTimer = UNPRESSDELAY/1000;
            myTrainerStatus.shortWorkStatus_e = StatusWidget::itUnPress;
            verticalLabel[myTrainerStatus.nowNumberElement]->setStyleSheet("background-color: blue");
            stopPressSound.play();
        }
        else if (myTrainerStatus.shortWorkStatus_e == StatusWidget::itUnPress){
            myTrainerStatus.shortSecTimer = PRESSDELAY/1000;
            myTrainerStatus.shortWorkStatus_e = StatusWidget::itPress;
            verticalLabel[myTrainerStatus.nowNumberElement]->setStyleSheet("background-color: green");
            startPressSound.play();
        }
    }

}

QTime MyTrainer::intToQTime(int sec) {
    int QTimeSec  = sec % 60;
    int QTimeMin  = (sec % 3600) / 60 ;

    return QTime(0, QTimeMin, QTimeSec, 0);
}

void MyTrainer::labelsStartInit(){
    verticalLabel[0]->setText("Разминка: на очереди");
    verticalLabel[0]->setStyleSheet("");

    for(int i=1; i < 2*WORKCYCLES-1; i++){
        if(i%2){
            verticalLabel[i]->setText("Отдых:       на очереди");
        } else {
            verticalLabel[i]->setText("Жим:          на очереди");
        }
        verticalLabel[i]->setStyleSheet("");
    }
}

MyTrainer::~MyTrainer() {}
