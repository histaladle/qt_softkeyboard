#include "FullKeyboard.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSizePolicy>
#include <QValidator>
#include <QDebug>
#include <QSpacerItem>
#include <QPlainTextEdit>
#include <QApplication>
#include <QDesktopWidget>
#include <QFont>
#include <QKeyEvent>
#include <QScrollArea>
#include <QScrollBar>
#include <QGridLayout>
FullKeyboard::FullKeyboard(QWidget *parent, Qt::WindowFlags f)
    : QWidget(parent, f)
{
    setWindowModality(Qt::WindowModal);
    initKeyboardPages();
    initKeyboard();
    for(int i=0;i<btnPages.size();i++)
    {
        updateKeyboard(i, keyboardStatus);
    }
    setWordBarVisible(false);
}

void FullKeyboard::initKeyboard()
{
    QPushButton *btn=nullptr;
    QList<QList<QPushButton*> > btnLines;

    QVBoxLayout *vlayout=nullptr, *kvlayout=nullptr;
    vlayout=new QVBoxLayout(this);
    vlayout->setMargin(0);
    vlayout->setSpacing(0);

    lineEdit=new QLineEdit(this);
    vlayout->addWidget(lineEdit);

    plainTextEdit=new QPlainTextEdit(this);
    vlayout->addWidget(plainTextEdit);

    QWidget *w=nullptr;
    QGridLayout *glayout=nullptr;
    glayout=new QGridLayout();
    vlayout->addItem(glayout);

    int wah=30;
    spellLabel=new QLabel(this);
    spellLabel->setMaximumWidth(200);
    spellLabel->setFixedHeight(wah);
    spellLabel->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
    glayout->addWidget(spellLabel,0,0);

    btn=new QPushButton("<",this);
    btn->setFixedWidth(40);
    btn->setFixedHeight(wah);
    btn->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
    leftWordAreaBtn=btn;
    connect(btn,&QPushButton::pressed,this,[this](){
        if(wordBtns.isEmpty()) {
            return;
        }
        wordArea->horizontalScrollBar()->setValue(wordArea->horizontalScrollBar()->value()-wordArea->horizontalScrollBar()->maximum()/wordBtns.size());
    });
    glayout->addWidget(btn,0,1);

    wordArea=new QScrollArea(this);
    wordArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    wordArea->setFixedHeight(wah);
    wordArea->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Maximum);
    glayout->addWidget(wordArea,0,2);
    wordArea->setWidgetResizable(true);

    w=new QWidget(this);
    wordContentLayout=new QGridLayout(w);
//    w->setStyleSheet("QWidget{background-color:red;}");
    wordContentLayout->setSpacing(0);
    wordContentLayout->setMargin(0);
    wordArea->setWidget(w);
    qDebug() << "debug82" << wordArea->widget() << w
             << w->layout() << wordContentLayout;

    btn=new QPushButton(">",this);
    btn->setFixedWidth(40);
    btn->setFixedHeight(wah);
    btn->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
    rightWordAreaBtn=btn;
    connect(btn,&QPushButton::pressed,this,[this](){
        if(wordBtns.isEmpty()) {
            return;
        }
        wordArea->horizontalScrollBar()->setValue(wordArea->horizontalScrollBar()->value()+wordArea->horizontalScrollBar()->maximum()/wordBtns.size());
    });
    glayout->addWidget(btn,0,3);



    int minKeyWidth=35,minKeyHeight=40;

    QWidget *kbwidget=nullptr;
    QList<QPushButton*> btnLine;
    QHBoxLayout *khlayout=nullptr;

    keyboardStack=new QStackedWidget(this);
    vlayout->addWidget(keyboardStack);

    for(int page=0;page<2;page++) {
        btnLines.clear();
        kbwidget=new QWidget();
        keyboardStack->addWidget(kbwidget);
        kvlayout=new QVBoxLayout(kbwidget);
        kvlayout->setMargin(0);
        kvlayout->setSpacing(0);
        for(int line=0;line<4;line++) {
            khlayout=new QHBoxLayout();
            khlayout->setMargin(3);
            khlayout->setSpacing(3);
            kvlayout->addItem(khlayout);
            btnLine.clear();
            for(int n=0;n<keyboardPages[page][line].size();n++) {
                btn=new QPushButton(kbwidget);
                btn->setFocusPolicy(Qt::NoFocus);
                btn->setMinimumSize(minKeyWidth,minKeyHeight);
                btn->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
                connect(btn,&QPushButton::released,this,[this,page,line,n]{
                    onKeyReleased(page,line,n);
                });
                khlayout->addWidget(btn);
                btnLine.append(btn);
            }
            btnLines.append(btnLine);
        }
        btnPages.append(btnLines);
    }

    setFixedWidth(600);
    qDebug() << "debug18" << this->width() << btnPages.size()
             << keyboardStack->count();
    connect(keyboardStack,&QStackedWidget::currentChanged,[this](int index){
        if(index==1) {
            setWordBarVisible(true);
        }
        else {
            setWordBarVisible(false);
        }
    });
    for(int l=0;l<btnLines.size();l++)
    {
        qDebug() << "key line" << l << btnLines[l].size();
    }
    QFont font;
    font=this->font();
    font.setPointSize(10);
    this->setFont(font);
}

