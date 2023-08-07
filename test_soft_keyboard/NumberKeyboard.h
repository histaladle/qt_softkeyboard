#ifndef NUMBERKEYBOARD_H
#define NUMBERKEYBOARD_H

#include <QWidget>
#include <QLineEdit>
class NumberKeyboard : public QFrame
{
    Q_OBJECT
public:
    explicit NumberKeyboard(QWidget *parent = nullptr,
                            Qt::WindowFlags f=Qt::Dialog);

    void attach(QWidget *w);
private:
    QWidget *atUi=nullptr;
    QLineEdit *inputEdit=nullptr;
    void initKeyboard();
    QList<QWidget*> targets;
protected:
    void showEvent(QShowEvent *event);
signals:

private slots:
    void onOkReleased();
};

#endif // NUMBERKEYBOARD_H
