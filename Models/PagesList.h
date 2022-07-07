typedef struct{
    Page* list[PAGES_PER_PROCESS];
    int count;
} PagesList;

PagesList* createPageList(){
    PagesList* pointer = (PagesList *) malloc(sizeof(PagesList));
    pointer->count = 0;
    return pointer;
}

void addPage(PagesList* pages, Page* p){
    pages->list[pages->count++] = p;
}

Page* getLRUPage(PagesList* p){
    Page* lruPage = p->list[0];
    for (int i = 1; i < p->count; i++)
    {
        if(p->list[i]->lastReference < lruPage->lastReference){
            lruPage = p->list[i];
        }
    }

    return lruPage;     
}