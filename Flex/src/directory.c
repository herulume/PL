#include "headers/directory.h"
#include <sys/stat.h>
#include <sys/types.h>

void
createStruct()
{
        mkdir("./output", 0777);
        mkdir("./output/articles", 0777);
        mkdir("./output/tags", 0777);
}
