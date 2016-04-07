#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QGraphicsRectItem>
#include <QMainWindow>
//class QGraphicsRectItem;
namespace Ui {
class MainWindow;
}

class QGraphicsScene;
class Field;
class QGraphicsSimpleTextItem;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void NewGame();
    void resizeField(int width, int height);

protected:
    void resizeEvent(QResizeEvent *event);

protected slots:
    void updateSceneScale();
    void onFieldNumberOfFlagsChanged(int number);


private slots:
    void on_actionNew_Game_triggered();
    void onFieldStateChanged();
    void on_actionExit_triggered();

    void on_actionBeginner_triggered();

    void on_actionIntermediate_triggered();

    void on_actionExpert_triggered();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *m_scene;
    Field *m_field;
    QGraphicsSimpleTextItem *m_gameStateText;
    QGraphicsRectItem *m_fieldItem;
    QGraphicsRectItem *m_gameStateRect;
};

#endif // MAINWINDOW_H
