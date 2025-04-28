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
    QString username = ui->lineEdit_InputUsername ->text();
    QString password = ui->lineEdit_InputPassword ->text();
    std::string usertemp = username.toStdString();
    std::string passwordtemp = password.toStdString();
    if(currentAction == "add")
    {
        QString path = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
        std::string string_path = path.toStdString();
        std::string new_string = string_path + "/Account.txt";
        std::ofstream PasswordFile(new_string, std::ios::app);
        std::string password_encrypted = Encrypt(passwordtemp);

        if(AddPassword(usertemp,password_encrypted))
        {
            if(PasswordFile.is_open())
            {
                PasswordFile << usertemp << ":" << password_encrypted<<std::endl;
                PasswordFile.close();
                ui->Result_Display->setText("Account added successfully !");
            }
            else
            {
                ui->Result_Display->setText("Error opening the file.");
            }
        }
        else
        {
            ui->Result_Display->setText("Error adding the account.");
        }
        ui->lineEdit_InputUsername->clear();
        ui->lineEdit_InputPassword->clear();
    }
    else if(currentAction == "delete")
    {
        QString account = ui->lineEdit_InputUsername->text();
        std::string accountstr = account.toStdString();
        std::string ligne;
        bool found = false;
        QString path = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
        std::string string_path = path.toStdString();
        std::string tempstring = path.toStdString() + "temp.txt";
        std::string new_string = string_path + "/Account.txt";
        std::ifstream file_read(new_string);
        std::ofstream file_write(tempstring);
        while(std::getline(file_read,ligne))
        {
            size_t pos = ligne.find(":");
            std::string username = ligne.substr(0,pos);
            std::string password = ligne.substr((ligne.find(":")+1));
            if(accountstr != username)
            {
                file_write << username << ":" << password << std::endl;
            }
            else
            {
                found = true;
            }
        }
        file_read.close();
        file_write.close();
        ui->lineEdit_InputUsername->clear();
        ui->lineEdit_InputPassword->clear();
            if(remove(new_string.c_str())!=0)
            {
                ui->Result_Display->setText("Error ! The file was not deleted.");
            }
            else if(rename(tempstring.c_str(),new_string.c_str()))
            {
                ui->Result_Display->setText("Error renaming the file.");
            }
            else
                if(found)
                {
                    ui->Result_Display->setText("Account deleted successfully.");
                }
                else
                {
                    ui-> Result_Display ->setText("Error ! Account not found.");
                }
    }
    else if(currentAction == "modify")
    {
        QString account = ui->lineEdit_InputUsername->text();
        if(account.isEmpty())
        {
            ui->Result_Display->setText("No username entered.");
            return;
        }
        bool ok;
        QString new_password = QInputDialog::getText(this, "New Password", "Enter the new password:",QLineEdit::Password,"",&ok);
        if(!ok||new_password.isEmpty())
        {
            ui->Result_Display->setText("No new password entered.");
            return;
        }
        std::string ligne;
        bool found = false;
        std::string accountstr = account.toStdString();
        std::string new_passwordstr = new_password.toStdString();
        std::string encrypted_password = Encrypt(new_passwordstr);
        QString path = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
        std::string string_path = path.toStdString();
        std::string tempstring = path.toStdString() + "temp.txt";
        std::string new_string = string_path + "/Account.txt";
        std::ifstream file_read(new_string);
        std::ofstream file_write(tempstring);
        while(std::getline(file_read,ligne))
        {
            size_t pos = ligne.find(":");
            std::string username = ligne.substr(0,pos);
            std::string password = ligne.substr(ligne.find(":")+1);
            if(username == accountstr)
            {
                file_write << username << ":" << encrypted_password <<std::endl;
                found = true;
            }
            else
            {
                file_write << ligne << std::endl;
            }
        }
        file_read.close();
        file_write.close();
        ui->lineEdit_InputUsername->clear();
        ui->lineEdit_InputPassword->clear();
        if(found)
        {
            ui->Result_Display->setText("Password modified successfully.");
            if(remove(new_string.c_str())!=0)
            {
                ui->Result_Display->setText("Error removing the file.");
            }
            else if(rename(tempstring.c_str(),new_string.c_str())!=0)
            {
                ui->Result_Display->setText("Error renaming the file.");
            }
        }
        else
        {
            ui->Result_Display->setText("No matching account found.");
        }
    }
}

void MainWindow::addPassword()
{
    currentAction = "add";
    ui->Result_Display->setText("Enter an username and a password.");
}

void MainWindow::deletePassword()
{
    currentAction = "delete";
    ui->Result_Display->setText("Enter an username.");
}

void MainWindow::modifyPassword()
{
    currentAction = "modify";
    ui->Result_Display->setText("Enter the username of the account you want to modify its password.");
}


bool MainWindow::showAllAccount()
{
    bool verify;
    QString inputPassword = QInputDialog::getText(this,"Password required", "Enter the password to display all the account",QLineEdit::Password,"",&verify);
    QString masterPassword = "Admin100";
    if(!verify)
    {
        ui->Result_Display->setText("Wrong Password.");
        return false;
    }
    if(inputPassword==masterPassword)
    {
        std::string ligne;
        QString path = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
        std::string string_path = path.toStdString() + "/Account.txt";
        std::ifstream file_read(string_path);
        if(!file_read)
        {
            ui->Result_Display->setText("Error opening the file.");
        }

        bool foundsomething = false;
        QString text;
        while(getline(file_read,ligne))
        {
            if(ligne.empty()) continue;
            size_t pos = ligne.find(":");
            std::string username = ligne.substr(0,pos);
            std::string password = ligne.substr(ligne.find(":") + 1);
            std::string decryptedPassword = Decrypt(password);
            text += "Username : " + QString::fromStdString(username) + "\n";
            text += "Password : " + QString::fromStdString(decryptedPassword) + "\n\n";
            foundsomething = true;
        }
        if(foundsomething)
        {
            ui->Result_Display->setText(text);
        }
        else
        {
            ui->Result_Display->setText("No account found, the file must be empty.");
        }
        return true;
    }
    else
    {
        QMessageBox::warning(this,"Error","Wrong Password");
        return false;
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
    connect(ui->showAllPassword, &QPushButton::clicked,this,&MainWindow::showAllAccount);
    connect(ui->modifyPassword,&QPushButton::clicked,this,&MainWindow::modifyPassword);
}

MainWindow::~MainWindow()
{
    delete ui;
}
