// Charniya Krish
// 23CS10012

#include <stdio.h>
#include <stdlib.h>

#define MAX_MACHINES 1000
#define MAX_TASKS 1000

// Global variables to store size of heaps
int size_free = 0, size_busy = 0;

// Task structure
typedef struct {
    int p; // Power needed by the machine (for free machines)
    int id; // Machine id (index)
} machine;

typedef struct {
    int time; // Time when the machine becomes free
    int machine_id; // Machine index
} busy_machine;

// Arrays to store free and busy machines
machine free_machines[MAX_MACHINES];
busy_machine busy_machines[MAX_MACHINES];

// Helper function to swap two machines
void swap_machine(machine* a, machine* b) {
    machine temp = *a;
    *a = *b;
    *b = temp;
}

// Helper function to swap two busy_machine entries
void swap_busy(busy_machine* a, busy_machine* b) {
    busy_machine temp = *a;
    *a = *b;
    *b = temp;
}

// Heapifying for free machines (min-heap by power)
void heapify_free(machine a[], int i) {
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int smallest = i;

    if (l < size_free && a[l].p < a[smallest].p)
        smallest = l;
    if (r < size_free && a[r].p < a[smallest].p)
        smallest = r;

    if (i != smallest) {
        swap_machine(&a[i], &a[smallest]);
        heapify_free(a, smallest);
    }
}

// Heapifying for busy machines (min-heap by time)
void heapify_busy(busy_machine a[], int i) {
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int smallest = i;

    if (l < size_busy && a[l].time < a[smallest].time)
        smallest = l;
    if (r < size_busy && a[r].time < a[smallest].time)
        smallest = r;

    if (i != smallest) {
        swap_busy(&a[i], &a[smallest]);
        heapify_busy(a, smallest);
    }
}

// Inserting a machine into the free machine heap
void insert_free(machine a[], machine val) {
    a[size_free] = val;
    size_free++;

    int i = size_free - 1;
    // Sift up the newly inserted element to restore heap property
    while (i > 0 && a[(i - 1) / 2].p > a[i].p) {
        swap_machine(&a[i], &a[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Inserting a machine into the busy machine heap
void insert_busy(busy_machine a[], busy_machine val) {
    a[size_busy] = val;
    size_busy++;

    int i = size_busy - 1;
    // Sift up the newly inserted element to restore heap property
    while (i > 0 && a[(i - 1) / 2].time > a[i].time) {
        swap_busy(&a[i], &a[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Extract the machine with the lowest power from the free heap
machine extract_free() {
    if (size_free == 0) {
        machine empty_machine = {-1, -1};
        return empty_machine; // Indicating no machine is available
    }

    machine min_machine = free_machines[0];
    free_machines[0] = free_machines[size_free - 1];
    size_free--;
    heapify_free(free_machines, 0);

    return min_machine;
}

// Extract the machine that becomes free the earliest from the busy heap
busy_machine extract_busy() {
    if (size_busy == 0) {
        busy_machine empty_busy = {-1, -1};
        return empty_busy; // Indicating no machine is available
    }

    busy_machine min_busy = busy_machines[0];
    busy_machines[0] = busy_machines[size_busy - 1];
    size_busy--;
    heapify_busy(busy_machines, 0);

    return min_busy;
}

// Main function to assign tasks
void assign_tasks(int* machines, int num_machines, int* tasks, int num_tasks, int* assign) {
    // Initialize the free machine heap with all machines
    for (int i = 0; i < num_machines; i++) {
        machine m = {machines[i], i};
        insert_free(free_machines, m);
    }

    // Process each task
    for (int j = 0; j < num_tasks; j++) {
        // Ensure all machines that have finished their tasks by time j are available again
        while (size_busy > 0 && busy_machines[0].time <= j) {
            busy_machine free_machine = extract_busy();
            machine m = {machines[free_machine.machine_id], free_machine.machine_id};
            insert_free(free_machines, m);
        }

        // Assign task j
        machine assigned_machine = extract_free();
        if (assigned_machine.id != -1) {
            assign[j] = assigned_machine.id;
            busy_machine bm = {j + tasks[j], assigned_machine.id}; // Machine will be free after j + tasks[j]
            insert_busy(busy_machines, bm);
        } else {
            // If no free machine is available, find the first available machine
            busy_machine next_free_machine = extract_busy();
            assign[j] = next_free_machine.machine_id;
            busy_machine bm = {next_free_machine.time + tasks[j], next_free_machine.machine_id};
            insert_busy(busy_machines, bm);
        }
    }
}

int main() {

    int n, m, time = 0;
    printf("Enter the Machine number n: ");
    scanf("%d", &n);

    int machines[n];
    printf("Enter Machines: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &machines[i]);
    }

    printf("Enter the Tasks number m: ");
    scanf("%d", &m);

    int task[m], ans[m];
    printf("Enter tasks: ");
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &task[i]);
    }


    assign_tasks(machines, n, task,m, ans);

    printf("Assignment of Tasks : ");
    for (int i = 0; i < m; i++) {
        printf(" %d", ans[i]);
    }
    printf("\n");

    return 0;
}
