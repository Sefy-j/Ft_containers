/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopez-f <jlopez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:42:22 by jlopez-f          #+#    #+#             */
/*   Updated: 2023/01/26 17:16:54 by jlopez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP

#include "rbtree.hpp"
#include "reverse_iterator.hpp"
#include <stdexcept>

namespace	ft
{
	template <typename Key, class Compare = std::less<Key>, typename Allocator = std::allocator<Key> >
	class set
	{
		public:

			/* Data types definitions */
			
			typedef Key											key_type;
			typedef Key											value_type;
			typedef Compare										key_compare;
			typedef Compare										value_compare;
			typedef Allocator									allocator_type;
			typedef typename Allocator::size_type				size_type;
			typedef typename Allocator::difference_type			difference_type;

			typedef typename Allocator::reference				reference;
			typedef typename Allocator::const_reference			const_reference;
			typedef typename Allocator::pointer					pointer;
			typedef typename Allocator::const_pointer			const_pointer;

			typedef ft::RbTree<value_type, value_compare, allocator_type>	tree_type;
			typedef typename tree_type::const_iterator						iterator;
			typedef typename tree_type::const_iterator						const_iterator;
			typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;

			/* Constructors */

			explicit set (const key_compare &comp = key_compare(), const allocator_type &Alloc = allocator_type()) : _rbtree(), _compare(comp), _alloc(Alloc) {}
			template <typename InputIterator>
			set (InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &Alloc = allocator_type()) :
			_compare(comp), _alloc(Alloc)
			{
				for (InputIterator it = first; it != last; it++)
						_rbtree.insert(*it);
			}
			set (const set &other) { *this = other; }

			/* Destructor */

			~set(void) {}

			/* Operator assignation */

			set &operator=(const set &other)
			{
				if (this != &other)
				{
					_rbtree = other._rbtree;
					_compare = other._compare;
					_alloc = other._alloc;
				}
				return (*this);
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
			void swap (set &other)
			{
				_rbtree.swap(other._rbtree);
				ft::swap(_compare, other._compare);
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
				ft::Node<value_type>	*node = _rbtree.find(key);

				if (node)
					return (iterator(node, _rbtree.getnil()));
				return (end());
			}
			const_iterator	find(const key_type &key) const
			{
				ft::Node<value_type>	*node = _rbtree.find(key);

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
					if (_compare(*it, key))
					{
						if (it.getnode()->right != _rbtree.getnil())
							it = iterator(it.getnode()->right, _rbtree.getnil());
						else
							return (end());
					}
					else if (_compare(key, *it))
					{
						if (it.getnode()->left != _rbtree.getnil())
							temp = it;
						else
							return (it);
						temp--;
						if (_compare(key, *temp) ||
						(!_compare(*temp, key) && !_compare(key, *temp)))
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
					if (_compare(*it, key))
					{
						if (it.getnode()->right != _rbtree.getnil())
							it = const_iterator(it.getnode()->right, _rbtree.getnil());
						else
							return (end());
					}
					else if (_compare(key, *it))
					{
						if (it.getnode()->left != _rbtree.getnil())
							temp = it;
						else
							return (it);
						temp--;
						if (_compare(key, *temp) ||
						(!_compare(*temp, key) && !_compare(key, *temp)))
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
					if (_compare(*it, key))
					{
						if (it.getnode()->right != _rbtree.getnil())
							it = iterator(it.getnode()->right, _rbtree.getnil());
						else
							return (end());
					}
					else if (_compare(key, *it))
					{
						if (it.getnode()->left != _rbtree.getnil())
							temp = it;
						else
							return (it);
						temp--;
						if (_compare(key, *temp))
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
					if (_compare(*it, key))
					{
						if (it.getnode()->right != _rbtree.getnil())
							it = const_iterator(it.getnode()->right, _rbtree.getnil());
						else
							return (end());
					}
					else if (_compare(key, *it))
					{
						if (it.getnode()->left != _rbtree.getnil())
							temp = it;
						else
							return (it);
						temp--;
						if (_compare(key, *temp))
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
			value_compare	value_comp(void) const {return (_compare); }

			/* Allocator */

			allocator_type	get_allocator(void) const {return (_alloc); }

		private:

			tree_type		_rbtree;
			key_compare		_compare;
			allocator_type	_alloc;
	};

	/* Non Member Operators */

	template <typename Key, typename Compare, typename Alloc>
	bool	operator==(const ft::set<Key, Compare, Alloc> &lhs, const ft::set<Key, Compare, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}
	template <typename Key, typename Compare, typename Alloc>
	bool	operator!=(const ft::set<Key, Compare, Alloc> &lhs, const ft::set<Key, Compare, Alloc> &rhs) { return (!(lhs == rhs)); }
	template <typename Key, typename Compare, typename Alloc>
	bool	operator<(const ft::set<Key, Compare, Alloc> &lhs, const ft::set<Key, Compare, Alloc> &rhs) { return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }
	template <typename Key, typename Compare, typename Alloc>
	bool	operator>(const ft::set<Key, Compare, Alloc> &lhs, const ft::set<Key, Compare, Alloc> &rhs) { return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end())); }
	template <typename Key, typename Compare, typename Alloc>
	bool	operator<=(const ft::set<Key, Compare, Alloc> &lhs, const ft::set<Key, Compare, Alloc> &rhs) { return (lhs == rhs || lhs < rhs); }
	template <typename Key, typename Compare, typename Alloc>
	bool	operator>=(const ft::set<Key, Compare, Alloc> &lhs, const ft::set<Key, Compare, Alloc> &rhs) { return (lhs == rhs || lhs > rhs); }

	/* Non Member Swap */

	template <typename Key, typename Compare, typename Alloc>
	void	swap(set<Key, Compare, Alloc> &x, set<Key, Compare, Alloc> &y) { x.swap(y); }
}

#endif
