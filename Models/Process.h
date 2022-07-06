typedef struct Process
{
    PagesList* pages;
} Process;

Process* createProcess(){
    Process* pointer = (Process*) malloc(sizeof(Process));
    pointer->pages = createPageList();
    return pointer;
}

int findProcessPages(Process* p){
    int pCount = 0;
    for (int i = 0; i < p->pages->count; i++)
    {
        if(p->pages->list[i]->present)
            pCount++;
    }
    return pCount;
}