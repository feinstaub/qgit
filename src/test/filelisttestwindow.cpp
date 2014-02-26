/*
    Author: Gregor Mitsch (C) 2014

    Copyright: See COPYING file that comes with this distribution
*/

#include "filelisttestwindow.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QString>
#include <QLabel>
#include <QGroupBox>

#include "../filelist.h"

class FileListTestCase
{
public:
    //FileList* fileList;
    QString title;
    QString testData; // TODO
};

class FileListTestDialogPrivate
{
public:
    void createTestCases()
    {
        {
            FileListTestCase testCase;
            testCase.title = "Test 1";
            testCaseList << testCase;
        }

        {
            FileListTestCase testCase;
            testCase.title = "Test 2";
            testCaseList << testCase;
        }

        {
            FileListTestCase testCase;
            testCase.title = "Test 3";
            testCaseList << testCase;
        }

        {
            FileListTestCase testCase;
            testCase.title = "Test 4";
            testCaseList << testCase;
        }

        {
            FileListTestCase testCase;
            testCase.title = "Test 5";
            testCaseList << testCase;
        }

    }

public:
    QList<FileListTestCase> testCaseList;
};


FileListTestDialog::FileListTestDialog() : d(new FileListTestDialogPrivate)
{
    d->createTestCases();
    createControls();
}

FileListTestDialog::~FileListTestDialog()
{
    delete d;
}

void FileListTestDialog::createControls()
{
    this->setWindowTitle(QString("qgit FileList Test Dialog - Test case count: %1").arg(d->testCaseList.count()));
    this->setMinimumSize(500, 500);

    // taken from http://qt-project.org/doc/qt-4.8/layouts-basiclayouts.html
    //QVBoxLayout *mainLayout = new QVBoxLayout();
    QGridLayout *mainLayout = new QGridLayout();
    //mainLayout->set
    setLayout(mainLayout);

    // TODO: Create array of FileList instance by example e. g. in ui_patchview.h (find usages)

    int row = 0;
    int col = 0;
    foreach(FileListTestCase testCase, d->testCaseList)
    {
        QGroupBox *groupBox = new QGroupBox(testCase.title);
        QVBoxLayout *vBox = new QVBoxLayout();
        groupBox->setLayout(vBox);

        //QLabel *label = new QLabel();
        //label->setText(testCase.testData);
        //vBox->addWidget(label);

        FileList *fileList = new FileList(this);
        vBox->addWidget(fileList);

        mainLayout->addWidget(groupBox, row, col);
        col++;
        if (col > 1) // two columns
        {
            col = 0;
            row++;
        }
    }
}
