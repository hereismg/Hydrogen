#include "../include/Shell.h"

int main(int argc, char* argv[]) {
    if (argc == 1){
        hdg::Shell::run();
    }
    else if (argc == 2){
        hdg::Shell::run(argv[1]);
    }
    else{
        std::cout << "Hydrogen: Too many arguments!" << std::endl;
    }
    return 0;
}
