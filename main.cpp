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
#include <QInputDialog>
#include <QMessageBox>
#include "Graph.hpp"
#include "MainWindow.hpp"
#include "GraphScene.hpp"
#include "tests.hpp"
#include "Path.hpp"
#include "HelpfulFunc.hpp"
#include <QFileDialog>

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


    
    
    if (event->button() == Qt::LeftButton) {
        if (!item) {
                auto *vertex = addEllipse(pos.x() - 15, pos.y() - 15, 30, 30, QPen(Qt::black), QBrush(Qt::blue));
                vertex->setData(0, currentVertexId); // Устанавливаем ID вершины
                addText(QString::number(currentVertexId))->setPos(pos.x() - 5, pos.y() - 25); // Подписываем вершину
                graph->AddVertex(currentVertexId++);
            } else if (item->type() == QGraphicsEllipseItem::Type) {
                auto *clickedVertex = qgraphicsitem_cast<QGraphicsEllipseItem *>(item);
        
                if (!startVertex) {
                    startVertex = clickedVertex;
                    startVertex->setBrush(Qt::red);
                } else {
                    auto *endVertex = clickedVertex;
                    if (startVertex != endVertex) {
                        auto startId = startVertex->data(0).toInt();
                        auto endId = endVertex->data(0).toInt();
                        
                        
                        bool ok;
                        int weight = QInputDialog::getInt(nullptr, "Вес дуги", "Введите вес дуги:", 1, 1, 100, 1, &ok);
                        if (!ok) {
                            startVertex->setBrush(Qt::blue);
                            startVertex = nullptr;
                            return;
                        }
                        graph->AddArc(startId, endId, weight);
                        QPointF startCenter = startVertex->rect().center() + startVertex->scenePos();
                        QPointF endCenter = endVertex->rect().center() + endVertex->scenePos();
                        auto *line = addLine(startCenter.x(), startCenter.y(), endCenter.x(), endCenter.y(), QPen(Qt::black));
                        line->setData(0, startId);
                        line->setData(1, endId);
        
                        QLineF lineVector(startCenter, endCenter);
                        double angle = std::atan2(-lineVector.dy(), lineVector.dx());
                        QPointF arrowP1 = endCenter - QPointF(std::sin(angle - M_PI / 3) * 10, std::cos(angle - M_PI / 3) * 10);
                        QPointF arrowP2 = endCenter - QPointF(std::sin(angle + M_PI / 3) * 10, std::cos(angle + M_PI / 3) * 10);
                        auto *arrow = addPolygon(QPolygonF() << endCenter << arrowP1 << arrowP2, QPen(Qt::black), QBrush(Qt::black));
                        
                        QPointF textPos = (startCenter + endCenter) / 2;
                        auto *text = addText(QString::number(weight));
                        text->setPos(textPos);
                    }
                    startVertex->setBrush(Qt::blue);
                    startVertex = nullptr;
                }
            }
        }
    else if (event->button() == Qt::RightButton) {
            if (item && item->type() == QGraphicsEllipseItem::Type) {
                auto *vertex = qgraphicsitem_cast<QGraphicsEllipseItem *>(item);

                if (!selectedStartVertex)
                {
                    selectedStartVertex = vertex;
                    selectedStartVertex->setBrush(Qt::green); // Подсвечиваем начальную вершину
                }
                
                else if (!selectedEndVertex)
                {
                    selectedEndVertex = vertex;
                    selectedEndVertex->setBrush(Qt::yellow); // Подсвечиваем конечную вершину

                    
                    emit verticesSelected(selectedStartVertex->data(0).toInt(),
                                          selectedEndVertex->data(0).toInt());
                    selectedStartVertex = nullptr;
                    selectedEndVertex = nullptr;
                }
                
                else {
                    
                    selectedStartVertex->setBrush(Qt::blue);
                    selectedEndVertex->setBrush(Qt::blue);

                    selectedStartVertex = vertex;
                    selectedEndVertex = nullptr;

                    selectedStartVertex->setBrush(Qt::green); // Подсвечиваем начальную вершину
                }
            }
        }
}

