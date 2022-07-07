//Structure responsible for dealing with processes and its pages, the total
//time elapsed and the memory frames.
typedef struct MemoryManager
{
    ProcessList* processes;
    int currentTime;
    FramesList* frames;
} MemoryManager;

//Instantiates a MemoryManager and returns a pointer to it
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

//Creates a new Process and adds it to the processes list
void addNewProcess(MemoryManager* m){
    Process* newProcess = createProcess();
    add(m->processes, newProcess);
}

//Allocates a random Page from a specified Process in the memory
void allocPage(MemoryManager* m, Process* p){  
    Page* rPage = getRandomPage(p);
    if(rPage->present){                             //update reference if the process is already allocated
        rPage->lastReference = m->currentTime; 
        return;
    }
    int emptyIndex = findEmpty(m->frames);

    if (emptyIndex == -1){
        //TODO: Implement swapping algorithm
    }

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

//Controls the period of time when either a process is
//created or requests a page allocation
void iteration(MemoryManager* m){
    m->currentTime += 3;
    for (int i = 0; i < m->processes->count; i++)
    {
        allocPage(m, m->processes->processList[i]);
    }

    addNewProcess(m);
}