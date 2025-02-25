#include "queue.h"

Node* init_node(char* new_data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = new_data;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

void free_node(Node* node) {
    if (node == NULL) return;
    node->next = NULL;
    node->prev = NULL;
    free(node);
}

void set_node_next(Node* node, Node* next_node) {
    node->next = next_node;
}

void set_node_prev(Node* node, Node* prev_node) {
    node->prev = prev_node;
}

char* get_node_data(Node* node) {
    return node->data;
}

Queue* init_queue() {
    Queue* new_queue = (Queue*)malloc(sizeof(Queue));
    Node* head = init_node(NULL);
    Node* tail = init_node(NULL);
    set_node_next(head, tail);
    set_node_prev(tail, head);
    new_queue->head = head;
    new_queue->tail = tail;
    return new_queue;
}

void free_queue(Queue* queue) {
    if (queue == NULL) return;
    Node* current = queue->head->next;
    while(current != NULL && current != queue->tail) {
        Node* temp = current;
        current = current->next;

        if(temp->next) {
            temp->next->prev = queue->head;
        }
        queue->head->next = current;
        free_node(temp);
    }
    free_node(queue->head);
    free_node(queue->tail);
    free(queue);
}

void enqueue(Queue* queue, Node* new_node) {
    if (new_node ==  NULL) return;
    Node* prev_node = queue->tail->prev;
    set_node_next(prev_node, new_node);
    set_node_prev(new_node, prev_node);
    set_node_next(new_node, queue->tail);
    set_node_prev(queue->tail, new_node);
}

void dequeue(Queue* queue) {
    Node* remove_node = queue->head->next;
    if (remove_node == queue->tail) return;

    queue->head->next = remove_node->next;
    remove_node->next->prev = queue->head;
    free_node(remove_node);
}

Node* get_front(Queue* queue) {
    Node* head_node = queue->head;
    if (head_node->next == NULL || head_node->next == queue->tail) return NULL;
    return head_node->next;
}

void print_queue(Queue* queue) {
    Node* current = queue->head->next;
    int i=1;
    while (current != queue->tail) {
        printf("%d. %s\n", i, current->data);
        printf("\t%s front node: %s\n", current->data, current->next->data == NULL ? "NULL" : current->next->data);
        printf("\t%s back node: %s\n", current->data, current->prev->data == NULL ? "NULL" : current->prev->data);
        current = current->next;
        i++;
    }
}
