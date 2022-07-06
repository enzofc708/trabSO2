typedef struct{
    Page* list[PAGES_PER_PROCESS];
    int count;
} PagesList;

PagesList* createPageList(){
    PagesList* pointer = (PagesList *) malloc(sizeof(PagesList));
    pointer->count = 0;
    return pointer;
}