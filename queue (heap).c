#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int heap_size = 0;
int arr_size =20;



//function for creat queue
void build_max_heap(int A[]);
void swap(int* a, int* b);
int get_right_child(int A[], int index);
int get_left_child(int A[], int index);
int get_parent(int A[], int index);
void heapify_down(int A[], int index);

int extract_max(int A[]);
void increase_key(int A[], int index, int key);
void decrease_key(int A[], int index, int key);
void insert(int A[], int key);
void print_heap(int A[]);


void main()
{
   
    int A[20];
    insert(A, 20);
    insert(A, 15);
    insert(A, 8);
    insert(A, 10);
    insert(A, 5);
    insert(A, 7);
    insert(A, 6);
    insert(A, 2);
    insert(A, 9);
    insert(A, 1);

    print_heap(A);

    increase_key(A, 5, 22);
    print_heap(A);

    decrease_key(A, 1, 13);
    print_heap(A);

    printf("%d\n\n", maximum(A));
    printf("%d\n\n", extract_max(A));

    print_heap(A);

    printf("%d\n", extract_max(A));
    printf("%d\n", extract_max(A));
    printf("%d\n", extract_max(A));
    printf("%d\n", extract_max(A));
    printf("%d\n", extract_max(A));
    printf("%d\n", extract_max(A));
    printf("%d\n", extract_max(A));
    printf("%d\n", extract_max(A));
    printf("%d\n", extract_max(A));
}
void build_max_heap(int A[]) { //build max heap , time complexy will be N 
    int i;
    for (i = heap_size / 2; i >= 1; i--) {
        heapify_down(A, i); // the heapfiy will work only on the inside nodes and not the leaves, the leaves are good.
    }
}

void swap(int* a, int* b) {
    int t;
    t = *a;
    *a = *b;
    *b = t;
}

//function to get right child of a node of a tree
int get_right_child(int A[], int index) {
    if ((((2 * index) + 1) < arr_size) && (index >= 1))
        return (2 * index) + 1;
    return -1;
}

//function to get left child of a node of a tree
int get_left_child(int A[], int index) {
    if (((2 * index) < arr_size) && (index >= 1))  // node is a leaf if 2*i>n -> we want the interior node
        return 2 * index;
    return -1;
}

//function to get the parent of a node of a tree
int get_parent(int A[], int index) {
    if ((index > 1) && (index < arr_size)) {
        return index / 2;
    }
    return -1;
}

void heapify_down(int A[], int index) {
    int left_child_index = get_left_child(A, index);
    int right_child_index = get_right_child(A, index);

    // finding largest among index, left child and right child
    int largest = index;

    if ((left_child_index <= heap_size) && (left_child_index > 0)) { //if left child is exist and is not a leaf 
        if (A[left_child_index] > A[largest]) {
            largest = left_child_index;
        }
    }

    if ((right_child_index <= heap_size && (right_child_index > 0))) { //if right child is exist and is not a leaf
        if (A[right_child_index] > A[largest]) {
            largest = right_child_index;
        }
    }

    // largest is not the node, node is not a heap
    if (largest != index) { //if lergest is the  given index we dont need to swap the heap is good.
        swap(&A[index], &A[largest]);
        heapify_down(A, largest);
    }
}

int maximum(int A[]) { //time complexy of O(1)
    return A[1];
}

int extract_max(int A[]) {
    int maxm = A[1];
    A[1] = A[heap_size];
    heap_size--;
    heapify_down(A, 1);
    return maxm;
}

void increase_key(int A[], int index, int key) {
    A[index] = key;
    while ((index > 1) && (A[get_parent(A, index)] < A[index])) {
        swap(&A[index], &A[get_parent(A, index)]);
        index = get_parent(A, index);
    }
}

void decrease_key(int A[], int index, int key) {
    A[index] = key;
    heapify_down(A, index);
}

void insert(int A[], int key) {
    heap_size++;
    A[heap_size] = key;
    heapify_down(A, A[heap_size]);
    
}

void print_heap(int A[]) {
    int i;
    for (i = 1; i <= heap_size; i++) {
        printf("%d\n", A[i]);
    }
    printf("\n");
}
