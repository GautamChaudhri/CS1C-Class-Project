#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "renderarea.h"
#include "../backend/Parser.h"
#include "../backend/ApiClient.h"
#include <QApplication>
#include <QGridLayout>
#include "ui_mainwindow.h"
#include "../backend/UserAccount.h"
#include <QComboBox>
#include <QFile>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    MainWindow(QWidget *parent, const alpha::vector<Shape*>* renderedShapes, const UserAccount* currUser);
    ~MainWindow();

    void setShapes2(const alpha::vector<Shape*>& shapes);

    void drawShapes() const;

    void shapes_to_treeWidget();

signals:
    // These signals connect to the slots in the AppDriver class
    void shapeAdded(Shape* shape);
    void shapeChanged(Shape* shape, QString key, int vaue);
    void shapeDeleted(int trackerId);
    void deleteAllShapes();

public slots:
    // Signals for these slots come from RenderAreaManager class
    void onRenderAreaChanged();
    void onRenderAreaNotChanged(const QString& message);
    void showRenderStatusMessage(const QString &message);

private slots:

    void onToggleStyle(bool checked = true);

    void on_actionnew_line_button_triggered();
    void on_actionnew_square_button_triggered();
    void on_actionnew_rectange_button_triggered();
    void on_actionnew_circle_button_triggered();
    void on_actionnew_ellipse_button_triggered();
    void on_actionnew_polyline_button_triggered();
    void on_actionnew_polygon_button_triggered();
    void on_actionnew_text_button_triggered();
    void on_actionremove_shape_button_triggered();
    
    // For modifying shape
    void onTreeWidgetItemChanged(QTreeWidgetItem*, int column);

private:
    Ui::MainWindow *ui;
    RenderArea *renderArea;

    const alpha::vector<Shape*>* renderShapes;      // Holds currently renderedShapes
    const UserAccount* currUser;

    void addToShapeTree(Shape* shape);

    QString loadStyleSheet(const QString &path);

    QComboBox* createShapeTypeComboBox(const QString& currentShapeType);
    QComboBox* createPenStyleComboBox(int currentPenStyle);
    QComboBox* createBrushStyleComboBox(int currentBrushStyle);

    QComboBox* createAlignmentComboBox(AlignmentFlag currentAlignment);
    QComboBox* createFontComboBox(QFont currentFont);
    QComboBox* createFontStyleComboBox(int currentFontStyle);
    QComboBox* createFontWeightComboBox(QFont::Weight currentFontWeight);

};
#endif // MAINWINDOW_H
