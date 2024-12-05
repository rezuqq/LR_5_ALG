#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generate_matrix(int** matrix, int n) {
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

void printMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int countEdges(int** matrix, int n) {
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

void findMatrixType(int** matrix, int n, int size) {
    int isolatedCount = 0, endCount = 0, dominantCount = 0;
    int isolatedPrinted = 0, endPrinted = 0, dominantPrinted = 0;
    for (int i = 0; i < n; i++) {
        int degree = 0;

        for (int j = 0; j < size; j++) {
            degree += matrix[i][j];
        }

        if (degree == 0) {
            if (!isolatedPrinted) {
                printf("\nIsolated vertices: ");
                isolatedPrinted = 1;
            }
            printf("%d ", i);
            isolatedCount++;
        }

        if (degree == 1) {
            if (!endPrinted) {
                printf("\nEnd vertices: ");
                endPrinted = 1;
            }
            printf("%d ", i);
            endCount++;
        }

        if (degree == size - 1) {
            if (!dominantPrinted) {
                printf("\nDominant vertices: ");
                dominantPrinted = 1;
            }
            printf("%d ", i);
            dominantCount++;
        }
    }

    if (isolatedPrinted == 0) printf("\nIsolated vertices: None");
    if (endPrinted == 0) printf("\nEnd vertices: None");
    if (dominantPrinted == 0) printf("\nDominant vertices: None");
    printf("\n");
}

void findVertexTypes(int **matrix, int n, int edgeCount) {

    printf("");
    if (n == edgeCount) {
        findMatrixType(matrix, n, n);
    }
    else
    {
        findMatrixType(matrix, n, edgeCount);
    }

    printf("\n");
}

void generate_incidence_matrix(int** matrix, int n, int edgeCount, int** incidenceMatrix) {
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

int countEdgesFromIncidenceMatrix(int** incidenceMatrix, int n, int edgeCount) {
    int edges = 0;
    for (int j = 0; j < edgeCount; j++) {
        int countOnes = 0;
        for (int i = 0; i < n; i++) {
            if (incidenceMatrix[i][j] == 1) {
                countOnes++;
            }
        }
        if (countOnes == 2) {
            edges++;
        }
    }
    return edges;
}

int main() {
    int n;
    srand(time(NULL));

    printf("Input count of vertices: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid count of vertices.\n");
        return 1;
    }

    // Динамическое выделение памяти для матрицы смежности
    int** adjacencyMatrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        adjacencyMatrix[i] = (int*)malloc(n * sizeof(int));
    }

    generate_matrix(adjacencyMatrix, n);

    printf("Generated adjacency matrix:\n");
    printMatrix(adjacencyMatrix, n);

    int edgeCount = countEdges(adjacencyMatrix, n);
    printf("Size of the graph (number of edges): %d\n", edgeCount);
    findVertexTypes(adjacencyMatrix, n, edgeCount);
    // Динамическое выделение памяти для матрицы инцидентности
    int** incidenceMatrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        incidenceMatrix[i] = (int*)calloc(edgeCount, sizeof(int)); // Инициализация нулями
    }

    generate_incidence_matrix(adjacencyMatrix, n, edgeCount, incidenceMatrix);

    int calculatedEdgeCount = countEdgesFromIncidenceMatrix(incidenceMatrix, n, edgeCount);
    printf("Calculated size of the graph (number of edges from incidence matrix): %d\n", calculatedEdgeCount);
    findVertexTypes(incidenceMatrix, n, edgeCount);

    // Освобождение памяти
    for (int i = 0; i < n; i++) {
        free(adjacencyMatrix[i]);
        free(incidenceMatrix[i]);
    }
    free(adjacencyMatrix);
    free(incidenceMatrix);

    return 0;
}
