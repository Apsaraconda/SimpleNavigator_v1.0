#ifndef SRC_S21_LIST_H
#define SRC_S21_LIST_H

#include <initializer_list>
#include <limits>
#include <utility>

namespace s21 {
template <typename T>
class list {
  class ListNode;
  class ListIterator;
  class ListConstIterator;

 public:
  /*------------- LIST MEMBER TYPE -------------*/

  using value_type = T;  // defines the type of an element
  using reference = T&;  // defines the type of the reference to an element
  using const_reference =
      const T&;  // defines the type of the constant reference
  using iterator =
      ListIterator;  // defines the type for iterating through the container
  using const_iterator = ListConstIterator;  // defines the constant type for
                                             // iterating through the container
  using size_type = size_t;  // defines the type of the container size

  /*------------- LIST CONSTRUCTORS -------------*/

  // Default constructor, creates an empty list
  list() : size_(0), head_(new ListNode), tail_(head_) {}

  // Parameterized constructor, creates the list of size n
  explicit list(size_type n) : size_(0) {
    head_ = tail_ = new ListNode;
    for (size_type i = 0; i < n; i++) push_back(0);
  }

  // Initializer list constructor, creates a list initizialized
  list(std::initializer_list<value_type> const& items) : list() {
    for (auto& elem : items) push_back(elem);
  }

  // Copy constructor
  list(const list& l) : list() { *this = l; }

  // Move constructor
  list(list&& l) : list() { *this = std::move(l); }

  // Destructor
  ~list() {
    clear();
    delete head_;
  }

  // Assignment operator overload for moving an object
  list& operator=(list&& l) noexcept {
    if (this != &l) {
      clear();
      swap(l);
    }
    return *this;
  }

  // Assignment operator overload for coping an object
  list& operator=(const list& l) {
    if (this != &l) copy(l);
    return *this;
  }

  /*------------- LIST ELEMENT ACCESS -------------*/

  // Access the first element
  const_reference front() noexcept { return *begin(); }

  const_reference front() const noexcept { return *begin(); }

  // Access the last element
  const_reference back() noexcept { return *(--end()); }

  const_reference back() const noexcept { return *(--end()); }

  /*------------- LIST ITERATORS -------------*/

  // Returns an iterator to the beginning
  iterator begin() noexcept { return iterator(head_); }

  const_iterator begin() const noexcept { return const_iterator(head_); }

  // Returns an iterator to the end
  iterator end() noexcept { return iterator(tail_); }

  const_iterator end() const noexcept { return const_iterator(tail_); }

  /*------------- LIST CAPACITY -------------*/

  // Checks whether the container is empty
  bool empty() const noexcept { return size_ == 0; }

  // Returns the number of elements
  size_type size() const noexcept { return size_; }

  // Returns the maximum possible number of elements
  size_type max_size() const noexcept {
    return ((std::numeric_limits<size_type>::max() / 2) / sizeof(ListNode));
  }

  /*------------- LIST MODIFIERS -------------*/

  // Inserts element into concrete pos and returns the iterator that points to
  // the new element
  iterator insert(iterator pos, const_reference value) {
    ListNode* node_to_add = new ListNode;
    node_to_add->val_ = value;
    node_to_add->next_ = pos.node_;

    if (size_ == 0 || pos == begin()) {
      node_to_add->prev_ = nullptr;
      head_ = node_to_add;
    } else {
      node_to_add->prev_ = pos.node_->prev_;
      pos.node_->prev_->next_ = node_to_add;
    }
    pos.node_->prev_ = node_to_add;
    if (pos == end()) tail_->prev_ = node_to_add;
    size_++;

    return iterator(node_to_add);
  }

  // Adds an element to the end
  void push_back(const_reference value) noexcept { insert(end(), value); }

  // Adds an element to the head
  void push_front(const_reference value) noexcept { insert(begin(), value); }

  // Erases an element at pos
  void erase(iterator pos) noexcept {
    if (size_ > 0) {
      if (pos == --end()) {
        if (pos != head_) {
          pos.node_->prev_->next_ = tail_;
        } else {
          head_ = tail_;
        }
        tail_->prev_ = pos.node_->prev_;
        ;
      } else if (pos == begin()) {
        head_ = pos.node_->next_;
        pos.node_->next_->prev_ = nullptr;
      } else {
        pos.node_->prev_->next_ = pos.node_->next_;
        pos.node_->next_->prev_ = pos.node_->prev_;
      }
      delete pos.node_;
      size_--;
    }
  }

  // Removes the last element
  void pop_back() noexcept { erase(--end()); }

  // Removes the first element
  void pop_front() noexcept { erase(begin()); }

  // Clears the contents
  void clear() noexcept {
    while (size_ > 0) pop_back();
  }

  // Swaps the contents
  void swap(list& other) {
    if (this != &other) {
      std::swap(size_, other.size_);
      std::swap(head_, other.head_);
      std::swap(tail_, other.tail_);
    }
  }

  // Merges two sorted lists
  void merge(list& other) {
    if (this != &other) {
      iterator iter = begin();
      iterator iter_other = other.begin();
      iterator temp;

      while (iter != end() && iter_other != other.end()) {
        if (*iter > *iter_other) {
          insert(iter, *iter_other);
          temp = iter_other;
          ++iter_other;
          other.erase(temp);
        } else {
          ++iter;
        }
      }
      splice(iter, other);
    }
  }

  // Reverses the order of the elements
  void reverse() {
    iterator iter = begin();
    size_type count = size_;
    while (count > 0) {
      if (iter == begin()) {
        iter.node_->prev_ = iter.node_->next_;
        iter.node_->next_ = tail_;
        tail_->prev_ = iter.node_;
        --iter;
      } else if (iter.node_->next_ == tail_) {
        iter.node_->next_ = iter.node_->prev_;
        iter.node_->prev_ = nullptr;
        head_ = iter.node_;
      } else {
        std::swap(iter.node_->next_, iter.node_->prev_);
        --iter;
      }
      count--;
    }
  }

