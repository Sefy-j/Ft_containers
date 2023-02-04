/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopez-f <jlopez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:42:22 by jlopez-f          #+#    #+#             */
/*   Updated: 2022/11/11 16:38:19 by jlopez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

#include "vector.hpp"

namespace	ft
{
	template <typename T, typename Container = vector<T> >
	class stack
	{
		public:

			/* Data types definitions */
			
			typedef Container							container_type;
			typedef typename Container::value_type		value_type;
			typedef typename Container::size_type		size_type;
			typedef typename Container::reference		reference;
			typedef typename Container::const_reference	const_reference;

			/* Constructors */

			explicit stack(const Container &cont = Container()) : c(cont) {}
			stack (const stack& other) { *this = other; }

			/* Destructor */

			virtual ~stack(void) {}

			/* Operator assignation */

			stack &operator=(const stack &other)
			{
				if (this != &other)
					c = other.c;
				return (*this);
			}

			/* Element access */

			reference		top(void) { return (c.back()); }
			const_reference	top(void) const { return (c.back()); }

			/* Capacity */

			size_type	size(void) const { return (c.size()); }
			bool 		empty(void) const { return (c.empty()); }

			/* Modifiers */


			void	push(const value_type &value) {c.push_back(value); }
			void	pop(void) { c.pop_back(); }

			/* Operators */

			template <typename U, typename V>
			friend bool	operator==(const stack<U, V> &lhs, const stack<U, V> &rhs);
			template <typename U, typename V>
			friend bool	operator<(const stack<U, V> &lhs, const stack<U, V> &rhs);

		protected:
		
			container_type	c;
	};

	/* Non Member Operators */

	template <typename T, typename Cont>
	bool	operator==(const ft::stack<T, Cont> &lhs, const ft::stack<T, Cont> &rhs) { return (lhs.c == rhs.c); }
	template <typename T, typename Cont>
	bool	operator!=(const ft::stack<T, Cont> &lhs, const ft::stack<T, Cont> &rhs) { return (!(lhs == rhs)); }
	template <typename T, typename Cont>
	bool	operator<(const ft::stack<T, Cont> &lhs, const ft::stack<T, Cont> &rhs) { return (lhs.c < rhs.c); }
	template <typename T, typename Cont>
	bool	operator>(const ft::stack<T, Cont> &lhs, const ft::stack<T, Cont> &rhs) { return (rhs < lhs); }
	template <typename T, typename Cont>
	bool	operator<=(const ft::stack<T, Cont> &lhs, const ft::stack<T, Cont> &rhs) { return (lhs == rhs || lhs < rhs); }
	template <typename T, typename Cont>
	bool	operator>=(const ft::stack<T, Cont> &lhs, const ft::stack<T, Cont> &rhs) { return (lhs == rhs || lhs > rhs); }
}

#endif