void FullKeyboard::updateKeyboard(int page, int status)
{
    QList<QList<QPushButton*> > btnLines;
    QList<QPushButton*> btnLine;
    btnLines=btnPages[page];
    for(int i=0;i<btnLines.size();i++) {
        btnLine=btnLines[i];
        for(int j=0;j<btnLine.size();j++) {
            if(status==Lowered) {
                btnLine[j]->setText(keyboardPages[page][i][j].label);
            }
            else if(status==Shifted) {
                btnLine[j]->setText(keyboardPages[page][i][j].shiftedLabel);
            }
        }
    }
}

void FullKeyboard::onKeyReleased(int page, int line, int index)
{
    int n=0;
    QString s;
    QStringList ss;
    insertKeyValue(page,line,index);
    qDebug() << "debug20" << page << line << index;
    if(line==2 && index==0) //shift
    {
        keyboardStatus=(keyboardStatus+1)%2;
        updateKeyboard(page,keyboardStatus);
    }
    else if(line==3 && index==11) //EN/ZH
    {
        if(page==0)
        {
            keyboardStack->setCurrentIndex(1);
        }
        else if(page==1)
        {
            keyboardStack->setCurrentIndex(0);
        }
        updateKeyboard(keyboardStack->currentIndex(),keyboardStatus);
    }
    else if(line==3 && index==12) //ok
    {
        if(atUi)
        {
            if(QString(atUi->metaObject()->className())=="QPlainTextEdit")
            {
                QPlainTextEdit *atTextEdit=static_cast<QPlainTextEdit*>(atUi);
                atTextEdit->setPlainText(plainTextEdit->toPlainText());
            }
            else if(QString(atUi->metaObject()->className())=="QLineEdit")
            {
                qDebug() << "debug23" << lineEdit->text();
                QLineEdit *atLineEdit=static_cast<QLineEdit*>(atUi);
                if(atLineEdit->validator())
                {
                    if(atLineEdit->validator()->validate(s,n)==QValidator::Acceptable)
                    {
                        atLineEdit->setText(lineEdit->text());
                    }
                }
                else
                {
                    atLineEdit->setText(lineEdit->text());
                }
            }
            atUi=nullptr;
        }
        close();
        clearWordArea();
        spellLabel->clear();
    }
    else if(line==0 && index==13) //<-
    {
        QKeyEvent *ke=nullptr;
        if(page==0) {
            ke=new QKeyEvent(QEvent::KeyPress,Qt::Key_Backspace,Qt::NoModifier);
            QApplication::postEvent(lineEdit,ke);
            ke=new QKeyEvent(QEvent::KeyRelease,Qt::Key_Backspace,Qt::NoModifier);
            QApplication::postEvent(lineEdit,ke);

            ke=new QKeyEvent(QEvent::KeyPress,Qt::Key_Backspace,Qt::NoModifier);
            QApplication::postEvent(plainTextEdit,ke);
            ke=new QKeyEvent(QEvent::KeyRelease,Qt::Key_Backspace,Qt::NoModifier);
            QApplication::postEvent(plainTextEdit,ke);
        }
        else if(page==1) {
            if(spellLabel->text().isEmpty()) {
                ke=new QKeyEvent(QEvent::KeyPress,Qt::Key_Backspace,Qt::NoModifier);
                QApplication::postEvent(lineEdit,ke);
                ke=new QKeyEvent(QEvent::KeyRelease,Qt::Key_Backspace,Qt::NoModifier);
                QApplication::postEvent(lineEdit,ke);

                ke=new QKeyEvent(QEvent::KeyPress,Qt::Key_Backspace,Qt::NoModifier);
                QApplication::postEvent(plainTextEdit,ke);
                ke=new QKeyEvent(QEvent::KeyRelease,Qt::Key_Backspace,Qt::NoModifier);
                QApplication::postEvent(plainTextEdit,ke);
            }
            else {
                s=spellLabel->text();
                s.remove(s.size()-1,1);
                spellLabel->setText(s);
                ss=pin(s);
                updateWordArea(ss);
            }
        }
    }
    else if(line==3 && index==0) //exit
    {
        lineEdit->clear();
        plainTextEdit->clear();
        atUi=nullptr;
        close();
        clearWordArea();
        spellLabel->clear();
    }
}

