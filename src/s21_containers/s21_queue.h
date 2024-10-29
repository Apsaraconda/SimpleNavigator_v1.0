#ifndef SRC_S21_QUEUE_H
#define SRC_S21_QUEUE_H

#include "s21_list.h"

namespace s21 {
template <typename T>
class queue {
 public:
  /*------------- QUEUE MEMBER TYPE -------------*/
  using value_type = T;  // defines the type of an element
  using reference = T&;  // defines the type of the reference to an element
  using const_reference =
      const T&;              // defines the type of the constant reference
  using size_type = size_t;  // defines the type of the container size

  /*------------- QUEUE CONSTRUCTORS -------------*/

  // Default constructor, creates empty queue
  queue() : list_() {}

  // Initializer list constructor, creates queue initizialized
  queue(std::initializer_list<value_type> const& items) : list_(items) {}

  // Copy constructor
  queue(const queue& q) : list_(q.list_) {}

  // Move constructor
  queue(queue&& q) : list_(std::move(q.list_)) {}

  // Destructor
  ~queue() = default;

  // Assignment operator overload for coping an object
  queue& operator=(const queue& q) {
    list_ = q.list_;
    return *this;
  }

  // Assignment operator overload for moving object
  queue& operator=(queue&& q) noexcept {
    list_ = std::move(q.list_);
    return *this;
  };

  /*------------- QUEUE ELEMENT ACCESS -------------*/

  // Access the first element
  const_reference front() const noexcept { return list_.front(); }

  // Access the last element
  const_reference back() const noexcept { return list_.back(); }

  // Checks whether the container is empty
  bool empty() const noexcept { return list_.empty(); }

  // Returns the number of elements
  size_type size() const noexcept { return list_.size(); }

  // Inserts element at the end
  void push(const_reference value) noexcept { list_.push_back(value); }

  // Removes the first element
  void pop() noexcept { list_.pop_front(); }

  // Swaps the contents
  void swap(queue& other) noexcept { list_.swap(other.list_); }

  // Appends new elements to the end of the container
  template <typename... Args>
  void insert_many_back(Args&&... args) {
    list_.insert_many_back(std::forward<Args>(args)...);
  }

 private:
  s21::list<T> list_;
};  // queue
}  // namespace s21

#endif  // SRC_S21_QUEUE_H