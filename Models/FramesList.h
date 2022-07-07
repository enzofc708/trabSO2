// A basic implementation of a List
typedef struct{
    int list[MEMORY_FRAMES];    //The list that contains the Frames
    int count;                  // # of elements inside the list
} FramesList;

//Instantiates a FrameList and returns a pointer to it
FramesList* createFramesList(){
    FramesList* list = (FramesList *) malloc(sizeof(FramesList));
    list->count = 0;
    return list;
}

//Finds the 1st empty frame on the List
int findEmpty(FramesList* f){
    for(int i = 0; i < MEMORY_FRAMES; i++){
        if(f->list[i] == 0){
            return i;
        }
    }
    return -1;
}