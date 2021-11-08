#include <painter.h>

PaintScene::PaintScene(QObject *parent) : QGraphicsScene(parent)
{
    _tempPen = new QPen(_color, _brushSize);
}

PaintScene::~PaintScene()
{

}

void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    addLine(event->scenePos().x() - 5, event->scenePos().y() - 5, 10, 10, QPen(Qt::NoPen));
    _previousPoint = event->scenePos();
    Line example(_tempLine, *_tempPen);
    addUndoAction(example);
    _tempLine.clear();
}

void PaintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QLineF line(_previousPoint.x(), _previousPoint.y(), event->scenePos().x(), event->scenePos().y());
    QPen pen(_color,_brushSize,Qt::SolidLine,Qt::RoundCap);
    addLine(line, pen);
    _previousPoint = event->scenePos();
    _tempLine.append(line);
    _tempPen = new QPen(_color, _brushSize);
}

void PaintScene::addUndoAction(Line example)
{
    if (_lines.size() == 100) {
        _lines.removeFirst();
    }
    _lines.append(example);
}

void PaintScene::changeColor()
{
    QColor newColor = QColorDialog::getColor(_color);
    if (newColor != _color)
    {
        _color = newColor;
        emit colorChanged(_color.name());
    }
}

void PaintScene::changeBrushSize(int size)
{
    _brushSize = size;
}

void PaintScene::undo()
{
    clear();
    if (!_lines.isEmpty()) {
        for (int i = _lines.size() - 1; i > 0; i--)
            for (int x = 0; x < _lines[i].line.size(); x++)
                addLine(_lines[i].line[x], _lines[i].pen);
        _lines.removeLast();
    }
}

void PaintScene::redo()
{

}

Line::Line(QList<QLineF> l, QPen p) : line(l), pen(p) { }
