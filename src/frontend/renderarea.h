#pragma once

#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QMouseEvent>

#include "../objects/all_shapes.h" // Includes all shape types
#include "../objects/vector.h"    // For alpha::vector

/**
 * @file renderarea.h
 * @brief Defines the RenderArea class, a custom QWidget for drawing and interacting with 2D shapes.
 */

/**
 * @brief The RenderArea class provides a canvas for drawing 2D shapes.
 * @details This widget handles mouse events for selecting and moving shapes,
 *          and it uses QPainter to render shapes provided to it. It also manages
 *          the selection state of shapes and editing privileges.
 */
class RenderArea : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief RenderArea Constructor.
     * @param parent The parent QWidget, if any.
     */
    explicit RenderArea(QWidget *parent = nullptr);

    /**
     * @name Core Interaction and Display Management
     * @brief Handles user mouse input for selecting and manipulating shapes, 
     *        manages shape selection state, and updates display coordinates.
     */
    /** @{ */
    void mousePressEvent(QMouseEvent* event) override;          ///< Handles mouse press events to detect clicks on shapes for selection.
    void mouseMoveEvent(QMouseEvent* event) override;           ///< Handles mouse move events to drag selected shapes if editing is allowed.
    void mouseDoubleClickEvent(QMouseEvent* event) override;    ///< Handles mouse double-click events, e.g., for expanding shape details.
    void mouseReleaseEvent(QMouseEvent* event) override;        ///< Handles mouse release events to finalize a shape move operation.
    void resetSelection();                                      ///< Resets the selection state of all shapes, clearing the current selection.
    void updateShapeDisplayCoords(Shape* item, const QPoint& position) const; ///< Updates display coordinates of a shape's properties, typically in an associated view.
    /** @} */

    /**
     * @name Accessor Functions
     * @brief Getters for RenderArea properties and state.
     */
    /** @{ */
    const alpha::vector<Shape*>& getShapes() const;             ///< Returns a const reference to the vector of shapes being rendered.
    int  getShapeSelected() const;                              ///< Returns the tracker ID of the currently selected shape, or -1 if no shape is selected.
    int  getShapeSelectedIndex() const;                         ///< Returns the index of the currently selected shape in the `renderShapes` vector, or -1 if none.
    /** @} */

    /**
     * @name Mutator Functions
     * @brief Setters for RenderArea properties and state.
     */
    /** @{ */
    void setRenderShapes(const alpha::vector<Shape*>* renderShapes);    ///< Sets the vector of shapes to be rendered. The RenderArea does not own these shapes.
    void setShapeSelectedIndex(int newIndex);                           ///< Sets the index of the currently selected shape.
    void setEditPrivileges(bool edit);                                  ///< Sets whether shapes can be edited (e.g., moved) on the canvas.
    /** @} */

protected:
    /**
     * @brief Handles paint events to draw all shapes onto the widget.
     * @details Iterates through the `renderShapes` vector and calls the `Draw` method for each shape.
     * @param event The QPaintEvent object.
     */
    void paintEvent(QPaintEvent *event) override;

private:
    /**
     * @name Private Members
     * @brief Internal data members for managing state and rendered content.
     */
    /** @{ */
    const alpha::vector<Shape*>* renderShapes;                  ///< Pointer to the external vector holding shapes to be rendered.
    int shapeSelectedIndex;                                     ///< Index of the currently selected shape in `renderShapes`. -1 if no shape is selected. This ensures only one shape can be selected at a time.
    bool allowEditing = false;                                  ///< Flag indicating whether shapes can be moved/edited. Defaults to false.
    /** @} */
};