void FullKeyboard::attach(QWidget *w)
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
        lineEdit->setText(edit->text());
        lineEdit->setValidator(v);
        lineEdit->setVisible(true);
        plainTextEdit->setVisible(false);
        setFixedHeight(250);
    }
    else if(QString(atUi->metaObject()->className())=="QPlainTextEdit")
    {
        QPlainTextEdit *textEdit=static_cast<QPlainTextEdit*>(atUi);
        this->plainTextEdit->setPlainText(textEdit->toPlainText());
        lineEdit->setVisible(false);
        plainTextEdit->setVisible(true);
        setFixedHeight(350);
    }
}

void FullKeyboard::insertKeyValue(int page, int line, int index)
{
    int n=0;
    QString s1,s2;
    QKeyEvent *ke=nullptr;
    if(lineEdit->isVisible()) {
        if(keyboardStack->currentIndex()==1) {
            QString spell;
            QStringList ss;
            spell=spellLabel->text();
            if(keyboardStatus==Lowered) {
                spell.append(keyboardPages[page][line][index].text);
            }
            else if(keyboardStatus==Shifted){
                spell.append(keyboardPages[page][line][index].shiftedText);
            }
            if(spell==spellLabel->text()) {
                return;
            }
            spellLabel->setText(spell);
            for(int i=0;i<spell.size();i++) {
                if(spell[i]==0x0a || spell[i]==0x0d) {
                    s1=lineEdit->text();
                    ke=new QKeyEvent(QEvent::KeyPress,0,Qt::NoModifier,spell.mid(0,i));
                    QApplication::sendEvent(lineEdit,ke);
                    delete ke;
                    ke=new QKeyEvent(QEvent::KeyRelease,0,Qt::NoModifier,spell.mid(0,i));
                    QApplication::sendEvent(lineEdit,ke);
                    delete ke;
                    s2=lineEdit->text();
                    if(lineEdit->validator())
                    {
                        if(lineEdit->validator()->validate(s2,n)!=QValidator::Acceptable)
                        {
                            lineEdit->setText(s1);
                        }
                    }
                    clearWordArea();
                    spellLabel->clear();
                    return;
                }
            }
            bool spellLegal=true;
            for(int i=0;i<spell.size();i++) {
                if(!spell[i].isLower()) {
                    spellLegal=false;
                    break;
                }
            }
            if(spellLegal) {
                ss=pin(spell);
                updateWordArea(ss);
            }
            else {
                clearWordArea();
            }
        }
        else {
            if(keyboardStatus==Lowered)
            {
                s1=lineEdit->text();
                ke=new QKeyEvent(QEvent::KeyPress,0,Qt::NoModifier,keyboardPages[page][line][index].text);
                QApplication::sendEvent(lineEdit,ke);
                delete ke;
                ke=new QKeyEvent(QEvent::KeyRelease,0,Qt::NoModifier,keyboardPages[page][line][index].text);
                QApplication::sendEvent(lineEdit,ke);
                delete ke;
                s2=lineEdit->text();
                if(lineEdit->validator())
                {
                    if(lineEdit->validator()->validate(s2,n)!=QValidator::Acceptable)
                    {
                        lineEdit->setText(s1);
                    }
                }
            }
            else if(keyboardStatus==Shifted)
            {
                s1=lineEdit->text();
                ke=new QKeyEvent(QEvent::KeyPress,0,Qt::NoModifier,keyboardPages[page][line][index].shiftedText);
                QApplication::sendEvent(lineEdit,ke);
                delete ke;
                ke=new QKeyEvent(QEvent::KeyRelease,0,Qt::NoModifier,keyboardPages[page][line][index].shiftedText);
                QApplication::sendEvent(lineEdit,ke);
                delete ke;
                s2=lineEdit->text();
                if(lineEdit->validator())
                {
                    if(lineEdit->validator()->validate(s2,n)!=QValidator::Acceptable)
                    {
                        lineEdit->setText(s1);
                    }
                }
            }
        }
    }
    else if(plainTextEdit->isVisible()) {
        if(keyboardStack->currentIndex()==1) {
            QString spell;
            QStringList ss;
            spell=spellLabel->text();
            if(keyboardStatus==Lowered) {
                spell.append(keyboardPages[page][line][index].text);
            }
            else if(keyboardStatus==Shifted){
                spell.append(keyboardPages[page][line][index].shiftedText);
            }
            if(spell==spellLabel->text()) {
                return;
            }
            spellLabel->setText(spell);
            for(int i=0;i<spell.size();i++) {
                if(spell[i]==0x0a || spell[i]==0x0d) {
                    ke=new QKeyEvent(QEvent::KeyPress,0,Qt::NoModifier,spell.mid(0,i+1));
                    QApplication::postEvent(plainTextEdit,ke);
                    ke=new QKeyEvent(QEvent::KeyRelease,0,Qt::NoModifier,spell.mid(0,i+1));
                    QApplication::postEvent(plainTextEdit,ke);
                    clearWordArea();
                    spellLabel->clear();
                    return;
                }
            }
            bool spellLegal=true;
            for(int i=0;i<spell.size();i++) {
                if(!spell[i].isLower()) {
                    spellLegal=false;
                    break;
                }
            }
            if(spellLegal) {
                ss=pin(spell);
                updateWordArea(ss);
            }
            else {
                clearWordArea();
            }
        }
        else {
            if(keyboardStatus==Lowered)
            {
                ke=new QKeyEvent(QEvent::KeyPress,0,Qt::NoModifier,keyboardPages[page][line][index].text);
                QApplication::postEvent(plainTextEdit,ke);
                ke=new QKeyEvent(QEvent::KeyRelease,0,Qt::NoModifier,keyboardPages[page][line][index].text);
                QApplication::postEvent(plainTextEdit,ke);
            }
            else if(keyboardStatus==Shifted)
            {
                ke=new QKeyEvent(QEvent::KeyPress,0,Qt::NoModifier,keyboardPages[page][line][index].shiftedText);
                QApplication::postEvent(plainTextEdit,ke);
                ke=new QKeyEvent(QEvent::KeyRelease,0,Qt::NoModifier,keyboardPages[page][line][index].shiftedText);
                QApplication::postEvent(plainTextEdit,ke);
            }
        }
    }
}

