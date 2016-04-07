#ifndef FIELD_HPP
#define FIELD_HPP

#include <QVector>
#include <QObject>
class Cell;

class Field: public QObject
{
    Q_OBJECT
public:
    enum State {
        StateIdle,
        StateStarted,
        StateEnded
    };
    Field();


    void setSize(int width, int height);
    void setNumberOfMines(int number);

    void generate(int x,int y);
    State state() const {return m_state;}
    bool isGenerated() const { return m_generated;}
    int width() const { return m_width; }
    int height() const { return m_height; }
    int numberOfMines() const { return m_numberOfMines; }
    int markFlags() {return m_MarkFlags;}
    void lose();
    void prepare();
    void win();

    Cell *cellAt(int x, int y) const;
signals:
    void numberOfFlagsChanged(int);
    void changeState(State NewState);

protected slots:
    void onCellOpened(int x, int y);
    void onCellMarkChanged();
private:
    void setState(State NewState);
    QVector<Cell*> m_cells;
    int m_MarkFlags;
    int m_width;
    int m_height;
    bool m_generated;
    int m_numberOfMines;
    int m_numberOfOpenedCells;
    State m_state;
};

#endif // FIELD_HPP
