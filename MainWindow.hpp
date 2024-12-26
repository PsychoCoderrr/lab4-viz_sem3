#ifndef LAB4_MAIN_WINDOW
#define LAB4_MAIN_WINDOW
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QVBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QGraphicsSceneMouseEvent>
class GraphScene;

class MainWindow : public QWidget {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void clearScene();
    void runTopologicalSort();
    void runDijkstra();
    void addArrowWithWeight(QPointF start, QPointF end, int weight);
    void loadGraphFromFile();
private:
    Graph<int> *graph;
    GraphScene *scene;
    QGraphicsView *view;
    int selectedStartVertex = -1;
    int selectedEndVertex = -1;
};

#endif //LAB4_MAIN_WINDOW
