#ifndef __GLIBCPP_INTERNAL_ITERATOR_H
#define __GLIBCPP_INTERNAL_ITERATOR_H

namespace std
{
// 24.4.1 Reverse iterators
template <typename _Iterator>
class reverse_iterator
	: public iterator<typename iterator_traits<_Iterator>::iterator_category,
					  typename iterator_traits<_Iterator>::value_type,
					  typename iterator_traits<_Iterator>::difference_type,
					  typename iterator_traits<_Iterator>::pointer,
					  typename iterator_traits<_Iterator>::reference>
{
protected:
	_Iterator _M_current;

public:
	typedef _Iterator iterator_type;
	typedef typename iterator_traits<_Iterator>::difference_type	difference_type;
	typedef typename iterator_traits<_Iterator>::reference			reference;
	typedef typename iterator_traits<_Iterator>::pointer			pointer;

public:
	reverse_iterator() {}

	explicit reverse_iterator(iterator_type __x) : _M_current(__x) {}

	reverse_iterator(const reverse_iterator &__x)
		: _M_current(__x._M_current) {}

	template <typename _Iter>
	reverse_iterator(const reverse_iterator<_Iter> &__x)
		: _M_current(__x.base()) {}

	iterator_type base() const { return _M_current; }

	reference operator*() const
	{
		_Iterator __tmp = _M_current;
		return *--__tmp;
	}

	pointer operator->() const { return &(operator*()); }

	reverse_iterator &operator++()
	{
		--_M_current;
		return *this;
	}

	reverse_iterator operator++(int)
	{
		reverse_iterator __tmp = *this;
		--_M_current;
		return __tmp;
	}

	reverse_iterator &operator--()
	{
		++_M_current;
		return *this;
	}

	reverse_iterator operator--(int)
	{
		reverse_iterator __tmp = *this;
		++_M_current;
		return __tmp;
	}

	reverse_iterator operator+(difference_type __n) const
	{
		return reverse_iterator(_M_current - __n);
	}

	reverse_iterator &operator+=(difference_type __n)
	{
		_M_current -= __n;
		return *this;
	}

	reverse_iterator operator-(difference_type __n) const
	{
		return reverse_iterator(_M_current + __n);
	}

	reverse_iterator &operator-=(difference_type __n)
	{
		_M_current += __n;
		return *this;
	}

	reference operator[](difference_type __n) const { return *(*this + __n); }
};

template <typename _Iterator>
inline bool operator==(const reverse_iterator<_Iterator> &__x,
					   const reverse_iterator<_Iterator> &__y)
{
	return __x.base() == __y.base();
}

template <typename _Iterator>
inline bool operator<(const reverse_iterator<_Iterator> &__x,
					  const reverse_iterator<_Iterator> &__y)
{
	return __y.base() < __x.base();
}

template <typename _Iterator>
inline bool operator!=(const reverse_iterator<_Iterator> &__x,
					   const reverse_iterator<_Iterator> &__y)
{
	return !(__x == __y);
}

template <typename _Iterator>
inline bool operator>(const reverse_iterator<_Iterator> &__x,
					  const reverse_iterator<_Iterator> &__y)
{
	return __y < __x;
}

template <typename _Iterator>
inline bool operator<=(const reverse_iterator<_Iterator> &__x,
					   const reverse_iterator<_Iterator> &__y)
{
	return !(__y < __x);
}

template <typename _Iterator>
inline bool operator>=(const reverse_iterator<_Iterator> &__x,
					   const reverse_iterator<_Iterator> &__y)
{
	return !(__x < __y);
}

template <typename _Iterator>
inline typename reverse_iterator<_Iterator>::difference_type
operator-(const reverse_iterator<_Iterator> &__x,
		  const reverse_iterator<_Iterator> &__y)
{
	return __y.base() - __x.base();
}

template <typename _Iterator>
inline reverse_iterator<_Iterator>
operator+(typename reverse_iterator<_Iterator>::difference_type __n,
		  const reverse_iterator<_Iterator> &__x)
{
	return reverse_iterator<_Iterator>(__x.base() - __n);
}

// 24.4.2.2.1 back_insert_iterator
template <typename _Container>
class back_insert_iterator
	: public iterator<output_iterator_tag, void, void, void, void>
{
protected:
	_Container *_M_container;

public:
	typedef _Container container_type;

	explicit back_insert_iterator(_Container &__x) : _M_container(&__x) {}

	back_insert_iterator &
	operator=(typename _Container::const_reference __value)
	{
		_M_container->push_back(__value);
		return *this;
	}

	back_insert_iterator &
	operator*() { return *this; }

	back_insert_iterator &
	operator++() { return *this; }

	back_insert_iterator
	operator++(int) { return *this; }
};

template <typename _Container>
inline back_insert_iterator<_Container>
back_inserter(_Container &__x)
{
	return back_insert_iterator<_Container>(__x);
}

template <typename _Container>
class front_insert_iterator
	: public iterator<output_iterator_tag, void, void, void, void>
{
protected:
	_Container *_M_container;

public:
	typedef _Container container_type;

	explicit front_insert_iterator(_Container &__x) : _M_container(&__x) {}

	front_insert_iterator &
	operator=(typename _Container::const_reference __value)
	{
		_M_container->push_front(__value);
		return *this;
	}

	front_insert_iterator &
	operator*() { return *this; }

	front_insert_iterator &
	operator++() { return *this; }

	front_insert_iterator
	operator++(int) { return *this; }
};

template <typename _Container>
inline front_insert_iterator<_Container>
front_inserter(_Container &__x)
{
	return front_insert_iterator<_Container>(__x);
}

template <typename _Container>
class insert_iterator
	: public iterator<output_iterator_tag, void, void, void, void>
{
protected:
	_Container *_M_container;
	typename _Container::iterator iter;

public:
	typedef _Container container_type;

	insert_iterator(_Container &__x, typename _Container::iterator __i)
		: _M_container(&__x), iter(__i) {}

	insert_iterator &
	operator=(const typename _Container::const_reference __value)
	{
		iter = _M_container->insert(iter, __value);
		++iter;
		return *this;
	}

	insert_iterator &
	operator*() { return *this; }

	insert_iterator &
	operator++() { return *this; }

	insert_iterator &
	operator++(int) { return *this; }
};

template <typename _Container, typename _Iterator>
inline insert_iterator<_Container>
inserter(_Container &__x, _Iterator __i)
{
	return insert_iterator<_Container>(__x,
									   typename _Container::iterator(__i));
}

// This iterator adapter is 'normal' in the sense that it does not
// change the semantics of any of the operators of its iterator
// parameter.  Its primary purpose is to convert an iterator that is
// not a class, e.g. a pointer, into an iterator that is a class.
// The _Container parameter exists solely so that different containers
// using this template can instantiate different types, even if the
// _Iterator parameter is the same.
template <typename _Iterator, typename _Container>
class __normal_iterator
	: public iterator<typename iterator_traits<_Iterator>::iterator_category,
					  typename iterator_traits<_Iterator>::value_type,
					  typename iterator_traits<_Iterator>::difference_type,
					  typename iterator_traits<_Iterator>::pointer,
					  typename iterator_traits<_Iterator>::reference>
{
protected:
	_Iterator _M_current;

public:
	typedef typename iterator_traits<_Iterator>::difference_type
		difference_type;
	typedef typename iterator_traits<_Iterator>::reference reference;
	typedef typename iterator_traits<_Iterator>::pointer pointer;

	__normal_iterator() : _M_current(_Iterator()) {}

	explicit __normal_iterator(const _Iterator &__i) : _M_current(__i) {}

	// Allow iterator to const_iterator conversion
	template <typename _Iter>
	inline __normal_iterator(const __normal_iterator<_Iter, _Container> &__i)
		: _M_current(__i.base()) {}

	// Forward iterator requirements
	reference
	operator*() const { return *_M_current; }

	pointer
	operator->() const { return _M_current; }

	__normal_iterator &
	operator++()
	{
		++_M_current;
		return *this;
	}

	__normal_iterator
	operator++(int) { return __normal_iterator(_M_current++); }

	// Bidirectional iterator requirements
	__normal_iterator &
	operator--()
	{
		--_M_current;
		return *this;
	}

	__normal_iterator
	operator--(int) { return __normal_iterator(_M_current--); }

	// Random access iterator requirements
	reference
	operator[](const difference_type &__n) const
	{
		return _M_current[__n];
	}

	__normal_iterator &
	operator+=(const difference_type &__n)
	{
		_M_current += __n;
		return *this;
	}

	__normal_iterator
	operator+(const difference_type &__n) const
	{
		return __normal_iterator(_M_current + __n);
	}

	__normal_iterator &
	operator-=(const difference_type &__n)
	{
		_M_current -= __n;
		return *this;
	}

	__normal_iterator
	operator-(const difference_type &__n) const
	{
		return __normal_iterator(_M_current - __n);
	}

	difference_type
	operator-(const __normal_iterator &__i) const
	{
		return _M_current - __i._M_current;
	}

	const _Iterator &
	base() const { return _M_current; }
};

// Forward iterator requirements
template <typename _IteratorL, typename _IteratorR, typename _Container>
inline bool
operator==(const __normal_iterator<_IteratorL, _Container> &__lhs,
		   const __normal_iterator<_IteratorR, _Container> &__rhs)
{
	return __lhs.base() == __rhs.base();
}

template <typename _IteratorL, typename _IteratorR, typename _Container>
inline bool
operator!=(const __normal_iterator<_IteratorL, _Container> &__lhs,
		   const __normal_iterator<_IteratorR, _Container> &__rhs)
{
	return !(__lhs == __rhs);
}

// Random access iterator requirements
template <typename _IteratorL, typename _IteratorR, typename _Container>
inline bool
operator<(const __normal_iterator<_IteratorL, _Container> &__lhs,
		  const __normal_iterator<_IteratorR, _Container> &__rhs)
{
	return __lhs.base() < __rhs.base();
}

template <typename _IteratorL, typename _IteratorR, typename _Container>
inline bool
operator>(const __normal_iterator<_IteratorL, _Container> &__lhs,
		  const __normal_iterator<_IteratorR, _Container> &__rhs)
{
	return __rhs < __lhs;
}

template <typename _IteratorL, typename _IteratorR, typename _Container>
inline bool
operator<=(const __normal_iterator<_IteratorL, _Container> &__lhs,
		   const __normal_iterator<_IteratorR, _Container> &__rhs)
{
	return !(__rhs < __lhs);
}

template <typename _IteratorL, typename _IteratorR, typename _Container>
inline bool
operator>=(const __normal_iterator<_IteratorL, _Container> &__lhs,
		   const __normal_iterator<_IteratorR, _Container> &__rhs)
{
	return !(__lhs < __rhs);
}

template <typename _Iterator, typename _Container>
inline __normal_iterator<_Iterator, _Container>
operator+(typename __normal_iterator<_Iterator, _Container>::difference_type __n,
		  const __normal_iterator<_Iterator, _Container> &__i)
{
	return __normal_iterator<_Iterator, _Container>(__i.base() + __n);
}
} // namespace std

#endif

// Local Variables:
// mode:C++
// End: