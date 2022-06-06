#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include "ui_dialog.h"
//#include<QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    Fname="";
    ui->plainTextEdit->setPlainText("");
}


void MainWindow::on_actionOpen_triggered()
{
  QString f=QFileDialog::getOpenFileName(this,"Open a file");
  if(!f.isEmpty())
  {
      QFile sF(f);
      if(sF.open(QFile::ReadOnly|QFile::Text))
      {
          Fname=f;
          QTextStream in(&sF);
          QString text=in.readAll();
          sF.close();
          ui->plainTextEdit->setPlainText(text);
      }
  }
}


void MainWindow::on_actionSave_triggered()
{
 if(Fname=="")
 {
     on_actionSave_As_triggered();
     return;
 }
 QFile file(Fname);
 if(file.open(QFile::WriteOnly|QFile::Text))
 {
     QTextStream out(&file);
     out<<ui->plainTextEdit->toPlainText();
     file.flush();
     file.close();
 }
}


void MainWindow::on_actionSave_As_triggered()
{
    QString f=QFileDialog::getSaveFileName(this,"Save a file");
    if(!f.isEmpty())
    {
            Fname=f;
            on_actionSave_triggered();

    }
}


void MainWindow::on_actionCopy_triggered()
{
    ui->plainTextEdit->copy();
}


void MainWindow::on_actionCut_triggered()
{
    ui->plainTextEdit->cut();
}


void MainWindow::on_actionPaste_triggered()
{
    ui->plainTextEdit->paste();
}


void MainWindow::on_actionUndo_triggered()
{
    ui->plainTextEdit->undo();
}



void MainWindow::on_actionRedo_triggered()
{
    ui->plainTextEdit->redo();
}


void MainWindow::on_actionDefault_triggered()
{
    ui->plainTextEdit->setPlainText("\n@author:Dhananjay");
}

void MainWindow::on_actionBold_triggered()
{
    QTextCursor cursor = ui->plainTextEdit->textCursor();
    QTextCharFormat format;
    if(!cursor.charFormat().font().bold())
    {
         format.setFontWeight(QFont::Bold);
         cursor.mergeCharFormat(format);
    }
    else
    {
        format.setFontWeight(400);
        cursor.mergeCharFormat(format);
    }
}


void MainWindow::on_actionItalicize_triggered()
{
    QTextCursor cursor = ui->plainTextEdit->textCursor();
    QTextCharFormat format;
    if(!cursor.charFormat().font().italic())
    {
         format.setFontItalic(true);
         cursor.mergeCharFormat(format);
    }
    else
    {
        format.setFontItalic(false);
        cursor.mergeCharFormat(format);
    }
}


void MainWindow::on_actionUnderline_triggered()
{
    QTextCursor cursor = ui->plainTextEdit->textCursor();
    QTextCharFormat format;
    if(!cursor.charFormat().font().underline())
    {
         format.setFontUnderline(true);
         cursor.mergeCharFormat(format);
    }
    else
    {
        format.setFontUnderline(false);
        cursor.mergeCharFormat(format);
    }
}


void MainWindow::on_actionSuperscript_triggered()
{
    QTextCursor cursor=ui->plainTextEdit->textCursor();
    int StartPos=cursor.selectionStart();
    int EndPos=cursor.selectionEnd();
    cursor.setPosition(StartPos, QTextCursor::MoveAnchor);
    cursor.setPosition(EndPos, QTextCursor::KeepAnchor);
    QString word =cursor.selectedText();
    cursor.removeSelectedText();
    QString s="<sup>"+word+"</sup>";
    cursor.insertHtml(s);
}


void MainWindow::on_actionSubscript_triggered()
{
    QTextCursor cursor=ui->plainTextEdit->textCursor();
    int StartPos=cursor.selectionStart();
    int EndPos=cursor.selectionEnd();
    cursor.setPosition(StartPos, QTextCursor::MoveAnchor);
    cursor.setPosition(EndPos, QTextCursor::KeepAnchor);
    QString word =cursor.selectedText();
    cursor.removeSelectedText();
    QString s="<sub>"+word+"</sub>";
    cursor.insertHtml(s);
}


void MainWindow::on_pushButton_clicked()
{
    d=new Dialog(this);
    d->show();

}

