#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>

#include <QtWinExtras>
#include <windows.h>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_danceButton_clicked();

    void on_findWindowButton_clicked();

    void sendMessageToClient(const QString &msg);

    void on_forwardJumpButton_clicked();

private:
    Ui::Widget *ui;

    HWND                    wowClient;
    LPDWORD                 wowProcessId;
    DWORD                   wowThreadId;
};

#endif // WIDGET_H
