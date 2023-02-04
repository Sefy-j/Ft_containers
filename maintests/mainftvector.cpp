/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainftvector.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopez-f <jlopez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:30:08 by jlopez-f          #+#    #+#             */
/*   Updated: 2023/01/26 18:41:10 by jlopez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vector.hpp"
#include <vector>
#include <string>
#include <iostream>

template <typename T>
void	printftvector(ft::vector<T> vec, std::string name)
{
	int	i = 0;

	std::cout << name << std::endl << "--------------------" << std::endl;
	for (typename ft::vector<T>::iterator it = vec.begin(); it != vec.end(); it++)
	{
		std::cout << "vector[" << i << "] = " << *it << std::endl;
		i++;
	}
	std::cout << std::endl;
}

int	main()
{
	{
		ft::vector<int>	*vec = new ft::vector<int>(5, 5);
		ft::vector<int>	*vec2 = new ft::vector<int>(*vec);
		ft::vector<int>	*vec3 = new ft::vector<int>();

		*vec3 = *vec;
		printftvector(*vec, "Vector");
		delete vec;
		printftvector(*vec2, "Vector cpy");
		printftvector(*vec3, "Vector assign");
		delete vec2;
		delete vec3;
	}
	{
		std::string			str = "abcdef";
		ft::vector<char>	vec(str.begin(), str.end());

		printftvector(vec, "Vector iterator constructor");
		vec[4] = '4';
		vec.front() = '0';
		vec.back() = '5';
		printftvector(vec, "Element access");
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
		printftvector(vec, "Capacity modifiers");
		vec.assign(5, 'a');
		printftvector(vec, "Assign Iter");
		vec.assign(str.begin(), str.end());
		printftvector(vec, "Assign");
		vec.push_back('g');
		printftvector(vec, "Push back");
		vec.pop_back();
		printftvector(vec, "Pop back");
		vec.insert(vec.begin() + 3, '0');
		printftvector(vec, "Insert");
		vec.insert(vec.begin() + 4, 3, '1');
		printftvector(vec, "Insert n");
		vec.insert(vec.begin() + 7, str.begin(), str.end());
		printftvector(vec, "Insert iter");
		vec.erase(vec.begin() + 7, vec.begin() + 13);
		printftvector(vec, "Erase iter");
		vec.erase(vec.begin() + 3);
		printftvector(vec, "Erase");

		ft::vector<char>	vec2(5, '0');
		printftvector(vec2, "Vector 2");
		vec2.clear();
		printftvector(vec2, "Vector 2");
		vec2.swap(vec);
		printftvector(vec, "Vector");
		printftvector(vec2, "Vector 2");
	}
	{
		ft::vector<int>	vec(3, 5);
		ft::vector<int>	vec2(3, 6);

		printftvector(vec, "Vector");
		printftvector(vec2, "Vector 2");
		std::cout << "Vec < vec2 = " << (vec < vec2) << std::endl;
		std::cout << "Vec == vec2 = " << (vec == vec2) << std::endl;
		vec[0] = 7;
		std::cout << "Vec < vec2 = " << (vec < vec2) << std::endl;
	}
}
