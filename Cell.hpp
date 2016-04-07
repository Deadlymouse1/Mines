#ifndef CELL_HPP
#define CELL_HPP

#include <QVector>
#include <QObject>

class Cell: public QObject
{
    Q_OBJECT
public:
    enum Mark {
        MarkNothing,
        MarkFlagged,
        MarkQuestioned
    };

    Cell(int x, int y);

    int x() const { return m_x; }
    int y() const { return m_y; }
    Mark mark() const {return m_mark;}
    int minesAround() const;

    bool haveMark() const {return m_haveMark;}
    bool haveMine() const { return m_haveMine; }
    void setNeighbors(const QVector<Cell*> &neighbors);
    void setHaveMine(bool haveMine);

    bool isOpen() const { return m_open; }
    void open();

    void reset();
    void toggleMark();
    void tryToOpenAround();



    QVector<Cell*> getNeighbors() const;
signals:
    void opened(int x, int y);
    void markChanged(Mark newMark);

private:


    int m_x;
    int m_y;
    Mark m_mark;

    QVector <Cell*> m_neighbors;
    bool m_haveMark;
    bool m_haveMine;
    bool m_open;

};

#endif // CELL_HPP
