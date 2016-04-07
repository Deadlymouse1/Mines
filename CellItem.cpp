#include "CellItem.hpp"

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSimpleTextItem>
#include <QPainter>

#include "Cell.hpp"

const int cellSize = 32;

CellItem::CellItem(Cell *cell) :
    QGraphicsItem()
{
    m_cell = cell;
    m_text = new QGraphicsSimpleTextItem(this);

    QFont f = m_text->font();
    f.setPixelSize(cellSize - 4);
    m_text->setFont(f);

    setPos(m_cell->x() * cellSize, m_cell->y() * cellSize);


}

QRectF CellItem::boundingRect() const
{
    return QRectF(0, 0, cellSize, cellSize);
}

void CellItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::HighQualityAntialiasing);

    painter->drawRect(0, 0, cellSize, cellSize);
    m_text->setPos((cellSize - m_text->boundingRect().width()) / 2, (cellSize - m_text->boundingRect().height()) / 2);
    static const int border = 4;
    if (m_cell->isOpen())
    {
        if (m_cell->haveMine())
        {
            m_text->setText("+");
            painter->fillRect(border, border, cellSize - border * 2, cellSize - border * 2, Qt::red);

        }

        else{if (m_cell->minesAround() != 0)
            {

                m_text->setText(QString::number(m_cell->minesAround()));
            }
            else{ m_text->setText(" ");}
        }
    }
    else{

        painter->fillRect(border, border, cellSize - border * 2, cellSize - border * 2, Qt::yellow);
        switch (m_cell->mark()) {
        case Cell::MarkNothing:
            m_text->setText("!");
            break;
        case Cell::MarkFlagged:
            m_text->setText("?");
            break;
        case Cell::MarkQuestioned:
            m_text->setText(" ");
            break;
        }

    }
}


void CellItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();
}

void CellItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if(m_cell->isOpen() == true){
            m_cell->tryToOpenAround();
        }
        else{
            m_cell->open();
        }

    }
    if (event->button() == Qt::RightButton) {
        m_cell->toggleMark();
    }


    update();
}
