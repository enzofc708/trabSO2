#include <stdlib.h>
#include <time.h>

#include "Constants/Constants.h"
#include "Constants/States.h"
#include "Models/Page.h"
#include "Models/PagesList.h"
#include "Models/Process.h"
#include "Models/ProcessList.h"
#include "Models/FramesList.h"
#include "Models/MemoryManager.h"

int main(int argc, char const *argv[])
{
    //Seed the random number geenrator
    srand(time(NULL));

    MemoryManager* m = createManager();

    //Get arguments from console
    if(argc < 2){
        printf("Usage: %s <number_of_iterations>\n", argv[0]);
        return 1;
    }

    int num_iters = atoi(argv[1]);
    if (num_iters < 0)
    {
        printf("Number of iterations should not be less than 0.\n");
        return 1;
    }

    for (int i = 0; i < num_iters; i++)   
    {
        iteration(m);
    }
    

    return 0;
}
