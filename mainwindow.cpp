#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /*this->setCentralWidget(ui->textEdit);
     * TODO: Настроить размещение элементов */
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    currFile.clear();
    ui->textEdit->setText(QString());

}

void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(filename);
    currFile = filename;
    if(!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file : " + file.errorString());
        return;
    }
    setWindowTitle(filename);
    QTextStream in(&file);
    for (int i = 0; !in.atEnd(); i++) {
        QString text = in.read(1);
        ui->textEdit->insertPlainText(text);
        if (text == "[")
            emit comboBoxTest();
    }
    file.close();
}

void MainWindow::on_actionSave_as_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save as");
    QFile file(filename);
    if(!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file : " + file.errorString());
        return;
    }
    currFile = filename;
    setWindowTitle(filename);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void MainWindow::comboBoxTest()
{
    QStringList lst;
    lst << "Linux" << "Windows" << "MacOSX" << "Android";
    ui->comboBox->addItems(lst);

    /*
    QStringList lst;
    QComboBox lwg;
    lst << "Linux" << "Windows" << "MacOSX" << "Android";
    lwg.addItems(lst);
    lwg.show();
    qDebug("Open");*/
}

