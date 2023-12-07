#pragma once

#include <memory>
#include <stdexcept>
#include <iostream>


namespace ft
{
	template<typename T, typename Allocator = std::allocator<T> >
	class list
	{
		public:
		typedef T								value_type;
		typedef Allocator						allocator_type;
		typedef std::size_type					size_type;
		typedef std::ptrdiff_t					difference_type;
		typedef value_type&						reference;
		typedef const value_type&				const_reference;
		typedef value_type*						pointer;
		typedef const value_type*				const_pointer;

		// Constructor
		explicit list(const allocator_type& alloc = allocator_type()) : alloc_(alloc), start_(NULL), end_(NULL), capacity_(NULL) {}
		explicit list(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : alloc_(alloc), start_(NULL), end_(NULL), capacity_(NULL) {
			if (n >= 0 && n < allocator_type().max_size()) {
				this->start_ = alloc_.allocate(n);
				this->capacity_ = this->start_ + n;
				this->end_ = this->start_;
				for (; n; n--) alloc_.construct(_end++, val);
			} else {
				std::__throw_length_error("ft::list");
			}
		}
		template<class InputIterator> list(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
			:
			alloc_(alloc),
			start_(NULL),
			end_(NULL),
			capacity_(NULL)
		{

		}
		
		list(const list& x) : alloc_(x.alloc_), start_(NULL), end_(NULL), capacity_(NULL) {
			const size_type cap = x.capacity();
			if (cap == 0)
				return ;
			this->start_ = alloc_.allocate(cap);
			this->end_ = this->start_;
			this->capacity_ = this->start_ + cap;
			for (pointer i = x.begin(); i != x.end(); i++) {
				this->alloc_.construct(this->end_, *i);
			}
		}

		private:
		allocator_type	alloc_;
		pointer		start_;
		pointer		end_;
		pointer		capacity_;
	}
}; //namespace ft
