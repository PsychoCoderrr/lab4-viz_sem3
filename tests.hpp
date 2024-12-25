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
    auto dist1 = result1.GetDistances();
    auto path1 = result1.GetPath();

    assert(dist1[3] == 9); // Проверяем стоимость пути
    assert(path1.get_size() == 4); // Проверяем длину пути
    assert(path1[0] == 0 && path1[1] == 2 && path1[2] == 1 && path1[3] == 3); // Проверяем сам путь

    // Тест 2: Кратчайший путь от вершины 0 к вершине 4
    auto result2 = graph.Dijkstra(0, 4);
    auto dist2 = result2.GetDistances();
    auto path2 = result2.GetPath();

    assert(dist2[4] == 5);
    assert(path2.get_size() == 3);
    assert(path2[0] == 0 && path2[1] == 2 && path2[2] == 4);

    // Тест 3: Кратчайший путь от вершины 0 к вершине 1
    auto result3 = graph.Dijkstra(0, 1);
    auto dist3 = result3.GetDistances();
    auto path3 = result3.GetPath();

    assert(dist3[1] == 7);
    assert(path3.get_size() == 3);
    assert(path3[0] == 0 && path3[1] == 2 && path3[2] == 1);
}

void TestTopologicalSort() {
    // Test 1: Acyclic graph with correct topological order
    Graph<int> graph1;
    graph1.AddVertex(0);
    graph1.AddVertex(1);
    graph1.AddVertex(2);
    graph1.AddVertex(3);
    graph1.AddArc(0, 1, 1);
    graph1.AddArc(1, 2, 1);
    graph1.AddArc(2, 3, 1);

    DynamicArray<int> result1;
    graph1.topologicalSort(result1);
    assert(result1.get_size() == 4);
    assert(result1[0] == 0);
    assert(result1[1] == 1);
    assert(result1[2] == 2);
    assert(result1[3] == 3);

    // Test 2: Graph with a cycle
    Graph<int> graph2;
    graph2.AddVertex(0);
    graph2.AddVertex(1);
    graph2.AddVertex(2);
    graph2.AddArc(0, 1, 1);
    graph2.AddArc(1, 2, 1);
    graph2.AddArc(2, 0, 1); // Cycle here

    DynamicArray<int> result2;
    graph2.topologicalSort(result2);
    assert(result2.get_size() == 0); // Topological sort should be impossible

    // Test 3: Empty graph
    Graph<int> graph3;

    DynamicArray<int> result3;
    graph3.topologicalSort(result3);
    assert(result3.get_size() == 0); // Empty graph, no topological order

    // Test 4: Graph with a single node
    Graph<int> graph4;
    graph4.AddVertex(0);

    DynamicArray<int> result4;
    graph4.topologicalSort(result4);
    assert(result4.get_size() == 1);
    assert(result4[0] == 0);

    // Test 5: Graph with multiple components
    Graph<int> graph5;
    graph5.AddVertex(0);
    graph5.AddVertex(1);
    graph5.AddVertex(2);
    graph5.AddVertex(3);
    graph5.AddArc(0, 1, 1);
    graph5.AddArc(2, 3, 1);

    DynamicArray<int> result5;
    graph5.topologicalSort(result5);
    assert(result5.get_size() == 4);
    assert((result5[0] == 0 && result5[1] == 1 && result5[2] == 2 && result5[3] == 3) ||
           (result5[0] == 2 && result5[1] == 3 && result5[2] == 0 && result5[3] == 1));
        

}

#endif //LAB4_TESTS