void FullKeyboard::initKeyboardPages()
{
    QList<QList<QList<KeyButtonInfo> > > keyboardPages = {
        //page 0
        {
            //line 0
            {
                {          "`",      "`",          "~",      "~"},
                {          "1",      "1",          "!",      "!"},
                {          "2",      "2",          "@",      "@"},
                {          "3",      "3",          "#",      "#"},
                {          "4",      "4",          "$",      "$"},
                {          "5",      "5",          "%",      "%"},
                {          "6",      "6",          "^",      "^"},
                {          "7",      "7",          "&",      "&"},
                {          "8",      "8",          "*",      "*"},
                {          "9",      "9",          "(",      "("},
                {          "0",      "0",          ")",      ")"},
                {          "-",      "-",          "_",      "_"},
                {          "=",      "=",          "+",      "+"},
                {         "<-",       "",         "<-",       ""},
            },
            //line 1
            {
                {        "Tab",     "\t",        "Tab",     "\t"},
                {          "q",      "q",          "Q",      "Q"},
                {          "w",      "w",          "W",      "W"},
                {          "e",      "e",          "E",      "E"},
                {          "r",      "r",          "R",      "R"},
                {          "t",      "t",          "T",      "T"},
                {          "y",      "y",          "Y",      "Y"},
                {          "u",      "u",          "U",      "U"},
                {          "i",      "i",          "I",      "I"},
                {          "o",      "o",          "O",      "O"},
                {          "p",      "p",          "P",      "P"},
                {          "[",      "[",          "{",      "{"},
                {          "]",      "]",          "}",      "}"},
                {         "\\",     "\\",          "|",      "|"},
                {        "[ ]",      " ",        "[ ]",      " "},
            },
            //line 2
            {
                {      "Shift",       "",      "Shift",       ""},
                {          "a",      "a",          "A",      "A"},
                {          "s",      "s",          "S",      "S"},
                {          "d",      "d",          "D",      "D"},
                {          "f",      "f",          "F",      "F"},
                {          "g",      "g",          "G",      "G"},
                {          "h",      "h",          "H",      "H"},
                {          "j",      "j",          "J",      "J"},
                {          "k",      "k",          "K",      "K"},
                {          "l",      "l",          "L",      "L"},
                {          ";",      ";",          ":",      ":"},
                {         "\'",     "\'",         "\"",     "\""},
                {      "Enter",     "\r",      "Enter",     "\r"},
            },
            //line 3
            {
                {        "Esc",       "",        "Esc",       ""},
                {          "z",      "z",          "Z",      "Z"},
                {          "x",      "x",          "X",      "X"},
                {          "c",      "c",          "C",      "C"},
                {          "v",      "v",          "V",      "V"},
                {          "b",      "b",          "B",      "B"},
                {          "n",      "n",          "N",      "N"},
                {          "m",      "m",          "M",      "M"},
                {          ",",      ",",          "<",      "<"},
                {          ".",      ".",          ">",      ">"},
                {          "/",      "/",          "?",      "?"},
                {         "EN",       "",         "EN",       ""},
                {         "Ok",       "",         "Ok",       ""},
            },
        },
        //page 1
        {
            //line 0
            {
                {          "`",      "`",          "~",      "~"},
                {          "1",      "1",          "!",      "!"},
                {          "2",      "2",          "@",      "@"},
                {          "3",      "3",          "#",      "#"},
                {          "4",      "4",          "$",      "$"},
                {          "5",      "5",          "%",      "%"},
                {          "6",      "6",          "^",      "^"},
                {          "7",      "7",          "&",      "&"},
                {          "8",      "8",          "*",      "*"},
                {          "9",      "9",          "(",      "("},
                {          "0",      "0",          ")",      ")"},
                {          "-",      "-",          "_",      "_"},
                {          "=",      "=",          "+",      "+"},
                {         "<-",       "",         "<-",       ""},
            },
            //line 1
            {
                {        "Tab",     "\t",        "Tab",     "\t"},
                {          "q",      "q",          "Q",      "Q"},
                {          "w",      "w",          "W",      "W"},
                {          "e",      "e",          "E",      "E"},
                {          "r",      "r",          "R",      "R"},
                {          "t",      "t",          "T",      "T"},
                {          "y",      "y",          "Y",      "Y"},
                {          "u",      "u",          "U",      "U"},
                {          "i",      "i",          "I",      "I"},
                {          "o",      "o",          "O",      "O"},
                {          "p",      "p",          "P",      "P"},
                {          "[",      "[",          "{",      "{"},
                {          "]",      "]",          "}",      "}"},
                {         "\\",     "\\",          "|",      "|"},
                {        "[ ]",      " ",        "[ ]",      " "},
            },
            //line 2
            {
                {      "Shift",       "",      "Shift",       ""},
                {          "a",      "a",          "A",      "A"},
                {          "s",      "s",          "S",      "S"},
                {          "d",      "d",          "D",      "D"},
                {          "f",      "f",          "F",      "F"},
                {          "g",      "g",          "G",      "G"},
                {          "h",      "h",          "H",      "H"},
                {          "j",      "j",          "J",      "J"},
                {          "k",      "k",          "K",      "K"},
                {          "l",      "l",          "L",      "L"},
                {          ";",      ";",          ":",      ":"},
                {         "\'",     "\'",         "\"",     "\""},
                {      "Enter",     "\r",      "Enter",     "\r"},
            },
            //line 3
            {
                {        "Esc",       "",        "Esc",       ""},
                {          "z",      "z",          "Z",      "Z"},
                {          "x",      "x",          "X",      "X"},
                {          "c",      "c",          "C",      "C"},
                {          "v",      "v",          "V",      "V"},
                {          "b",      "b",          "B",      "B"},
                {          "n",      "n",          "N",      "N"},
                {          "m",      "m",          "M",      "M"},
                {          ",",      ",",          "<",      "<"},
                {          ".",      ".",          ">",      ">"},
                {          "/",      "/",          "?",      "?"},
                {        "ZHS",       "",        "ZHS",       ""},
                {         "Ok",       "",         "Ok",       ""},
            },
        },
    };
    this->keyboardPages=keyboardPages;
}

