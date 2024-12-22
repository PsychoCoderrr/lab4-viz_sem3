#ifndef LAB4_GRAPH_SCENE
#define LAB4_GRAPH_SCENE
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsSceneMouseEvent>
#include "Graph.hpp"

class GraphScene : public QGraphicsScene {
    Q_OBJECT
public:
    explicit GraphScene(Graph<int> *graph, QObject *parent = nullptr);
    void setGraph(Graph<int> *newGraph);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    
private:
    Graph<int> *graph;
    int currentVertexId;
    QGraphicsEllipseItem *startVertex;
};

#endif //LAB4_GRAPh_SCENE
