/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopez-f <jlopez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 17:55:26 by jlopez-f          #+#    #+#             */
/*   Updated: 2022/11/12 00:53:35 by jlopez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

#include "iterator_traits.hpp"

namespace	ft
{
	/* Enable if */

	template <bool B, typename T = void>
	struct enable_if {};
 
	template <typename T>
	struct enable_if<true, T> { typedef T type; };

	/* Is integral */

	template <typename T>
	struct	is_integral { static bool const value = false; };
	template <>	struct
	is_integral<bool> { static bool const value = true; };
	template <>	struct
	is_integral<char> { static bool const value = true; };
	template <>	struct
	is_integral<wchar_t> { static bool const value = true; };
	template <>	struct
	is_integral<signed char> { static bool const value = true; };
	template <>	struct
	is_integral<short int> { static bool const value = true; };
	template <>	struct
	is_integral<int> { static bool const value = true; };
	template <>	struct
	is_integral<long int> { static bool const value = true; };
	template <>	struct
	is_integral<long long int> { static bool const value = true; };
	template <>	struct
	is_integral<unsigned char> { static bool const value = true; };
	template <>	struct
	is_integral<unsigned short int> { static bool const value = true; };
	template <>	struct
	is_integral<unsigned int> { static bool const value = true; };
	template <>	struct
	is_integral<unsigned long int> { static bool const value = true; };
	template <>	struct
	is_integral<unsigned long long int> { static bool const value = true; };
	template <>	struct
	is_integral<const bool> { static bool const value = true; };
	template <>	struct
	is_integral<const char> { static bool const value = true; };
	template <>	struct
	is_integral<const wchar_t> { static bool const value = true; };
	template <>	struct
	is_integral<const signed char> { static bool const value = true; };
	template <>	struct
	is_integral<const short int> { static bool const value = true; };
	template <>	struct
	is_integral<const int> { static bool const value = true; };
	template <>	struct
	is_integral<const long int> { static bool const value = true; };
	template <>	struct
	is_integral<const long long int> { static bool const value = true; };
	template <>	struct
	is_integral<const unsigned char> { static bool const value = true; };
	template <>	struct
	is_integral<const unsigned short int> { static bool const value = true; };
	template <>	struct
	is_integral<const unsigned int> { static bool const value = true; };
	template <>	struct
	is_integral<const unsigned long int> { static bool const value = true; };
	template <>	struct
	is_integral<const unsigned long long int> { static bool const value = true; };
	template <>	struct
	is_integral<volatile bool> { static bool const value = true; };
	template <>	struct
	is_integral<volatile char> { static bool const value = true; };
	template <>	struct
	is_integral<volatile wchar_t> { static bool const value = true; };
	template <>	struct
	is_integral<volatile signed char> { static bool const value = true; };
	template <>	struct
	is_integral<volatile short int> { static bool const value = true; };
	template <>	struct
	is_integral<volatile int> { static bool const value = true; };
	template <>	struct
	is_integral<volatile long int> { static bool const value = true; };
	template <>	struct
	is_integral<volatile long long int> { static bool const value = true; };
	template <>	struct
	is_integral<volatile unsigned char> { static bool const value = true; };
	template <>	struct
	is_integral<volatile unsigned short int> { static bool const value = true; };
	template <>	struct
	is_integral<volatile unsigned int> { static bool const value = true; };
	template <>	struct
	is_integral<volatile unsigned long int> { static bool const value = true; };
	template <>	struct
	is_integral<volatile unsigned long long int> { static bool const value = true; };
	template <>	struct
	is_integral<const volatile bool> { static bool const value = true; };
	template <>	struct
	is_integral<const volatile char> { static bool const value = true; };
	template <>	struct
	is_integral<const volatile wchar_t> { static bool const value = true; };
	template <>	struct
	is_integral<const volatile signed char> { static bool const value = true; };
	template <>	struct
	is_integral<const volatile short int> { static bool const value = true; };
	template <>	struct
	is_integral<const volatile int> { static bool const value = true; };
	template <>	struct
	is_integral<const volatile long int> { static bool const value = true; };
	template <>	struct
	is_integral<const volatile long long int> { static bool const value = true; };
	template <>	struct
	is_integral<const volatile unsigned char> { static bool const value = true; };
	template <>	struct
	is_integral<const volatile unsigned short int> { static bool const value = true; };
	template <>	struct
	is_integral<const volatile unsigned int> { static bool const value = true; };
	template <>	struct
	is_integral<const volatile unsigned long int> { static bool const value = true; };
	template <>	struct
	is_integral<const volatile unsigned long long int> { static bool const value = true; };

	/* Is input_iterator */

	template <typename T>
	struct	is_inputit { static bool const value = false; };
	template <>	struct
	is_inputit<std::input_iterator_tag> { static bool const value = true; };

	/* Comparisons */

	template <typename InputIt1, typename InputIt2>
	bool	equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
	{
		while (first1 != last1)
		{
			if (*first1 != *first2)
				return (false);
			first1++;
			first2++;
		}
		return (true);
	}
	template <typename InputIt1, typename InputIt2>
	bool	lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
	{
		while (first1!=last1)
		{
			if (first2 == last2)
				return (false);
			if (*first1 < *first2)
				return (true);
			if (*first2 < *first1)
				return (false);
			first1++;
			first2++;
		}
		return (first2 != last2);
	}

	/* Utils */

	template <typename T>
	void	swap(T &x, T &y)
	{
		T	tmp;

		tmp = x;
		x = y;
		y = tmp;
	}

	template <typename T>
	T*		addressof(T &arg) { return (reinterpret_cast<T*>(&const_cast<char&>(reinterpret_cast<const volatile char&>(arg)))); }
}

