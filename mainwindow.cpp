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
        if (text == "[")                     // TODO: В принципе бесполезно на данном этапе
            emit comboBox_addElements();
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

void MainWindow::comboBox_addElements()
{
    QStringList lst;
    lst << "Linux" << "Windows" << "MacOSX" << "Android";  // TODO: сделать загрузку вариантов из нужных файлов для нужных файлов
    ui->comboBox->addItems(lst);
}


void MainWindow::on_comboBox_activated(const QString &arg1)
{
    ui->textEdit->insertPlainText(arg1);
}
