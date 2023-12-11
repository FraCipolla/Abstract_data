#pragma once

#include <cstddef>
#include <typeinfo>
#include <string>
#include "iterator_traits.hpp"

namespace ft
{
    template<class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
    struct iterator
    {
        typedef Category            iterator_category;
        typedef T                   value_type;
        typedef Distance            difference_type;
        typedef Pointer             pointer;
        typedef Reference           reference;
    }; // struct iterator

    template <class T>
    struct forward_iterator : ft::iterator<ft::forward_iterator_tag, T>
    {
        typedef typename ft::forward_iterator_tag                                       iterator_category;
        typedef typename ft::iterator<ft::forward_iterator_tag, T>::difference_type     difference_type;
        typedef typename ft::iterator<ft::forward_iterator_tag, T>::value_type          value_type;
        typedef typename ft::iterator<ft::forward_iterator_tag, T>::pointer             pointer;
        typedef typename ft::iterator<ft::forward_iterator_tag, T>::reference           reference;
    }; // struct forward_iterator

    template <class T>
    class bidirectional_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
    {
        public:
        typedef typename ft::bidirectional_iterator_tag                                     iterator_category;
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type   difference_type;
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type        value_type;
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::pointer           pointer;
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::reference         reference;

        // constructor and destructor
        bidirectional_iterator() : ptr_(NULL) {}
        bidirectional_iterator(pointer p) : ptr_(p) {}
        bidirectional_iterator(const bidirectional_iterator& other) : ptr_(other.ptr_) {}
        bidirectional_iterator& operator=(bidirectional_iterator const & rhs) {
            if (this != &rhs) {
                this->ptr_ = rhs.ptr_;
            }
            return (*this);
        }
        virtual ~bidirectional_iterator() {};

        // overload operator
        reference operator*() const { return *(this->ptr_); }
        bool operator==(bidirectional_iterator const & rhs) { return this->ptr_ == rhs.ptr_; }
        bool operator!=(bidirectional_iterator const & rhs) { return this->ptr_ != rhs.ptr_; }
        bidirectional_iterator& operator++() { return *(++this->ptr_); }
        bidirectional_iterator operator++(int) { bidirectional_iterator ret(*this); ++this->ptr_; return ret; }
        bidirectional_iterator& operator--() { return *(--this->ptr_); }
        bidirectional_iterator operator--(int) { bidirectional_iterator ret(*this); --this->ptr_; return ret; }

        template <class InputIt>
			friend size_t operator-(InputIt const & lhs, InputIt const & rhs);

        private:
        pointer ptr_;
    }; // struct bidirectional_iterator

    template <class T>
    class random_access_iterator : ft::iterator<ft::random_access_iterator_tag, T>
    {
        public:
        typedef typename ft::random_access_iterator_tag                                     iterator_category;
        typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type   difference_type; 
        typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type        value_type;
        typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer           pointer;
        typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference         reference;

        // constructor and destructor
        random_access_iterator() : ptr_(NULL) {}
        random_access_iterator(pointer p) : ptr_(p) {}
        random_access_iterator(random_access_iterator const & other) : ptr_(other.ptr_) {}
        random_access_iterator& operator=(random_access_iterator const & rhs) {
            if (*this != rhs)
                this->ptr_ = rhs.ptr_;
            return *this;
        }
        virtual ~random_access_iterator() {}

        //overload operator
        reference operator*() { return *(this->ptr_); }
        pointer operator->() { return &(this->operator*()); }
        bool operator==(random_access_iterator const & rhs) { return this->ptr_ == rhs.ptr_; }
        bool operator!=(random_access_iterator const & rhs) { return this->ptr_ != rhs.ptr_; }
        random_access_iterator& operator++() { return *(++this->ptr_); }
        random_access_iterator operator++(int) { random_access_iterator ret(*this); ++this->ptr_; return ret; }
        random_access_iterator& operator--() { return *(--this->ptr_); }
        random_access_iterator operator--(int) { random_access_iterator ret(*this); --this->ptr_; return ret; }
        random_access_iterator operator-(difference_type n) const { return this->ptr_ - n; }
        random_access_iterator operator+(difference_type n) const { return this->ptr_ + n; }
        random_access_iterator operator+=(difference_type n) { this->ptr_ += n; return *this; }
        random_access_iterator operator-=(difference_type n) { this->ptr -= n; return *this; }
        random_access_iterator operator[](int pos) { return (this->ptr_ + pos); } // ???????????????????????????? non sicuro

