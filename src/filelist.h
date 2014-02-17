/*
	Author: Marco Costalba (C) 2005-2007

	Copyright: See COPYING file that comes with this distribution
*/
#ifndef FILELIST_H
#define FILELIST_H

#include <QTreeWidget>
#include "common.h"

class Domain;
class StateInfo;
class Git;

class FileList: public QTreeWidget {
Q_OBJECT
public:
	FileList(QWidget* parent);
	void setup(Domain* dm, Git* g);
	void update(const RevFile* files, bool newFiles);

signals:
	void contextMenu(const QString&, int);

public slots:
	void on_changeFont(const QFont& f);

protected:
	virtual void focusInEvent(QFocusEvent*);
	virtual void mousePressEvent(QMouseEvent*);
	virtual void mouseMoveEvent(QMouseEvent*);
	virtual void mouseReleaseEvent(QMouseEvent*);

private slots:
	void on_currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*);
	void on_customContextMenuRequested(const QPoint&);

private:
    void addItem(const QString& label, const QColor& clr);
    QString currentText();

    /**
     * clears file list contents and refills it with the given files
     */
	void refreshFileList(const RevFile* files);

	Domain* d;
	Git* git;
	StateInfo* st;
	QString dragFileName;
};

#endif
