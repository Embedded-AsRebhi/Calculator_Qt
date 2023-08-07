#include "mainwindow.h"
#include "ui_mainwindow.h"

double calcVal = 0.0;
bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;

bool userIsTypingSecondNumber = false;
double labelNumber;



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(calcVal));
    QPushButton *numButtons[10];
    for(int i =0; i<10; i++) {
        QString butName = "Button" + QString::number(i);
        numButtons[i] = MainWindow::findChild<QPushButton *> (butName);

        connect(numButtons[i],SIGNAL(released()),this,SLOT(NumPressed()));

    }

    connect(ui->ButtonAdd, SIGNAL(released()),this,SLOT(MathButtonPressed()));
    connect(ui->ButtonMinus, SIGNAL(released()),this,SLOT(MathButtonPressed()));
    connect(ui->ButtonMultiplication, SIGNAL(released()),this,SLOT(MathButtonPressed()));
    connect(ui->ButtonDivision, SIGNAL(released()),this,SLOT(MathButtonPressed()));

    connect(ui->ButtonEqual, SIGNAL(released()),this,SLOT(EqualButton()));
    connect(ui->ButtonChangeSign, SIGNAL(released()),this,SLOT(ChangeNumberSign()));

    connect(ui->ButtonChangeSign,SIGNAL(released()),this,SLOT(unary_operation_pressed()));


    ui->ButtonAdd->setCheckable(true);
    ui->ButtonMinus->setCheckable(true);
    ui->ButtonMultiplication->setCheckable(true);
    ui->ButtonDivision->setCheckable(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::NumPressed() {
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    QString displayVal = ui->Display->text();

    if ((displayVal.toDouble() == 0) || (displayVal.toDouble() ==0.0)) {
        ui->Display->setText(butVal);

    } else {
        QString newVal = displayVal + butVal;
        double  dblNewVal = newVal.toDouble();
        userIsTypingSecondNumber = true ;

        ui->Display->setText(QString::number(dblNewVal, 'g', 16));
    }

}

void MainWindow::MathButtonPressed() {

   divTrigger = false;
   multTrigger = false;
   addTrigger = false;
   subTrigger = false;

   QString displayVal = ui->Display->text();
   calcVal = displayVal.toDouble();
   QPushButton *button = (QPushButton *)sender();
   QString butVal = button->text();

   if(QString::compare(butVal, "/", Qt::CaseInsensitive) == 0){
        divTrigger = true;
   } else if (QString::compare(butVal, "*", Qt::CaseInsensitive) == 0)
   { multTrigger = true;

   } else if (QString::compare(butVal, "+", Qt::CaseInsensitive) == 0)
   { addTrigger  = true;

   }  else if (QString::compare(butVal, "-", Qt::CaseInsensitive) == 0)
   { subTrigger  = true;

   }

   ui->Display->setText ("");
}

void MainWindow::EqualButton(){

   double solution = 0.0;
   QString displayVal = ui->Display->text();
   double dblDisplayVal = displayVal.toDouble();

   if (addTrigger || subTrigger || multTrigger || divTrigger ) {
       if(addTrigger) {
            solution = calcVal + dblDisplayVal;
   } else if(subTrigger) {
        solution = calcVal - dblDisplayVal;
   } else if(multTrigger) {
        solution = calcVal * dblDisplayVal;
   } else if(divTrigger) {
        solution = calcVal / dblDisplayVal;
   }

}

   ui->Display->setText(QString::number(solution));
}


/*void MainWindow:: ChangeNumberSign(){

   QString displayVal = ui->Display->text();
   QRegExp reg("[-]?[0-9.]*");

   if (reg.exactMatch(displayVal)) {
   double dblDisplayVal = displayVal.toDouble();
   double dblDisplayValSign = -1 * displayVal.toDouble();
   ui->Display->setText(QString::number( dblDisplayValSign));

   }

} */

void MainWindow::unary_operation_pressed()
{
   QPushButton * button = (QPushButton*) sender();
   double dblNewVal;
   QString newLabel;

   if (button->text() == "+/-")
   {
   dblNewVal = ui->Display->text().toDouble();
   labelNumber = labelNumber * -1;
   newLabel = QString::number(labelNumber,'g',15);
   ui->Display->setText(newLabel);
   }


}

void MainWindow::on_pushButton_Clear_released()
{
   ui->ButtonAdd->setChecked(false);
   ui->ButtonMinus->setChecked(false);
   ui->ButtonMultiplication->setChecked(false);
   ui->ButtonDivision->setChecked(false);

   userIsTypingSecondNumber = false;

   ui->Display->setText("0");
}


