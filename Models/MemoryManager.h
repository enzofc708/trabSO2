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
void addNewProcess(MemoryManager* m, FILE* log){
    if(m->processes->count == MAX_PROCESSES) return;
    Process* newProcess = createProcess();
    add(m->processes, newProcess);
    fprintf(log, "New process created! PID = %d.\n", m->processes->count - 1);
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
void allocPage(MemoryManager* m, Process* p, FILE* log){
    if(p->currentState == NewState){                //Updates state if process is new
        p->currentState = RunningState;
        p->statusTime = m->currentTime;
        fprintf(log, "New process is now running.\n");
    }
    else if (p->currentState == BlockedState)
    {
        if(newProcessesCount(m) > 0){
            fprintf(log, "Process is blocked and there are still new processes to be allocated. Skipping.\n");
            return;       //If there are still new processes, those blocked will remain blocked
        }
        if(findEmpty(m->frames) >= 0){
            fprintf(log, "Process is blocked and there are still empty frames available. Skipping.\n");
            return;
        }
        
        Process* oldest = getOldestRunningProcess(m->processes, log);
        deallocProcessPages(m, oldest);
        p->currentState = RunningState;
        fprintf(log, "Blocked process returned to memory.\n");
    }
       
    Page* rPage = getRandomPage(p, log);
    if(rPage->present){                             //update reference if the process is already allocated
        fprintf(log, "Page already allocated. Updating reference.\n");
        rPage->lastReference = m->currentTime; 
        return;
    }
    int emptyIndex = findEmpty(m->frames);

    if(emptyIndex == -1){
        Process* oldest = getOldestRunningProcess(m->processes, log);
        deallocProcessPages(m, oldest);
        emptyIndex = findEmpty(m->frames);
    }

    PagesList* presentPages = getPresentPages(p);
    if(presentPages->count == WORKING_SET_LIMIT){  
        fprintf(log, "Working set limit restriction. Applying LRU algorithm.\n");
        Page* lruPage = getLRUPage(presentPages);
        fprintf(log, "LRU completed!. Page %d was chosen to be replaced.\n", findPage(p->pages, lruPage));
        emptyIndex = lruPage->frameNumber;
        lruPage->present = 0;
    }
    m->frames->list[emptyIndex] = 1;
    rPage->present = 1;
    rPage->lastReference = m->currentTime;
    rPage->frameNumber = emptyIndex;
    fprintf(log, "Page allocated on frame %d.\n", emptyIndex);
}

//Controls the period of time when either a process is
//created or requests a page allocation
void iteration(MemoryManager* m, FILE* log){
    fprintf(log, "-------------------------\n");
    fprintf(log, "Time = %d\n", m->currentTime);
    fprintf(log, "-------------------------\n");
    for (int i = 0; i < m->processes->count; i++)
    {
        fprintf(log, "Allocating page for process %d.\n", i);
        allocPage(m, m->processes->processList[i], log);
        fprintf(log, "Allocation for process %d completed.\n", i);
    }

    addNewProcess(m, log);
    m->currentTime += 3;
}