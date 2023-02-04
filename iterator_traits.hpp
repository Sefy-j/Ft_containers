/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopez-f <jlopez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 17:55:26 by jlopez-f          #+#    #+#             */
/*   Updated: 2022/10/04 17:21:36 by jlopez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

#include <iterator>
#include <cstddef>

namespace	ft
{
	template <typename T>
	struct iterator_traits
	{
		typedef typename T::value_type			value_type;
		typedef typename T::difference_type		difference_type;
		typedef typename T::pointer				pointer;
		typedef typename T::reference			reference;
		typedef typename T::iterator_category	iterator_category;
	};

	template <typename T>
	struct iterator_traits<T*>
	{
		typedef T								value_type;
		typedef ptrdiff_t						difference_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};

	template <typename T>
	struct iterator_traits<const T*>
	{
		typedef T								value_type;
		typedef ptrdiff_t						difference_type;
		typedef const T*						pointer;
		typedef const T&						reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};
}

#endif

/**
* @brief
*
* De manera general, los miembros de iterator_traits se obtienen a partir del propio iterador
* utilizado como parametro del template. Así, en un iterador que tenga todos los elementos bien
* definidos podremos obtener facilmente sus traits a partir de el mismo.
*
* Sin embargo, en el caso especial de los punteros (y por extension, de los punteros constantes),
* no podemos obtener estos datos como si fueran una clase, porque no tienen miembros como tal. Pero
* si que pueden ser utilizados como iteradores (de hecho, es el tipo de iterador mas básico, pues no
* requiere implementación como clase). Así, utilizamos dos especializaciones de los iterator_traits
* para punteros y punteros constantes, donde definimos directamente que vamos a utilizar como miembros
* a partir de ellos mismos. Es interesante ver como los punteros son random access iterators, puesto
* que permiten todas las operaciones que tiene un iterador de este tipo.
*
* Utilizamos los tags estandar para hacer 
* https://www.codeproject.com/Articles/36530/An-Introduction-to-Iterator-Traits
*/
