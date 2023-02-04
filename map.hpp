/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopez-f <jlopez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:42:22 by jlopez-f          #+#    #+#             */
/*   Updated: 2023/01/26 17:17:01 by jlopez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

#include "rbtree.hpp"
#include "reverse_iterator.hpp"
#include <stdexcept>

namespace	ft
{
	template <typename Key, typename T, class Compare = std::less<Key>, typename Allocator = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		public:

			/* Data types definitions */
			
			typedef Key											key_type;
			typedef T											mapped_type;
			typedef ft::pair<const key_type, mapped_type>		value_type;
			typedef Compare										key_compare;
			typedef Allocator									allocator_type;
			typedef typename Allocator::size_type				size_type;
			typedef typename Allocator::difference_type			difference_type;

			typedef typename Allocator::reference				reference;
			typedef typename Allocator::const_reference			const_reference;
			typedef typename Allocator::pointer					pointer;
			typedef typename Allocator::const_pointer			const_pointer;

			class value_compare
			{
				public:

					/* Member objects */

					typedef bool		result_type;
					typedef value_type	first_argument_type;
					typedef value_type	second_argument_type;

					/* Constructors */

					value_compare() : _comp() {}

					/* Operators */

					bool	operator()(const value_type &lhs, const value_type &rhs) const { return (_comp(lhs.first, rhs.first)); }

				protected:

					key_compare	_comp;
			};

			typedef ft::RbTree<value_type, value_compare, allocator_type>	tree_type;
			typedef typename tree_type::iterator							iterator;
			typedef typename tree_type::const_iterator						const_iterator;
			typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;

			/* Constructors */

			explicit map (const key_compare &comp = key_compare(), const allocator_type &Alloc = allocator_type()) : _rbtree(), _compare(comp), _value_compare(value_compare()), _alloc(Alloc) {}
			template <typename InputIterator>
			map (InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &Alloc = allocator_type()) :
			_compare(comp), _value_compare(value_compare()), _alloc(Alloc)
			{
				for (InputIterator it = first; it != last; it++)
						_rbtree.insert(*it);
			}
			map (const map &other) { *this = other; }

			/* Destructor */

			~map(void) {}

			/* Operator assignation */

			map &operator=(const map &other)
			{
				if (this != &other)
				{
					_rbtree = other._rbtree;
					_compare = other._compare;
					_value_compare = other._value_compare;
					_alloc = other._alloc;
				}
				return (*this);
			}

			/* Element access */

			mapped_type			&operator[](const key_type &key)
			{
				iterator	it = find(key);

				if (it != end())
					return (it->second);
				return (insert(ft::make_pair(key, mapped_type())).first->second);
			}
			mapped_type			&at(const key_type &key)
			{
				iterator	it = find(key);

				if (it == end())
					throw (std::out_of_range("Error. Out of range"));
				return (it->second);
			}
			const mapped_type	at(const key_type &key) const
			{
				const_iterator	it = find(key);

				if (it == end())
					throw (std::out_of_range("Error. Out of range"));
				return (it->second);
			}

			/* Iterators */

			iterator				begin(void) { return (_rbtree.begin()); }
			iterator				end(void) { return (_rbtree.end()); }
			const_iterator			begin(void) const { return (_rbtree.begin()); }
			const_iterator			end(void) const { return (_rbtree.end()); }

			reverse_iterator		rbegin(void) { return (_rbtree.rbegin()); }
			reverse_iterator		rend(void) { return (_rbtree.rend()); }
			const_reverse_iterator	rbegin(void) const { return (_rbtree.rbegin()); }
			const_reverse_iterator	rend(void) const { return (_rbtree.rend()); }

			/* Capacity */

			bool 		empty(void) const { return (_rbtree.getsize() == 0); }
			size_type	size(void) const { return (_rbtree.getsize()); }
			size_type	max_size(void) const { return (_rbtree.getmaxsize()); }

			/* Modifiers */

			void						clear(void) { _rbtree.clear(); }
			ft::pair<iterator, bool>	insert(const value_type &val) { return (_rbtree.insert(val)); }
			iterator					insert(iterator position, const value_type &val) { (void)position; return (_rbtree.insert(val).first); }
			template <typename InputIterator>
			void		insert(InputIterator first, InputIterator last)
			{
				for (InputIterator it = first; it != last; it++)
					_rbtree.insert(*it);
			}
			void		erase(iterator position) { _rbtree.erase(*position); }
			void		erase (iterator first, iterator last)
			{
				for (iterator it = first; it != last;)
					_rbtree.erase(*(it++));
			}
			size_type	erase(const key_type &key)
			{
				iterator	it = find(key);

				if (it != end())
				{
					_rbtree.erase(*it);
					return (1);
				}
				return (0);
			}
			void swap (map &other)
			{
				_rbtree.swap(other._rbtree);
				ft::swap(_compare, other._compare);
				ft::swap(_value_compare, other._value_compare);
				ft::swap(_alloc, other._alloc);
			}

			/* Lookup */

			size_type	count(const key_type &key ) const
			{
				const_iterator	it = find(key);

				if (it != end())
					return (1);
				return (0);
			}
			iterator	find(const key_type &key)
			{
				ft::Node<value_type>	*node = _rbtree.find(ft::make_pair(key, mapped_type()));

				if (node)
					return (iterator(node, _rbtree.getnil()));
				return (end());
			}
			const_iterator	find(const key_type &key) const
			{
				ft::Node<value_type>	*node = _rbtree.find(ft::make_pair(key, mapped_type()));

				if (node)
					return (const_iterator(node, _rbtree.getnil()));
				return (end());
			}
			iterator	lower_bound(const key_type &key)
			{
				iterator	it = iterator(_rbtree.getroot(), _rbtree.getnil());
				iterator	temp;

				while (1)
				{
					if (_value_compare(*it, ft::make_pair(key, mapped_type())))
					{
						if (it.getnode()->right != _rbtree.getnil())
							it = iterator(it.getnode()->right, _rbtree.getnil());
						else
							return (end());
					}
					else if (_value_compare(ft::make_pair(key, mapped_type()), *it))
					{
						if (it.getnode()->left != _rbtree.getnil())
							temp = it;
						else
							return (it);
						temp--;
						if (_value_compare(ft::make_pair(key, mapped_type()), *temp) ||
						(!_value_compare(*temp, ft::make_pair(key, mapped_type())) && !_value_compare(ft::make_pair(key, mapped_type()), *temp)))
							it = iterator(it.getnode()->left, _rbtree.getnil());
						else
							return (it);
					}
					else
						return (it);
				}
			}
			const_iterator	lower_bound(const key_type &key) const
			{
				const_iterator	it = const_iterator(_rbtree.getroot(), _rbtree.getnil());
				const_iterator	temp;

				while (1)
				{
					if (_value_compare(*it, ft::make_pair(key, mapped_type())))
					{
						if (it.getnode()->right != _rbtree.getnil())
							it = const_iterator(it.getnode()->right, _rbtree.getnil());
						else
							return (end());
					}
					else if (_value_compare(ft::make_pair(key, mapped_type()), *it))
					{
						if (it.getnode()->left != _rbtree.getnil())
							temp = it;
						else
							return (it);
						temp--;
						if (_value_compare(ft::make_pair(key, mapped_type()), *temp) ||
						(!_value_compare(*temp, ft::make_pair(key, mapped_type())) && !_value_compare(ft::make_pair(key, mapped_type()), *temp)))
							it = const_iterator(it.getnode()->left, _rbtree.getnil());
						else
							return (it);
					}
					else
						return (it);
				}
			}
			iterator	upper_bound(const key_type &key)
			{
				iterator	it = iterator(_rbtree.getroot(), _rbtree.getnil());
				iterator	temp;

				while (1)
				{
					if (_value_compare(*it, ft::make_pair(key, mapped_type())))
					{
						if (it.getnode()->right != _rbtree.getnil())
							it = iterator(it.getnode()->right, _rbtree.getnil());
						else
							return (end());
					}
					else if (_value_compare(ft::make_pair(key, mapped_type()), *it))
					{
						if (it.getnode()->left != _rbtree.getnil())
							temp = it;
						else
							return (it);
						temp--;
						if (_value_compare(ft::make_pair(key, mapped_type()), *temp))
							it = iterator(it.getnode()->left, _rbtree.getnil());
						else
							return (it);
					}
					else
						return (++it);
				}
			}
			const_iterator	upper_bound(const key_type &key) const
			{
				const_iterator	it = const_iterator(_rbtree.getroot(), _rbtree.getnil());
				const_iterator	temp;

				while (1)
				{
					if (_value_compare(*it, ft::make_pair(key, mapped_type())))
					{
						if (it.getnode()->right != _rbtree.getnil())
							it = const_iterator(it.getnode()->right, _rbtree.getnil());
						else
							return (end());
					}
					else if (_value_compare(ft::make_pair(key, mapped_type()), *it))
					{
						if (it.getnode()->left != _rbtree.getnil())
							temp = it;
						else
							return (it);
						temp--;
						if (_value_compare(ft::make_pair(key, mapped_type()), *temp))
							it = const_iterator(it.getnode()->left, _rbtree.getnil());
						else
							return (it);
					}
					else
						return (++it);
				}
			}
			ft::pair<iterator, iterator>				equal_range(const key_type &key) { return (ft::make_pair(lower_bound(key), upper_bound(key))); }
			ft::pair<const_iterator, const_iterator>	equal_range(const key_type &key) const{ return (ft::make_pair(lower_bound(key), upper_bound(key))); }

			/* Observers */

			key_compare		key_comp(void) const {return (_compare); }
			value_compare	value_comp(void) const {return (_value_compare); }

			/* Allocator */

			allocator_type	get_allocator(void) const {return (_alloc); }

		private:

			tree_type		_rbtree;
			key_compare		_compare;
			value_compare	_value_compare;
			allocator_type	_alloc;
	};

	/* Non Member Operators */

	template <typename Key, typename T, typename Compare, typename Alloc>
	bool	operator==(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}
	template <typename Key, typename T, typename Compare, typename Alloc>
	bool	operator!=(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs) { return (!(lhs == rhs)); }
	template <typename Key, typename T, typename Compare, typename Alloc>
	bool	operator<(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs) { return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }
	template <typename Key, typename T, typename Compare, typename Alloc>
	bool	operator>(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs) { return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end())); }
	template <typename Key, typename T, typename Compare, typename Alloc>
	bool	operator<=(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs) { return (lhs == rhs || lhs < rhs); }
	template <typename Key, typename T, typename Compare, typename Alloc>
	bool	operator>=(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs) { return (lhs == rhs || lhs > rhs); }

	/* Non Member Swap */

	template <typename Key, typename T, typename Compare, typename Alloc>
	void	swap(map<Key, T, Compare, Alloc> &x, map<Key, T, Compare, Alloc> &y) { x.swap(y); }
}

#endif
