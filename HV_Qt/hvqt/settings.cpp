#include "settings.h"
#include<QLabel>
#include<QSlider>
#include<QPushButton>
#include<QHBoxLayout>
#include<QLineEdit>
#include<QMessageBox>
#include<exception>

Settings::Settings(bool start):start(start)
{
    setup();
}

void Settings::setup(){
    lblN=new QLabel(tr("Number of discs:"));
    lblTime=new QLabel(tr("Time per one move[ms]: "));
    editTime=new QLineEdit;
    lblTime->setBuddy(editTime);
    lblNvalue=new QLabel;
    sliderN=new QSlider;
    sliderN->setRange(1,19);
    lblNvalue->setText(QString::number(sliderN->value()));
    N=unsigned(sliderN->value());
    btnOk=new QPushButton(tr("&Ok"));
    btnCancel=new QPushButton(tr("&Cancel"));

    lTime=new QHBoxLayout;
    lN=new QHBoxLayout;
    lButtons=new QHBoxLayout;
    lMain=new QVBoxLayout;

    lTime->addWidget(lblTime);
    lTime->addWidget(editTime);
    lN->addWidget(lblN);
    lN->addWidget(lblNvalue);
    lN->addWidget(sliderN);
    lButtons->addWidget(btnOk);
    lButtons->addWidget(btnCancel);
    lMain->addLayout(lTime);
    lMain->addLayout(lN);
    lMain->addLayout(lButtons);
    if(start)btnCancel->setEnabled(false);
    btnOk->setEnabled(false);
    editTime->setText(QString::number(time));
    sliderN->setValue(int(N));
    connect(sliderN,SIGNAL(valueChanged(int)),this,SLOT(slider()));
    connect(btnOk,SIGNAL(clicked()),this,SLOT(accept()));
    connect(btnCancel,SIGNAL(clicked()),this,SLOT(close()));
    connect(editTime,SIGNAL(editingFinished()),this,SLOT(edit()));
    this->setLayout(lMain);
    this->setWindowTitle(tr("Settings"));
}

void Settings::slider(){
    N=unsigned(sliderN->value());
    lblNvalue->setText(QString::number(N));
}
void Settings::edit(){
    try {
        time=editTime->text().toUInt();
    } catch (std::exception &e){
        QMessageBox::critical(this,tr("Critical failure"),e.what(),QMessageBox::Close);

    }
    if(time>0&&time<60000){
        btnOk->setEnabled(true);
    }else{
        if(QMessageBox::warning(this,tr("Wrong value!"),tr("You can enter time greater then zero and less then a minute."),QMessageBox::Ok)!=QMessageBox::Ok)close();
        btnOk->setEnabled(false);
        editTime->setText("10");
    }
}



