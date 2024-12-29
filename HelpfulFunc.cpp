#include "HelpfulFunc.hpp"

void SetShortestPathIntoFile(Graph<int>* graph, Path<int>& item) {
    std::ofstream outFile("/Users/vitalijkoldasev/Desktop/laboratories_3_sem/try_qt/try_qt/output.txt");
    if (!outFile.is_open()) {
        throw std::runtime_error("Unable to open output file");
    }
    
    outFile << "Vertices: ";
    for (int i = 0; i < graph->GetSize(); i++) {
        outFile << graph->Get(i).GetName();
        if (i != graph->GetSize() - 1) {
            outFile << ", ";
        }
    }
    outFile << std::endl;
    
    for (int i = 0; i < graph->GetSize(); i++) {
        const Vertex<int>& vertex = graph->Get(graph->Get(i).GetName());
        for (const auto& edge : vertex.GetEdges()) {
            outFile << edge.GetFirst() << " -> " << edge.GetLast() << " : " << edge.GetWeight() << std::endl;
        }
    }
    
    const auto& path = item.GetPath();
    const auto& distances = item.GetDistances();
    
    if (!path.is_empty()) {
        outFile << "Shortest path: ";
        for (size_t i = 0; i < path.get_size(); i++) {
            outFile << path[i];
            if (i != path.get_size() - 1) {
                outFile << " -> ";
            }
        }
        outFile << "\nTotal distance: " << distances[path[path.get_size() - 1]] << std::endl;
    } else {
        outFile << "Shortest path not found." << std::endl;
    }
    
    outFile.close();
}

