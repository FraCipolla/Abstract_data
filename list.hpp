#pragma once

#include <memory>
#include <iostream>
#include "iterator_types.hpp"

namespace ft
{
template<typename T, typename Allocator = std::allocator<T> >
class list
{
	public:
	typedef T												value_type;
	typedef Allocator										allocator_type;
	typedef std::size_t										size_type;
	typedef std::ptrdiff_t									difference_type;
	typedef value_type&										reference;
	typedef const value_type&								const_reference;
	typedef value_type*										pointer;
	typedef const value_type*								const_pointer;
	typedef ft::bidirectional_iterator<value_type>			iterator;
	typedef ft::bidirectional_iterator<const value_type>	const_iterator;
	typedef ft::reverse_iterator<iterator>					reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;
	
	// member functions
	explicit list(const allocator_type& alloc = allocator_type()) : alloc_(alloc), start_(NULL), end_(NULL), capacity_(NULL) {}
	explicit list(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : alloc_(alloc), start_(NULL), end_(NULL), capacity_(NULL) {
		if (n >= 0 && n < this->max_size()) {
			this->start_ = alloc_.allocate(n);
			this->capacity_ = this->start_ + n;
			this->end_ = this->start_;
			while (n--) alloc_.construct(this->end_++, val);
		} else {
			std::cout << "Error: explicit list(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())" << std::endl;
		}
	}
	template<class InputIterator>
	list(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
		:
		alloc_(alloc),
		start_(NULL),
		end_(NULL),
		capacity_(NULL)
	{
		if (!ft::is_ft_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category>::value)
			throw ft::InvalidIteratorException<typename ft::is_ft_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category>::type>();
		difference_type n = ft::distance(first, last);
		this->start_ = alloc_.allocate(n);
		this->capacity_ = this->start_ + n;
		this->end_ = this->start_;
		for (; n; n--) {
			alloc_.construct(this->end_++, *first++);
		}
	}
	
	list(const list& x) : alloc_(x.alloc_), start_(NULL), end_(NULL), capacity_(NULL) {
		const size_type cap = x.capacity();
		if (cap == 0)
			throw ft::InvalidIteratorException<typename ft::is_ft_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category>::type>();
		this->start_ = alloc_.allocate(cap);
		this->end_ = this->start_;
		this->capacity_ = this->start_ + cap;
		for (pointer i = x.begin(); i != x.end(); i++) {
			this->alloc_.construct(this->end_, *i);
		}
	}
	
	~list() {
		std::cout << "list destructor" << std::endl;
	}

	list& operator=(const list& x) {
		if (*this == x)
			return *this;
		this->clear();
		// if (this->capacity() < x.capactiy())
	}

	// iterators
	iterator begin() { return this->start_; };
	const_iterator begin() const { return this->start_; };
	iterator end() { return this->end_; }
	const_iterator end() const { return this->end_; }
	reverse_iterator rbegin() { return reverse_iterator(this->end_); }
	const_reverse_iterator rbegin() const { return const_reverse_iterator(this->end_); }
	reverse_iterator rend() { return reverse_iterator(this->start_); }
	const_reverse_iterator rend() const { return const_reverse_iterator(this->start_); }
	const_iterator cbegin() const noexcept { return this->start_; }
	const_iterator cend() const noexcept { return this->end_; }
	const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(this->end); }
	const_reverse_iterator crend() const noexcept { return const_reverse_iterator(this->start_); }

	// Capacity
	bool empty() const { return this->capacity_ - this->start_ == 0 ? true : false; }
	size_type size() const { return size_type(this->end_ - this->start_); }
	size_type max_size() const { return allocator_type().max_size(); }

	// Element access
	reference front() { return *this->start_; }
	const_reference front() const { return *this->start_; }
	reference back() { return *(this->end_ - 1); }
	const_reference back() const { return *(this->end_ - 1); }

	// Modifiers
	void clear() {
		while (this->end_ != this->start_) {
			this->alloc_.destroy(--this->end_);
		}
	}
	iterator insert( const_iterator pos, const T& value ) {
		if (this->capacity_ == (this->end_)) {
			pointer newStart = this->alloc_.allocate(this->size() + 1);
			pointer newEnd = newStart;
			while (newEnd != pos) {
				this->alloc_.construct(newEnd++, (*this->start_)++);
			}
			this->alloc_.construct(newEnd++, value);
			while (this->start_ != this->end_) {
				this->alloc_.construct(newEnd++, (*this->start_)++);
			}
			this->clear();
			this->start_ = newStart;
			this->end_ = newEnd;
			this->capacity_ = this->end_;
		} else {
			this->end_++;
			pointer end_cpy = this->end_;
			pointer offset = this->start_ + pos + 1;
			while (--end_cpy != offset) {
				this->alloc_.construct(end_cpy, *end_cpy - 1);
			}
			this->alloc_.construct(this->start_ + pos, value);
		}
	return pos;
	}

	iterator insert( const_iterator pos, size_type count, const T& value ) {

	}

	template< class InputIt >
	iterator insert( const_iterator pos, InputIt first, InputIt last ) {

	}

	template <class InputIterator>
	void assign(InputIterator first, InputIterator last) {
		if (!ft::is_ft_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category>::value)
			return ;
		this->clear();
		size_type capacity = this->capacity_ - this->start_;
		difference_type n = ft::distance(first, last);
		if (n > capacity) {
			this->start_ = alloc_.allocate(n);
			this->capacity_ = this->start_ + n;
			this->end_ = this->start_;
		}
		while (n--) {
			alloc_.construct(this->end_++, *first++);
		}
	}
	
	void assign(size_type n, const value_type& val) {
		this->clear();
		size_type capacity = this->capacity_ - this->start_;
		if (n > this->capacity_) {
			this->alloc_.deallocate(start_, capacity);
			this->start_ = alloc_.allocate(n);
			this->capacity_ = this->start_ + n;
		}
		this->end_ = this->start_;
		while (n--)
			this->alloc_.construct(this->end++, val);
	}

	

	private:
	allocator_type	alloc_;
	pointer		start_;
	pointer		end_;
	pointer		capacity_;
}; // class list
}; //namespace ft
