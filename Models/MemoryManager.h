typedef struct MemoryManager
{
    ProcessList* processes;
} MemoryManager;

MemoryManager* createManager(){
    MemoryManager* pointer = (MemoryManager*) malloc(sizeof(MemoryManager));
    pointer->processes = createList();
    return pointer;
}

void addProcess(MemoryManager* m, Process* p){
    add(m->processes, p);
}