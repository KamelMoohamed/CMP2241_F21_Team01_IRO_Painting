#ifndef ROMB_H
#define ROMB_H
#include "square.h"

#include <QObject>
#include <QGraphicsItem>
#include "figure.h"

class Romb : public Figure
{
    Q_OBJECT

public:

    explicit Romb(QPointF point,QColor color,int LineWeight, QObject *parent = 0);
    ~Romb();

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};

#endif // ROMB_H