#include "paintscene.h"
#include "romb.h"
#include "triangle.h"
#include "square.h"
#include"line.h"
#include "commands.h"
#include <QVector>
#include "figure.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>

PaintScene::PaintScene(QGraphicsView *view, QObject *parent) : QGraphicsScene(parent)
{
    this->view=view;
    undoStack = new QUndoStack(this);
    paintingColor=Qt::black;
    LineWeight=1;
    ItemsVec=new QVector<Figure*>();
}

PaintScene::~PaintScene()
{
}

int PaintScene::typeFigure() const
{
    return m_typeFigure;
}

void PaintScene::setTypeFigure(const int type)
{
    m_typeFigure = type;

}

void PaintScene::setColor(QColor color)
{
    paintingColor=color;
}

void PaintScene::setWeight(int Value)
{
    LineWeight=Value;
}

void PaintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

    EndPoint=event->scenePos();
    tempFigure->setEndPoint(EndPoint);


    this->update(QRectF(0,0,this->width(), this->height()));
}

void PaintScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    EndPoint=event->scenePos();
    tempFigure->setEndPoint(EndPoint);

       this->update();
       QUndoCommand *addCommand = new AddCommand(this,tempFigure,startPoint);
       undoStack->push(addCommand);

}


void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    switch (m_typeFigure) {
    case SquareType: {
        startPoint = event->scenePos();
        Square *item = new Square(startPoint,paintingColor,LineWeight);
        EndPoint = event->pos();
        item->setPos(EndPoint);
        tempFigure = item;


        break;
    }
    case RombType: {
      startPoint = event->scenePos();
      Romb *item = new Romb(startPoint,paintingColor,LineWeight);
      EndPoint = event->pos();
      item->setPos(event->pos());
      tempFigure = item;


      break;

    }
    case LineType: {
      startPoint = event->scenePos();
      Line *item = new Line(startPoint,paintingColor,LineWeight);
      EndPoint = event->pos();
      item->setPos(event->pos());
      tempFigure = item;

      break;

    }
    case TriangleType: {
        Figure *item = new Triangle(event->scenePos(),paintingColor,LineWeight);
        item->setPos(event->pos());
        tempFigure = item;

        break;
    }
    case EraserType :{ //this is the case for when you're selecting the eraser button and clicked on something
        //debug message, because i love it when clicking a button does something.
        qDebug()<<"shape is being deleted.";
        //this method gets the position of the mouse.
        QPointF mousePos(event->buttonDownScenePos(Qt::LeftButton).x(),
                             event->buttonDownScenePos(Qt::LeftButton).y());
        //this gets the items at this position and puts them in the list.
        const QVector<QGraphicsItem *> deletedItems = items(mousePos);
        //then we delete the item from the view and update.
        if(deletedItems.isEmpty()==false){
            qDebug()<<"you deleted :";
            //we delete the item from the vector (ItemsVec) , NOT DONE.


            //we add the command for the deletion to the undo stack.
            QUndoCommand *deleteCommand = new DeleteCommand(this,(Figure*)deletedItems[0],startPoint);
            undoStack->push(deleteCommand);

            //we add a command for the deletion (we  remove the first item in the list (i.e)element on top)
            removeItem(deletedItems[0]);

        }else qDebug()<<"no elements selcted";
        //we make the command for the delete and send it to undo stack, somehow.

        //debug message for the items vector.
//        for (int i=0;i<ItemsVec->size();i++){
//           qDebug()<<(*ItemsVec)[i]->name;
//        }
    }
    default:{
        Square *item = new Square(event->scenePos(),paintingColor,LineWeight);
        item->setPos(event->pos());
        tempFigure = item;

        break;
    }
    }
    this->addItem(tempFigure);

    }


