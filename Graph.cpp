#include "Graph.h"
#include <iostream>

#define VERYBIGINT 1000000000

void Graph::addVertex(int vNumber)
{
    vertexes[vertexCount++] = vNumber;
}

void Graph::addEdge(int v1, int v2)
{
    matrix[v1][v2] = 1;
    matrix[v2][v1] = 1;
}

void Graph::delVertex(int vNumber)
{
    // обнуляем столбец и строку матрицы
    for (int i = 0; i < SIZE; i++)
    {
        matrix[i][vNumber] = 0;
        matrix[vNumber][i] = 0;
    }
    // удаляем вершину из списка вершин
    int foundIndex = -1;
    for (int i = 0; i < vertexCount; i++)
    {
        if (vertexes[i] == vNumber)
            foundIndex = i;
    }
    vertexCount--;
    for (int i = foundIndex; i < vertexCount; i++)
    {
        vertexes[i] = vertexes[i + 1];
    }
}

void Graph::delEdge(int v1, int v2)
{
    matrix[v1][v2] = 0;
    matrix[v2][v1] = 0;
}

/* Для проверки, существует ли ребро, нужно посмотреть значение элемента матрицы смежности с индексами номеров вершин (если есть ребро, он отличен от 0).*/
bool Graph::edgeExists(int v1, int v2)
{
    return matrix[v1][v2] != 0;
}

/*Для проверки, существует ли вершина, нужно проверить, есть ли ее номер в массиве vertexes.*/
bool Graph::vertexExists(int vnumber)
{
    for (int i = 0; i < vertexCount; i++)
        if (vertexes[i] == vnumber)
            return true;
    return false;
}

//Найти все пары, расстояние между которыми <= distance
void Graph::showPairs(int distance)
{
    //int pairs[2][SIZE];

    //for (int i = 0; i < 2; i++)
    //    for (int j = 0; j < SIZE; j++)
    //    {
    //        pairs[i][j] = 0;
    //    }

    bool visited[SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        visited[i] = false;
    }

    std::cout << "vertexes with distance less or equal of " << distance << ": " << std::endl;
    for (int i = 0; i < vertexCount; i++)
    {
        int ci = vertexes[i];
        visited[ci] = true;
        for (int j = 0; j < vertexCount; j++)
        {
            int cj = vertexes[j];

            if (!visited[cj])
            {
                int d = findMinDistances(ci, cj);
                if (d >= distance)
                {
                    std::cout << ci << " " << cj << std::endl;
                }
            }
        }
    }
}

int Graph::findMinDistances(int from, int to)
{
    int weights[SIZE][SIZE]; // матрица путей
    // инициализаци матрицы
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (i == j)
            {
                weights[i][j] = 0; // путь до самой себя равен 0
            }
            else {
                if (!edgeExists(i, j))
                {
                    weights[i][j] = VERYBIGINT; // если ребра нет
                }
                else {
                    weights[i][j] = matrix[i][j]; // если ребро есть
                }
            }
        }
    }

    for (int k = 0; k < vertexCount; k++) // итерации по k
    {
        int ck = vertexes[k]; // возьмем номер вершины
        for (int i = 0; i < vertexCount; i++)
        {
            if (i == k)
                continue;
            int ci = vertexes[i];
            for (int j = 0; j < vertexCount; j++)
            {
                if (j == k)
                    continue;
                int cj = vertexes[j];
                if (weights[ci][ck] + weights[ck][cj] < weights[ci][cj]) {
                    // пересчет мматрицы путей
                    weights[ci][cj] = weights[ci][ck] + weights[ck][cj];
                }
            }
        }
    }

    return weights[from][to];
}

