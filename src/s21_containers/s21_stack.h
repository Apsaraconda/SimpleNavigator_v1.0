#ifndef SRC_S21_STACK_H
#define SRC_S21_STACK_H

#include "s21_list.h"

namespace s21 {
template <typename T>
class stack {
 public:
  /*------------- STACK MEMBER TYPE -------------*/
  using value_type = T;  // defines the type of an element
  using reference = T&;  // defines the type of the reference to an element
  using const_reference =
      const T&;              // defines the type of the constant reference
  using size_type = size_t;  // defines the type of the container size

  /*------------- STACK CONSTRUCTORS -------------*/

  // Default constructor, creates empty stack
  stack() : list_() {}

  // Initializer list constructor, creates stack initizialized
  stack(std::initializer_list<value_type> const& items) : list_(items) {}

  // Copy constructor
  stack(const stack& s) : list_(s.list_) {}

  // Move constructor
  stack(stack&& s) : list_(std::move(s.list_)) {}

  // Destructor
  ~stack() = default;

  // Assignment operator overload for coping an object
  stack& operator=(const stack& s) {
    list_ = s.list_;
    return *this;
  }

  // Assignment operator overload for moving object
  stack& operator=(stack&& s) noexcept {
    list_ = std::move(s.list_);
    return *this;
  };

  /*------------- STACK ELEMENT ACCESS -------------*/

  // Access the head
  const_reference top() const noexcept { return list_.back(); }

  // Checks whether the container is empty
  bool empty() const noexcept { return list_.empty(); }

  // Returns the number of elements
  size_type size() const noexcept { return list_.size(); }

  // Inserts element at the head
  void push(const_reference value) noexcept { list_.push_back(value); }

  // Removes the head
  void pop() noexcept { list_.pop_back(); }

  // Swaps the contents
  void swap(stack& other) noexcept { list_.swap(other.list_); }

  // Appends new elements to the top of the container
  template <typename... Args>
  void insert_many_front(Args&&... args) {
    list_.insert_many_front(std::forward<Args>(args)...);
  }

 private:
  s21::list<T> list_;
};  // stack
}  // namespace s21

#endif  // SRC_S21_STACK_H