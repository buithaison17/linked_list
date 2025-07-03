#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
} Node;

// Tạo một nốt
Node* createNode(int data){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Thêm phần tử vào cuối
void pushNode(Node** head, int data){
    Node* newNode = createNode(data);
    if(*head == NULL){
        *head = newNode;
    }
    else{
        Node* current = *head;
        while(current->next != NULL){
            current = current->next;
        }
        current->next = newNode;
    }
}

// Thêm phần tử vào đầu
void unshiftNode(Node** head, int data){
    Node* newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}

// Xóa tại vị trí đầu
void shiftNode(Node** head){
    Node* temp = *head;
    *head = (*head)->next;
    free(temp);
}

// Lấy chiều dài danh sách
int getLengthNode(Node* head){
    Node* current = head;
    int length = 0;
    while(current != NULL){
        length++;
        current = current->next;
    }
    return length;
}

// Chèn tại vị trí bất kì
void insertNodeAt(Node** head, int index, int data){
    int length = getLengthNode(*head);
    if(index < 0 || index > length) return;
    if(index == length){
        pushNode(head, data);
        return;
    }
    if(index == 0){
        unshiftNode(head, data);
        return;
    }
    Node* newNode = createNode(data);
    Node* current = *head;
    for(int i = 0; i < index - 1; i++){
        current = current->next;
    }
    Node* nextNode = current->next;
    current->next = newNode;
    newNode->next = nextNode;
}

// Xóa tại vị trí bất kì
void deleteNodeAt(Node** head, int index){
    int length = getLengthNode(*head);
    if(index < 0 || index > length - 1) return;
    if(index == 0){
        shiftNode(head);
        return;
    }
    Node* current = *head;
    for(int i = 0; i < index - 1; i++){
        current = current->next;
    }
    Node* temp = current->next;
    current->next = temp->next;
    free(temp);
}

// Đảo ngược
void reverseNode(Node** head){
    Node* prev = NULL;
    Node* current = *head;
    Node* next = NULL;
    while(current != NULL){
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
}

// In danh sách
void printListNode(Node* head){
    Node* current = head;
    while(current != NULL){
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

int main(){
    Node* head = NULL;
    unshiftNode(&head, 10);
    unshiftNode(&head, 120);
    insertNodeAt(&head, 1, 0);
    reverseNode(&head);
    printListNode(head);
    return 0;
}