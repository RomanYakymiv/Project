#include <thread>
#include <queue>
#include <atomic>
#include <filesystem>
#include <iostream>
#include "Header.h"

const int MAX_THREADS = 8;
std::queue<std::string> fileQ;
std::atomic<bool> found(false);

void searchFile(const std::string& directory, const std::string& filename) {
    std::queue<std::string> q;
    q.push(directory);
    while (!q.empty() && !found) {
        std::string currentPath = q.front();
        q.pop();
        try {
            for (const auto& entry : std::filesystem::directory_iterator(currentPath, std::filesystem::directory_options::skip_permission_denied)) {
                if (std::filesystem::path(entry).filename() == filename) {
                    std::cout << std::endl << std::filesystem::path(entry) << std::endl;
                    found = true;
                }
                if (entry.is_directory() && std::filesystem::status(currentPath).permissions() == std::filesystem::perms::all) {
                    q.push(entry.path().string());
                }
            }
        }
        catch (const std::filesystem::filesystem_error& e) {
            std::cerr << "filesystem error: " << e.what() << " [" << currentPath << "]" << std::endl;
        }
    }
}

void startSearch(const std::string& directory, const std::string& filename) {
    for (const auto& entry : std::filesystem::directory_iterator(directory, std::filesystem::directory_options::skip_permission_denied)) {
        if (std::filesystem::path(entry).filename() == filename) {
            std::cout << std::endl << std::filesystem::path(entry) << std::endl;
            found = true;
        }
        if (entry.is_directory()) {
            fileQ.push(entry.path().string());
        }
    }
    std::vector<std::thread> search_threads(MAX_THREADS);
    while (!fileQ.empty() && !found) {
        for (int i = 0; i < MAX_THREADS; i++) {
            if (fileQ.empty()) { break; }
            std::string currFile = fileQ.front();
            fileQ.pop();
            search_threads[i] = std::thread(searchFile, currFile, filename);
        }

        for (std::thread& thread : search_threads) {
            if (thread.joinable()) {
                thread.join();
            }
        }
    }
}