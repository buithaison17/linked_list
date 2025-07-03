#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct DoublyLinkedList{
    Node* head;
    Node* tail;
} DoublyLinkedList;


void createList(DoublyLinkedList** list){
    *list = (DoublyLinkedList*)malloc(sizeof(DoublyLinkedList));
    (*list)->head = NULL;
    (*list)->tail = NULL;
}

void freeList(DoublyLinkedList* list){
    Node* current = list->head;
    Node* temp = NULL;
    while(current != NULL){
        temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

Node* createNode(int data){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Thêm phần tử vào cuối
void pushNode(DoublyLinkedList** list, int data){
    Node* newNode = createNode(data);
    if((*list)->head == NULL){
        (*list)->head = newNode;
        (*list)->tail = newNode;
    }
    else{
        (*list)->tail->next = newNode;
        newNode->prev = (*list)->tail;
        (*list)->tail = newNode;
    }
}

// Thêm phần tử vào đầu
void unshiftNode(DoublyLinkedList** list, int data){
    Node* newNode = createNode(data);
    if((*list)->head == NULL){
        (*list)->head = newNode;
        (*list)->tail = newNode;
        return;
    }
    newNode->next = (*list)->head;
    (*list)->head->prev = newNode;
    (*list)->head = newNode;
}

// In danh sách
void printListNode(DoublyLinkedList* list){
    Node* current = list->head;
    while(current != NULL){
        printf("%d <-> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// Lấy chiều dài
int getLengthNode(DoublyLinkedList* list){
    int length = 0;
    Node* current = list->head;
    while(current != NULL){
        length++;
        current = current->next;
    }
    return length;
}

// Chèn phần tử
void insertNodeAt(DoublyLinkedList** list, int index, int data){
    int length = getLengthNode(*list);
    if(index < 0 || index > length) return;
    if(index == 0){
        unshiftNode(list, data);
        return;
    }
    if(index == length){
        pushNode(list, data);
        return;
    }
    Node* newNode = createNode(data);
    Node* current = (*list)->head;
    for(int i = 0; i < index - 1; i++){
        current = current->next;
    }
    Node* nextNode = current->next;
    current->next = newNode;
    newNode->prev = current;
    newNode->next = nextNode;
    nextNode->prev = newNode;
}

// Xóa phần tử ở cuối
void popNode(DoublyLinkedList** list){
    Node* temp = (*list)->tail;
    (*list)->tail = (*list)->tail->prev;
    (*list)->tail->next = NULL;
    free(temp);
}

// Xóa phần tử ở đầu
void shiftNode(DoublyLinkedList** list){
    int length = getLengthNode(*list);
    Node* temp = (*list)->head;
    if(length == 1){
        (*list)->head = NULL;
        (*list)->tail = NULL;
    }
    else{
        (*list)->head = (*list)->head->next;
        (*list)->head->prev = NULL;
    }
    free(temp);
}

// Xóa phần tử tại vị trí bất kì
void deleteNodeAt(DoublyLinkedList** list, int index){
    int length = getLengthNode(*list);
    if(index < 0 || index > length - 1) return;
    if(index == 0){
        shiftNode(list);
        return;
    }
    if(index == length - 1){
        popNode(list);
        return;
    }
    Node* current = (*list)->head;
    for(int i = 0; i < index - 1; i++){
        current = current->next;
    }
    Node* temp = current->next;
    current->next = temp->next;
    temp->next->prev = current;
    free(temp);
}

// Đảo ngược
void reverseList(DoublyLinkedList** list){
    Node* current = (*list)->head;
    Node* temp = NULL;
    while(current != NULL){
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
    if(temp != NULL){
        (*list)->tail = (*list)->head;
        (*list)->head = temp->prev;
    }
}

int main(){
    DoublyLinkedList* list = NULL;
    createList(&list);
    pushNode(&list, 10);
    pushNode(&list, 30);
    insertNodeAt(&list, 1, 20);
    shiftNode(&list);
    popNode(&list);
    // reverseList(&list);
    printListNode(list);
    freeList(list);
    return 0;
}