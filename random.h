#include<stdlib.h>
#include<time.h>
void initialize_random()
{
    time_t mTime; 
    srand((unsigned) time(&mTime));
}
