/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopez-f <jlopez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 17:36:30 by jlopez-f          #+#    #+#             */
/*   Updated: 2022/11/11 23:22:58 by jlopez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_ITERATOR_HPP
# define RBTREE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace	ft
{
	template <typename Node, typename Pair>
 	class rbtree_iterator
	{
		public:

			/* Data types definitions */
		
			typedef Pair												value_type;
			typedef value_type*											pointer;
			typedef value_type&											reference;
			typedef typename ft::iterator_traits<Node>::value_type			node_type;
			typedef typename ft::iterator_traits<Node>::difference_type	difference_type;
			typedef typename ft::iterator_traits<Node>::pointer			node_pointer;
			typedef typename ft::iterator_traits<Node>::reference			node_reference;
			typedef typename std::bidirectional_iterator_tag			iterator_category;

			/* Constructors */

			rbtree_iterator(void) : _node(), _nil() {}
			explicit	rbtree_iterator(node_pointer node, node_pointer nil) :
			_node(node), _nil(nil) {}
			template <typename N, typename P>
			rbtree_iterator(const rbtree_iterator<N, P> &other) { *this = other; }

			/* Destructor */

			~rbtree_iterator(void) {}

			/* Operator assignation */
			
			template <typename N, typename P>
			rbtree_iterator	&operator=(const rbtree_iterator<N, P> &other)
			{
				_node = other.getnode();
				_nil = other.getnil();
				return (*this);
			}

			/* Access */

			node_pointer getnode(void) const { return (_node); }
			node_pointer getnil(void) const { return (_nil); }

			/* Operators */

			reference	operator*(void) const { return (_node->data); }
			pointer		operator->(void) const { return (&_node->data); }

			rbtree_iterator	&operator++(void)
			{
				if (_node->right != _nil)
				{
					_node = _node->right;
					while(_node->left != _nil)
						_node = _node->left;
				}
				else
				{
					while(_node->parent != _nil && _node == _node->parent->right)
						_node = _node->parent;
					_node = _node->parent;
				}
				return (*this);
			}
			rbtree_iterator	&operator--(void)
			{
				if (_node->left != _nil)
				{
					_node = _node->left;
					while(_node->right != _nil)
						_node = _node->right;
				}
				else
				{
					while(_node->parent != _nil && _node == _node->parent->left)
						_node = _node->parent;
					_node = _node->parent;
				}
				return (*this);
			}
			rbtree_iterator	operator++(int) { rbtree_iterator temp(*this); operator++(); return (temp); }
			rbtree_iterator	operator--(int) { rbtree_iterator temp(*this); operator--(); return (temp); }

	 	private:

	 		node_pointer	_node;
	 		node_pointer	_nil;
	};

	/* Non Member Operators */

	template <typename N1, typename P1, typename N2, typename P2>
	bool	operator<(const rbtree_iterator<N1, P1> &lhs, const rbtree_iterator<N2, P2> &rhs) { return (lhs.getnode() < rhs.getnode()); }
	template <typename N1, typename P1, typename N2, typename P2>
	bool	operator>(const rbtree_iterator<N1, P1> &lhs, const rbtree_iterator<N2, P2> &rhs) { return (lhs.getnode() > rhs.getnode()); }
	template <typename N1, typename P1, typename N2, typename P2>
	bool	operator<=(const rbtree_iterator<N1, P1> &lhs, const rbtree_iterator<N2, P2> &rhs) {return (lhs.getnode() <= rhs.getnode()); }
	template <typename N1, typename P1, typename N2, typename P2>
	bool	operator>=(const rbtree_iterator<N1, P1> &lhs, const rbtree_iterator<N2, P2> &rhs) { return (lhs.getnode() >= rhs.getnode()); }
	template <typename N1, typename P1, typename N2, typename P2>
	bool	operator==(const rbtree_iterator<N1, P1> &lhs, const rbtree_iterator<N2, P2> &rhs) { return (lhs.getnode() == rhs.getnode()); }
	template <typename N1, typename P1, typename N2, typename P2>
	bool	operator!=(const rbtree_iterator<N1, P1> &lhs, const rbtree_iterator<N2, P2> &rhs) { return (lhs.getnode() != rhs.getnode()); }

	template <typename N1, typename P1>
	rbtree_iterator<N1, P1>	operator+(typename rbtree_iterator<N1, P1>::difference_type n, const rbtree_iterator<N1, P1> &rhs)
	{ return (rbtree_iterator<N1, P1>(rhs.getnode() + n)); }
	template <typename N1, typename P1, typename N2, typename P2>
	typename rbtree_iterator<N1, P1>::difference_type	operator-(const rbtree_iterator<N1, P1> &lhs, const rbtree_iterator<N2, P2> &rhs)
	{ return (lhs.getnode() - rhs.getnode()); }
}

#endif
