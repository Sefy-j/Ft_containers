/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainstdvector.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopez-f <jlopez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:30:08 by jlopez-f          #+#    #+#             */
/*   Updated: 2023/01/26 18:44:13 by jlopez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vector.hpp"
#include <vector>
#include <string>
#include <iostream>

template <typename T>
void	printstdvector(std::vector<T> vec, std::string name)
{
	int	i = 0;

	std::cout << name << std::endl << "--------------------" << std::endl;
	for (typename std::vector<T>::iterator it = vec.begin(); it != vec.end(); it++)
	{
		std::cout << "vector[" << i << "] = " << *it << std::endl;
		i++;
	}
	std::cout << std::endl;
}

int	main()
{
	{
		std::vector<int>	*vec = new std::vector<int>(5, 5);
		std::vector<int>	*vec2 = new std::vector<int>(*vec);
		std::vector<int>	*vec3 = new std::vector<int>();

		*vec3 = *vec;
		printstdvector(*vec, "Vector");
		delete vec;
		printstdvector(*vec2, "Vector cpy");
		printstdvector(*vec3, "Vector assign");
		delete vec2;
		delete vec3;
	}
	{
		std::string			str = "abcdef";
		std::vector<char>	vec(str.begin(), str.end());

		printstdvector(vec, "Vector iterator constructor");
		vec[4] = '4';
		vec.front() = '0';
		vec.back() = '5';
		printstdvector(vec, "Element access");
		try
		{
			vec.at(10);
		}
		catch(const std::exception &e)
		{
			std::cout << e.what() << std::endl << std::endl;
		}
		std::cout << "Capacity = " << vec.capacity() << std::endl << std::endl;
		vec.reserve(8);
		std::cout << "Capacity = " << vec.capacity() << std::endl << std::endl;
		std::cout << "Size = " << vec.size() << std::endl << std::endl;
		vec.resize(10, 'E');
		std::cout << "Capacity = " << vec.capacity() << std::endl << std::endl;
		std::cout << "Size = " << vec.size() << std::endl << std::endl;
		printstdvector(vec, "Capacity modifiers");
		vec.assign(5, 'a');
		printstdvector(vec, "Assign Iter");
		vec.assign(str.begin(), str.end());
		printstdvector(vec, "Assign");
		vec.push_back('g');
		printstdvector(vec, "Push back");
		vec.pop_back();
		printstdvector(vec, "Pop back");
		vec.insert(vec.begin() + 3, '0');
		printstdvector(vec, "Insert");
		vec.insert(vec.begin() + 4, 3, '1');
		printstdvector(vec, "Insert n");
		vec.insert(vec.begin() + 7, str.begin(), str.end());
		printstdvector(vec, "Insert iter");
		vec.erase(vec.begin() + 7, vec.begin() + 13);
		printstdvector(vec, "Erase iter");
		vec.erase(vec.begin() + 3);
		printstdvector(vec, "Erase");

		std::vector<char>	vec2(5, '0');
		printstdvector(vec2, "Vector 2");
		vec2.clear();
		printstdvector(vec2, "Vector 2");
		vec2.swap(vec);
		printstdvector(vec, "Vector");
		printstdvector(vec2, "Vector 2");
	}
	{
		std::vector<int>	vec(3, 5);
		std::vector<int>	vec2(3, 6);

		printstdvector(vec, "Vector");
		printstdvector(vec2, "Vector 2");
		std::cout << "Vec < vec2 = " << (vec < vec2) << std::endl;
		std::cout << "Vec == vec2 = " << (vec == vec2) << std::endl;
		vec[0] = 7;
		std::cout << "Vec < vec2 = " << (vec < vec2) << std::endl;
	}
}
