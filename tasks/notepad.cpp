#include <pthread.h>
#include <unistd.h>

#include <fstream>
#include <iostream>
#include <string>

std::string buffer;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
bool running = true;

void* autoSave(void*) {
  while (running) {
    sleep(30);
    pthread_mutex_lock(&mtx);
    std::ofstream out("notes_autosave.txt");
    out << buffer;
    pthread_mutex_unlock(&mtx);
  }
  return nullptr;
}

int main() {
  pthread_t t;
  pthread_create(&t, nullptr, autoSave, nullptr);
  std::cout << "Notepad (type ':q' to quit)\n";
  std::string line;
  std::getline(std::cin, line);
  while (true) {
    std::getline(std::cin, line);
    if (line == ":q") break;
    pthread_mutex_lock(&mtx);
    buffer += line + "\n";
    pthread_mutex_unlock(&mtx);
  }
  running = false;
  pthread_join(t, nullptr);
  return 0;
}
