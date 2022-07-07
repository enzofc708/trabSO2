typedef struct Process
{
    PagesList* pages;
} Process;

Process* createProcess(){
    Process* pointer = (Process*) malloc(sizeof(Process));
    pointer->pages = createPageList();
    for (int i = 0; i < PAGES_PER_PROCESS; i++)
    {
        Page* newPage = createPage();
        addPage(pointer->pages, newPage);
    }
    return pointer;
}

PagesList* getPresentPages(Process* p){
    PagesList* presentPages = createPageList();
    for (int i = 0; i < p->pages->count; i++)
    {
        if(p->pages->list[i]->present)
            addPage(presentPages, p->pages->list[i]);
    }
    return presentPages;
}

Page* getRandomPage(Process* p){
    return p->pages->list[rand() % p->pages->count];
}