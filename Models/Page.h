typedef struct Page
{
    int present;        //Indicates wether the page is loaded in memory or not.
    int frameNumber;    //If the page is loaded in memory, contains the number of the frame where it is located.
} Page;

Page* createPage(){
    Page* pointer = (Page*) malloc(sizeof(Page));
    pointer->present = 0;
    pointer->frameNumber = 0;
    return pointer;
}
