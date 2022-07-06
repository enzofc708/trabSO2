typedef struct{
    Process* processList[MAX_PROCESSES];
    int count;
} ProcessList;

ProcessList* createList(){
    ProcessList* list = (ProcessList *) malloc(sizeof(ProcessList));
    list->count = 0;
    return list;
}

int isEmptyList(ProcessList* list){
    return !list->count;   
}

void add(ProcessList* list, Process* p){
    list->processList[list->count++] = p;
}

Process* popHead(ProcessList* list){
    Process* head = list->processList[0];
    for (int i = 0; i < list->count - 1; i++)
    {
         list->processList[i] = list->processList[i+1];
    }
    list->count--;
    return head;
}

void append(ProcessList* p1, ProcessList* p2){
    for (int i = 0; i < p2->count; i++)
    {
        add(p1, p2->processList[i]);
    }    
}