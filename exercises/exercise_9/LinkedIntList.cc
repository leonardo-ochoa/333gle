/*
 * Copyright ©2023 Leonardo Ochoa
 */
// Leonardo Ochoa
// lochoa2
#include "LinkedIntList.h"

namespace intlist333 {

  LinkedIntList::LinkedIntList() : num_elements_(0),
                                  head_(nullptr), tail_(nullptr)  {}

  int LinkedIntList::num_elements() const {
    return num_elements_;
  }

  void LinkedIntList::Push(const int payload) {
    shared_ptr<Node> ln(new Node());
    ln->payload = unique_ptr<int>(new int (payload));
    if (num_elements_ == 0) {
      ln->next = nullptr;
      head_ = ln;
      tail_ = ln;
    } else {
      head_->prev = ln;
      ln->next = head_;
      head_ = ln;
    }
    num_elements_++;
  }

  void LinkedIntList::Append(const int payload) {
    shared_ptr<Node> ln(new Node());
    ln->payload = unique_ptr<int>(new int (payload));
    ln->next = nullptr;
    if (num_elements_ == 0) {
      head_ = ln;
      tail_ = ln;
    } else {
      tail_->next = ln;
      ln->prev = tail_;
      tail_ = ln;
    }
    num_elements_++;
  }

  bool LinkedIntList::Pop(int* const payload_ptr) {
    if (num_elements_ == 0) {
      return false;
    }
    *payload_ptr = *head_->payload;
    if (num_elements_ == 1) {
      head_ = nullptr;
      tail_ = nullptr;
    } else {
      head_ = head_->next;
    }
    num_elements_--;
    return true;
  }

  bool LinkedIntList::Slice(int* const payload_ptr) {
    if (num_elements_ == 0) {
      return false;
    }
    *payload_ptr = *tail_->payload;
    if (num_elements_ == 1) {
      head_ = nullptr;
      tail_ = nullptr;
    } else {
      tail_ = tail_->prev.lock();
      tail_->next = nullptr;
    }
    num_elements_--;
    return true;
  }

}   // namespace intlist333
