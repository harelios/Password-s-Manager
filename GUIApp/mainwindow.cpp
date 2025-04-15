#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "PasswordManager.h"
#include "QInputDialog"
#include "QMessageBox"
#include <fstream>
#include <Qdir>
#include <QDebug>
#include <QStandardPaths>

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

void MainWindow::onOkCliqued()
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    std::string string_path = path.toStdString();
    std::string new_string = string_path + "/Account.txt";
    std::ofstream PasswordFile(new_string, std::ios::app);
    addPassword();
    std::string password_encrypted = Encrypt(passwordtemp);
    if(AddPassword(usertemp,password_encrypted))
    {
        if(PasswordFile.is_open())
        {
            PasswordFile << usertemp << ":" << password_encrypted << std::endl;
            PasswordFile.close();
            ui->Result_Display->setText("Account added successfully !");
        }
        else
        {
            ui->Result_Display->setText("Error opening the file.");
        }
    }
    else
    {     ui->Result_Display->setText("Error adding the account.");
    }
    ui->lineEdit_InputUsername->clear();
    ui->lineEdit_InputPassword->clear();
}

void MainWindow::addPassword()
{
    ui->Result_Display->setText("Enter an username and a password.");
    QString username = ui->lineEdit_InputUsername->text();
    QString password = ui->lineEdit_InputPassword->text();
    usertemp = username.toStdString();
    passwordtemp = password.toStdString();
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
    connect(ui->OKButton, &QPushButton::clicked, this, &MainWindow::onOkCliqued);
}

MainWindow::~MainWindow()
{
    delete ui;
}
