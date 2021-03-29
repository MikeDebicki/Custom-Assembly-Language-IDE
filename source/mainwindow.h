#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include "compilecontrol.h"
#include "program.h"
#include "runcontrol.h"
#include <QInputDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    //base class for QT object
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int get_rdi_value();

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionExit_triggered();

    void on_actionSaveAs_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionCut_triggered();

    void on_actionCompile_triggered();

     void update_compile_outputtext(QString errorText);

     void on_actionRun_triggered();

     void rdi_triggered();

     void update_run_outputtext(QString errorText);

private:
    Ui::MainWindow *ui;
    QString currentFile = "";
    QString data;
    CompileControl control;
    RunControl* run_control;
    int n;
    QString error="";
   // Program pgm;
    //Program* pgm=new Program();
};

#endif // MAINWINDOW_H
