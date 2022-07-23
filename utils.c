#include "utils.h"
#include "libft.h"

#include <time.h>

int64_t get_time()
{
	struct timespec tms;

    if (clock_gettime(CLOCK_REALTIME, &tms)) {
        return -1;
    }
    
    int64_t millisec = tms.tv_sec * 1000;

    millisec += tms.tv_nsec/1000000;

    if (tms.tv_nsec % 1000000 >= 500000) {
        ++millisec;
    }
	return millisec;
}