  // Transfers elements from list other starting from pos
  void splice(const_iterator pos, list& other) {
    list* temp = &other;
    iterator iter = (*temp).begin();
    iterator iter2;
    iter2.node_ = pos.node_;
    size_type count = temp->size_;
    while (count > 0) {
      insert(iter2, *iter);
      ++iter;
      (*temp).pop_front();
      count--;
    }
  }

  // Removes consecutive duplicate elements
  void unique() {
    iterator iter = begin();
    iterator iter2;
    while (iter != tail_) {
      iter2 = iter;
      ++iter;
      if (iter.node_->val_ == iter.node_->prev_->val_) erase(iter2);
    }
  }

  // Sorts the elements
  void sort() {
    if (size_ > 1) listSort(begin(), --end());
  }

  // Inserts new elements into the container directly before pos
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args) {
    iterator iter(pos.node_);
    for (auto elem : {std::forward<Args>(args)...}) {
      insert(iter, elem);
    }
    return iter;
  }

  // Appends new elements to the end of the container
  template <typename... Args>
  void insert_many_back(Args&&... args) {
    insert_many(end(), std::forward<Args>(args)...);
  }

  // Appends new elements to the top of the container
  template <typename... Args>
  void insert_many_front(Args&&... args) {
    insert_many(begin(), std::forward<Args>(args)...);
  }

 private:
  size_type size_;  // Mount of elements of the list
  ListNode* head_;  // First element
  ListNode* tail_;  // End of list (next of the last element)

  /*------------- NODE OF LIST -------------*/

  class ListNode {
    friend list;
    // Default constructor, creates empty node
    ListNode() : next_(this), prev_(this), val_(value_type{}) {}
    ~ListNode(){};  // Destructor

    ListNode* next_;  // Points to the next node in the list
    ListNode* prev_;  // Points to the previos node in the list
    value_type val_;  // Data
  };

  /*------------- ITERATORS -------------*/

  // Provide an access to container elements
  class ListIterator {
    friend list;

   public:
    // Default constructor, creates empty iterator
    ListIterator() : node_(nullptr) {}

    // Copy constructor for iterator
    ListIterator(const iterator& other) : node_(other.node_) {}

    // Assignment operator overload for coping object
    iterator& operator=(const iterator& other) {
      node_ = other.node_;
      return *this;
    }

    // Gets the element pointed to by the const iterator;
    reference operator*() { return node_->val_; }

    // Two iterators are equal if they point to the same element
    bool operator==(const iterator& other) { return node_ == other.node_; }

    // Two iterators are not equal if they point to different elements
    bool operator!=(const iterator& other) { return node_ != other.node_; }

    // Moves the iterator forward to the next element
    iterator& operator++() {
      node_ = node_->next_;
      return *this;
    }

    // Moves the iterator backwards to the previous element;
    iterator& operator--() {
      node_ = node_->prev_;
      return *this;
    }

   private:
    // Copy constructor for
    ListIterator(ListNode* l) : node_(l) {}
    ListNode* node_;
  };

  // Provide an access to container elements whithout changes
  class ListConstIterator {
    friend list;

    // Two iterators are equal if they point to the same element
    friend bool operator==(const const_iterator& iter1,
                           const const_iterator& iter2) {
      return iter1.currentNode_ == iter2.currentNode_;
    }

    // Two iterators are not equal if they point to different elements
    friend bool operator!=(const const_iterator& iter1,
                           const const_iterator& iter2) {
      return iter1.currentNode_ != iter2.currentNode_;
    }

   public:
    // Default constructor, creates empty const iterator
    ListConstIterator() : node_(nullptr) {}

    // Copy constructor for iterator
    ListConstIterator(const iterator& other) : node_(other.node_) {}

    // Copy constructor for const iterator
    ListConstIterator(const const_iterator& other) : node_(other.node_) {}

    // Assignment operator overload for coping const object
    const_iterator& operator=(const const_iterator& other) {
      if (this != &other) node_ = other.node_;
      return *this;
    }

    // Gets the element pointed to by the const iterator;
    const_reference operator*() { return node_->val_; }

    // Moves the const iterator forward to the next element
    const_iterator& operator++() {
      node_ = node_->next_;
      return *this;
    }

    // Moves the const iterator backwards to the previous element;
    const_iterator& operator--() {
      node_ = node_->prev_;
      return *this;
    }

   private:
    ListNode* node_;  // Current node
  };

  /*------------- ADDITIONAL FUNCTIONS -------------*/
  // Copy list
  void copy(const list& l) {
    if (this->size_ > 0) clear();
    ListNode* current = l.head_;
    for (size_type i = 0; i != l.size_; i++) {
      push_back(current->val_);
      current = current->next_;
    }
  }

  // Distributes elements
  // Puts to the right all elements greater than the last one
  // Puts to the left all elements less than the last
  iterator partition(iterator start, iterator final) {
    iterator op = start;
    value_type mid = final.node_->val_;
    for (auto it = start; it != final; ++it) {
      if (mid >= it.node_->val_) {
        std::swap(op.node_->val_, it.node_->val_);
        ++op;
      }
    }
    std::swap(op.node_->val_, final.node_->val_);
    return op;
  }

  // Quick sort
  void listSort(iterator start, iterator final) {
    if (final == head_ || start == final) return;
    iterator op = partition(start, final);
    if (op != head_) listSort(start, --op);
    listSort(++op, final);
  }
};  // list
}  // namespace s21

#endif  // SRC_S21_LIST_H