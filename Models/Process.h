//Class that represents a Process and its pages
typedef struct Process
{
    PagesList* pages;           //List of all the Pages that belong to this Process
    int statusTime;             //The time when this process entered the current status
    enum States currentState;   //Current state of the process
} Process;

//Instantiates a Process and returns a pointer to it
Process* createProcess(){
    Process* pointer = (Process*) malloc(sizeof(Process));
    pointer->pages = createPageList();
    for (int i = 0; i < PAGES_PER_PROCESS; i++)
    {
        Page* newPage = createPage();
        addPage(pointer->pages, newPage);
    }
    pointer->statusTime = 0;
    pointer->currentState = NewState;
    return pointer;
}

//Get all the Pages that are allocated in memory from a given Process 
PagesList* getPresentPages(Process* p){
    PagesList* presentPages = createPageList();
    for (int i = 0; i < p->pages->count; i++)
    {
        if(p->pages->list[i]->present)
            addPage(presentPages, p->pages->list[i]);
    }
    return presentPages;
}

//Get a random Page from a given Process
Page* getRandomPage(Process* p){
    return p->pages->list[rand() % p->pages->count];
}