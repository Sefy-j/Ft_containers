/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopez-f <jlopez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 23:11:19 by jlopez-f          #+#    #+#             */
/*   Updated: 2022/11/11 23:22:13 by jlopez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
# define RBTREE_HPP

#include "rbtree_iterator.hpp"
#include "reverse_iterator.hpp"
#include "utils.hpp"
#include "pair.hpp"

#define RED 0
#define BLACK 1

namespace	ft
{
	template <typename T>
	class Node
	{
		public:

			/* Member objects */

			T		data;
			Node*	parent;
			Node*	left;
			Node*	right;
			bool	colour;

			/* Constructors */

			Node(const T &value) : data(value), parent(0), left(0), right(0), colour(BLACK) {}

			/* Destructor */

			~Node(void) {}

	};

	template <typename T, typename Compare = std::less<T>, typename Allocator = std::allocator<T> >
	class RbTree
	{
		public:

			/* Data types definitions */
			
			typedef T														value_type;
			typedef ft::Node<T>												node_type;
			typedef size_t													size_type;
			typedef Compare													compare;
			typedef Allocator												allocator;
			typedef typename Allocator::template rebind<node_type>::other	node_allocator;

			typedef typename node_allocator::reference						reference;
			typedef typename node_allocator::const_reference				const_reference;
			typedef typename node_allocator::pointer						pointer;
			typedef typename node_allocator::const_pointer					const_pointer;

			typedef ft::rbtree_iterator<pointer, T>							iterator;
			typedef ft::rbtree_iterator<const_pointer, const T>				const_iterator;
			typedef ft::reverse_iterator<iterator>							reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;


			/* Constructors */

			RbTree(void) : _size(0), _compare(compare())
			{
				_nil = _node_allocator.allocate(1);
				_node_allocator.construct(_nil, value_type());
				_nil->parent = _nil;
				_nil->left = _nil;
				_nil->right = _nil;
				_root = _nil;
			}
			RbTree(const RbTree &other) { *this = other; }

			/* Destructor */

			~RbTree(void)
			{
				destructor(_root);
				_node_allocator.destroy(_nil);
				_node_allocator.deallocate(_nil, 1);
			}

			/* Operator assignation */

			RbTree	&operator=(const RbTree &other)
			{
				if (this != &other)
				{
					destructor(_root);
					_node_allocator.destroy(_nil);
					_node_allocator.deallocate(_nil, 1);
					_size = 0;
					_node_allocator = other._node_allocator;
					_pair_allocator = other._pair_allocator;
					_compare = other._compare;
					_nil = _node_allocator.allocate(1);
					_node_allocator.construct(_nil, value_type());
					_nil->parent = _nil;
					_nil->left = _nil;
					_nil->right = _nil;
					_root = _nil;
					copyrecursion(other._root, other._nil);
					relinktree();
				}
				return (*this);
			}

			/* Element access */

			size_type	getsize(void) const { return (_size); }
			size_type	getmaxsize(void) const { return (_node_allocator.max_size()); }
			pointer		getroot(void) const { return (_root); }
			pointer		getnil(void) const { return (_nil); }

			/* Iterators */

			iterator				begin(void) { return (iterator(min(), _nil)); }
			iterator				end(void) { return (iterator(_nil, _nil)); }
			const_iterator			begin(void) const { return (const_iterator(min(), _nil)); }
			const_iterator			end(void) const { return (const_iterator(_nil, _nil)); }

			reverse_iterator		rbegin(void) { return (reverse_iterator(end())); }
			reverse_iterator		rend(void) { return (reverse_iterator(begin())); }
			const_reverse_iterator	rbegin(void) const { return (const_reverse_iterator(end())); }
			const_reverse_iterator	rend(void) const { return (const_reverse_iterator(begin())); }

			/* Modifiers */

			void	clear(void)
			{
				if (_root && _root != _nil)
				{
					destructor(_root);
					_size = 0;
					_root = _nil;
				}
			}
			ft::pair<iterator, bool>	insert(const value_type &value)
			{
				if (_root == _nil)
				{
					_root = newNode(value);
					_size++;
					relinktree();
					return (ft::make_pair(iterator(_root, _nil), true));
				}
				else
				{
					pointer	temp = _root;

					while (temp)
					{
						if(_compare(temp->data, value) > 0)
						{
							if (temp->right == _nil)
							{
								temp->right = newNode(value);
								temp->right->parent = temp;
								temp = temp->right;
								break ;
							}
							temp = temp->right;
						}
						else if (_compare(value, temp->data) > 0)
						{
							if (temp->left == _nil)
							{
								temp->left = newNode(value);
								temp->left->parent = temp;
								temp = temp->left;
								break ;
							}
							temp = temp->left;
						}
						else
							return (ft::make_pair(iterator(temp, _nil), false));
					}
					_size++;
					fixinsertion(temp);
					relinktree();
					return (ft::make_pair(iterator(temp, _nil), true));
				}
			}
			void	erase(const value_type &value)
			{
				pointer	node = find(value);
				pointer	temp;
				bool	ogcolour;

				if (node == _nil)
					return ;
				ogcolour = node->colour;
				if (node->left == _nil)
				{
					temp = node->right;
					transplant(node, temp);
					
				}
				else if (node->right == _nil)
				{
					temp = node->left;
					transplant(node, temp);
				}
				else
				{
					pointer min = node->right;

					while (min->left != _nil)
						min = min->left;
					ogcolour = min->colour;
					temp = min->right;
					if (min->parent == node)
						temp->parent = min;
					else
					{
						transplant(min, min->right);
						min->right = node->right;
						min->right->parent = min;
					}
					transplant(node, min);
					min->left = node->left;
					min->left->parent = min;
					min->colour = node->colour;
						
				}
				_size--;
				_node_allocator.destroy(node);
				_node_allocator.deallocate(node, 1);
				if (ogcolour == BLACK)
					fixerase(temp);
				relinktree();
			}
			void	swap(RbTree &other)
			{
				ft::swap(_root, other._root);
				ft::swap(_nil, other._nil);
				ft::swap(_size, other._size);
				ft::swap(_node_allocator, other._node_allocator);
				ft::swap(_pair_allocator, other._pair_allocator);
				ft::swap(_compare, other._compare);
			}

			/* Lookup */

			pointer	find(const value_type &value) const
			{
				pointer	temp = _root;

				while (temp != _nil)
				{
					if (_compare(temp->data, value))
						temp = temp->right;
					else if (_compare(value, temp->data))
						temp = temp->left;
					else
						return (temp);
				}
				return (NULL);
			}
			pointer	min(void) const
			{
				pointer	temp = _root;

				while (temp != _nil && temp->left != _nil)
					temp = temp->left;
				return (temp);
			}

		private:

			/* Destructor helper */

			void	destructor(pointer node)
			{
				if (node != _nil)
				{
					destructor(node->left);
					destructor(node->right);
					_node_allocator.destroy(node);
					_node_allocator.deallocate(node, 1);
				}
			}

			/* Element creation */

			pointer	newNode(const value_type &value)
			{
				pointer	newNode;

				newNode = _node_allocator.allocate(1);
				_node_allocator.construct(newNode, value);
				newNode->parent = _nil;
				newNode->left = _nil;
				newNode->right = _nil;
				newNode->colour = RED;
				return (newNode);
			}
			void	copyrecursion(pointer node, pointer nil)
			{				
				if (node != nil)
				{
					insert(node->data);
					if (node->right != nil)
						insert(node->right->data);
					if (node->left != nil)
						insert(node->left->data);
					copyrecursion(node->right, nil);
					copyrecursion(node->left, nil);
				}
			}

			/* Insert and erase helpers */

			void	relinktree(void)
			{
				_root->colour = BLACK;
				_root->parent = _nil;
				_nil->left = _root;
				_nil->right = _root;
			}
			void	leftrotation(pointer node)
			{
				pointer	temp = node->right;

				node->right = temp->left;
				if (temp->left != _nil)
					temp->left->parent = node;
				temp->parent = node->parent;
				if (node->parent == _nil)
					_root = temp;
				else if (node == node->parent->left)
					node->parent->left = temp;
				else
					node->parent->right = temp;
				temp->left = node;
				node->parent = temp;
			}
			void	rightrotation(pointer node)
			{
				pointer	temp = node->left;

				node->left = temp->right;
				if (temp->right != _nil)
					temp->right->parent = node;
				temp->parent = node->parent;
				if (node->parent == _nil)
					_root = temp;
				else if (node == node->parent->right)
					node->parent->right = temp;
				else
					node->parent->left = temp;
				temp->right = node;
				node->parent = temp;
			}
			void	fixinsertion(pointer node)
			{
				while (node != _root && node->parent->colour == RED)
				{
					if (node->parent == node->parent->parent->left)
					{
						if (node->parent->parent->right->colour == RED)
						{
							node->parent->parent->right->colour = BLACK;
							node->parent->colour = BLACK;
							node->parent->parent->colour = RED;
							node = node->parent->parent;
						}
						else if (node == node->parent->right)
						{
							node = node->parent;
							leftrotation(node);
						}
						else
						{
							node->parent->colour = BLACK;
							node->parent->parent->colour = RED;
							rightrotation(node->parent->parent);
						}
					}
					else
					{
						if (node->parent->parent->left->colour == RED)
						{
							node->parent->parent->left->colour = BLACK;
							node->parent->colour = BLACK;
							node->parent->parent->colour = RED;
							node = node->parent->parent;
						}
						else if (node == node->parent->left)
						{
							node = node->parent;
							rightrotation(node);
						}
						else
						{
							node->parent->colour = BLACK;
							node->parent->parent->colour = RED;
							leftrotation(node->parent->parent);
						}
					}
				}
			}
			void	fixerase(pointer node)
			{
				pointer	temp;

				while (node->parent != _nil && node->colour == BLACK)
				{
					if (node == node->parent->left)
					{
						temp = node->parent->right;
						if (temp->colour == RED)
						{
							temp->colour = BLACK;
							node->parent->colour = RED;
							leftrotation(node->parent);
							temp = node->parent->right;
						}
						if (temp->right->colour == BLACK && temp->left->colour == BLACK)
						{
							temp->colour = RED;
							node = node->parent;
						}
						else
						{
							if (temp->right->colour == BLACK)
							{
								temp->left->colour = BLACK;
								temp->colour = RED;
								rightrotation(temp);
								temp = node->parent->right;
							}
							temp->colour = node->parent->colour;
							node->parent->colour = BLACK;
							temp->right->colour = BLACK;
							leftrotation(node->parent);
							node = _root;
						}
					}
					else
					{
						temp = node->parent->left;
						if (temp->colour == RED)
						{
							temp->colour = BLACK;
							node->parent->colour = RED;
							rightrotation(node->parent);
							temp = node->parent->left;
						}
						if (temp->right->colour == BLACK && temp->left->colour == BLACK)
						{
							temp->colour = RED;
							node = node->parent;
						}
						else
						{
							if (temp->left->colour == BLACK)
							{
								temp->right->colour = BLACK;
								temp->colour = RED;
								leftrotation(temp);
								temp = node->parent->left;
							}
							temp->colour = node->parent->colour;
							node->parent->colour = BLACK;
							temp->left->colour = BLACK;
							rightrotation(node->parent);
							node = _root;
						}
					}
				}
				node->colour = BLACK;
			}
			void	transplant(pointer node, pointer temp)
			{
				if (node->parent == _nil)
						_root = temp;
				else if (node == node->parent->left)
					node->parent->left = temp;
				else if (node == node->parent->right)
					node->parent->right = temp;
				temp->parent = node->parent;
			}

			pointer			_root;
			pointer			_nil;
			size_type		_size;
			node_allocator	_node_allocator;
			allocator		_pair_allocator;
			compare			_compare;
	};
}

#endif

/**
* @brief
*
* --rebind--
* Debido a que utilizo un mismo alocador para dos tipos distintos de datos, los datos de cada nodo, y los nodos
* en si mismo, necesito decirle al sistema que voy a generar objetos de otro tipo, por lo que uso rebind para
* obtener un "segundo tipo" de alocador.
*
* --_nil y _root--
* Se trata de dos sentinel nodes. Sirven como elementos simplificadores. Para referirnos a un nodo
* vacio utilizamos nil, y para evitar que al generarse el arbol este este vacio, utilizamos root.
* Evita que tengamos que checkear los casos extremos, tales como el arbol vacio, extremos nulos, etc
* Root tiene padre nil siempre, y nil tiene hijos a izq y dcha root.
**/