#endif

/**
* @brief
*
* --SFINAE(Substitution Failure Is Not An Error)--
* Se trata de una característica del compilador que permite que al intentar sustituir una variable en un
* template, si esta sustitución falla, no se entienda directamente como un error. Así, el sistema intentará
* sustituir la variable en otra especialización del mismo template y, siempre que exista al menos una opción
* válida, se utilizará dicha versión. De este modo se puede conseguir que el sistema entienda de manera
* pseudo-inteligente que versión es la que queremos utilizar. Es parecido a hacer especializaciones múltiples
* de un template, pero de una manera mucho más genérica, puesto que es el propio compilador el que se encarga
* de encontrar la "especialización" más adecuada.
*
* --Enable_if--
* Se utiliza para activar de forma condicional ciertos templates o especializaciones de funciones gracias al uso
* del SFINAE. Debe combinarse con una función booleana tipo "is_integral". Así, si el resultado de la función
* booleana es true, el miembro "type" del enable if quedará definido como el parámetro del template, mientras que
* si falla, no existirá. Así, cuando el compilador intente activar un template que disponga de un parámetro dado
* como enable if, este solo existirá si la condición es cierta, de modo que solo podra realizarse la sustitución
* en dicho template si es válido. Si no, fallará, y mediante el SFINAE intentará hacer la sustitución en otro
* template distinto.
*
* --Is_integral-
* Es una serie de templates especializados, de modo que si el parámetro T se corresponde con alguno de los tipos
* válidos (un tipo integral), la struct quedará inicializada a true, mientras que en el caso contrario lo estará
* a false. Utiliza SFINAE. Muy útil en combinación con enable if.
*
* --Addressof--
* Se utiliza para obtener la dirección de memoria de un elemento. Sirve cuando se ha sobrecargado el operador
* &, de modo que aun en ese caso podamos obtener dicha dirección. Consiste en tres casteos distintos:
*     -> Se castea el objeto T a un "const volatile char&". Es un char debido a que el es un tipo intrinseco de
*       dato, de modo que no puede tener el operador sobrecargado. Además, el alineamiento (los bytes que deben
*       dejarse entre objeto y objeto) es de 1 (frente a por ejemplo, los int, que serian 4), de modo que no
*       puede modificar la memoria de ninguna forma. Además, se añaden los calificadores const y volatile porque
*       el reinterpret cast puede añadir dichos parámetros pero no quitarlos. Si el objeto T tuviese alguno de
*       dichos parámetros, daría un error al intentar eliminarlos, por si ya tuviesen uno u ambos.
*     -> Para eliminar ahora los parámetros const y volatile, se caste con un const_cast, que si puede eliminarlos.
*     -> Por último, ya podemos usar este resultado para castearlo como dirección de objeto T.
* https://stackoverflow.com/questions/16195032/implementation-of-addressof
**/

