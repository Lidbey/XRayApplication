#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <QDebug>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->image->setPixmap(QPixmap("default.jpg"));
    timer.setSingleShot(true);
    connect(&timer, &QTimer::timeout, this, &MainWindow::refresh);
    connect(ui->pSimpleButton, &QPushButton::clicked, this, [=](){runModelScript("SimpleModel");});
    connect(ui->pLogisticButton, &QPushButton::clicked, this, [=](){runModelScript("LogisticRegression");});
    connect(ui->pSupportButton, &QPushButton::clicked, this, [=](){runModelScript("SVMModel");});
    connect(ui->sharpenButton, &QPushButton::clicked, this, [=](){runScript("SharpenPhoto");});
    connect(ui->gammaButton, &QPushButton::clicked, this, [=](){runScript("AdjustGamma");});
    connect(ui->logButton, &QPushButton::clicked, this, [=](){runScript("AdjustLog");});
    connect(ui->sigmoidButton, &QPushButton::clicked, this, [=](){runScript("AdjustSigmoid");});
    connect(ui->intensButton, &QPushButton::clicked, this, [=](){runScript("RescaleIntensity");});
    connect(ui->eqhistButton, &QPushButton::clicked, this, [=](){runScript("EqualizeHist");});
    connect(ui->fileButton, &QPushButton::clicked, this, &MainWindow::chooseFile);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::chooseFile()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Open image"), ".", tr("Image Files (*.jpg *.jpeg *.png *.bmp)"));
    if(file!="")
    {
        QPixmap pixmap(file);
        int w = ui->image->width();
        int h = ui->image->height();
        ui->image->setPixmap(pixmap.scaled(w,h, Qt::KeepAspectRatio));
        ui->imageLabel->setPalette(QPalette());
        ui->imageLabel->setText("Not yet predicted");
    }
}

void MainWindow::refresh()
{
    current="";
}

void MainWindow::getOutput()
{
    if(current=="") return;

    if (     current=="SimpleModel" ||
             current=="LogisticRegression" ||
             current=="SVMModel")
    {
        QProcess* process = dynamic_cast<QProcess*>(sender());
        QString out = process->readAllStandardOutput();
        double val = out.simplified().toDouble();
        double colour = val * 255.0;
        QPalette palette;
        palette.setColor(QPalette::Window, QColor((colour)*0.66, (255-colour)*0.66, 0));
        palette.setColor(QPalette::WindowText, QColor(255,255,255));
        ui->imageLabel->setText(val>0.5?"Sick":"Healthy");
        ui->imageLabel->setAutoFillBackground(true);
        ui->imageLabel->setPalette(palette);
        sender()->deleteLater();
    }
    else
    {
        ui->image->setPixmap(QPixmap("./PythonImage.jpg"));
        sender()->deleteLater();
        ui->imageLabel->setPalette(QPalette());
        ui->imageLabel->setText("Not yet predicted");
    }
}

void MainWindow::runModelScript(QString script)
{
    ui->imageLabel->setPalette(QPalette());
    ui->imageLabel->setText("Not yet predicted");
    runScript(script);
}

void MainWindow::runScript(QString script)
{
    current = script;
    const QPixmap* pixmap = ui->image->pixmap();
    pixmap->save("./GUIImage.jpg");
    timer.start(15000);
    QProcess* process = new QProcess(this);
    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &MainWindow::getOutput);
    process->start("python", {script+".py", "./GUIImage.jpg"});
}

