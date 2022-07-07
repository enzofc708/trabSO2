typedef struct{
    int list[MEMORY_FRAMES];
    int count;
} FramesList;

FramesList* createFramesList(){
    FramesList* list = (FramesList *) malloc(sizeof(FramesList));
    list->count = 0;
    return list;
}

int findEmpty(FramesList* f){
    for(int i = 0; i < MEMORY_FRAMES; i++){
        if(f->list[i] == 0){
            return i;
        }
    }
    return -1;
}