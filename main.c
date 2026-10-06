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

void set(char* key,char* value){

    node* pt = head;
    while(pt != NULL){
        if(strcmp(pt->key,key) == 0){
            printf("Key should be unique.\n");      //Duplicate check.
            return;
        }
        pt = pt->next;
    }

    node* new_node = (node*)malloc(sizeof(node));

    strcpy(new_node->key, key);
    strcpy(new_node->value, value);

    new_node->next = head;
    head = new_node;
    printf("OK \n");
    return;         
    }

void save(char* filename){

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

void load(char* filename){

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
    printf("Loaded.\n");
    fclose(ptr);
    return;
}

void get(char* key){

    node* ptr = head;
    while(ptr != NULL){
        if(strcmp(ptr->key,key) == 0){
            printf("%s\n",ptr->value);
            return;
        }
        ptr = ptr->next;
    }
    printf("Couldn't find a record with given key.");

    return;
}

void del(char* key){

    node* curr = head;   
    node* prev = NULL;   
    while(curr != NULL){
        if(strcmp(curr->key, key) == 0){
            if(prev == NULL)
                head = curr->next;     
            else
                prev->next = curr->next; 
            free(curr);                  
            printf("OK\n");
            return;                       
        }
        prev = curr;      
        curr = curr->next; 
    }
    printf("Couldn't find a record with given key.\n");

    return;
}

bool exists(char* key){

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
    load("data.txt");   // restore state from the last session, if any

    while(true){
        char choice[25];
        printf("Enter the operation: ");
        if(fgets(choice,sizeof(choice),stdin) == NULL) break;
        char command[24];
        char key[9];
        char value[9];
        char filename[45];

        int n = sscanf(choice, "%23s %8s %8s", command ,key, value);
        sscanf(choice, "%*s %44s", filename);   // separate parse, sized for filenames

        if(strcmp("SET",command) == 0){
            if(n <3) printf("ERROR: usage: SET <KEY> <VALUE>");
            else set(key,value);
        }   
        else if(strcmp("GET",command) == 0){
            if(n<2) printf("ERROR: usage: GET <KEY>");
            else get(key);
        } 
        else if(strcmp("DEL",command) == 0){
            if(n<2) printf("ERROR: usage: DEL <KEY>");
            else del(key);
        }    
        else if(strcmp("EXISTS",command) == 0){
            if(n<2) printf("ERROR: usage: EXISTS <KEY>");
            else{
                if(exists(key)) printf("True\n");
                else printf("False.\n");
            }
        }
        else if(strcmp("SAVE",command) == 0){
            if(n<2) printf("ERROR: usage: SAVE <FILENAME>\n");
            else save(filename);
        }
        else if(strcmp("LOAD",command) == 0){
            if(n<2) printf("ERROR: usage: LOAD <FILENAME>\n");
            else load(filename);
        }
        else{
            printf("Enter valid operation.\n");
            break;
        }

        char y[45];
        char yfilename[45] = "";
        char ycommand[45] = "";
        printf("Want to save or load the file's content?(else it will continue.): ");
        if(fgets(y,sizeof(y),stdin) == NULL) break;
        y[strcspn(y,"\n")] = '\0';
        int yn = sscanf(y, "%15s %44s", ycommand, yfilename);
        if(strcmp("SAVE",ycommand) == 0) {
            if(yn<2) printf("ERROR: usage: SAVE <FILENAME>");
            else save(yfilename);
        }    
        if(strcmp("LOAD",ycommand) == 0){
            if(yn<2) printf("ERROR: usage: LOAD <FILENAME>");
            else load(yfilename);
        }
        
        char x;
        printf("Want to continue(Y/N): ");
        scanf(" %c",&x);
        int c;
        while((c = getchar()) != '\n' && c != EOF);   // flush rest of the line
        if(x == 'N') break;
    }
}
