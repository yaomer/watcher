#include <unistd.h>
#include <iostream>
#include "Watcher.h"

int main()
{
    Watcher wcr;
    while (true) {
        wcr.find();
        wcr.watch();
    }
}
