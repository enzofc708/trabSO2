// A basic implementation of a List, specified for the class Process
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

Process* getOldestRunningProcess(ProcessList* list){
    int oldest = -1;
    Process* oldestP;
    for (int i = 0; i < list->count; i++)
    {
        if(list->processList[i]->currentState == RunningState &&
           list->processList[i]->statusTime < oldest &&
           oldest )
    }
    
}