void FullKeyboard::setWordBarVisible(bool f)
{
    spellLabel->setVisible(f);
    leftWordAreaBtn->setVisible(f);
    wordArea->setVisible(f);
    rightWordAreaBtn->setVisible(f);
}

QStringList FullKeyboard::pin(QString pinyin)
{
    QStringList ss;
    QString s;
    if(pinyin.isEmpty()) {
        return ss;
    }
//    for(int i=0;i<15;i++) {
//        s=pinyin+QString::number(i);
//        ss.append(s);
//    }
    if(!pinyinDb.isOpen()) {
        pinyinDb=QSqlDatabase::addDatabase("QSQLITE","fullkeyboard");
        pinyinDb.setDatabaseName(QApplication::applicationDirPath()+"/han_character_frequency.db");
        if(!pinyinDb.open()) {
            return ss;
        }
    }
    QSqlQuery query(pinyinDb);
    query.exec(QString("select karacter from character_frequency where pinyin=\'%1\';").arg(pinyin));
    while(query.next()) {
        ss.append(query.value(0).toString());
    }
    return ss;
}

void FullKeyboard::clearWordArea()
{
    for(int i=0;i<wordBtns.size();i++) {
        disconnect(wordBtns[i]);
        wordContentLayout->removeWidget(wordBtns[i]);
        wordBtns[i]->deleteLater();
    }
    wordBtns.clear();
}