        // definire fuori dalla classe
        // friend bool operator>(const random_access_iterator & lhs, const random_access_iterator & rhs);
        // friend bool operator>=(const random_access_iterator & lhs, const random_access_iterator & rhs);
        // friend bool operator<(const random_access_iterator & lhs, const random_access_iterator & rhs);
        // friend bool operator<=(const random_access_iterator & lhs, const random_access_iterator & rhs);


        private:
        pointer ptr_;
    }; // class random_access_iterator

    template <class InputIterator>
    class reverse_iterator : ft::iterator<typename InputIterator::iterator_categoray, typename InputIterator::value_type>
    {
        public:
        typedef InputIterator                                                      iterator_type;
        typedef typename ft::iterator_traits<InputIterator>::iterator_category     iterator_category;
        typedef typename ft::iterator_traits<InputIterator>::value_type            value_type;
        typedef typename ft::iterator_traits<InputIterator>::difference_type       difference_type;
        typedef typename ft::iterator_traits<InputIterator>::pointer               pointer;
        typedef typename ft::iterator_traits<InputIterator>::reference             reference;

        reverse_iterator() {}
        explicit reverse_iterator(iterator_type it) : it_(it) {}
        template <class Iter>
        reverse_iterator(const reverse_iterator<Iter>& rev_it) : it_(rev_it.base()) {}
        virtual ~reverse_iterator() {}

        // member functions
        iterator_type base() const { return this->it_; }
        reference operator*() const { return *(this->it_ - 1); }
        reverse_iterator operator+(difference_type n) const { return reverse_iterator(this->it_ - n); }
        reverse_iterator& operator++() { --this->it_; return *this; }
        reverse_iterator operator++(int) {
            reverse_iterator temp = *this;
            ++(*this);
            return temp;
        }
        reverse_iterator& operator+=(difference_type n) {
            this->it_ -= n;
            return *this;
        }
        reverse_iterator operator-(difference_type n) const { return reverse_iterator(this->it_ + n); }
        reverse_iterator operator--() { ++(*this); return *this; }
        reverse_iterator operator--(int) {
            reverse_iterator temp = *this;
            --(*this);
            return temp;
        }
        reverse_iterator operator-=(difference_type n) {
            *this += n;
            return *this;
        }
        pointer operator->() const { return &(operator*()); }
        reference operator[](difference_type n) { return base()[-n-1]; }

        // non-member functions overloads
        // template <class Iterator>
        // bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);
        // template <class Iterator>
        // bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);
        // template <class Iterator>
        // bool operator<  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);
        // template <class Iterator>
        // bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);
        // template <class Iterator>
        // bool operator>  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);
        // template <class Iterator>
        // bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);
        // template <class Iterator>
        // reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it);
        // template <class Iterator>
        // typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);

        private:
        iterator_type it_;
    }; // class reverse_iterator

    template <class InputIterator>
	typename ft::iterator_traits<InputIterator>::difference_type distance(InputIterator first, InputIterator last)
	{
		typename ft::iterator_traits<InputIterator>::difference_type ret = 0;

		while (first++ != last)
			ret++;
		return (ret);
	}

	template <class InputIterator1, class InputIterator2>
	typename ft::iterator_traits<InputIterator1>::difference_type
	distance(InputIterator1 first, InputIterator2 last)
	{
		typename ft::iterator_traits<InputIterator1>::difference_type ret = 0;

		while (first++ != last)
			ret++;
		return (ret);
	}
}; // namespace ft

// prova senza definire il tipo di iteratore
template<class Itlhs, class Itrhs>
bool operator>(Itlhs & lhs, Itrhs & rhs) {
    return lhs() > rhs() ? true : false;
}