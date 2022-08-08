#ifndef NUMBERKEYBOARD_H
#define NUMBERKEYBOARD_H

#include <QWidget>
#include <QLineEdit>
class NumberKeyboard : public QFrame
{
    Q_OBJECT
public:
    explicit NumberKeyboard(QWidget *parent = 0,
                            Qt::WindowFlags f=Qt::Dialog);

    void attach(QWidget *w);
    bool install(QWidget *w);
    void uninstall(QWidget *w);
private:
    QWidget *atUi=nullptr;
    QLineEdit *inputEdit=nullptr;
    void initKeyboard();
    QList<QWidget*> targets;
protected:
    bool eventFilter(QObject *watched, QEvent *event);
signals:

private slots:
    void onOkReleased();
};

#endif // NUMBERKEYBOARD_H
