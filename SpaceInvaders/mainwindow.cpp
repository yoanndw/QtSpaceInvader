#include "mainwindow.h"

#include <Qt>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "globalconsts.h"

MainWindow::MainWindow(QWidget* parent)
    : QGraphicsView(parent)
{
    m_scene = new MainScene(this);
    setWindowTitle("Space Invaders - yoannd");
    setScene(m_scene);
    setFixedSize(WIN_W + 10, WIN_H + 10);
    setAlignment(Qt::AlignLeft | Qt::AlignTop);
    setFocusPolicy(Qt::StrongFocus);
}

MainWindow::~MainWindow()
{

}

void MainWindow::keyPressEvent(QKeyEvent* evt)
{
    m_scene->keyPressEvent(evt);
}