void FullKeyboard::updateWordArea(QStringList words)
{
    QPushButton *btn=nullptr;
    clearWordArea();
    for(int i=0;i<words.size();i++) {
        btn=new QPushButton(words[i],this);
        btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        connect(btn,&QPushButton::pressed,this,[this,btn](){
            int n=0;
            QString s1,s2;
            QKeyEvent *ke=nullptr;
            if(lineEdit->isVisible()) {
                s1=lineEdit->text();
                ke=new QKeyEvent(QEvent::KeyPress, 0, Qt::NoModifier, btn->text());
                QApplication::sendEvent(lineEdit,ke);
                delete ke;
                ke=new QKeyEvent(QEvent::KeyPress, 0, Qt::NoModifier, btn->text());
                delete ke;
                s2=lineEdit->text();
                if(lineEdit->validator()) {
                    if(lineEdit->validator()->validate(s2,n)!=QValidator::Acceptable) {
                        lineEdit->setText(s1);
                    }
                }
                clearWordArea();
                spellLabel->clear();
            }
            else if(plainTextEdit->isVisible()){
                ke=new QKeyEvent(QEvent::KeyPress,0,Qt::NoModifier,btn->text());
                QApplication::postEvent(plainTextEdit,ke);
                ke=new QKeyEvent(QEvent::KeyRelease,0,Qt::NoModifier,btn->text());
                QApplication::postEvent(plainTextEdit,ke);
                clearWordArea();
                spellLabel->clear();
            }
        });
        wordContentLayout->addWidget(btn, 0, i);
        wordBtns.append(btn);
    }
}

void FullKeyboard::showEvent(QShowEvent *event)
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
