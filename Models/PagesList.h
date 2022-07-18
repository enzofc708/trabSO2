// A basic implementation of a List, specified for the class Page
typedef struct{
    Page* list[PAGES_PER_PROCESS];
    int count;
} PagesList;

//Instantiates a PageList and returns a pointer to it
PagesList* createPageList(){
    PagesList* pointer = (PagesList *) malloc(sizeof(PagesList));
    pointer->count = 0;
    return pointer;
}

//Adds a Page to the list and updates the page counter
void addPage(PagesList* pages, Page* p){
    pages->list[pages->count++] = p;
}

//Gets the Page in the list that was Least Recently Used (hence, LRU)
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

int findPage(PagesList* list, Page* p){
    for(int i = 0; i < list->count; i++){
        if(list->list[i] == p){
            return i;
        }
    }
    return -1;
}