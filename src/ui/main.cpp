#include "LibraryApp.h"
#include <iostream>

int main() {
    try {
        LibraryApp app;
        app.run();

    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << '\n';
        return 1;

    }

    return 0;
}