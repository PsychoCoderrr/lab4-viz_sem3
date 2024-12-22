#include <iostream>
#include "GraphParts.hpp"
#include "Graph.hpp"
#include "DynamicArray.hpp"
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
#include <QMessageBox>
#include "Graph.hpp"
#include "MainWindow.hpp"
#include "GraphScene.hpp"

GraphScene::GraphScene(Graph<int> *graph, QObject *parent)
    : QGraphicsScene(parent), graph(graph), currentVertexId(0), startVertex(nullptr) {}

void GraphScene::setGraph(Graph<int> *newGraph) {
    this->graph = newGraph;
    this->currentVertexId = 0;
    this->startVertex = nullptr;
}

void GraphScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QPointF pos = event->scenePos();
    QGraphicsItem *item = itemAt(pos, QTransform());

    if (!item) {
        // Добавляем вершину
        auto *vertex = addEllipse(pos.x() - 15, pos.y() - 15, 30, 30, QPen(Qt::black), QBrush(Qt::blue));
        vertex->setData(0, currentVertexId); // Устанавливаем ID вершины
        addText(QString::number(currentVertexId))->setPos(pos.x() - 5, pos.y() - 25); // Подписываем вершину
        graph->AddVertex(currentVertexId++);
    } else if (item->type() == QGraphicsEllipseItem::Type) {
        auto *clickedVertex = qgraphicsitem_cast<QGraphicsEllipseItem *>(item);

        if (!startVertex) {
            // Указываем начальную вершину
            startVertex = clickedVertex;
            startVertex->setBrush(Qt::red);
        } else {
            // Создаем дугу
            auto *endVertex = clickedVertex;
            if (startVertex != endVertex) {
                auto startId = startVertex->data(0).toInt();
                auto endId = endVertex->data(0).toInt();
                graph->AddArc(startId, endId, 1); // Добавляем дугу в граф
                auto *line = addLine(startVertex->rect().center().x() + startVertex->scenePos().x(),
                        startVertex->rect().center().y() + startVertex->scenePos().y(),
                        endVertex->rect().center().x() + endVertex->scenePos().x(),
                        endVertex->rect().center().y() + endVertex->scenePos().y(),
                        QPen(Qt::black));
                line->setData(0, startId);
                line->setData(1, endId);
            }
            startVertex->setBrush(Qt::blue);
            startVertex = nullptr;
        }
    }
}

void MainWindow::runDijkstra() {
    int startVertexId = 0; // Можно добавить возможность выбора начальной вершины
    int endVertexId = graph->GetSize() - 1; // Последняя вершина

    auto [dist, path] = graph->Dijkstra(startVertexId, endVertexId);

    if (path.get_size() < 2) {
        QMessageBox::information(this, "Результат", "Кратчайший путь не найден!");
        return;
    }

    // Подсвечиваем путь
    for (size_t i = 0; i < path.get_size() - 1; ++i) {
        int u = path[i];
        int v = path[i + 1];

        for (auto &item : scene->items()) {
            auto *line = qgraphicsitem_cast<QGraphicsLineItem *>(item);
            if (line && line->data(0).toInt() == u && line->data(1).toInt() == v) {
                line->setPen(QPen(Qt::red, 3)); // Красный цвет для пути
            }
        }
    }

    QMessageBox::information(this, "Результат", "Кратчайший путь найден!");
}

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent), graph(new Graph<int>()), scene(new GraphScene(graph, this)) {
    auto *layout = new QVBoxLayout(this);

    // Создаем сцену и вид
    view = new QGraphicsView(scene, this);
    layout->addWidget(view);

    // Кнопка для очистки
    auto *clearButton = new QPushButton("Очистить", this);
    layout->addWidget(clearButton);
    connect(clearButton, &QPushButton::clicked, this, &MainWindow::clearScene);
        
    auto *topSortButton = new QPushButton("Топологическая сортировка", this);
    layout->addWidget(topSortButton);
    connect(topSortButton, &QPushButton::clicked, this, &MainWindow::runTopologicalSort);

    auto *dijkstraButton = new QPushButton("Алгоритм Дейкстры", this);
    layout->addWidget(dijkstraButton);
    connect(dijkstraButton, &QPushButton::clicked, this, &MainWindow::runDijkstra);
        
    setLayout(layout);
    setWindowTitle("Редактор графа");
    resize(800, 600);
}

void MainWindow::runTopologicalSort() {
    DynamicArray<int> sortedVertices;
    
    if (graph->hasCycle()) {
        QMessageBox::warning(this, "Ошибка", "Граф содержит цикл! Топологическая сортировка невозможна.");
        return;
    }
    
    graph->topologicalSort(sortedVertices);
    
    // Перестраиваем граф
    scene->clear();

    for (size_t i = 0; i < sortedVertices.get_size(); ++i) {
        QPointF pos(i * 100 + 50, 100);
        auto *vertex = scene->addEllipse(pos.x() - 15, pos.y() - 15, 30, 30, QPen(Qt::black), QBrush(Qt::blue));
        vertex->setData(0, sortedVertices[i]);
        scene->addText(QString::number(sortedVertices[i]))->setPos(pos.x() - 5, pos.y() - 25);
    }

    QMessageBox::information(this, "Результат", "Топологическая сортировка выполнена!");
}

void MainWindow::clearScene() {
    scene->clear();
    delete graph;            // Удаляем старый граф
    graph = new Graph<int>(); // Создаем новый граф
    scene->clear();          // Удаляем все элементы со сцены
    scene->setGraph(graph);
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    return app.exec();
}
