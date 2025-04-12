#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "PasswordManager.h"
#include "QInputDialog"
#include "QMessageBox"

bool MainWindow::checkPassword()
{
    bool verify;
    QString enteredPassword = QInputDialog::getText(this, "Password required", "Enter the password owner : ", QLineEdit::Password, "",&verify);
    QString masterPassword = "Admin1234";
    if(!verify)
    {
        ui->Result_Display->setText("Wrong Password");
        return false;
    }
    if(masterPassword == enteredPassword)
    {
        return true;
    }
    else
    {
        QMessageBox::warning(this,"Access Denied", "Incorrect Password");
        return false;
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
        ui->lineEdit_InputUsername->clear();
        ui->lineEdit_InputPassword->clear();
    }
    else
    {
        ui->Result_Display->setText("Error ! Account not deleted.");
        ui->lineEdit_InputUsername->clear();
        ui->lineEdit_InputPassword->clear();
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
        ui->lineEdit_InputUsername->clear();
        ui->lineEdit_InputPassword->clear();
    }
    else
    {
        ui->Result_Display->setText("Error ! Password not changed.");
        ui->lineEdit_InputUsername->clear();
        ui->lineEdit_InputPassword->clear();
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
