#ifndef LAB4_TESTS
#define LAB4_TESTS

#include "Graph.hpp"
#include <cassert>

void TestDijkstra() {
    Graph<int> graph;

    // Добавляем вершины
    graph.AddVertex(0);
    graph.AddVertex(1);
    graph.AddVertex(2);
    graph.AddVertex(3);
    graph.AddVertex(4);

    // Добавляем рёбра
    graph.AddArc(0, 1, 10);
    graph.AddArc(0, 2, 3);
    graph.AddArc(1, 2, 1);
    graph.AddArc(1, 3, 2);
    graph.AddArc(2, 1, 4);
    graph.AddArc(2, 3, 8);
    graph.AddArc(2, 4, 2);
    graph.AddArc(3, 4, 7);
    graph.AddArc(4, 3, 9);

    // Тест 1: Кратчайший путь от вершины 0 к вершине 3
    auto result1 = graph.Dijkstra(0, 3);
    auto dist1 = result1.first;
    auto path1 = result1.second;

    assert(dist1[3] == 9); // Проверяем стоимость пути
    assert(path1.get_size() == 4); // Проверяем длину пути
    assert(path1[0] == 0 && path1[1] == 2 && path1[2] == 1 && path1[3] == 3); // Проверяем сам путь

    // Тест 2: Кратчайший путь от вершины 0 к вершине 4
    auto result2 = graph.Dijkstra(0, 4);
    auto dist2 = result2.first;
    auto path2 = result2.second;

    assert(dist2[4] == 5);
    assert(path2.get_size() == 3);
    assert(path2[0] == 0 && path2[1] == 2 && path2[2] == 4);

    // Тест 3: Кратчайший путь от вершины 0 к вершине 1
    auto result3 = graph.Dijkstra(0, 1);
    auto dist3 = result3.first;
    auto path3 = result3.second;

    assert(dist3[1] == 7);
    assert(path3.get_size() == 3);
    assert(path3[0] == 0 && path3[1] == 2 && path3[2] == 1);
}



#endif //LAB4_TESTS
