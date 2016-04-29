#ifndef FIELD_HPP
#define FIELD_HPP

#include <QVector>
#include <QObject>
class Cell;


class Field: public QObject
{
    Q_OBJECT
    Q_PROPERTY(int width READ width NOTIFY widthChanged)
    Q_PROPERTY(int height READ height NOTIFY heightChanged)

    Q_PROPERTY(State state READ state NOTIFY changeState)
public:
    enum State {
        StateIdle,
        StateStarted,
        StateEnded
    };
    Q_ENUM(State)
    Field();


    void setSize(int width, int height);
    void setNumberOfMines(int number);

    void generate(int x,int y);

    State state() const {return m_state;}

    bool isGenerated() const { return m_generated;}
    int width() const { return m_width; }
    int height() const { return m_height; }

    Q_INVOKABLE Cell *cellAt(int x, int y) const;

    int numberOfMines() const { return m_numberOfMines; }
    int markFlags() {return m_MarkFlags;}
    void lose();
    void prepare();
    void win();

signals:
    void numberOfFlagsChanged(int);
    void changeState(State NewState);

    void widthChanged(int newWidth);
    void heightChanged(int newHeight);

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
