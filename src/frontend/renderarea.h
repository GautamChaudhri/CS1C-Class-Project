#pragma once

#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QMouseEvent>

#include "../objects/all_shapes.h"
#include "../objects/vector.h"

/**
 * @brief The RenderArea class
 *
 * @details The render area which shape objects draw to using paintEvent
 */
class RenderArea : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief RenderArea Constructor
     * @param parent - QWidget which render area belongs to
     */
    RenderArea(QWidget *parent = nullptr);

    /**
     * @brief mousePressEvent - Handles mouseClicks
     * @param event
     */
    void mousePressEvent(QMouseEvent* event) override;

    /**
     * @brief mouseMoveEvent - Handles the mouse being clicked and dragged
     * @param event
     */
    void mouseMoveEvent(QMouseEvent* event) override;

    /**
     * @brief mouseDoubleClickEvent - Handles mouse double clicking
     * @param event
     */
    void mouseDoubleClickEvent(QMouseEvent* event) override;

    /**
     * @brief mouseReleaseEvent - Handles mouse being released
     * @param event
     */
    void mouseReleaseEvent(QMouseEvent* event) override;

    /**
     * @brief resetSelection - sets the shapeSelectedIndex to -1 for all objects in renderShapes
     */
    void resetSelection();

    /**
     * @brief updateShapeDisplayCoords - Updated the coords of a shape when it is moved
     * @param item - Shape being updated
     * @param position - Coords of new position
     */
    void updateShapeDisplayCoords(Shape* item, const QPoint& position) const;

    /// Accessor Functions
    const alpha::vector<Shape*>& getShapes() const;
    int  getShapeSelected() const;
    int  getShapeSelectedIndex() const;

    /// Mutator Functions
    void setRenderShapes(const alpha::vector<Shape*>* renderShapes);
    void setShapeSelectedIndex(int newIndex);
    void setEditPrivileges(bool edit);

protected:
    /**
     * @brief paintEvent - Paints to the render area
     * @param event
     */
    void paintEvent(QPaintEvent *event) override;

private:
    const alpha::vector<Shape*>* renderShapes; ///< Holds currently renderedShapes
    int shapeSelectedIndex; ///< This is the vector index of the current shape selected, this is done so we prevent multiple shapes being selected at once
    bool allowEditing = false; ///< by default you cannot edit shapes
};
