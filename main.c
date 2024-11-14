#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

void generate_matrix(int matrix[MAX][MAX], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (i == j) {
                matrix[i][j] = 0;
            }
            else {
                matrix[i][j] = matrix[j][i] = rand() % 2;
            }
        }
    }
}

void printMatrix(int matrix[MAX][MAX], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int countEdges(int matrix[MAX][MAX], int n) {
    int edges = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (matrix[i][j] == 1) {
                edges++;
            }
        }
    }
    return edges;
}

void findVertexTypes(int matrix[MAX][MAX], int n) {
    int isolatedCount = 0, endCount = 0, dominantCount = 0;

    printf("Isolated vertices: ");
    for (int i = 0; i < n; i++) {
        int degree = 0;
        for (int j = 0; j < n; j++) {
            degree += matrix[i][j];
        }
        if (degree == 0) {
            printf("%d ", i);
            isolatedCount++;
        }
    }
    if (isolatedCount == 0) printf("None");
    printf("\n");

    printf("End vertices: ");
    for (int i = 0; i < n; i++) {
        int degree = 0;
        for (int j = 0; j < n; j++) {
            degree += matrix[i][j];
        }
        if (degree == 1) {
            printf("%d ", i);
            endCount++;
        }
    }
    if (endCount == 0) printf("None");
    printf("\n");

    printf("Dominant vertices: ");
    for (int i = 0; i < n; i++) {
        int degree = 0;
        for (int j = 0; j < n; j++) {
            degree += matrix[i][j];
        }
        if (degree == n - 1) {
            printf("%d ", i);
            dominantCount++;
        }
    }
    if (dominantCount == 0) printf("None");
    printf("\n");
}

void generate_incidence_matrix(int matrix[MAX][MAX], int n, int edgeCount, int incidenceMatrix[MAX][MAX]) {
    int edgeIndex = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (matrix[i][j] == 1) {
                incidenceMatrix[i][edgeIndex] = 1;
                incidenceMatrix[j][edgeIndex] = 1;
                edgeIndex++;
            }
        }
    }

    printf("Incidence matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < edgeCount; j++) {
            printf("%d ", incidenceMatrix[i][j]);
        }
        printf("\n");
    }
}

int countEdgesFromIncidenceMatrix(int incidenceMatrix[MAX][MAX], int n, int edgeCount) {
    int edges = 0;
    for (int j = 0; j < edgeCount; j++) {
        int countOnes = 0;
        for (int i = 0; i < n; i++) {
            if (incidenceMatrix[i][j] == 1) {
                countOnes++;
            }
        }
        if (countOnes == 2) { // ≈сли инцидентность 2 вершин, то это ребро
            edges++;
        }
    }
    return edges;
}

int main() {
    int n;
    srand(time(NULL));

    int adjacencyMatrix[MAX][MAX];
    int incidenceMatrix[MAX][MAX] = { 0 };

    printf("Input count of vertices (no more than %d): ", MAX);
    scanf("%d", &n);

    if (n > MAX || n <= 0) {
        printf("Invalid count of vertices.\n");
        return 1;
    }

    generate_matrix(adjacencyMatrix, n);

    printf("Generated adjacency matrix:\n");
    printMatrix(adjacencyMatrix, n);

    int edgeCount = countEdges(adjacencyMatrix, n);
    printf("Size of the graph (number of edges): %d\n", edgeCount);

    findVertexTypes(adjacencyMatrix, n);

    generate_incidence_matrix(adjacencyMatrix, n, edgeCount, incidenceMatrix);

    int calculatedEdgeCount = countEdgesFromIncidenceMatrix(incidenceMatrix, n, edgeCount);
    printf("Calculated size of the graph (number of edges from incidence matrix): %d\n", calculatedEdgeCount);

    findVertexTypes(incidenceMatrix, n);

    return 0;
}
