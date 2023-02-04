/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainstdset.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopez-f <jlopez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:30:08 by jlopez-f          #+#    #+#             */
/*   Updated: 2023/01/23 14:08:47 by jlopez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../set.hpp"
#include <set>
#include <string>
#include <iostream>

template <typename T>
void	printstdset(std::set<T> set, std::string name)
{
	int	i = 0;

	std::cout << name << std::endl << "--------------------" << std::endl;
	for (typename std::set<T>::iterator it = set.begin(); it != set.end(); it++)
	{
		std::cout << "set[" << i << "] = " << *it << std::endl;
		i++;
	}
	std::cout << std::endl;
}

int	main()
{
		std::set<int>	*set0 = new std::set<int>;
		set0->insert(0);
		set0->insert(1);
		set0->insert(2);
		set0->insert(3);
		printstdset(*set0, "Set");

		std::set<int>	*set3 = new std::set<int>;
		std::set<int>	*set2 = new std::set<int>(*set0);
		*set3 = *set0;
		delete set0;
		printstdset(*set2, "Set cpy");
		printstdset(*set3, "Set assign");
		std::cout << "Size = " << set3->size() << std::endl << std::endl;
		std::cout << "Empty = " << set3->empty() << std::endl << std::endl;
		set3->clear();
		std::cout << "Size = " << set3->size() << std::endl << std::endl;
		std::cout << "Empty = " << set3->empty() << std::endl << std::endl;
		printstdset(*set3, "Set clear");

		std::set<int>	set((*set2).begin(), (*set2).end());

		delete set2;
		delete set3;
		printstdset(set, "Set iterator constructor");
		std::set<int>	set4;
		set4.insert(4);
		set4.insert(5);
		set4.insert(6);
		set.insert(set4.begin(), set4.end());
		printstdset(set, "Insert iter");
		std::set<int>::iterator	it = set.begin();
		it++;
		it++;
		it++;
		set.erase(it, set.end());
		printstdset(set, "Erase iter");
		it = set.begin();
		it++;
		set.erase(it);
		printstdset(set, "Erase iter");

		set.clear();
		printstdset(set, "Set");
		set4.swap(set);
		printstdset(set, "Set");
		printstdset(set4, "Set 4");

		std::cout << "Count = " << set.count(3) << std::endl;
		std::cout << "Count = " << set.count(4) << std::endl;
		std::cout << "Find(4) = " << *set.find(4) << std::endl;
		it = set.find(3);
		if (it == set.end())
			std::cout << "Find(3) = END" << std::endl;
		else
			std::cout << "Find(3) = " << *set.find(3) << std::endl;
		std::cout << "Lower bound(4) = " << *set.lower_bound(4) << std::endl;
		std::cout << "Upper bound(4) = " << *set.upper_bound(4) << std::endl;
}
