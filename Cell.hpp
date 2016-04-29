#ifndef CELL_HPP
#define CELL_HPP

#include <QVector>
#include <QObject>

class Cell: public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool haveMine READ haveMine NOTIFY haveMineChanged)
    Q_PROPERTY(bool isOpen READ isOpen NOTIFY opened)
    Q_PROPERTY(bool exploded READ isExploded NOTIFY isExplodedChanged)
    Q_PROPERTY(int minesAround READ minesAround NOTIFY minesAroundChanged)
    Q_PROPERTY(Mark mark READ mark NOTIFY markChanged)
public:
    enum Mark {
        MarkFlagged,
        MarkQuestioned,
        MarkNothing,
    };



    Q_ENUM(Mark)

    Cell(int x = 0, int y = 0);

    int x() const { return m_x; }
    int y() const { return m_y; }
    Mark mark() const {return m_mark;}
    int minesAround() const;

    bool haveMark() const {return m_haveMark;}
    bool haveMine() const { return m_haveMine; }

    void reveal();
    bool isExploded() const {return m_exploded;}

    void setNeighbors(const QVector<Cell*> &neighbors);
    void setHaveMine(bool haveMine);


    bool isOpen() const { return m_open; }

    void reset();
    void toggleMark();
    void tryToOpenAround();



    QVector<Cell*> getNeighbors() const;
public slots:
    void open();
signals:


    void opened(int x, int y);
    void markChanged(Mark newMark);

    void isOpenChanged(bool newIsOpen);
    void haveMineChanged(bool newHaveMine);
    void isExplodedChanged(bool newIsExploded);
    void minesAroundChanged(int newMinesAround);

private:


    int m_x;
    int m_y;
    Mark m_mark;

    QVector <Cell*> m_neighbors;
    bool m_haveMark;
    bool m_haveMine;
    bool m_open;
    bool m_exploded;
};

#endif // CELL_HPP
