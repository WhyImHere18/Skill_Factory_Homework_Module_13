#pragma once

#define SIZE 15

class Graph
{
public:

    Graph() {
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                matrix[i][j] = 0;
        vertexCount = 0;
    }
    void addVertex(int vNumber);
    void addEdge(int v1, int v2);
    void delVertex(int vNumber);
    void delEdge(int v1, int v2);
    void showPairs(int distance);
    int findMinDistances(int from, int to);

private:
    bool edgeExists(int v1, int v2);
    bool vertexExists(int v);
    int matrix[SIZE][SIZE]; // матрица смежности

    int vertexes[SIZE]; // хранилище вершин
    int vertexCount; // количество добавленных вершин
};

