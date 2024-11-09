#include <iostream>
#include <climits>
using namespace std;

class BinaryHeap {
private:
    int* heap;
    int capacity;
    int size;
    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }

    void heapifyUp(int i) {
        while (i > 0 && heap[parent(i)] > heap[i]) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    void heapifyDown(int i) {
        int minIndex = i;
        int left = leftChild(i);
        int right = rightChild(i);

        if (left < size && heap[left] < heap[minIndex])
            minIndex = left;
        if (right < size && heap[right] < heap[minIndex])
            minIndex = right;

        if (minIndex != i) {
            swap(heap[i], heap[minIndex]);
            heapifyDown(minIndex);
        }
    }

public:
    BinaryHeap(int cap) {
        capacity = cap;
        size = 0;
        heap = new int[capacity];
    }

    ~BinaryHeap() {
        delete[] heap;
    }

    void insert(int key) {
        if (size == capacity) {
            cout << "Heap is full\n";
            return;
        }

        heap[size] = key;
        size++;
        heapifyUp(size - 1);
    }

    int getMin() {
        if (size <= 0)
            return -1;
        return heap[0];
    }

    int extractMin() {
        if (size <= 0)
            return -1;

        int min = heap[0];
        heap[0] = heap[size - 1];
        size--;
        heapifyDown(0);
        return min;
    }

    int getSize() {
        return size;
    }
};

class PriorityQueue {
private:
    BinaryHeap* heap;

public:
    PriorityQueue(int capacity) {
        heap = new BinaryHeap(capacity);
    }

    ~PriorityQueue() {
        delete heap;
    }

    void push(int value) {
        heap->insert(value);
    }

    int top() {
        return heap->getMin();
    }

    void pop() {
        heap->extractMin();
    }

    int size() {
        return heap->getSize();
    }

    bool empty() {
        return size() == 0;
    }
};

struct Edge {
    int dest;
    int weight;
    Edge* next;

    Edge(int d, int w) : dest(d), weight(w), next(nullptr) {}
};

class Vertex {
public:
    Edge* head;

    Vertex() : head(nullptr) {}

    void addEdge(int dest, int weight) {
        Edge* newEdge = new Edge(dest, weight);
        newEdge->next = head;
        head = newEdge;
    }
};

class Graph {
private:
    int V;
    Vertex* vertices;

public:
    Graph(int v) {
        V = v;
        vertices = new Vertex[V];
    }

    ~Graph() {
        for (int i = 0; i < V; i++) {
            Edge* current = vertices[i].head;
            while (current != nullptr) {
                Edge* next = current->next;
                delete current;
                current = next;
            }
        }
        delete[] vertices;
    }

    void addEdge(int src, int dest, int weight) {
        vertices[src].addEdge(dest, weight);
        vertices[dest].addEdge(src, weight);
    }

    // Thuật toán Prim
    void primMST() {
        int* key = new int[V];
        int* parent = new int[V];
        bool* inMST = new bool[V];

        for (int i = 0; i < V; i++) {
            key[i] = INT_MAX;
            inMST[i] = false;
        }

        key[0] = 0;
        parent[0] = -1;

        PriorityQueue pq(V);
        pq.push(0);

        while (!pq.empty()) {
            int u = pq.top();
            pq.pop();
            inMST[u] = true;

            Edge* current = vertices[u].head;
            while (current != nullptr) {
                int v = current->dest;
                int weight = current->weight;

                if (!inMST[v] && weight < key[v]) {
                    parent[v] = u;
                    key[v] = weight;
                    pq.push(v);
                }
                current = current->next;
            }
        }

        cout << "Edge \tWeight\n";
        for (int i = 1; i < V; i++) {
            cout << parent[i] << " - " << i << "\t" << key[i] << endl;
        }

        delete[] key;
        delete[] parent;
        delete[] inMST;
    }
};

int main() {
    Graph g(5);
    g.addEdge(0, 1, 2);
    g.addEdge(0, 3, 6);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 8);
    g.addEdge(1, 4, 5);
    g.addEdge(2, 4, 7);
    g.addEdge(3, 4, 9);

    cout << "Minimum Spanning Tree:\n";
    g.primMST();

    return 0;
}
