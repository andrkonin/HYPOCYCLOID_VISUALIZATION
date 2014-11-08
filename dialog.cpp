#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::Dialog)
{
    ui->setupUi(this);

    QFont font1("Times", 12, QFont::Normal);
    QFont font("Times", 10, QFont::Normal);

    lm=new QLabel("<u>Matrix:</u>");
    m1=new QLineEdit("1");
    m2=new QLineEdit("0");
    m3=new QLineEdit("0");
    m4=new QLineEdit("1");
    M=new QLineEdit("5");
    R=new QLineEdit("0.25");
    mm=new QLabel("m = ");
    rr=new QLabel("R = ");
    speed=new QLabel("Speed:");
    voptions=new QLabel("<u>Picture options:</u>");
    viewoptions=new QLabel("<u>View options:</u>");
    zoomlabel=new QLabel("<u>Scaling:</u>");
    zoomlabel->setFont(font1);
    lm->setFont(font1);
    mm->setFont(font1);
    rr->setFont(font1);
    speed->setFont(font1);
    voptions->setFont(font1);
    viewoptions->setFont(font1);
    //QDoubleValidator *b=new QDoubleValidator(0,9999,begin);
    //QIntValidator *e=new QIntValidator(1,10000,end);

    //begin->setValidator(b);
    //end->setValidator(e);

    QLabel *space=new QLabel(" ");

    //mm1=new QLabel("mm");
    //mm2=new QLabel("mm");
    //mm1->setFont(font1);
    //mm2->setFont(font1);

   // lbegin=new QLabel("From:");
   // lend=new QLabel("To:");

    //lbegin->setFont(font);
    //lend->setFont(font);


    backDef=new QPushButton("Default view");
    pmdstop=new QPushButton("Stop");
    goButton=new QPushButton("Go!");
    delaxis=new QPushButton("Delete axis");
    delmcircle=new QPushButton("Delete moving circle");
    delscircle=new QPushButton("Delete static circle");
    aboutbutton=new QPushButton("About");
    zoombutton=new QPushButton("Fit to screen");
    zoombutton->setFont(font1);
    aboutbutton->setFont(font1);
    backDef->setFont(font1);
    pmdstop->setFont(font1);
    goButton->setFont(font1);
    delaxis->setFont(font1);
    delmcircle->setFont(font1);
    delscircle->setFont(font1);
    delaxis->setFont(font);
    delmcircle->setFont(font);
    delscircle->setFont(font);
    zoombutton->setFixedHeight(25);
    zoombutton->setFixedWidth(120);
    delmcircle->setFixedWidth(120);
    backDef->setFixedWidth(120);
    pmdstop->setFixedWidth(120);
    goButton->setFixedWidth(120);
    delscircle->setFixedWidth(120);
    delaxis->setFixedWidth(120);
    delmcircle->setFixedHeight(25);
    backDef->setFixedHeight(25);
    pmdstop->setFixedHeight(25);
    goButton->setFixedHeight(25);
    delscircle->setFixedHeight(25);
    delaxis->setFixedHeight(25);
    delmcircle->setFixedHeight(25);
    aboutbutton->setFixedWidth(120);
    aboutbutton->setFixedHeight(20);
    aboutbutton->setFont(font);
    fast=new QPushButton(">");
    fast->setFont(font1);
    fast->setFixedWidth(20);
    slow=new QPushButton("<");
    slow->setFont(font1);
    slow->setFixedWidth(20);
    //pmdstop->setDisabled(true);
    //backDef->setDisabled(true);

    QHBoxLayout *main=new QHBoxLayout;
    QGridLayout *gl=new QGridLayout;

    int size=250;
    p1=new PMD1;
    p1->setFixedSize(size,size);
    p2=new PMD2;
    p2->setFixedSize(size,size);
    p3=new PMD3;
    p3->setFixedSize(size,size);
    p4=new PMD4;
    p4->setFixedSize(size,size);

    gl->addWidget(p1,0,0,1,1,Qt::AlignCenter);
    gl->addWidget(p2,0,1,1,1,Qt::AlignCenter);
    gl->addWidget(p3,1,0,1,1,Qt::AlignCenter);
    gl->addWidget(p4,1,1,1,1,Qt::AlignCenter);
    main->addLayout(gl);

    QVBoxLayout *left=new QVBoxLayout;
    QGridLayout *panel=new QGridLayout;

    panel->addWidget(lm,0,0,1,4,Qt::AlignCenter);
    panel->addWidget(m1,1,0,1,2,Qt::AlignCenter);
    panel->addWidget(m2,1,2,1,2,Qt::AlignCenter);
    panel->addWidget(m3,2,0,1,2,Qt::AlignCenter);
    panel->addWidget(m4,2,2,1,2,Qt::AlignCenter);
    panel->addWidget(rr,3,0,1,2,Qt::AlignRight);
    panel->addWidget(R,3,2,1,2,Qt::AlignCenter);
    panel->addWidget(mm,4,0,1,2,Qt::AlignRight);
    panel->addWidget(M,4,2,1,2,Qt::AlignCenter);
    panel->addWidget(speed,5,0,1,2,Qt::AlignCenter);
    panel->addWidget(slow,5,2,1,1,Qt::AlignCenter);
    panel->addWidget(fast,5,3,1,1,Qt::AlignCenter);
    panel->addWidget(goButton,6,0,1,4,Qt::AlignCenter);
    panel->addWidget(voptions,7,0,1,4,Qt::AlignCenter);
    panel->addWidget(delaxis,8,0,1,4,Qt::AlignCenter);
    panel->addWidget(delmcircle,9,0,1,4,Qt::AlignCenter);
    panel->addWidget(delscircle,10,0,1,4,Qt::AlignCenter);
    panel->addWidget(zoomlabel,11,0,1,4,Qt::AlignCenter);
    panel->addWidget(zoombutton,12,0,1,4,Qt::AlignCenter);
    panel->addWidget(viewoptions,13,0,1,4,Qt::AlignCenter);
    panel->addWidget(backDef,14,0,1,4,Qt::AlignCenter);
    panel->addWidget(pmdstop,15,0,1,4,Qt::AlignCenter);
    //panel->addWidget(space,16,0,1,4,Qt::AlignCenter);
    panel->addWidget(aboutbutton,17,0,1,4,Qt::AlignCenter);
    left->addLayout(panel);
    left->addStretch();
    main->addLayout(left);

    QObject::connect(backDef,SIGNAL(clicked()),this,
                     SLOT(backDefault()));
    QObject::connect(pmdstop,SIGNAL(clicked()),this,
                     SLOT(pmdStop()));
    QObject::connect(goButton,SIGNAL(clicked()),this,
                     SLOT(pmdGo()));
    QObject::connect(fast,SIGNAL(clicked()),this,
                     SLOT(makefast()));
    QObject::connect(slow,SIGNAL(clicked()),this,
                     SLOT(makeslow()));
    QObject::connect(delaxis,SIGNAL(clicked()),this,
                     SLOT(deleteaxis()));
    QObject::connect(delmcircle,SIGNAL(clicked()),this,
                     SLOT(deletemcircle()));
    QObject::connect(delscircle,SIGNAL(clicked()),this,
                     SLOT(deletescircle()));
    QObject::connect(aboutbutton,SIGNAL(clicked()),this,
                     SLOT(about()));
    QObject::connect(zoombutton,SIGNAL(clicked()),this,
                     SLOT(zoom()));
    Dialog::setLayout(main);

    timer = new QTimer(this);

    //connect(timer, SIGNAL(timeout()), p1, SLOT(update()));
    //connect(timer, SIGNAL(timeout()), p2, SLOT(update()));
    //connect(timer, SIGNAL(timeout()), p3, SLOT(update()));
    connect(timer, SIGNAL(timeout()), p4, SLOT(update()));
    timer->start(50);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::backDefault()
{
    emit p1->backDefault();
    emit p2->backDefault();
    emit p3->backDefault();
    emit p4->backDefault();
}

void Dialog::pmdStop()
{
    if (!p1->stop) pmdstop->setText("Start");
    else pmdstop->setText("Stop");
    p1->stop=!p1->stop;

    if (!p2->stop) pmdstop->setText("Start");
    else pmdstop->setText("Stop");
    p2->stop=!p2->stop;

    if (!p3->stop) pmdstop->setText("Start");
    else pmdstop->setText("Stop");
    p3->stop=!p3->stop;

    if (!p4->stop) pmdstop->setText("Start");
    else pmdstop->setText("Stop");
    p4->stop=!p4->stop;

}

void Dialog::pmdGo()
{
    float M_,R_;
    float m1_,m2_,m3_,m4_;
    M_=M->text().toDouble();
    m1_=m1->text().toDouble();
    m2_=m2->text().toDouble();
    m3_=m3->text().toDouble();
    m4_=m4->text().toDouble();
    R_=R->text().toDouble();
    p1->getData(M_,m1_,m2_,m3_,m4_,R_);
    p2->getData(M_,m1_,m2_,m3_,m4_,R_);
    p3->getData(M_,m1_,m2_,m3_,m4_,R_);
    p4->getData(M_,m1_,m2_,m3_,m4_,R_);

}

void Dialog::makeslow()
{
    p4->changeSpeed(-1);
}

void Dialog::makefast()
{
    p4->changeSpeed(1);
}

void Dialog::deleteaxis()
{
    p1->deleteaxis();
    p2->deleteaxis();
    p3->deleteaxis();
    p4->deleteaxis();
    if (!p1->axis) delaxis->setText("Show axis");
    else delaxis->setText("Delete axis");
}

void Dialog::deletemcircle()
{
    p1->deletemcircle();
    p2->deletemcircle();
    p3->deletemcircle();
    p4->deletemcircle();
    if (!p1->mcircle) delmcircle->setText("Show moving circle");
    else delmcircle->setText("Delete moving circle");

}

void Dialog::deletescircle()
{
    p1->deletescircle();
    p2->deletescircle();
    p3->deletescircle();
    p4->deletescircle();
    if (!p1->scircle) delscircle->setText("Show static circle");
    else delscircle->setText("Delete static circle");

}

void Dialog::about()
{
    QMessageBox msgBox;
    QFont font("Times", 8, QFont::Normal);
    msgBox.setWindowTitle("About");
    msgBox.setFont(font);
    msgBox.setFixedWidth(700);
    msgBox.setText("<center>Copyright by Andrey Konin</center>"
                   "<center>www.AKonin.com</center>");
    msgBox.exec();
}

void Dialog::zoom()
{
    p1->zoom();
    p2->zoom();
    p3->zoom();
    p4->maxX=p2->maxX;
    p4->maxY=p2->maxY;
    p4->zoom();

    if (p1->zoomflag) zoombutton->setText("Real size");
    else zoombutton->setText("Fit to screen");
}
