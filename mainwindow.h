#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QtWidgets>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_as_triggered();

    void comboBox_addElements(QStringList &lst);

    void on_comboBox_activated(const QString &arg1);

    void on_actionLoad_case_triggered();

    void on_actionSave_case_triggered();

private:
    Ui::MainWindow *ui;
    QString currFile = "";
};
#endif // MAINWINDOW_H
