/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopez-f <jlopez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 17:36:30 by jlopez-f          #+#    #+#             */
/*   Updated: 2022/11/03 15:38:02 by jlopez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace	ft
{
	template <typename T>
 	class vector_iterator
	{
		public:

			/* Data types definitions */
		
			typedef typename ft::iterator_traits<T>::value_type			value_type;
			typedef typename ft::iterator_traits<T>::difference_type	difference_type;
			typedef typename ft::iterator_traits<T>::pointer			pointer;
			typedef typename ft::iterator_traits<T>::reference			reference;
			typedef typename ft::iterator_traits<T>::iterator_category	iterator_category;

			/* Constructors */

			vector_iterator(void) : _data(0) {}
			explicit	vector_iterator(T elem) : _data(elem) {}
			template <typename U>
			vector_iterator(const vector_iterator<U> &other) { *this = other; }

			/* Destructor */

			~vector_iterator(void) {}

			/* Operator assignation */
			
			template <typename U>
			vector_iterator	&operator=(const vector_iterator<U> &other)
			{
				_data = other.base();
				return (*this);
			}

			/* Access */

			pointer base(void) const { return (_data); }

			/* Operators */

			reference	operator*(void) const { return (*_data); }
			reference	operator[](difference_type n) const { return (*(_data + n)); }
			pointer		operator->(void) const { return (_data); }

			vector_iterator	operator+(difference_type n) const { return (vector_iterator(_data + n)); }
			vector_iterator	operator-(difference_type n) const { return (vector_iterator(_data - n)); }
			vector_iterator	&operator+=(difference_type n) { _data += n; return (*this); }
			vector_iterator	&operator-=(difference_type n) { _data -= n; return (*this); }
			vector_iterator	&operator++(void) { _data++; return (*this); }
			vector_iterator	&operator--(void) { _data--; return (*this); }
			vector_iterator	operator++(int) { vector_iterator temp(*this); _data++; return (temp); }
			vector_iterator	operator--(int) { vector_iterator temp(*this); _data--; return (temp); }

	 	private:

	 		pointer	_data;
	};

	/* Non Member Operators */

	template <typename T, typename U>
	bool	operator<(const vector_iterator<T> &lhs, const vector_iterator<U> &rhs) { return (lhs.base() < rhs.base()); }
	template <typename T, typename U>
	bool	operator>(const vector_iterator<T> &lhs, const vector_iterator<U> &rhs) { return (lhs.base() > rhs.base()); }
	template <typename T, typename U>
	bool	operator<=(const vector_iterator<T> &lhs, const vector_iterator<U> &rhs) {return (lhs.base() <= rhs.base()); }
	template <typename T, typename U>
	bool	operator>=(const vector_iterator<T> &lhs, const vector_iterator<U> &rhs) { return (lhs.base() >= rhs.base()); }
	template <typename T, typename U>
	bool	operator==(const vector_iterator<T> &lhs, const vector_iterator<U> &rhs) { return (lhs.base() == rhs.base()); }
	template <typename T, typename U>
	bool	operator!=(const vector_iterator<T> &lhs, const vector_iterator<U> &rhs) { return (lhs.base() != rhs.base()); }

	template <typename T>
	vector_iterator<T>	operator+(typename vector_iterator<T>::difference_type n, const vector_iterator<T> &rhs)
	{ return (vector_iterator<T>(rhs.base() + n)); }
	template <typename T, typename U>
	typename vector_iterator<T>::difference_type	operator-(const vector_iterator<T> &lhs, const vector_iterator<U> &rhs)
	{ return (lhs.base() - rhs.base()); }
}

#endif

/**
* @brief
*
* Un iterador es una clase que permite el desplazamiento a traves de los elementos de una serie de datos
* (en este caso los contenedores) mediante distintos operadores. Dependiendo de los
* posibles movimientos (solo en un sentido, solo hacia "adelante", en saltos, etc.) o de las
* opciones de acceso a los datos (solo lectura, solo escritura o total) se clasifican de distintas formas.
* Como mínimo deben permitir el incremento (++) y la desreferenciacion (*), pero segun su
* tipo pueden permitir otra serie de operadores (==, --, !=, [i], +i, etc.) 
*
* Generalmente, todos estos iteradores tienen una serie de elementos comunes, especificados en los
* iterators_traits. Se trata de distintos miembros que van a permitir aplicar dichos iteradores a
* cualquier conjunto de datos. Elementos como el tipo de datos al que se refieren, el elemento que se va a usar
* como puntero o referencia a los mismos, o el elemento que va a permitir calcular las distancias entre ellos.
*
* Además, es importante la iterator_category, que marca el tipo de iterador de acuerdo a los tipos estándar.
* De manera estandar, estos tipos se encuentran en iterators_tags, que esta compuesto por una serie de
* structs que sirven como nombres para los distintos tipos. Estan vacias, puesto que el único uso es el de
* darle un nombre (tag), para diferenciarlos, y en ciertos casos tener en cuenta las herencias entre estos tipos.
*
* https://cplusplus.com/reference/iterator/
* https://cplusplus.com/reference/iterator/iterator_traits/
* https://www.codeproject.com/Articles/36530/An-Introduction-to-Iterator-Traits
* https://www.internalpointers.com/post/writing-custom-iterators-modern-cpp
* https://www.drdobbs.com/the-standard-librarian-defining-iterato/184401331
**/
