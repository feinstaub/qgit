/*
    Author: Gregor Mitsch (C) 2014

    Copyright: See COPYING file that comes with this distribution
*/
#ifndef FILELISTTESTWINDOW_H
#define FILELISTTESTWINDOW_H

#include <QDialog>

class FileListTestDialogPrivate;

class FileListTestDialog : public QDialog
{
    Q_OBJECT

public:
    FileListTestDialog();
    virtual ~FileListTestDialog();

private:
    void createControls();

//     QMenuBar *menuBar;
//     QGroupBox *horizontalGroupBox;
//     QGroupBox *gridGroupBox;
//     QGroupBox *formGroupBox;
//     QTextEdit *smallEditor;
//     QTextEdit *bigEditor;
//     QLabel *labels[NumGridRows];
//     QLineEdit *lineEdits[NumGridRows];
//     QPushButton *buttons[NumButtons];
//     QDialogButtonBox *buttonBox;
//
//     QMenu *fileMenu;
//     QAction *exitAction;

private:
    FileListTestDialogPrivate *const d;
};


#endif
