typedef struct MemoryManager
{
    ProcessList* processes;
    int currentTime;
    FramesList* frames;
} MemoryManager;

MemoryManager* createManager(){
    MemoryManager* pointer = (MemoryManager*) malloc(sizeof(MemoryManager));
    pointer->processes = createList();
    pointer->currentTime = 0;
    for (int i = 0; i < MEMORY_FRAMES - 1; i++)
    {
        pointer->frames->list[i] = 0;
    }
    
    return pointer;
}

void addProcess(MemoryManager* m, Process* p){
    add(m->processes, p);
}

void allocPage(MemoryManager* m, Page* p){  
    addToFrame(m->frames, p);
    p->lastReference = m->currentTime;
}