void MainWindow::runDijkstra() {
    if (selectedStartVertex == -1 || selectedEndVertex == -1) {
            QMessageBox::warning(this, "Ошибка", "Выберите начальную и конечную вершины для поиска!");
            return;
        }
        Path item = graph->Dijkstra(selectedStartVertex, selectedEndVertex);
    if (item.GetPath().get_size() < 2) {
            QMessageBox::information(this, "Результат", "Кратчайший путь не найден!");
            return;
        }
    SetShortestPathIntoFile(graph, item);
        for (size_t i = 0; i < item.GetPath().get_size() - 1; ++i) {
            int u = item.GetPath()[i];
            int v = item.GetPath()[i + 1];

            for (auto *item : scene->items()) {
                auto *line = qgraphicsitem_cast<QGraphicsLineItem *>(item);
                if (line && line->data(0).toInt() == u && line->data(1).toInt() == v) {
                    line->setPen(QPen(Qt::red, 3));
                    break;
                }
            }
        }

    QMessageBox::information(this, "Результат", "Кратчайший путь найден!");
}


MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent), graph(new Graph<int>()), scene(new GraphScene(graph, this)),selectedStartVertex(-1), selectedEndVertex(-1) {
    auto *layout = new QVBoxLayout(this);

    view = new QGraphicsView(scene, this);
    layout->addWidget(view);

    auto *clearButton = new QPushButton("Очистить", this);
    layout->addWidget(clearButton);
    connect(clearButton, &QPushButton::clicked, this, &MainWindow::clearScene);
        
    auto *topSortButton = new QPushButton("Топологическая сортировка", this);
    layout->addWidget(topSortButton);
    connect(topSortButton, &QPushButton::clicked, this, &MainWindow::runTopologicalSort);

    auto *dijkstraButton = new QPushButton("Алгоритм Дейкстры", this);
    layout->addWidget(dijkstraButton);
    connect(dijkstraButton, &QPushButton::clicked, this, &MainWindow::runDijkstra);
        
        auto *loadGraphButton = new QPushButton("Загрузить граф", this);
        layout->addWidget(loadGraphButton);
        connect(loadGraphButton, &QPushButton::clicked, this, &MainWindow::loadGraphFromFile);


    connect(scene, &GraphScene::verticesSelected, this, [this](int start, int end) {
        this->selectedStartVertex = start;
        this->selectedEndVertex = end;
    });
        
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
    
    
    scene->clear();
    QVector<QPointF> vertexPositions;

    for (size_t i = 0; i < sortedVertices.get_size(); ++i) {
        QPointF pos(i * 100 + 50, 100); // Позиция для вершины
        auto *vertex = scene->addEllipse(pos.x() - 15, pos.y() - 15, 30, 30, QPen(Qt::black), QBrush(Qt::blue));
        vertex->setData(0, sortedVertices[i]);
        scene->addText(QString::number(sortedVertices[i]))->setPos(pos.x() - 5, pos.y() - 25);

        vertexPositions.append(pos);
    }
    
    
    
    for (size_t i = 0; i < sortedVertices.get_size(); ++i) {
        int fromVertex = sortedVertices[i];

        
        for (const auto &arc : graph->Get(fromVertex).GetEdges()) {
            int toVertex = arc.GetLast();
            int fromIndex = -1, toIndex = -1;
            for (int j = 0; j < sortedVertices.get_size(); ++j) {
                if (sortedVertices[j] == fromVertex) {
                    fromIndex = j;
                }
                if (sortedVertices[j] == toVertex) {
                    toIndex = j;
                }
            }
            
            if (fromIndex != -1 && toIndex != -1) {
                
                QPointF startPos = vertexPositions[fromIndex];
                QPointF endPos = vertexPositions[toIndex];

                QPainterPath path(startPos);
                QPointF controlPoint((startPos.x() + endPos.x()) / 2,
                                     startPos.y() - 50 - abs(startPos.x() - endPos.x()) / 4);
                path.quadTo(controlPoint, endPos);

                scene->addPath(path, QPen(Qt::black));

                QPointF textPos = (startPos + endPos) / 2 + QPointF(0, -20);
                scene->addText(QString::number(arc.GetWeight()))->setPos(textPos);
            }
        }
    }

        QMessageBox::information(this, "Результат", "Топологическая сортировка выполнена!");
}


