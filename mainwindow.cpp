#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iostream"
#include "network.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->Login, &QPushButton::clicked, this, &MainWindow::LoginClicked);

    ui->EnterYourName->setText(QString::fromStdString("Enter your name: "));

    n.readUsers("/Users/vishal/SocialNetwork/users.txt");
    n.readPosts("/Users/vishal/SocialNetwork/posts.txt");

    connect(ui->Friends, &QTableWidget::cellClicked, this, &MainWindow::FriendsClicked);

    connect(ui->Home, &QPushButton::clicked, this, &MainWindow::HomeClicked);

    connect(ui->Suggest, &QTableWidget::cellClicked, this, &MainWindow::SuggestClicked);

    connect(ui->AddFriend, &QPushButton::clicked, this, &MainWindow::AddFriendClicked);


    ui->Home->setText(QString::fromStdString("Home"));
    ui->Home->hide();
    ui->Friends->hide();
    ui->Posts->hide();
    ui->Suggest->hide();
    ui->Fr->setText(QString::fromStdString("Friends"));
    ui->Fr->hide();
    ui->label_2->setText(QString::fromStdString("Friend Suggestions"));
    ui->label_2->hide();
    ui->FriendAdded->hide();
    ui->AddFriend->setText(QString::fromStdString("Add Friend"));
    ui->AddFriend->hide();
    ui->PLabel->hide();

}

void MainWindow::LoginClicked()
{   std::string name = ui->Username->toPlainText().toStdString();
    name.erase(std::remove(name.begin(), name.end(), '\n'), name.end());
    user = n.getUser(n.getId(name));
    current_user = user;
    if(n.inNetwork(n.getId(name)))
    {
        ui->Login->hide();
        ui->EnterYourName->hide();
        ui->Username->hide();
        ui->Profile->setText("My Profile");
        ui->Friends->setRowCount(n.getUser(n.getId(name))->getFriends().size());
        ui->Friends->setColumnCount(1);
        std::vector <std::string> friends;

        //std::cout << n.getUser(*current_user->getFriends().begin())->getName() << std::endl;
        //ui->Friends->setItem(0,1, new QTableWidgetItem(QString::fromStdString(n.getUser(*current_user->getFriends().begin())->getName())));
        for(auto f: current_user->getFriends())
        {
            friends.push_back(n.getUser(f)->getName());
        }
        for(auto c = 0; c < ui->Friends->rowCount(); c++)
        {
            //ui->Friends->setItem(c, 0, friends[c]);
            ui->Friends->setItem(c,0, new QTableWidgetItem(QString::fromStdString(friends[c])));
        }
        std::string res;
        ui->Friends->show();
        if(user == current_user)
        {   ui->PLabel->setText(QString::fromStdString("My Feed"));
            ui->PLabel->show();
            res += user->getPostsString(5, false);
            ui->Posts->setText(QString::fromStdString(res));
        }
        else
        {   ui->PLabel->setText(QString::fromStdString("My Feed"));
            ui->PLabel->show();
            ui->Posts->setText(QString::fromStdString(user->getPostsString(5, true)));
        }
        ui->Posts->show();
        int score;
        std::vector <int> r = n.suggestFriends(n.getId(name), score);
        std::vector <int>  suggest;
        for(int i = 0; i < n.numUsers(); i++)
        {
            if(n.getScore(i, n.getId(name)) == score)
            {
                suggest.push_back(i);
            }
        }
        ui->Suggest->setColumnCount(2);
        ui->Suggest->setRowCount(suggest.size());
        for(auto j = 0; j < suggest.size(); j++)
        {
            ui->Suggest->setItem(j, 0, new QTableWidgetItem(QString::fromStdString(n.getUser(suggest[j])->getName())));
            ui->Suggest->setItem(j, 1, new QTableWidgetItem(QString::fromStdString("Add Friend")));
        }
        ui->Suggest->show();
        ui->label_2->show();
        ui->Fr->show();
        ui->Home->show();

    }
    else
    {
        ui->EnterYourName->setText("Enter a valid name: ");
    }


}

