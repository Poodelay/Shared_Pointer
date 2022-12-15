#pragma once

#include "smart_ptr.hpp"
#include <cstddef> // std::size_t
#include <iostream>

template <typename T>
class shared_ptr : sp::smart_ptr<T>
{
  public:
    using typename sp::smart_ptr<T>::element_type;
    using size_type = std::size_t;

    shared_ptr();
    shared_ptr(const element_type& element);
    shared_ptr(const shared_ptr &other);
    shared_ptr(shared_ptr &&other);
    ~shared_ptr();

    shared_ptr& operator=(const element_type& element);
    shared_ptr& operator=(const shared_ptr& other);
    shared_ptr& operator=(shared_ptr&& other);

    size_type use_count() const;

  private:
    size_type *count_;
};

  template <typename T>
shared_ptr<T>::shared_ptr() : sp::smart_ptr<T>()
{
  this->count_ = nullptr;
}

  template <typename T>
shared_ptr<T>::shared_ptr(const element_type& el) : sp::smart_ptr<T>(el)
{
  this->count_ = new size_type(1);
}

  template <typename T>
shared_ptr<T>::shared_ptr(const shared_ptr& other) : sp::smart_ptr<T>(other)
{
  ++(*(this->count_ = other.count_));
  //std::cout << *this->count_ << std::endl;
}

  template <typename T>
shared_ptr<T>::shared_ptr(shared_ptr&& other) : sp::smart_ptr<T>(other)
{
  this->count_ = other.count_;
  other.count_ = nullptr;
}

  template <typename T>
shared_ptr<T>::~shared_ptr()
{
  std::cout << "shared" << std::endl;
  if (this->count_ != nullptr) {
    if (*this->count_ == 1) {
      delete this->count_;
      *this->state_ = true;
    } else { --(*this->count_); }
  }
}

  template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(const element_type& el)
{
  if (*(this->count_) == 1)
  {
    delete this->pointer_;
    delete this->count_;
  }
  else if (*(this->count_) != 0)
  {
    --(*(this->count_));
  }
  this->count_ = new size_type(1);
  this->pointer_ = new element_type{el};
  return *this;
}

  template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr& other)
{
  //std::cout << "a" << std::endl;

  if (this->count_ != nullptr) {
    if (*this->count_ == 1) { this->~shared_ptr(); }
    else { --(*this->count_); }
  }

  //std::cout << "b" << std::endl;

  this->pointer_ = other.pointer_;
  this->state_ = other.state_;
  ++(*(this->count_ = other.count_));

  //std::cout << "c" << std::endl;

  return *this;
}

  template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr&& other)
{
  if (*(this->count_) == 1)
  {
    delete this->count_;
    delete this->pointer_;
  }
  else if (this->count_ != nullptr)
    --(this->count_);
  this->pointer_ = other.pointer_;
  this->count_ = other.count_;
  other = shared_ptr();
  return *this;
}

template <typename T>
typename shared_ptr<T>::size_type shared_ptr<T>::use_count() const
{
  if (this->count_ != nullptr)
    return *(this->count_);
  else
    return 0;
}
