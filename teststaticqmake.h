#ifndef TESTSTATICQMAKE_H
#define TESTSTATICQMAKE_H

#include <QWidget>

class TestStaticQmake : public QWidget
{
    Q_OBJECT

public:
    TestStaticQmake(QWidget *parent = nullptr);
    ~TestStaticQmake();
};
#endif // TESTSTATICQMAKE_H
