/*
 * Copyright ©2023 Leonardo Ochoa
 */
// Leonardo Ochoa
// lochoa2
#ifndef LINKEDINTLIST_H_
#define LINKEDINTLIST_H_

#include <memory>
#include "IntList.h"
using std::shared_ptr;
using std::unique_ptr;
using std::weak_ptr;

namespace intlist333 {

// LinkedIntList is an implementation of
// the IntList abstract class. Implemented using
// a doubly linked list
class LinkedIntList : public IntList {
 public:
  // default 0 argument constructor
  LinkedIntList();

  // disabled copy constructor
  LinkedIntList(const LinkedIntList& copy) = delete;

  // disabled assignment operator
  LinkedIntList& operator=(const LinkedIntList& other) = delete;

  // Returns the number of elements in the LinkedIntList
  int num_elements() const override;

  // Pushes the given integer(payload) into the front of the this List
  void Push(const int payload) override;

  // Pushes the given integer(payload) into the back of the this List
  void Append(const int payload) override;

  // Removes the first element in the List and returns it through payload_ptr.
  // Returns true if removal is successful and false if an element cannot be
  // removed.
  bool Pop(int* const payload_ptr) override;

  // Removes the last element in the List and returns it through payload_ptr.
  // Returns true if removal is successful and false if an element cannot be
  // removed.
  bool Slice(int* const payload_ptr) override;

  // Destructor should be kept default
  // since smart pointers should clean
  // everything up for us
  virtual ~LinkedIntList() = default;

 private:
  int num_elements_;
  // Note that these should be modified
  // to use smart pointers at some point
  struct Node {
    unique_ptr<int> payload;
    shared_ptr<Node> next;
    weak_ptr<Node> prev;
  };
  shared_ptr<Node> head_;
  shared_ptr<Node> tail_;
};

}  // namespace intlist333

#endif  // LINKEDINTLIST_H_