void MainWindow::loadGraphFromFile() {
    QString fileName = QFileDialog::getOpenFileName(this, "Открыть файл графа", "", "Текстовые файлы (*.txt)");
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл!");
        return;
    }

    QTextStream in(&file);

    QString line = in.readLine();
    QStringList vertices = line.split(',');

    clearScene();


    QVector<QGraphicsEllipseItem *> vertexItems;
    QVector<QPointF> vertexPositions;
    for (int i = 0; i < vertices.size(); ++i) {
        int vertexId = vertices[i].toInt();
        graph->AddVertex(vertexId);

        
        double angle = i * (2 * M_PI / vertices.size());
        QPointF pos(300 + 200 * std::cos(angle), 300 + 200 * std::sin(angle));
        auto *vertex = scene->addEllipse(pos.x() - 15, pos.y() - 15, 30, 30, QPen(Qt::black), QBrush(Qt::blue));
        vertex->setData(0, vertexId);
        scene->addText(QString::number(vertexId))->setPos(pos.x() - 5, pos.y() - 25);

        vertexItems.append(vertex);
        vertexPositions.append(pos);
    }

    while (!in.atEnd()) {
        line = in.readLine();
        QStringList edgeData = line.split(',');
        if (edgeData.size() != 3) {
            QMessageBox::warning(this, "Ошибка", "Неверный формат строки: " + line);
            continue;
        }

        int fromVertex = edgeData[0].toInt();
        int toVertex = edgeData[1].toInt();
        int weight = edgeData[2].toInt();

        graph->AddArc(fromVertex, toVertex, weight);

        QPointF startPos, endPos;
        for (int i = 0; i < vertexItems.size(); ++i) {
            if (vertexItems[i]->data(0).toInt() == fromVertex) startPos = vertexPositions[i];
            if (vertexItems[i]->data(0).toInt() == toVertex) endPos = vertexPositions[i];
        }

        addArrowWithWeight(startPos, endPos, weight);
    }

    file.close();

    scene->setGraph(graph);
    connect(scene, &GraphScene::verticesSelected, this, [this](int start, int end) {
        this->selectedStartVertex = start;
        this->selectedEndVertex = end;
    });
}

void MainWindow::addArrowWithWeight(QPointF start, QPointF end, int weight) {
    QLineF line(start, end);
    scene->addLine(line, QPen(Qt::black));
    
    double angle = std::atan2(-line.dy(), line.dx());
    QPointF arrowP1 = end - QPointF(std::sin(angle - M_PI / 3) * 10, std::cos(angle - M_PI / 3) * 10);
    QPointF arrowP2 = end - QPointF(std::sin(angle + M_PI / 3) * 10, std::cos(angle + M_PI / 3) * 10);
    scene->addPolygon(QPolygonF() << end << arrowP1 << arrowP2, QPen(Qt::black), QBrush(Qt::black));

    QPointF textPos = (start + end) / 2 + QPointF(0, -10);
    scene->addText(QString::number(weight))->setPos(textPos);
}







void MainWindow::clearScene() {
    scene->clear(); 
    
    graph = new Graph<int>();
    scene->setGraph(graph);
    
    selectedStartVertex = -1;
    selectedEndVertex = -1;
    connect(scene, &GraphScene::verticesSelected, this, [this](int start, int end) {
        this->selectedStartVertex = start;
        this->selectedEndVertex = end;
    });
    
}

int main(int argc, char *argv[]) {
    TestDijkstra();
    TestTopologicalSort();
    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    return app.exec();
}
