#include "../include/kernel/Shell.h"

int main(int argc, char* argv[]) {
    hdg::Shell shell;
    shell.exe(argc, argv);
    return 0;
}
