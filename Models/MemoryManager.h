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

//Counts the number of processes that have never been allocated
int newProcessesCount(MemoryManager* m){
    int counter = 0;
    for (int i = 0; i < m->processes->count; i++)
    {
        if(m->processes->processList[i]->currentState == NewState){
            counter++;
        }
    }
    return counter;
}

//Deallocates all pages that belong to a given process and mark it as blocked
int deallocProcessPages(MemoryManager* m, Process* p){
    for (int i = 0; i < p->pages->count; i++)
    {
        Page* pointer = p->pages->list[i];
        if (pointer->present)
        {
            pointer->present = 0;
            m->frames->list[pointer->frameNumber] = 0;
        }
    }
    p->currentState = BlockedState;
    p->statusTime = m->currentTime;
}

//Allocates a random Page from a specified Process in the memory
void allocPage(MemoryManager* m, Process* p){
    if(p->currentState == NewState){                //Updates state if process is new
        p->currentState = RunningState;
        p->statusTime = m->currentTime;
    }
    else if (p->currentState == BlockedState)
    {
        if(newProcessesCount(m) > 0) return;       //If there are still new processes, those blocked will remain blocked

        Process* oldest = getOldestRunningProcess();
        deallocProcessPages(m, oldest);    
    }
       
    Page* rPage = getRandomPage(p);
    if(rPage->present){                             //update reference if the process is already allocated
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