typedef struct{
    Page* list[PAGES_PER_PROCESS];
    int count;
} PagesList;