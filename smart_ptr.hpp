#pragma once

#include <iostream>

namespace sp
{
  template <typename T>
    class smart_ptr
    {
      public:
        using element_type = T;

        smart_ptr(); // nullptr
        smart_ptr(const element_type &element);
        smart_ptr(const smart_ptr &other);
        smart_ptr(smart_ptr &&other);
        ~smart_ptr();

        smart_ptr& operator=(const element_type& elemeent);
        smart_ptr& operator=(const smart_ptr& other);
        smart_ptr& operator=(smart_ptr&& other);

      protected:
        element_type *pointer_;
        bool *state_;
    };
}

template <typename T>
sp::smart_ptr<T>::smart_ptr() : pointer_{nullptr}, state_{new bool{false}}
{}

  template <typename T>
sp::smart_ptr<T>::smart_ptr(const element_type &el) : smart_ptr()
{
  this->pointer_ = new element_type(el);
}

template <typename T>
sp::smart_ptr<T>::smart_ptr(const smart_ptr &other) :
  pointer_{other.pointer_}, state_{other.state_}
{}

template <typename T>
sp::smart_ptr<T>::smart_ptr(smart_ptr &&other) : smart_ptr{other}
{
  other = smart_ptr();
}

  template <typename T>
sp::smart_ptr<T>::~smart_ptr()
{
  if (this->pointer_ != nullptr) {
    if (*this->state_) {
      delete this->pointer_;
    }
  }
}

  template <typename T>
sp::smart_ptr<T>& sp::smart_ptr<T>::operator=(const element_type& el)
{
  this->pointer_ = new element_type{el};
  return *this;
}

  template <typename T>
sp::smart_ptr<T>& sp::smart_ptr<T>::operator=(const smart_ptr& other)
{
  this->pointer_ = other.pointer_;
  return *this;
}

  template <typename T>
sp::smart_ptr<T>& sp::smart_ptr<T>::operator=(smart_ptr&& other)
{
  this->pointer_ = other.pointer_;
  other = smart_ptr();
  return *this;
}
