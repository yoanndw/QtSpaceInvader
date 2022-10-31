#pragma once

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsView>
#include <QKeyEvent>
#include <QMainWindow>

#include "mainscene.h"

class MainWindow : public QGraphicsView
{
    Q_OBJECT

    MainScene* m_scene;

public:
    MainWindow(QWidget* parent = 0);
    ~MainWindow();

    void keyPressEvent(QKeyEvent* evt) override;
};


#endif // MAINWINDOW_H
