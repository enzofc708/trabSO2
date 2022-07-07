typedef struct MemoryManager
{
    ProcessList* processes;
    int currentTime;
    FramesList* frames;
} MemoryManager;

MemoryManager* createManager(){
    MemoryManager* pointer = (MemoryManager*) malloc(sizeof(MemoryManager));
    pointer->processes = createProcessList();
    pointer->frames = createFramesList();
    pointer->currentTime = 0;
    for (int i = 0; i < MEMORY_FRAMES - 1; i++)
    {
        pointer->frames->list[i] = 0;
    }
    
    return pointer;
}

void addNewProcess(MemoryManager* m){
    Process* newProcess = createProcess();
    add(m->processes, newProcess);
}

void allocPage(MemoryManager* m, Process* p){  
    Page* rPage = getRandomPage(p);
    if(rPage->present){
        rPage->lastReference = m->currentTime;
        return;
    }
    int emptyIndex = findEmpty(m->frames);
    PagesList* presentPages = getPresentPages(p);
    if(presentPages->count == WORKING_SET_LIMIT){
        Page* lruPage = getLRUPage(presentPages);
        emptyIndex = lruPage->frameNumber;
        lruPage->present = 0;
    }
    m->frames->list[emptyIndex] = 1;
    rPage->present = 1;
    rPage->lastReference = m->currentTime;
    rPage->frameNumber = emptyIndex;
}

void iteration(MemoryManager* m){
    m->currentTime += 3;
    for (int i = 0; i < m->processes->count; i++)
    {
        allocPage(m, m->processes->processList[i]);
    }

    addNewProcess(m);
}