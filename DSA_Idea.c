#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

#define V 16384
#define MATRIX_SIZE 16384
#define Num_Nodes 128

int adjacency_matrix[MATRIX_SIZE][MATRIX_SIZE];

int minDistance(int dist[], bool sptSet[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}

void printSolution(int dist[], int pred[], int src, int dest, const char* output){
    FILE* file = fopen(output, "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    for (int i = dest; i != src; i = pred[i]) {
    printf("%d ", i);
    fprintf(file, "%d ", i);
    }
    printf("%d\n", src);
    fprintf(file, "%d\n", src);


    fclose(file);
}

void dijkstra(int src, int dest, const char* output){
    int dist[V];
    int pred[V];
    bool sptSet[V];

    for (int i = 0; i < V; i++){
        dist[i] = INT_MAX, sptSet[i] = false;
    }
    dist[src] = 0;
    pred[src] = -1;
    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;
        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && adjacency_matrix[u][v] && dist[u] != INT_MAX &&
                dist[u] + adjacency_matrix[u][v] < dist[v]) {
                dist[v] = dist[u] + adjacency_matrix[u][v];
                pred[v] = u;
            }
        }
    }

    printSolution(dist, pred, src, dest, output);
}

void read_adjacency_matrix(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL){
        printf("Error opening file.\n");
        exit(1);
    }

    for (int i = 0; i < MATRIX_SIZE; i++){
        for (int j = 0; j < MATRIX_SIZE; j++) {
            fscanf(file, "%d", &adjacency_matrix[i][j]);
        }
    }

    fclose(file);
}

int main() {
    printf("Code Running\n");
    const char* filename = "array.txt";

    printf("Reading Matrix\n");
    read_adjacency_matrix(filename);

    int src = 8975;
    int dest = 8360;

    const char* output_filename = "output_file_8975_to_8360.txt";

    printf("Performing Dijkstra\n");
    dijkstra(src, dest, output_filename);

    return 0;
}

