#pragma once

#include <cstddef>
#include <typeinfo>
#include <string>

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

    /* Defines the category of an iterator.
       Each tag is an empty type.
       Iterator category tags carry information
       that can be used to select the most efficient
       algorithms for the specific requirement
       set that is implied by the category.
    */
    struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag	{};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};
	struct contiguous_iterator_tag : public random_access_iterator_tag {};

    template <bool is_valid, typename T>
	struct valid_iterator_tag_res
	{
		typedef T			type;
		const static bool	value = is_valid;
	};

    template <typename T>
	struct is_input_iterator_tagged : public valid_iterator_tag_res<false, T> {};
	template <>
	struct is_input_iterator_tagged<input_iterator_tag> : public valid_iterator_tag_res<true, input_iterator_tag> {};
	template <>
	struct is_input_iterator_tagged<output_iterator_tag> : public valid_iterator_tag_res<true, output_iterator_tag> {};
	template <>
	struct is_input_iterator_tagged<forward_iterator_tag> : public valid_iterator_tag_res<true, forward_iterator_tag> {};
	template <>
	struct is_input_iterator_tagged<bidirectional_iterator_tag> : public valid_iterator_tag_res<true, bidirectional_iterator_tag> {};
	template <>
	struct is_input_iterator_tagged<random_access_iterator_tag> : public valid_iterator_tag_res<true, random_access_iterator_tag> {};
	
    // template <typename T>
	// struct is_ft_iterator_tagged : public valid_iterator_tag_res<false, T> {};
	// template <>
	// struct is_ft_iterator_tagged<random_access_iterator_tag> : public valid_iterator_tag_res<true, random_access_iterator_tag> {};
	// template <>
	// struct is_ft_iterator_tagged< ::std::random_access_iterator_tag> : public valid_iterator_tag_res<true, ::std::random_access_iterator_tag> {};
	// template <>
	// struct is_ft_iterator_tagged<bidirectional_iterator_tag> : public valid_iterator_tag_res<true, bidirectional_iterator_tag> {};
	// template <>
	// struct is_ft_iterator_tagged< ::std::bidirectional_iterator_tag> : public valid_iterator_tag_res<true, ::std::bidirectional_iterator_tag> {};
	// template <>
	// struct is_ft_iterator_tagged<forward_iterator_tag> : public valid_iterator_tag_res<true, forward_iterator_tag> {};
	// template <>
	// struct is_ft_iterator_tagged< ::std::forward_iterator_tag> : public valid_iterator_tag_res<true, ::std::forward_iterator_tag> {};
	// template <>
	// struct is_ft_iterator_tagged<input_iterator_tag> : public valid_iterator_tag_res<true, input_iterator_tag> {};
	// template <>
	// struct is_ft_iterator_tagged< ::std::input_iterator_tag> : public valid_iterator_tag_res<true, ::std::input_iterator_tag> {};
	// template <>
	// struct is_ft_iterator_tagged<output_iterator_tag> : public valid_iterator_tag_res<true, output_iterator_tag> {};
	// template <>
	// struct is_ft_iterator_tagged< ::std::output_iterator_tag> : public valid_iterator_tag_res<true, ::std::output_iterator_tag> {};

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
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, t>::difference_type   difference_type;
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, t>::value_type        value_type;
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, t>::pointer           pointer;
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, t>::reference         reference;

        // constructor and destructor
        bidirectional_iterator() : ptr_(NULL) {}
        bidirectional_iterator(pointer p) : ptr_(p) {}
        bidirectional_iterator(const bidirectional_iterator& other) : ptr_(other.ptr_) {}
        bidirectional_iterator& operator=(const & bidirectional_iterator rhs) {
            if (this != rhs) {
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
        pointer operator() { return this->ptr_; }
        bool operator==(random_access_iterator const & rhs) { return this->ptr_ == rhs.ptr_; }
        bool operator!=(random_access_iterator const & rhs) { return this->ptr_ != rhs.ptr_; }
        random_access_iterator& operator++() { return *(++this->ptr_); }
        random_access_iterator operator++(int) { random_access_iterator ret(*this); ++this->ptr_; return ret; }
        random_access_iterator& operator--() { return *(--this->ptr_); }
        random_access_iterator operator--(int) { random_access_iterator ret(*this); --this->ptr_; return ret; }
        random_access_iterator operator-(difference_type n) const { return this->ptr_ - n; }
        random_access_iterator operator+(difference_type n) const { return this->ptr_ + n; }
        random_access_iterator operator+=(difference_type n) { this->ptr_ += n; return *this; }
        random_access_iterator operator-=(difference_type n) { thist->ptr -= n; return *this; }
        random_access_iterator operator[](int pos) { return (this->ptr_ + pos); } // ???????????????????????????? non sicuro

        // definire fuori dalla classe
        friend bool operator>(const random_access_iterator & lhs, const random_access_iterator & rhs);
        friend bool operator>=(const random_access_iterator & lhs, const random_access_iterator & rhs);
        friend bool operator<(const random_access_iterator & lhs, const random_access_iterator & rhs);
        friend bool operator<=(const random_access_iterator & lhs, const random_access_iterator & rhs);


        private:
        pointer ptr_;
    }; // class random_access_iterator
}; // namespace ft

// prova senza definire il tipo di iteratore
template<class Itlhs, class Itrhs>
bool operator>(Itlhs & lhs, Itrhs & rhs) {
    lhs() > rhs() ? true : false;
}