typedef struct Process
{
    PagesList pages;
} Process;

Process* createProcess(){
    Process* pointer = (Process*) malloc(sizeof(Process));
    return pointer;
}