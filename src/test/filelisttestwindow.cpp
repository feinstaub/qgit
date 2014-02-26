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
#include <QDebug>
#include <QDir>

#include "../filelist.h"
#include "../domain.h"
#include "../revsview.h"
#include "../git.h"

class MainImpl;

class FileListTestCase {
public:
    // title of the test case
    QString title;

    // sha of qgit's own code
    QString sha1;

    // when given a diff between sha1 and sha2 is calculated
    QString sha2;
};

class FileListTestDialogPrivate {
public:
    void createTestCases() {
        {
            FileListTestCase testCase;
            testCase.title = "Test 1 / simple / add, mod, remove";
            testCase.sha1 = "0012ed7f7648b7bad794e8c58307cb2767c67fb8";
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

class MockDomain : public Domain {
public:
    // with default ctor we would fail later
    // isMain must be true otherwise FileHistory will not be inited
    MockDomain(MainImpl* mi, Git* g) : Domain(mi, g, true) { };

protected:
    virtual bool doUpdate(bool force) {
        qDebug() << QString("doUpdate: force=%1").arg(force);
    }
};

FileListTestDialog::FileListTestDialog() : d(new FileListTestDialogPrivate) {
    d->createTestCases();
    createControls();
}

FileListTestDialog::~FileListTestDialog() {
    delete d;
}

void FileListTestDialog::createControls() {
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
    foreach(FileListTestCase testCase, d->testCaseList) {
        qDebug() << QString("testCase: %1").arg(testCase.title);

        QGroupBox *groupBox = new QGroupBox(testCase.title);
        QVBoxLayout *vBox = new QVBoxLayout();
        groupBox->setLayout(vBox);

        //QLabel *label = new QLabel();
        //label->setText(testCase.testData);
        //vBox->addWidget(label);

        FileList *fileList = new FileList(this);
        //QScopedPointer<Domain> domain();
        // Domain* domain = new Domain(0, 0, false); // is abstract

        Git* git = new Git(this);
        Domain* domain = new MockDomain(0, git); // 1. must be first

        fileList->setup(domain, git);

        {
            QDir qgitSrcDir = QDir::current();
            qgitSrcDir.cdUp();
            QString qgitSrcPath = qgitSrcDir.absolutePath(); // assuming the build is done in a subfolder of the source tree
            bool quit; // todo: why?
            qDebug() << qgitSrcPath;
            //git->stop(false);
            Q_ASSERT(git->init(qgitSrcPath, false, 0, false, &quit)); // 2. must be next
        }


        vBox->addWidget(fileList);

        mainLayout->addWidget(groupBox, row, col);
        col++;
        if (col > 1) {// two columns
            col = 0;
            row++;
        }

        delete domain; // needed?
    }
}
