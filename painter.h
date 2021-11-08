#ifndef PAINTER_H
#define PAINTER_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QObject>
#include <QPointF>
#include <QTimer>
#include <QPushButton>
#include <QColorDialog>
#include <QColor>
#include <QPushButton>
#include <QSpinBox>
#include <QLineF>
#include <QList>
#include <QConstIterator>

class Line;
class PaintScene;

class PaintScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit PaintScene(QObject *parent = nullptr);
    ~PaintScene();
    void changeColor();
    void changeBrushSize(int);
    void undo();
    void redo();

private:
    QPointF _previousPoint;
    QColor _color;
    quint16 _brushSize = 10;
    QList<Line> _lines;

    QList<QLineF> _tempLine;
    QPen *_tempPen;

signals:
    void colorChanged(QString);

private:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void addUndoAction(Line);
};

class Line
{
public:
    Line(QList<QLineF> l, QPen p);
    QList<QLineF> line;
    QPen pen;
};

#endif // PAINTER_H
