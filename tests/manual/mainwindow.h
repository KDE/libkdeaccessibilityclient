/*
    Copyright 2012 Frederik Gladhorn <gladhorn@kde.org>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) version 3, or any
    later version accepted by the membership of KDE e.V. (or its
    successor approved by the membership of KDE e.V.), which shall
    act as a proxy defined in Section 6 of version 3 of the license.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

#include <qmainwindow.h>
#include <qdebug.h>

#include "kdeaccessibilityclient/accessibleobject.h"
#include "accessibletree.h"

class MainWindow :public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    void listAccessibles();

private Q_SLOTS:
    void selectionChanged(const QModelIndex &current, const QModelIndex &);
    void focusChanged(const KAccessibleClient::AccessibleObject &object);
    void treeCustomContextMenuRequested(const QPoint &pos);
    void focusChanged(int,int);

private:
    Ui::MainWindow ui;
    AccessibleTree *m_model;
    KAccessibleClient::Registry *m_registry;
};

#endif
