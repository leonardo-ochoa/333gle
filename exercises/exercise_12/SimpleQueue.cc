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
#include "SimpleQueue.h"

#include <memory>

using std::string;
using std::shared_ptr;

SimpleQueue::SimpleQueue() {
  this->size_ = 0;
  this->front_.reset();
  this->end_.reset();
  pthread_mutex_init(&pmt, nullptr);
}

SimpleQueue::~SimpleQueue() {
  pthread_mutex_destroy(&pmt);
}

void SimpleQueue::Enqueue(const string& item) {
  pthread_mutex_lock(&pmt);
  shared_ptr<Node> new_node(new Node());
  new_node->next.reset();
  new_node->item = item;
  if (this->end_) {
    this->end_->next = new_node;
  } else  {
    this->front_ = new_node;
  }
  this->end_ = new_node;
  this->size_++;
  pthread_mutex_unlock(&pmt);
}

bool SimpleQueue::Dequeue(string* const result) {
  pthread_mutex_lock(&pmt);
  if (this->size_ == 0) {
    pthread_mutex_unlock(&pmt);
    return false;
  }
  *result = this->front_->item;
  if (this->end_ == this->front_) {
    this->end_ = this->front_ = this->front_->next;
  } else {
    this->front_ = this->front_->next;
  }
  this->size_--;
  pthread_mutex_unlock(&pmt);
  return true;
}

int SimpleQueue::Size() const {
  pthread_mutex_lock(&pmt);
  bool size = size_ == 0;
  pthread_mutex_unlock(&pmt);
  return size;
}

bool SimpleQueue::IsEmpty() const {
  pthread_mutex_lock(&pmt);
  bool empty = size_ == 0;
  pthread_mutex_unlock(&pmt);
  return empty;
}
