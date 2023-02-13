#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QScrollArea>
#include <QGridLayout>
#include <QDebug>
#include <QPushButton>
#include <QScrollBar>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    fullKeyboard(new FullKeyboard(this)),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPushButton *btn=nullptr;
    QWidget *w=nullptr;
    QGridLayout *glayout=nullptr;
    QScrollArea *scrarea=nullptr;
    scrarea=new QScrollArea(this);
    ui->gridLayout_widget->addWidget(scrarea);
    qDebug() << "debug27" <<scrarea->widget();
    ui->lineEdit->installEventFilter(this);
    w=new QWidget(this);
    glayout=new QGridLayout(w);
//    w->setFixedSize(400,200);
    w->setStyleSheet("background-color:red");
    glayout->setSpacing(0);
    glayout->setMargin(0);
//    for(int i=0;i<10;i++) {
//        for(int j=0;j<10;j++) {
//            btn=new QPushButton(QString::number(i)+","+QString::number(j),this);
//            glayout->addWidget(btn,i,j);
//        }
//    }
    scrarea->setWidget(w);
    scrarea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    setStyleSheet("QScrollBar::add-line:horizontal{width:1px;background:none;color:none;}");
    btn=new QPushButton("<",this);
    ui->gridLayout_widget->addWidget(btn);
    connect(btn,&QPushButton::released,this,[scrarea](){
        scrarea->horizontalScrollBar()->setValue(scrarea->horizontalScrollBar()->value()-scrarea->horizontalScrollBar()->maximum()/10);
    });
    btn=new QPushButton(">",this);
    ui->gridLayout_widget->addWidget(btn);
    connect(btn,&QPushButton::released,this,[scrarea](){
        scrarea->horizontalScrollBar()->setValue(scrarea->horizontalScrollBar()->value()+scrarea->horizontalScrollBar()->maximum()/10);
    });
    connect(ui->pushButton_edit,&QPushButton::released,this,[this](){
        fullKeyboard->attach(ui->plainTextEdit);
        fullKeyboard->show();
    });
//    fullKeyboard->setLanguageEnabled(1,false);
    QChar c('1');
    qDebug() << "debug26" << c.isLower();
//    HanCharacter hanch;
//    hanch.initDb();
    QValidator *valid=nullptr;
    valid=new QRegExpValidator(QRegExp("^\\w+$"));
    //ui->lineEdit->setValidator(valid);
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type()==QEvent::MouseButtonRelease) {
        if(watched==ui->lineEdit) {
            fullKeyboard->attach(ui->lineEdit);
            fullKeyboard->show();
        }
    }
    return false;
}

MainWindow::~MainWindow()
{
    delete ui;
}
