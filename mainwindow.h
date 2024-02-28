#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "user.h"
#include "network.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void LoginClicked();
    void FriendsClicked(int row, int col);
    void HomeClicked();
    void SuggestClicked(int row, int col);
    void AddFriendClicked();

private:
    Ui::MainWindow *ui;
    User *user;
    User *current_user;
    Network n;
};
#endif // MAINWINDOW_H
