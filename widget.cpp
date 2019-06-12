#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent),
                                  ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_danceButton_clicked()
{
    if(wowClient != nullptr){
        ShowWindow(wowClient, SW_RESTORE);
        SetForegroundWindow(wowClient);
        UpdateWindow(wowClient);
    }

    sendMessageToClient("/dance");
}

void Widget::on_findWindowButton_clicked()
{
    // find WoW window
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QString s = codec->toUnicode("World of Warcraft");
    LPCWSTR lps = LPCWSTR(s.utf16());

    HWND hWnd = FindWindow(nullptr, lps);
    if(hWnd != nullptr) wowClient = hWnd;
}

void Widget::sendMessageToClient(const QString &msg)
{
    SendMessage(wowClient, WM_INPUTLANGCHANGEREQUEST, 2, 0x10331033);
    qDebug() << "current keyboard layout: " << LOWORD(GetKeyboardLayout(GetWindowThreadProcessId(wowClient, NULL)));
    SendMessage(wowClient, WM_INPUTLANGCHANGEREQUEST, 2, 0x10491049);
    qDebug() << "current keyboard layout: " << LOWORD(GetKeyboardLayout(GetWindowThreadProcessId(wowClient, NULL)));

    // 1049 - rus, 1033 - eng

    // enter
    keybd_event(VK_RETURN, 0, KEYEVENTF_EXTENDEDKEY | 0, 0 );
    keybd_event(VK_RETURN, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);

    // т = 0x4e
    keybd_event(0x4e, 0, KEYEVENTF_EXTENDEDKEY | 0, 0 );
    keybd_event(0x4e, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);

    // а
    keybd_event(0x46, 0, KEYEVENTF_EXTENDEDKEY | 0, 0 );
    keybd_event(0x46, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);

    // н
    keybd_event(0x59, 0, KEYEVENTF_EXTENDEDKEY | 0, 0 );
    keybd_event(0x59, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);

    // enter
    keybd_event(VK_RETURN, 0, KEYEVENTF_EXTENDEDKEY | 0, 0 );
    keybd_event(VK_RETURN, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
}

void Widget::on_forwardJumpButton_clicked()
{
    if(wowClient != nullptr){
        ShowWindow(wowClient, SW_RESTORE);
        SetForegroundWindow(wowClient);
        UpdateWindow(wowClient);
    }
    keybd_event(0x57, 0, KEYEVENTF_EXTENDEDKEY | 0, 0 );

    keybd_event(VK_SPACE, 0, KEYEVENTF_EXTENDEDKEY | 0, 0 );
    keybd_event(VK_SPACE, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);

    keybd_event(0x57, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
}
