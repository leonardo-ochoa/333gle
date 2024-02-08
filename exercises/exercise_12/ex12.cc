/*
 * Copyright ©2023 Justin Hsia.  All rights reserved.  Permission is
 * hereby granted to students registered for University of Washington
 * CSE 333 for use solely during Winter Quarter 2023 for purposes of
 * the course.  No other use, copying, distribution, or modification
 * is permitted without prior written consent. Copyrights for
 * third-party components of this work must be honored.  Instructors
 * interested in reusing these course materials should contact the
 * author.
 */

// Leonardo Ocho
// lochoa2@uw.edu
#include <iostream>
#include <thread> // NOLINT [build/c++11]
#include <chrono> // NOLINT [build/c++11]
#include <cstdlib>
#include <string>
#include <ctime>

#include "SimpleQueue.h"

using std::cout;
using std::endl;
using std::string;
using std::thread;

static constexpr int kNumSnacks = 6;
static SimpleQueue queue;
static unsigned int seed = time(nullptr);
static pthread_mutex_t write_lock;

// Thread safe print that prints the given str on a line
// Arguments:
// - str: the string to print out
void thread_safe_print(const string& str);

// Produces kNumSnacks snacks of the given type
// You should NOT modify this method at all
// Arguments:
// - snack_type: the type of snack
void producer(const string& snack_type);

// Eats 2 * kNumSnacks snacks
// You should NOT modify this method at all
void consumer();

// used for processing producers
void* Producer_Thread(void* arg);

// used for processing consumers
void* Consumer_Thread(void* arg);

int main(int argc, char** argv) {
  pthread_mutex_init(&write_lock, nullptr);
  // Your task: Make the two producers and the single consumer
  // all run concurrently (hint: use pthreads)
  pthread_t p1, p2, c;
  char piroshki[] = "piroshki";
  char nalysnyky[] = "nalysnyky";
  pthread_create(&p1, nullptr, &Producer_Thread, piroshki);
  pthread_create(&p2, nullptr, &Producer_Thread, nalysnyky);
  pthread_create(&c, nullptr, &Consumer_Thread, nullptr);
  pthread_join(p1, nullptr);
  pthread_join(p2, nullptr);
  pthread_join(c, nullptr);
  pthread_mutex_destroy(&write_lock);
  return EXIT_SUCCESS;
}

void thread_safe_print(const string& str) {
  pthread_mutex_lock(&write_lock);
  // Only one thread can hold the lock at a time, making it safe to
  // use cout. If we didn't lock before using cout, the order of things
  // put into the stream could be mixed up.
  cout << str << endl;
  pthread_mutex_unlock(&write_lock);
}

void producer(const string& snack_type) {
  for (int i = 0; i < kNumSnacks; i++) {
    queue.Enqueue(snack_type);
    thread_safe_print(snack_type + " ready!");
    int sleep_time = rand_r(&seed) % 500 + 1;
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
  }
}

void consumer() {
  for (int i = 0; i < kNumSnacks * 2; i++) {
    bool successful = false;
    string snack_type;
    while (!successful) {
      while (queue.IsEmpty()) {
        // Sleep for a bit and then check again
        int sleep_time = rand_r(&seed) % 800 + 1;
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
      }
      successful = queue.Dequeue(&snack_type);
    }
    thread_safe_print(snack_type + " eaten!");
  }
}

void* Producer_Thread(void* arg) {
  char* snack = reinterpret_cast<char*>(arg);
  producer(snack);
  pthread_exit(nullptr);
}

void* Consumer_Thread(void* arg) {
  consumer();
  pthread_exit(nullptr);
}
