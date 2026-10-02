#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

struct Node{
    char key[9];
    char value[9];
    struct Node* next;
};

typedef struct Node node;

node* head = NULL;

void set(){
    char key[9], value[9];

    printf("Enter key and value: ");
    scanf("%8s %8s", key,value);

    node* pt = head;
    while(pt != NULL){
        if(strcmp(pt->key,key) == 0){
            printf("Key should be unique.");      //Duplicate check.
            return;
        }
        pt = pt->next;
    }

    node* new_node = (node*)malloc(sizeof(node));

    strcpy(new_node->key, key);
    strcpy(new_node->value, value);

    new_node->next = head;
    head = new_node;
    printf("Record added");
    return;         
    }

void save(){
    char filename[45];
    printf("Enter filename(should be less than 44 chars and file should exist): ");
    scanf("%44s",filename);

    FILE* ptr = fopen(filename,"w");
    if(ptr == NULL) {
        printf("Enter a existing filename\n");
        return;
    }
    node* pt = head;
    while(pt != NULL){
        fprintf(ptr, "%s %s\n",pt->key,pt->value);
        pt = pt->next;
    }
    fclose(ptr);

    printf("saved\n");
    return;
}

void load(){
    char filename[45];
    printf("Enter filename: ");
    scanf("%44s",filename);

    FILE* ptr = fopen(filename,"r");
    if(ptr == NULL){
        printf("Could not open file\n.");
        return;
    }

    char key[9], value[9];
    while(fscanf(ptr,"%s %s\n",key , value) == 2){
        node* nodes = (node*)malloc(sizeof(node));
        strcpy(nodes->key,key);
        strcpy(nodes->value,value);
        nodes->next = head;
        head = nodes;
    }
    fclose(ptr);
    printf("Loaded.\n");

    return;
}

void get(){
    char key[9];
    printf("Enter the key of the record whose value you need: ");
    scanf("%8s",key);

    node* ptr = head;
    while(ptr != NULL){
        if(strcmp(ptr->key,key) == 0){
            printf("The value is: %s\n",ptr->value);
            return;
        }
        ptr = ptr->next;
    }
    printf("Couldn't find a element with given key.");

    return;
}

void del(){
    char key[9];
    printf("Enter the key of the record to be deleted: ");
    scanf("%8s", key);

    node* curr = head;   
    node* prev = NULL;   
    while(curr != NULL){
        if(strcmp(curr->key, key) == 0){
            if(prev == NULL)
                head = curr->next;     
            else
                prev->next = curr->next; 
            free(curr);                  
            printf("Deleted.\n");
            return;                       
        }
        prev = curr;      
        curr = curr->next; 
    }
    printf("Couldn't find a element with given key.\n");

    return;
}

bool exists(){
    char key[9];
    printf("Enter the key of the record to be searched: ");
    scanf("%8s",key);

    node* pt = head;
    while(pt != NULL){
        if(strcmp(pt->key,key) == 0){ 
            return true;
        }    
        pt = pt->next;
    }
    return false;
}

int main(){
    while(true){
        char choice[25];
        printf("Enter the operation: ");
        scanf("%s",choice);

        if(strcmp("set",choice) == 0) set();   
        else if(strcmp("get",choice) == 0) get();
        else if(strcmp("del",choice) == 0) del();
        else if(strcmp("exists",choice) == 0){
            if(exists()) printf("Record exists.\n");
            else printf("Record doesn't exist with such key.\n");
        }
        else if(strcmp("load",choice) == 0) load();
        else{
            printf("Enter valid operation.");
        }

        char y[5];
        printf("Want to save or read the file's content?(else it will continue.).: ");
        scanf("%4s",y);
        if(strcmp("save",y) == 0) save();
        if(strcmp("read",y) == 0) load();
        
        char x;
        printf("Want to continue(Y/N): ");
        scanf(" %c",&x);
        if(x == 'N') break;
    }
}