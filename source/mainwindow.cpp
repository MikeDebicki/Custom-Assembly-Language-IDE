#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{   //sets up UI
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
    this->setWindowTitle(tr("SCAPES"));
    QDockWidget *dockWidget = new QDockWidget(tr("Console Output"), this);
    dockWidget->setAllowedAreas(Qt::BottomDockWidgetArea);
    dockWidget->setWidget(ui->plainTextEdit);
    //dockWidget->setWidget(ui->plainTextEdit->setReadOnly(true));
    //dockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
    addDockWidget(Qt::BottomDockWidgetArea, dockWidget);



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    currentFile.clear();
    ui->textEdit->setText(QString());
    ui->plainTextEdit->setPlainText(QString());
}

void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(filename);
    currentFile = filename;
    if (!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot open file : " + file.errorString());
        return;
    }
    setWindowTitle(filename);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    //ui->plainTextEdit->setPlainText(text);
    file.close();

}

void MainWindow::on_actionSave_triggered()
{
    QString fileName;
        // If there is no filename from before, get one.
        if (currentFile.isEmpty()) {
            fileName = QFileDialog::getSaveFileName(this, "Save");
            currentFile = fileName;
        } else {
            fileName = currentFile;
        }
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
            QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
            return;
        }
        setWindowTitle(fileName);
        QTextStream out(&file);
        QString text = ui->textEdit->toPlainText();
        out << text;
        file.close();
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionSaveAs_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save as");
    QFile file(filename);
    if (!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot save file : " + file.errorString());
        return;
    }
    currentFile = filename;
    setWindowTitle(filename);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionCompile_triggered()
{
 //Program *pgm = new Program();

 connect(&control,SIGNAL(send_print_errors_to_mainwindow(QString)),this,SLOT(update_compile_outputtext(QString)));
 ui->plainTextEdit->clear();
 //CompileControl *obj = new CompileControl();
 data = ui->textEdit->toPlainText();
 control.launch(&data);
 //pgm->parse(&data);
// pgm->serialize();

}


void MainWindow::update_compile_outputtext(QString errorText){
    qDebug()<<"I am HERE";
    ui->plainTextEdit->setReadOnly(true);
    ui->plainTextEdit->setPlainText(errorText);

}

void MainWindow::update_run_outputtext(QString errorText){
    qDebug()<<"I am HERE";

    error+=errorText+"\n";
    ui->plainTextEdit->setPlainText(error);

}

void MainWindow::on_actionRun_triggered()
{
    run_control = new RunControl;
    connect(run_control,SIGNAL(send_rdi_command_to_mainwindow()),this,SLOT(rdi_triggered()));
    connect(run_control,SIGNAL(send_output_to_mainwindow(QString)),this,SLOT(update_run_outputtext(QString)));
    QMessageBox::StandardButton response;
    response = QMessageBox::question(this,tr(" Hold up "), tr("Did you compile your code? If not, any "
                        "changes will not be reflected"), QMessageBox::Yes|QMessageBox::No);

    if (response == QMessageBox::No){

       QMessageBox::information(this, tr(" Why not? "), tr("Compile your code"), QMessageBox::Ok);
    }
    else {
//        on_actionCompile_triggered();
        //this is a new Program object, not the same one created in compile
        //approach to take: 1)_ create program so that compil and run have access to the same instance
        // 2) create anew Pgm instance that only reads from the SCAPES.json and creates obj from that vs recompiling

        //I COMMENTED THIS PART OUT BECAUSE I AM DOING THIS IN THE RUNCONTROL CLASS!!!!
        /*
        Program *pgm = new Program();
        pgm->read();

        */

        //triggers the RunControl
        run_control->launch();

    }
}

void MainWindow::rdi_triggered()
{

    n = QInputDialog::getInt(this,"Enter an integar","Integar",0,0,1000000);
    qDebug()<<"THIS IS ON OF RDI TRIGGERED"<<n;
    qDebug()<<"returning rdi from mainwindow = "<<n;
    run_control->passing_rdi_from_gui(&n);
}

int MainWindow::get_rdi_value()         // we need a getter to get the rdi value
{
  return n;
}
