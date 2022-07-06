typedef struct{
    int list[MEMORY_FRAMES];
    int count;
} FramesList;

int findEmpty(FramesList* f){
    for(int i = 0; i < MEMORY_FRAMES; i++){
        if(f->list[i] == 0){
            return i;
        }
    }
    return -1;
}