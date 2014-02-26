/*
    Author: Gregor Mitsch (C) 2014

    Copyright: See COPYING file that comes with this distribution
*/

#include "filelisttestwindow.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QString>

#include "../filelist.h"

class FileListTestCase
{
public:
    FileList* fileList;
    QString testData; // TODO
};

class FileListTestDialogPrivate
{
public:
    void createTestCases()
    {
        {
            FileListTestCase testCase;
            testCase.fileList = 0;
            testCase.testData = "Test 1";
            testCaseList << testCase;
        }

        {
            FileListTestCase testCase;
            testCase.fileList = 0;
            testCase.testData = "Test 2";
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
    setLayout(mainLayout);

    // TODO: Create array of FileList instance by example e. g. in ui_patchview.h (find usages)

    foreach(FileListTestCase testCase, d->testCaseList)
    {
        QPushButton *pushButton = new QPushButton();
        pushButton->setText(testCase.testData);
        mainLayout->addWidget(pushButton);
    }
}
