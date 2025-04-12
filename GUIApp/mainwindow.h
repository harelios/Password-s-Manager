#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    bool checkPassword();


private:
    Ui::MainWindow *ui;
    void addPassword();
    void deletePassword();
    void modifyPassword();
};
#endif // MAINWINDOW_H
