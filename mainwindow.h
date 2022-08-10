#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString current;
    QTimer timer;
private slots:
    void chooseFile();
    void refresh();
    void getOutput();
    void runModelScript(QString script);
    void runScript(QString script);
};
#endif // MAINWINDOW_H
