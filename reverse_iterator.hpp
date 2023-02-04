/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopez-f <jlopez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 17:55:26 by jlopez-f          #+#    #+#             */
/*   Updated: 2022/11/11 22:15:49 by jlopez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"
#include "utils.hpp"

namespace	ft
{
	template <typename T>
 	class reverse_iterator
	{
		public:

			/* Data types definitions */

			typedef T													iterator_type;
			typedef typename ft::iterator_traits<T>::value_type			value_type;
			typedef typename ft::iterator_traits<T>::difference_type	difference_type;
			typedef typename ft::iterator_traits<T>::pointer			pointer;
			typedef typename ft::iterator_traits<T>::reference			reference;
			typedef typename ft::iterator_traits<T>::iterator_category	iterator_category;

			/* Constructors */

			reverse_iterator(void) : _iter() {}
			explicit	reverse_iterator(iterator_type iter) : _iter(iter) {}
			template <typename U>
			reverse_iterator(const reverse_iterator<U> &other) { *this = other; }

			/* Destructor */

			~reverse_iterator(void) {}

			/* Operator assignation */
			
			template <typename U>
			reverse_iterator	&operator=(const reverse_iterator<U> &other)
			{
				_iter = other.base();
				return (*this);
			}

			/* Access */

			iterator_type base(void) const { return (_iter); }

			/* Operators */

			reference	operator*(void) const { iterator_type temp(_iter); return (*(--temp)); }
			reference	operator[](difference_type n) const { return *(*this + n); }
			pointer		operator->(void) const { return (ft::addressof(operator*())); }

			reverse_iterator	operator+(difference_type n) const { return (reverse_iterator(_iter - n)); }
			reverse_iterator	operator-(difference_type n) const { return (reverse_iterator(_iter + n)); }
			reverse_iterator	&operator+=(difference_type n) { _iter -= n; return (*this); }
			reverse_iterator	&operator-=(difference_type n) { _iter += n; return (*this); }
			reverse_iterator	&operator++(void) { _iter--; return (*this); }
			reverse_iterator	&operator--(void) { _iter++; return (*this); }
			reverse_iterator	operator++(int) { reverse_iterator temp(*this); _iter--; return (temp); }
			reverse_iterator	operator--(int) { reverse_iterator temp(*this); _iter++; return (temp); }

		private:

			T	_iter;
	};

	/* Non Member Operators */

	template <typename T, typename U>
	bool	operator<(const reverse_iterator<T> &lhs, const reverse_iterator<U> &rhs) { return (lhs.base() > rhs.base()); }
	template <typename T, typename U>
	bool	operator>(const reverse_iterator<T> &lhs, const reverse_iterator<U> &rhs) { return (lhs.base() < rhs.base()); }
	template <typename T, typename U>
	bool	operator<=(const reverse_iterator<T> &lhs, const reverse_iterator<U> &rhs) {return (lhs.base() >= rhs.base()); }
	template <typename T, typename U>
	bool	operator>=(const reverse_iterator<T> &lhs, const reverse_iterator<U> &rhs) { return (lhs.base() <= rhs.base()); }
	template <typename T, typename U>
	bool	operator==(const reverse_iterator<T> &lhs, const reverse_iterator<U> &rhs) { return (lhs.base() == rhs.base()); }
	template <typename T, typename U>
	bool	operator!=(const reverse_iterator<T> &lhs, const reverse_iterator<U> &rhs) { return (lhs.base() != rhs.base()); }

	template <typename T>
	reverse_iterator<T>	operator+(typename reverse_iterator<T>::difference_type n, const reverse_iterator<T> &rhs)
	{ return (reverse_iterator<T>(rhs.base() - n)); }
	template <typename T, typename U>
	typename reverse_iterator<T>::difference_type	operator-(const reverse_iterator<U> &lhs, const reverse_iterator<T> &rhs)
	{ return (rhs.base() - lhs.base()); }
}

#endif
