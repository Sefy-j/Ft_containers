/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopez-f <jlopez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 19:28:31 by jlopez-f          #+#    #+#             */
/*   Updated: 2022/11/11 18:35:42 by jlopez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

namespace	ft
{
	template <typename T1, typename T2>
	struct pair
	{
		/* Data types definitions */

		typedef T1	first_type;
		typedef T2	second_type;

		/* Member objects */

		T1	first;
		T2	second;

		/* Constructors */

		pair(void) : first(first_type()), second(second_type()) {}
		pair(const T1 &x, const T2 &y) : first(x), second(y) {}
		template <typename U1, typename U2>
		pair(const pair<U1, U2> &other) : first(other.first), second(other.second) {}

		/* Destructor */

		~pair(void) {}

		/* Operator assignation */

		pair	&operator=(const pair &other)
		{
			if (this != &other)
			{
				first = other.first;
				second = other.second;
			}
			return (*this);
		}
	};

	/* Non Member Make Pair */

	template <typename T1, typename T2 >
	ft::pair<T1, T2>	make_pair(T1 t, T2 u) { return (ft::pair<T1, T2>(t, u)); }

	/* Non Member Operators */

	template <typename T1, typename T2>
	bool	operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) { return (lhs.first < rhs.first || lhs.second < rhs.second); }
	template <typename T1, typename T2>
	bool	operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) { return (lhs.first > rhs.first || lhs.second > rhs.second); }
	template <typename T1, typename T2>
	bool	operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {return ((lhs.first <= rhs.first || lhs.second <= rhs.second)); }
	template <typename T1, typename T2>
	bool	operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) { return ((lhs.first >= rhs.first || lhs.second >= rhs.second)); }
	template <typename T1, typename T2>
	bool	operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) { return ((lhs.first == rhs.first || lhs.second == rhs.second)); }
	template <typename T1, typename T2>
	bool	operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) { return ((lhs.first != rhs.first || lhs.second != rhs.second)); }

}

#endif
