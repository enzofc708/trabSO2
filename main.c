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
    srand(time(NULL));

    MemoryManager* m = createManager();

    while(1==1)
    {
        iteration(m);
    }
    

    return 0;
}
