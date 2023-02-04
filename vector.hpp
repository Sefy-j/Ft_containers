/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopez-f <jlopez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:42:22 by jlopez-f          #+#    #+#             */
/*   Updated: 2023/01/26 17:15:08 by jlopez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include "vector_iterator.hpp"
#include "reverse_iterator.hpp"
#include "utils.hpp"
#include <stdexcept>


namespace	ft
{
	template <typename T, typename Allocator = std::allocator<T> >
	class vector
	{
		public:

			/* Data types definitions */
			
			typedef T										value_type;
			typedef Allocator								allocator_type;
			typedef typename Allocator::size_type			size_type;
			typedef typename Allocator::difference_type		difference_type;

			typedef typename Allocator::reference			reference;
			typedef typename Allocator::const_reference		const_reference;
			typedef typename Allocator::pointer				pointer;
			typedef typename Allocator::const_pointer		const_pointer;

			typedef ft::vector_iterator<pointer>			iterator;
			typedef ft::vector_iterator<const_pointer>		const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

			/* Constructors */

			explicit vector (const allocator_type &Alloc = allocator_type()) : _start(0), _size(0), _capacity(0), _alloc(Alloc) {}
			explicit vector (size_type n, const value_type &val = value_type(), const allocator_type &Alloc = allocator_type()) :
			_size(n), _capacity(n), _alloc(Alloc)
			{
				if (n > _alloc.max_size())
					throw (std::length_error("Error. Allocation size is too big"));
				if (n > 0)
					_start = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _capacity; i++)
					_alloc.construct(&_start[i], val);
			}
			template <typename InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type &Alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) :
			_size(0), _capacity(0), _alloc(Alloc)
			{
				if (ft::is_inputit<typename ft::iterator_traits<InputIterator>::iterator_category>::value == true)
				{
					vector	temp;

					for (InputIterator it = first; it != last; it++)
						temp.push_back(*first);
					assign(temp.begin(), temp.end());
				}
				else
				{
					size_type	i = 0;

					for (InputIterator it = first; it != last; it++)
						i++;
					if (i > 0)
						_start = _alloc.allocate(i);
					_size = i;
					_capacity = i;
					for (i = 0; i < _size; i++)
						_alloc.construct(&_start[i], *first++);
				}
			}
			vector (const vector &other) : _size(other._size), _capacity(other._capacity), _alloc(other._alloc)
			{
				if(_capacity > 0)
					_start = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(&_start[i], other._start[i]);
			}

			/* Destructor */

			~vector(void)
			{
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(&_start[i]);
				if (_capacity > 0)
					_alloc.deallocate(_start, _capacity);
			}

			/* Operator assignation */

			vector &operator=(const vector &other)
			{
				if (this != &other)
				{
					if (other._size > _capacity)
					{
						pointer	tmp;

						if (other._capacity > 0)
							tmp = _alloc.allocate(other._capacity);
						for (size_type i = 0; i < other._size; i++)
							_alloc.construct(&tmp[i], other._start[i]);
						for (size_type i = 0; i < _size; i++)
							_alloc.destroy(&_start[i]);
						if (_capacity > 0)
							_alloc.deallocate(_start, _capacity);
						_capacity = other._capacity;
						_size = other._size;
						_start = tmp;
					}
					else
					{
						for (size_type i = 0; i < _size; i++)
							_alloc.destroy(&_start[i]);
						_size = other._size;
						for (size_type i = 0; i < _size; i++)
							_alloc.construct(&_start[i], other._start[i]);
					}
				}
				return (*this);
			}

			/* Element access */

			reference		operator[](size_type n) { return (_start[n]); }
			const_reference	operator[](size_type n) const { return (_start[n]); }
			reference		at(size_type n)
			{
				if (n >= _size)
					throw (std::out_of_range("Error. Out of range"));
				return (_start[n]);
			}
			const_reference	at(size_type n) const
			{
				if (n >= _size)
					throw (std::out_of_range("Error. Out of range"));
				return (_start[n]);
			}
			reference		front(void) { return _start[0]; }
			const_reference	front(void) const { return _start[0]; }
			reference		back(void) { return _start[_size - 1]; }
			const_reference	back(void) const { return _start[_size - 1]; }
			pointer			data(void) { return _start; }
			const_pointer*	data(void) const { return _start; }

			/* Iterators */

			iterator				begin(void) { return (iterator(_start)); }
			iterator				end(void) { return (iterator(_start + _size)); }
			const_iterator			begin(void) const { return (const_iterator(_start)); }
			const_iterator			end(void) const { return (const_iterator(_start + _size)); }

			reverse_iterator		rbegin(void) { return (reverse_iterator(end())); }
			reverse_iterator		rend(void) { return (reverse_iterator(begin())); }
			const_reverse_iterator	rbegin(void) const { return (const_reverse_iterator(end())); }
			const_reverse_iterator	rend(void) const { return (const_reverse_iterator(begin())); }

			/* Capacity */

			size_type	size(void) const { return (_size); }
			size_type	max_size(void) const { return (_alloc.max_size()); }
			void		resize(size_type n, value_type val = value_type())
			{
				if (n < _size)
				{
					for (size_type i = n; i < _size; i++)
						_alloc.destroy(&_start[i]);
					_size = n;
				}
				else if (n < _capacity)
				{	
					for (size_type i = _size; i < n; i++)
						_alloc.construct(&_start[i], val);
					_size = n;
				}
				else
				{
					size_type	newcap = (_capacity < 1) ? 1 : _capacity;

					while (n >= newcap)
						newcap *= 2;
					reserve(newcap);
					for (size_type i = _size; i < n; i++)
						_alloc.construct(&_start[i], val);
					_size = n;
				}
			}
			size_type	capacity(void) const { return (_capacity); }
			bool 		empty(void) const { return (_size == 0); }
			void		reserve(size_type n)
			{
				if (n > _alloc.max_size())
					throw (std::length_error("Error. Reserve size is too big"));
				else if (n < _capacity)
					return ;
				else
				{
					pointer	tmp;

					if (n > 0)
						tmp = _alloc.allocate(n);
					for (size_type i = 0; i < _size; i++)
						_alloc.construct(&tmp[i], _start[i]);
					for (size_type i = 0; i < _size; i++)
						_alloc.destroy(&_start[i]);
					if (_capacity > 0)
						_alloc.deallocate(_start, _capacity);
					_capacity = n;
					_start = tmp;
				}
			}

			/* Modifiers */

			void	assign(size_type n, const value_type &val)
			{
				if (n > _capacity)
				{
					pointer	tmp;

					if (n > 0)
						tmp = _alloc.allocate(n);
					for (size_type i = 0; i < n; i++)
						_alloc.construct(&tmp[i], val);
					for (size_type i = 0; i < _size; i++)
						_alloc.destroy(&_start[i]);
					if (_capacity > 0)
						_alloc.deallocate(_start, _capacity);
					_capacity = n;
					_size = n;
					_start = tmp;
				}
				else
				{
					for (size_type i = 0; i < _size; i++)
						_alloc.destroy(&_start[i]);
					_size = n;
					for (size_type i = 0; i < _size; i++)
						_alloc.construct(&_start[i], val);
				}
			}
			template <typename InputIterator>
			void	assign(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
			{
				if (ft::is_inputit<typename ft::iterator_traits<InputIterator>::iterator_category>::value == true)
				{
					vector	temp;

					for (InputIterator it = first; it != last; it++)
						temp.push_back(*first);
					assign(temp.begin(), temp.end());
				}
				else
				{
					size_type	n = 0;

					for (InputIterator it = first; it != last; it++)
						n++;
					if (n > _capacity)
					{
						pointer		tmp;
						size_type	i = 0;

						if (n > 0)
							tmp = _alloc.allocate(n);
						for (InputIterator it = first; it != last; it++)
							_alloc.construct(&tmp[i++], *it);
						for (size_type i = 0; i < _size; i++)
							_alloc.destroy(&_start[i]);
						if (_capacity > 0)
							_alloc.deallocate(_start, _capacity);
						_capacity = n;
						_size = n;
						_start = tmp;
					}
					else
					{
						for (size_type i = 0; i < _size; i++)
							_alloc.destroy(&_start[i]);
						_size = 0;
						for (InputIterator it = first; it != last; it++)
							push_back(*it);
					}
				}
			}
			void	push_back(const value_type &value) 
			{
				if (_size == _capacity)
					reserve((_capacity < 1) ? 1 : _capacity * 2);
				_alloc.construct(&_start[_size], value);
				_size++;
			}
			void	pop_back(void)
			{
				if(_size > 0)
					_alloc.destroy(&_start[--_size]);
			}
			iterator	insert(iterator position, const value_type &val)
			{
				size_type	i = position - begin();

				if (_size + 1 > _capacity)
					reserve((_capacity < 1) ? 1 : _capacity * 2);
				for(iterator it = end(); it != begin() + i;)
				{
					_alloc.construct(&(*it), *(--it));
					_alloc.destroy(&(*it));
				}
				_alloc.construct(&_start[i], val);
				_size++;
				return (begin() + i);
			}
			void		insert(iterator position, size_type n, const value_type &val)
			{
				if (n == 0)
					return ;
				else
				{
					size_type	i = position - begin();

					if (_size + n > _capacity)
					{
						size_type	newcap = (_capacity < 1) ? 1 : _capacity;

						while (_size + n >= newcap)
							newcap *= 2;
						reserve(newcap);
					}
					for(iterator it = end() + n - 1; it != begin() + i + n - 1; it--)
					{
						_alloc.construct(&(*(it)), *(it - n));
						_alloc.destroy(&(*(it - n)));
					}
					for(size_type j = 0; j < n; j++)
					{
						_alloc.construct(&(*(begin() + i + j)), val);
						_size++;
					}
				}
			}
			template <typename InputIterator>
			void		insert(iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
			{
				if (ft::is_inputit<typename ft::iterator_traits<InputIterator>::iterator_category>::value == true)
				{
					vector	temp;

					for (InputIterator it = first; it != last; it++)
						temp.push_back(*first);
					insert(position, temp.begin(), temp.end());
				}
				else
				{
					size_type	i = position - begin();
					size_type	j = 0;
					size_type	n = 0;

					for (InputIterator it = first; it != last; it++)
						n++;
					if (_size + n > _capacity)
					{
						size_type	newcap = (_capacity < 1) ? 1 : _capacity;

						while (_size + n >= newcap)
							newcap *= 2;
						reserve(newcap);
					}
					for(iterator it = end() + n - 1; it != begin() + i + n - 1; it--)
					{
						_alloc.construct(&(*it), *(it - n));
						_alloc.destroy(&(*(it - n)));
					}
					for (InputIterator it = first; it != last; it++)
					{
						_alloc.construct(&*(begin() + i + j), *it);
						j++;
					}
					_size +=n;
				}
			}
			iterator	erase(iterator position)
			{
				if (position == end())
				{
					pop_back();
					return (end());
				}
				else
				{
					size_type	i = 0;
					iterator	it = begin();

					while (it != position)
					{
						i++;
						it++;
					}
					_alloc.destroy(&_start[i]);
					while(i < _size - 1)
					{
						_alloc.construct(&_start[i], _start[i + 1]);
						_alloc.destroy(&_start[i + 1]);
						i++;
					}
					_size--;
					return (it);
				}
			}
			iterator erase (iterator first, iterator last)
			{
				iterator it = first;
				
				if (first == last)
						return (it);
				if (last == end())
				{
					while (first != last)
					{
						_alloc.destroy(&(*first));
						first++;
						_size--;
					}
					return (end());
				}
				else
				{
					size_type	deleted = 0;

					while (first != last)
					{
						_alloc.destroy(&(*first));
						first++;
						deleted++;
					}
					while (last != end())
					{
						_alloc.construct(&(*(last - deleted)), *last);
						_alloc.destroy(&(*last));
						last++;
					}
					_size -= deleted;
				}
				return (it);
			}
			void swap (vector &other)
			{
				ft::swap(_start, other._start);
				ft::swap(_size, other._size);
				ft::swap(_capacity, other._capacity);
				ft::swap(_alloc, other._alloc);
			}
			void	clear(void)
			{
				while (_size > 0)
					_alloc.destroy(&_start[--_size]);
			}

			/* Allocator */

			allocator_type	get_allocator(void) const {return (_alloc); }

		private:
		
			pointer			_start;
			size_type		_size;
			size_type		_capacity;
			allocator_type	_alloc;
	};

	/* Non Member Operators */

	template <typename T, typename Alloc>
	bool	operator==(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}
	template <typename T, typename Alloc>
	bool	operator!=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) { return (!(lhs == rhs)); }
	template <typename T, typename Alloc>
	bool	operator<(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) { return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }
	template <typename T, typename Alloc>
	bool	operator>(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) { return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end())); }
	template <typename T, typename Alloc>
	bool	operator<=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) { return (lhs == rhs || lhs < rhs); }
	template <typename T, typename Alloc>
	bool	operator>=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) { return (lhs == rhs || lhs > rhs); }

	/* Non Member Swap */

	template <typename T, typename Alloc>
	void	swap(vector<T, Alloc> &x, vector<T, Alloc> &y) { x.swap(y); }
}

#endif
