#include "numberkeyboard.h"
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QDebug>
#include <QKeyEvent>
#include <QCoreApplication>
#include <QApplication>
#include <QDesktopWidget>
#include <QFont>
NumberKeyboard::NumberKeyboard(QWidget *parent, Qt::WindowFlags f)
    : QFrame(parent, f)
{
    initKeyboard();
    setWindowModality(Qt::WindowModal);
    setFrameShadow(QFrame::Sunken);
    setFrameShape(QFrame::Box);
    setLineWidth(2);
    QFont font;
    font=this->font();
    font.setPointSize(12);
    this->setFont(font);
}

void NumberKeyboard::initKeyboard()
{
    setFixedWidth(500);
    setFixedHeight(400);
    QPushButton *btn=nullptr;

    QGridLayout *glayout=new QGridLayout(this);
    glayout->setMargin(5);
    glayout->setSpacing(3);

    inputEdit=new QLineEdit(this);
    inputEdit->setFocusPolicy(Qt::StrongFocus);
    inputEdit->setFocus();
    inputEdit->setReadOnly(true);
    glayout->addWidget(inputEdit,0,0,1,4);

    //1
    btn=new QPushButton(this);
    btn->setText("1");
    btn->setFocusPolicy(Qt::NoFocus);
    btn->setContentsMargins(100,100,0,0);
    btn->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    connect(btn,&QPushButton::released,
            this,[=](){
        int n=0;
        QString s=inputEdit->text();
        s.append("1");
        if(inputEdit->validator())
        {
            if(inputEdit->validator()->validate(s,n)==QValidator::Acceptable)
            {
                inputEdit->setText(s);
            }
        }
        else
        {
            inputEdit->setText(s);
        }
    });
    glayout->addWidget(btn,1,0);

    //2
    btn=new QPushButton(this);
    btn->setText("2");
    btn->setFocusPolicy(Qt::NoFocus);
    btn->setContentsMargins(0,0,0,0);
    btn->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    connect(btn,&QPushButton::released,
            this,[=](){
        int n=0;
        QString s=inputEdit->text();
        s.append("2");
        if(inputEdit->validator())
        {
            if(inputEdit->validator()->validate(s,n)==QValidator::Acceptable)
            {
                inputEdit->setText(s);
            }
        }
        else
        {
            inputEdit->setText(s);
        }
    });
    glayout->addWidget(btn,1,1);

    //3
    btn=new QPushButton(this);
    btn->setText("3");
    btn->setFocusPolicy(Qt::NoFocus);
    btn->setContentsMargins(0,0,0,0);
    btn->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    connect(btn,&QPushButton::released,
            this,[=](){
        int n=0;
        QString s=inputEdit->text();
        s.append("3");
        if(inputEdit->validator())
        {
            if(inputEdit->validator()->validate(s,n)==QValidator::Acceptable)
            {
                inputEdit->setText(s);
            }
        }
        else
        {
            inputEdit->setText(s);
        }
    });
    glayout->addWidget(btn,1,2);

    //4
    btn=new QPushButton(this);
    btn->setText("4");
    btn->setFocusPolicy(Qt::NoFocus);
    btn->setContentsMargins(0,0,0,0);
    btn->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    connect(btn,&QPushButton::released,
            this,[=](){
        int n=0;
        QString s=inputEdit->text();
        s.append("4");
        if(inputEdit->validator())
        {
            if(inputEdit->validator()->validate(s,n)==QValidator::Acceptable)
            {
                inputEdit->setText(s);
            }
        }
        else
        {
            inputEdit->setText(s);
        }
    });
    glayout->addWidget(btn,2,0);

    //5
    btn=new QPushButton(this);
    btn->setText("5");
    btn->setFocusPolicy(Qt::NoFocus);
    btn->setContentsMargins(0,0,0,0);
    btn->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    connect(btn,&QPushButton::released,
            this,[=](){
        int n=0;
        QString s=inputEdit->text();
        s.append("5");
        if(inputEdit->validator())
        {
            if(inputEdit->validator()->validate(s,n)==QValidator::Acceptable)
            {
                inputEdit->setText(s);
            }
        }
        else
        {
            inputEdit->setText(s);
        }
    });
    glayout->addWidget(btn,2,1);

    //6
    btn=new QPushButton(this);
    btn->setText("6");
    btn->setFocusPolicy(Qt::NoFocus);
    btn->setContentsMargins(0,0,0,0);
    btn->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    connect(btn,&QPushButton::released,
            this,[=](){
        int n=0;
        QString s=inputEdit->text();
        s.append("6");
        if(inputEdit->validator())
        {
            if(inputEdit->validator()->validate(s,n)==QValidator::Acceptable)
            {
                inputEdit->setText(s);
            }
        }
        else
        {
            inputEdit->setText(s);
        }
    });
    glayout->addWidget(btn,2,2);

    //7
    btn=new QPushButton(this);
    btn->setText("7");
    btn->setFocusPolicy(Qt::NoFocus);
    btn->setContentsMargins(0,0,0,0);
    btn->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    connect(btn,&QPushButton::released,
            this,[=](){
        int n=0;
        QString s=inputEdit->text();
        s.append("7");
        if(inputEdit->validator())
        {
            if(inputEdit->validator()->validate(s,n)==QValidator::Acceptable)
            {
                inputEdit->setText(s);
            }
        }
        else
        {
            inputEdit->setText(s);
        }
    });
    glayout->addWidget(btn,3,0);

    //8
    btn=new QPushButton(this);
    btn->setText("8");
    btn->setFocusPolicy(Qt::NoFocus);
    btn->setContentsMargins(0,0,0,0);
    btn->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    connect(btn,&QPushButton::released,
            this,[=](){
        int n=0;
        QString s=inputEdit->text();
        s.append("8");
        if(inputEdit->validator())
        {
            if(inputEdit->validator()->validate(s,n)==QValidator::Acceptable)
            {
                inputEdit->setText(s);
            }
        }
        else
        {
            inputEdit->setText(s);
        }
    });
    glayout->addWidget(btn,3,1);

    //9
    btn=new QPushButton(this);
    btn->setText("9");
    btn->setFocusPolicy(Qt::NoFocus);
    btn->setContentsMargins(0,0,0,0);
    btn->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    connect(btn,&QPushButton::released,
            this,[=](){
        int n=0;
        QString s=inputEdit->text();
        s.append("9");
        if(inputEdit->validator())
        {
            if(inputEdit->validator()->validate(s,n)==QValidator::Acceptable)
            {
                inputEdit->setText(s);
            }
        }
        else
        {
            inputEdit->setText(s);
        }
    });
    glayout->addWidget(btn,3,2);

    //cancel
    btn=new QPushButton(this);
    btn->setText(tr("cancel"));
    btn->setFocusPolicy(Qt::NoFocus);
    btn->setContentsMargins(0,0,0,0);
    btn->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    connect(btn,&QPushButton::released,
            this,[=](){
        this->hide();
    });
    glayout->addWidget(btn,4,0);

    //0
    btn=new QPushButton(this);
    btn->setText("0");
    btn->setFocusPolicy(Qt::NoFocus);
    btn->setContentsMargins(0,0,0,0);
    btn->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    connect(btn,&QPushButton::released,
            this,[=](){
        int n=0;
        QString s=inputEdit->text();
        s.append("0");
        if(inputEdit->validator())
        {
            if(inputEdit->validator()->validate(s,n)==QValidator::Acceptable)
            {
                inputEdit->setText(s);
            }
        }
        else
        {
            inputEdit->setText(s);
        }
    });
    glayout->addWidget(btn,4,1);

    //.
    btn=new QPushButton(this);
    btn->setText(".");
    btn->setFocusPolicy(Qt::NoFocus);
    btn->setContentsMargins(0,0,0,0);
    btn->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    connect(btn,&QPushButton::released,
            this,[=](){
        int n=0;
        QString s=inputEdit->text();
        s.append(".");
        if(inputEdit->validator())
        {
            if(inputEdit->validator()->validate(s,n)==QValidator::Acceptable)
            {
                inputEdit->setText(s);
            }
        }
        else
        {
            inputEdit->setText(s);
        }
    });
    glayout->addWidget(btn,4,2);

    //<-
    btn=new QPushButton(this);
    btn->setText("<-");
    btn->setFocusPolicy(Qt::NoFocus);
    btn->setContentsMargins(0,0,0,0);
    btn->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    connect(btn,&QPushButton::released,
            this,[=](){
        QString s=inputEdit->text();
        s.remove(s.size()-1,1);
        inputEdit->setText(s);
    });
    glayout->addWidget(btn,1,3);

    //OK
    btn=new QPushButton(this);
    btn->setText("OK");
    btn->setFocusPolicy(Qt::NoFocus);
    btn->setContentsMargins(0,0,0,0);
    btn->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    connect(btn,SIGNAL(released()),this,SLOT(onOkReleased()));
    glayout->addWidget(btn,4,3);
}

void NumberKeyboard::attach(QWidget *w)
{
    atUi=w;
    QValidator *v=nullptr;
    const QDoubleValidator *cdv=nullptr;
    const QIntValidator *civ=nullptr;
    const QRegExpValidator *crv=nullptr;
    if(atUi==nullptr)
    {
        return;
    }
    if(QString(atUi->metaObject()->className())=="QLineEdit")
    {
        QLineEdit *edit=static_cast<QLineEdit*>(atUi);
        if(edit->validator() && edit->validator()->metaObject()->className()==QString("QDoubleValidator"))
        {
            cdv=static_cast<const QDoubleValidator*>(edit->validator());
            v=new QDoubleValidator(cdv->bottom(),cdv->top(),cdv->decimals());
        }
        else if(edit->validator() && edit->validator()->metaObject()->className()==QString("QIntValidator"))
        {
            civ=static_cast<const QIntValidator*>(edit->validator());
            v=new QIntValidator(civ->bottom(),civ->top());
        }
        else if(edit->validator() && edit->validator()->metaObject()->className()==QString("QRegExpValidator"))
        {
            crv=static_cast<const QRegExpValidator*>(edit->validator());
            v=new QRegExpValidator(crv->regExp());
        }
        inputEdit->setText(edit->text());
        inputEdit->setValidator(v);
    }
}

void NumberKeyboard::onOkReleased()
{
    QString s;
    int n=0;
    close();
    if(!atUi) return;
    if(atUi->metaObject()->className()==QString("QLineEdit"))
    {
        QLineEdit *edit=static_cast<QLineEdit*>(atUi);
        s=inputEdit->text();
        if(edit->validator())
        {
            if(edit->validator()->validate(s,n)==QValidator::Acceptable)
            {
                edit->setText(inputEdit->text());
            }
        }
        else
        {
            edit->setText(inputEdit->text());
        }
        atUi=nullptr;
    }
}

void NumberKeyboard::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    int sx,sy;
    QRect rc;
    if(parentWidget()) {
        rc=parentWidget()->geometry();
    }
    else {
        QDesktopWidget* desktopWidget = QApplication::desktop();
        rc=desktopWidget->availableGeometry();
    }
    sx=rc.center().x()-size().width()/2;
    sy=rc.center().y()-size().height()/2;
    setGeometry(sx,sy,width(),height());
}