void MainWindow::FriendsClicked(int row, int col)
{ //ui->Profile->setText();
    ui->FriendAdded->hide();
    current_user = n.getUser(n.getId((ui->Friends->item(row, col)->text()).toStdString()));
    if(current_user != user)
    {
        ui->Profile->setText(QString::fromStdString(current_user->getName() + "'s " + "profile: " ));
        ui->AddFriend->show();
        current_user->addFriend(user->getId());
    }
    else
    {
        ui->Profile->setText(QString::fromStdString("My Profile"));
    }

    ui->Friends->setRowCount(current_user->getFriends().size());
    ui->Friends->setColumnCount(1);

    std::vector <std::string> friends;
    for(auto f: current_user->getFriends())
    {
        friends.push_back(n.getUser(f)->getName());
    }
    for(auto c = 0; c < ui->Friends->rowCount(); c++)
    {

        ui->Friends->setItem(c,0, new QTableWidgetItem(QString::fromStdString(friends[c])));
    }
    if(current_user == user)
    {   ui->PLabel->setText(QString::fromStdString("My Feed"));
        ui->PLabel->show();
        ui->Posts->setText(QString::fromStdString(current_user->getPostsString(5, false)));
        int score;
        std::vector <int> r = n.suggestFriends(current_user->getId(), score);
        std::vector <int>  suggest;
        for(int i = 0; i < n.numUsers(); i++)
        {
            if(n.getScore(i, current_user->getId()) == score)
            {
                suggest.push_back(i);
            }
        }
        ui->Suggest->setColumnCount(2);
        ui->Suggest->setRowCount(suggest.size());
        for(auto j = 0; j < suggest.size(); j++)
        {
            ui->Suggest->setItem(j, 0, new QTableWidgetItem(QString::fromStdString(n.getUser(suggest[j])->getName())));
            ui->Suggest->setItem(j, 1, new QTableWidgetItem(QString::fromStdString("Add Friend")));
        }
        ui->Suggest->show();
        ui->label_2->show();
    }
    else
    {   ui->PLabel->setText(QString::fromStdString(current_user->getName() + "'s" + " Feed"));
        ui->PLabel->show();
        ui->Posts->setText(QString::fromStdString(current_user->getPostsString(5, true)));
        ui->Suggest->hide();
        ui->label_2->hide();
    }
    ui->Home->show();
    ui->Fr->show();

}

void MainWindow::HomeClicked()
{   ui->FriendAdded->hide();
    ui->AddFriend->hide();
    current_user = user;
    ui->Profile->setText(QString::fromStdString("My Profile"));
    ui->PLabel->setText(QString::fromStdString("My Feed"));
    ui->PLabel->show();
    ui->Posts->setText(QString::fromStdString(current_user->getPostsString(5, false)));
    std::vector <std::string> friends;

    ui->Friends->setRowCount(current_user->getFriends().size());
    ui->Friends->setColumnCount(1);
    for(auto f: current_user->getFriends())
    {
        friends.push_back(n.getUser(f)->getName());
    }
    for(auto c = 0; c < ui->Friends->rowCount(); c++)
    {

        ui->Friends->setItem(c,0, new QTableWidgetItem(QString::fromStdString(friends[c])));
    }
    int score;
    std::vector <int> r = n.suggestFriends(user->getId(), score);
    std::vector <int>  suggest;
    for(int i = 0; i < n.numUsers(); i++)
    {
        if(n.getScore(i, user->getId()) == score)
        {
            suggest.push_back(i);
        }
    }
    ui->Suggest->setColumnCount(2);
    ui->Suggest->setRowCount(suggest.size());
    for(auto j = 0; j < suggest.size(); j++)
    {
        ui->Suggest->setItem(j, 0, new QTableWidgetItem(QString::fromStdString(n.getUser(suggest[j])->getName())));
        ui->Suggest->setItem(j, 1, new QTableWidgetItem(QString::fromStdString("Add Friend")));
    }

    ui->Suggest->show();
    ui->Fr->show();
    ui->label_2->show();
}

void MainWindow::SuggestClicked(int row, int col)
{   if(col == 1)
    {
    User *u = n.getUser(n.getId((ui->Suggest->item(row, col - 1)->text()).toStdString()));
    if(u != user)
    {
        user->addFriend(u->getId());
        ui->FriendAdded->setText(QString::fromStdString(u->getName() + " has been added as a friend."));
        ui->FriendAdded->show();
        n.writeUsers("/Users/vishal/SocialNetwork/users.txt");
        n.writePosts("/Users/vishal/SocialNetwork/posts.txt");
    }
    }

}

void MainWindow::AddFriendClicked()
{
    if(current_user != user)
    {
        user->addFriend(current_user->getId());
        ui->FriendAdded->setText(QString::fromStdString(current_user->getName() + " has been added as a friend."));
        ui->FriendAdded->show();
        n.writeUsers("/Users/vishal/SocialNetwork/users.txt");
        n.writePosts("/Users/vishal/SocialNetwork/posts.txt");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
