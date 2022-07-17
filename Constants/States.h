//Process States

enum States {
    NewState,       //Process is waiting to be allocated
    RunningState,   //Process is currently running
    BlockedState    //Process has stopped executing
};