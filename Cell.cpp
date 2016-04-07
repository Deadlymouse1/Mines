#include "Cell.hpp"



Cell::Cell(int x, int y):QObject()
{
    m_x = x;
    m_y = y;
    m_haveMine = false;
    m_open = false;
    //m_haveMark = false;
    m_mark = MarkQuestioned;
    m_exploded = false;

}

int Cell::minesAround() const
{
    int mines = 0;
    for (Cell *cell : getNeighbors()) {
        if (cell->haveMine()) {
            ++mines;

        }
    }

    return mines;
}

void Cell::reveal()
{
    m_open = true;
}

void Cell::setHaveMine(bool haveMine)
{
    m_haveMine = haveMine;
}

void Cell::open()
{

    if(m_open == true)
    {
        return;
    }
    m_open = true;

    emit(opened(x(),y()));


    if( minesAround() == 0 && m_haveMine == false)
    {
        for (Cell *cell : getNeighbors())
        {
            cell->open();
        }
    }
    if(haveMine() == true){

        m_exploded = true;
    }

}

QVector<Cell *> Cell::getNeighbors() const
{

    return m_neighbors;
}
void Cell::reset(){
    m_haveMine = false;
    m_open = false;
    m_haveMark = true;
    m_mark = MarkQuestioned;


}
void Cell::toggleMark(){
    switch (m_mark) {
    case MarkNothing:
        m_mark = MarkFlagged;
        //m_haveMark = true;
        emit(markChanged(Mark()));
        break;
    case MarkFlagged:
        m_mark = MarkQuestioned;
        //m_haveMark = false;
        emit(markChanged(Mark()));
        break;
    case MarkQuestioned:
        m_mark = MarkNothing;
        emit(markChanged(Mark()));
        break;
    /*if (m_mark == 2) {
        m_mark = 0;
    } else {
        ++m_mark;
        if(m_mark == 1){
            m_haveMark = false;
        }
        else{
            m_haveMark = true;
        }*/



    }
}
void Cell::tryToOpenAround(){
    for (Cell *cell : getNeighbors()){
        if(cell->haveMark() == true ){
            cell->open();

        }
    }

}
void Cell::setNeighbors(const QVector<Cell*> &neighbors){
    m_neighbors = neighbors;
}

