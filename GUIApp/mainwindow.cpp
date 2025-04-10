#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "PasswordManager.h"

void MainWindow::checkPassword()
{
    QString enteredPassword = ui->lineEdit_InputPassword->text();
    QString masterPassword = "Admin1234";
    if(enteredPassword == masterPassword)
    {
        ui->Result_Display->setText("Acces granted !");
        //Continuer la fonction (C'est find Account)
    }
    else
    {
        ui->Result_Display->setText("Access refused.");
    }
}

void MainWindow::addPassword()
{
    ui->Result_Display->setText("Enter an username and a password.");
    QString username = ui->lineEdit_InputUsername->text();
    QString password = ui->lineEdit_InputPassword->text();
    std::string user = username.toStdString();
    std::string pass = password.toStdString();
    AddPassword(user,pass);
    ui->Result_Display->setText("Account added successfully !");
    ui->lineEdit_InputUsername->clear();
    ui->lineEdit_InputPassword->clear();
}


void MainWindow::deletePassword()
{
    ui->Result_Display->setText("Enter an username.");
    QString account = ui->lineEdit_InputUsername->text();
    std::string accountstr = account.toStdString();
    if(DeleteAccount(accountstr))
    {
        ui->Result_Display->setText("Account deleted successfully !");
    }
    else
    {
        ui->Result_Display->setText("Error ! Account not deleted.");
    }

}

void MainWindow::modifyPassword()
{
    ui->Result_Display->setText("Enter the username of the account you want to modify its password.");
    ui->Result_Display->setText("Enter the new password : ");
    QString account = ui->lineEdit_InputUsername->text();
    QString new_password = ui->lineEdit_InputPassword->text();
    std::string accountstr = account.toStdString();
    std::string new_passwordstr = new_password.toStdString();
    if(ModifyPassword(accountstr,new_passwordstr))
    {
        ui->Result_Display->setText("Password changed.");
    }
    else
    {
        ui->Result_Display->setText("Error ! Password not changed.");
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->findAccount, &QPushButton::clicked, this, &MainWindow::checkPassword);
    connect(ui->addAccount, &QPushButton::clicked, this, &MainWindow::addPassword);
    connect(ui->deletePassword, &QPushButton::clicked, this, &MainWindow::deletePassword);
}

MainWindow::~MainWindow()
{
    delete ui;
}
