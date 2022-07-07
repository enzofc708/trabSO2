typedef struct{
    Process* processList[MAX_PROCESSES];
    int count;
} ProcessList;
    
//Instantiates a ProcessList and returns a pointer to it
ProcessList* createProcessList(){
    ProcessList* list = (ProcessList *) malloc(sizeof(ProcessList));
    list->count = 0;
    return list;
}

//Adds a Process to the list and updates the process counter
void add(ProcessList* list, Process* p){
    list->processList[list->count++] = p;
}