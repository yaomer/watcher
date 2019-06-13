#include <unistd.h>
#include "Watcher.h"

int main()
{
    Watcher wcr;
    while (true) {
        wcr.find();
        wcr.watch();
        sleep(30);
    }
}
