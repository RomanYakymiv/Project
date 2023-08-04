#include <iostream>
#include <C:\Users\roman\source\repos\StaticLibV2\Header.h>

int main() {
    const std::string searchDir = "C:/";
    std::string targetFile;
    std::cout << "Enter target file: ";
    std::cin >> targetFile;
    startSearch(searchDir, targetFile);

    return 0;
}   