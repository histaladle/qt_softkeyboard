#ifndef FULLKEYBOARD_H
#define FULLKEYBOARD_H

#include <QWidget>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QStackedWidget>
#include <QLabel>
#include <QScrollArea>
#include <QGridLayout>
#include <QSqlDatabase>
#include <QSqlQuery>
class KeyButtonInfo {
public:
    QString label;
    QString text;
    QString shiftedLabel;
    QString shiftedText;
};

class FullKeyboard : public QWidget
{
    Q_OBJECT
public:
    enum KeyboardStatus {
        Lowered,
        Shifted,
    };

    explicit FullKeyboard(QWidget *parent=0, Qt::WindowFlags f=Qt::Window);
    void attach(QWidget *w);
    void setPinyinEnable(bool f);
private:
    QWidget *atUi=nullptr;
    QLineEdit *lineEdit=nullptr;
    QPlainTextEdit *plainTextEdit=nullptr;
    QStackedWidget *keyboardStack=nullptr;
    QLabel *spellLabel;
    QScrollArea *wordArea;
    QPushButton *leftWordAreaBtn;
    QPushButton *rightWordAreaBtn;
    QGridLayout *wordContentLayout;
    void initKeyboard();
    QList<QList<QList<KeyButtonInfo> > > keyboardPages;
//    QList<QList<QPushButton*> > btnLines;
    QList<QList<QList<QPushButton*> > > btnPages;
    void initKeyboardPages();
    int getKeyboardPagesSize();
    int getKeyboardPageSize(int page);
    int getKeyboardLineSize(int page,int line);
    int keyboardStatus=0;
//    int page=0;
    void updateKeyboard(int page, int status);
    QList<QPushButton*> wordBtns;
    QStringList pin(QString pinyin);
    void setWordBarVisible(bool f);
    void clearWordArea();
    void updateWordArea(QStringList words);
    void insertKeyValue(int page, int line, int index);
    QSqlDatabase pinyinDb;
    bool pinyinEnabled;
signals:

public slots:
    void onKeyReleased(int page,int line,int index);
    void showEvent(QShowEvent *event);
public:
protected:
};

#endif // FULLKEYBOARD_H
