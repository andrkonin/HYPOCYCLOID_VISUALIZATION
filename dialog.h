#ifndef DIALOG_H
#define DIALOG_H

#include <QtGui/QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include "pmd1.h"
#include "pmd2.h"
#include "pmd3.h"
#include "pmd4.h"

namespace Ui
{
    class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = 0);
    ~Dialog();
    PMD1 *p1;
    PMD2 *p2;
    PMD3 *p3;
    PMD4 *p4;
    QTimer *timer;
    QPushButton *backDef;
    QPushButton *pmdstop;
    QPushButton *goButton;
    QLineEdit *m1;
    QLineEdit *m2;
    QLineEdit *m3;
    QLineEdit *m4;
    QLineEdit *M;
    QLineEdit *R;
    QLabel *rr;
    QLabel *lm;
    QLabel *mm;
    QLabel *voptions;
    QLabel *space;
    QLabel *viewoptions;
    QPushButton *fast;
    QPushButton *slow;
    QPushButton *delaxis;
    QPushButton *delmcircle;
    QPushButton *delscircle;
    QPushButton *zoombutton;
    QLabel *speed;
    QLabel *zoomlabel;
    QPushButton *aboutbutton;

public slots:

    void backDefault();
    void pmdStop();
    void pmdGo();
    void makeslow();
    void makefast();
    void deleteaxis();
    void deletemcircle();
    void deletescircle();
    void about();
    void zoom();
private:
    Ui::Dialog *ui;

};

#endif // DIALOG_H
