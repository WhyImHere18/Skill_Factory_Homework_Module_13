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
    // �������� ������� � ������ �������
    for (int i = 0; i < SIZE; i++)
    {
        matrix[i][vNumber] = 0;
        matrix[vNumber][i] = 0;
    }
    // ������� ������� �� ������ ������
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

/* ��� ��������, ���������� �� �����, ����� ���������� �������� �������� ������� ��������� � ��������� ������� ������ (���� ���� �����, �� ������� �� 0).*/
bool Graph::edgeExists(int v1, int v2)
{
    return matrix[v1][v2] != 0;
}

/*��� ��������, ���������� �� �������, ����� ���������, ���� �� �� ����� � ������� vertexes.*/
bool Graph::vertexExists(int vnumber)
{
    for (int i = 0; i < vertexCount; i++)
        if (vertexes[i] == vnumber)
            return true;
    return false;
}

//����� ��� ����, ���������� ����� �������� <= distance
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
    int weights[SIZE][SIZE]; // ������� �����
    // ������������ �������
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (i == j)
            {
                weights[i][j] = 0; // ���� �� ����� ���� ����� 0
            }
            else {
                if (!edgeExists(i, j))
                {
                    weights[i][j] = VERYBIGINT; // ���� ����� ���
                }
                else {
                    weights[i][j] = matrix[i][j]; // ���� ����� ����
                }
            }
        }
    }

    for (int k = 0; k < vertexCount; k++) // �������� �� k
    {
        int ck = vertexes[k]; // ������� ����� �������
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
                    // �������� �������� �����
                    weights[ci][cj] = weights[ci][ck] + weights[ck][cj];
                }
            }
        }
    }

    return weights[from][to];
}

