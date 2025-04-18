#ifndef SHAPECONTROLLER_H
#define SHAPECONTROLLER_H

#pragma once

#include <QObject>
#include "mainwindow.h"

class ShapeController : public QObject {
    Q_OBJECT

public:
    explicit ShapeController(QObject* parent = nullptr) : QObject(parent) {}

signals:
    void ShapesReady(const alpha::vector<Shape*>& shapes);
};

#endif // SHAPECONTROLLER_H
