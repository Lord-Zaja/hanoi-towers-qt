#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
class QLabel;
#include<QSlider>
class QPushButton;
class QHBoxLayout;
class QVBoxLayout;
#include<QLineEdit>
class Settings : public QDialog
{
    Q_OBJECT
    bool start;
    unsigned int N=1;
    unsigned int time=10;
    QLineEdit *editTime;
    QLabel *lblN;
    QLabel *lblNvalue;
    QLabel *lblTime;
    QSlider *sliderN;
    QPushButton *btnOk;
    QPushButton *btnCancel;
    QHBoxLayout *lTime;
    QHBoxLayout *lN;
    QHBoxLayout *lButtons;
    QVBoxLayout *lMain;
    void setup();
public:
    Settings(bool start=false);
    unsigned int getN()const{return N;}
    unsigned int getTime()const{return time;}
    void setN(unsigned int n){N=n;sliderN->setValue(int(N));}
    void setTime(unsigned int t){time=t;editTime->setText(QString::number(time));}
private slots:
    void slider();
    void edit();
};

#endif // SETTINGS_H
