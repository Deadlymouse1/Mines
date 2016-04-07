#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include "Field.hpp"

#include "CellItem.hpp"

#include <QGLWidget>
#include <QGraphicsScene>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    m_gameStateText = new QGraphicsSimpleTextItem();
    QFont text = m_gameStateText->font();
    text.setPixelSize(32);
    m_gameStateText->setFont(text);
    m_gameStateText->setZValue(2);

    ui->setupUi(this);
    m_scene = new QGraphicsScene();
    m_field = new Field();
    m_field->setSize(8, 8);
    m_field->setNumberOfMines(10);

    QGLFormat f = QGLFormat::defaultFormat();
    f.setSampleBuffers(true);
    f.setSamples(4);
    m_scene->addItem(m_gameStateText);

    ui->graphicsView->setViewport(new QGLWidget(f));

    ui->graphicsView->setScene(m_scene);

    for (int y = 0; y < m_field->height(); ++y) {
        for (int x = 0; x < m_field->width(); ++x) {
            m_scene->addItem(new CellItem(m_field->cellAt(x, y)));
        }
    }
    NewGame();

    connect(m_field, SIGNAL(numberOfFlagsChanged(int)), this, SLOT(onFieldNumberOfFlagsChanged(int)));

    //m_field->generate(x,y);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QTimer::singleShot(0, this, SLOT(updateSceneScale()));
}

void MainWindow::updateSceneScale()
{
    ui->graphicsView->fitInView(m_scene->sceneRect(), Qt::KeepAspectRatio);
}

void MainWindow::onFieldNumberOfFlagsChanged(int number)
{
   ui->MinesLabel->setText(QString("%1/%2").arg(number).arg(m_field->numberOfMines()));
}
void MainWindow::NewGame()
{
    m_field->prepare();
    m_scene->update();
}
void MainWindow::on_actionNew_Game_triggered()
{
    NewGame();
}

void MainWindow::onFieldStateChanged()
{
    if (m_field->state() == Field::StateEnded) {
            m_gameStateText->setText("Game over");
            m_gameStateText->setPos((m_scene->width() - m_gameStateText->boundingRect().width()) / 2,
                                   (m_scene->height() - m_gameStateText->boundingRect().height()) / 2);
            m_gameStateText->setVisible(true);
        } else {
            m_gameStateText->setVisible(false);
        }
}

void MainWindow::on_actionExit_triggered()
{
    close();
}
