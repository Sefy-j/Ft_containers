/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainstdmap.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopez-f <jlopez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:30:08 by jlopez-f          #+#    #+#             */
/*   Updated: 2023/01/23 13:32:47 by jlopez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../map.hpp"
#include <map>
#include <string>
#include <iostream>

template <typename T, typename U>
void	printstdmap(std::map<T, U> map, std::string name)
{
	int	i = 0;

	std::cout << name << std::endl << "--------------------" << std::endl;
	for (typename std::map<T, U>::iterator it = map.begin(); it != map.end(); it++)
	{
		std::cout << "map[" << i << "] = {" << (*it).first << "," << (*it).second << "}" << std::endl;
		i++;
	}
	std::cout << std::endl;
}

int	main()
{
		std::map<int, std::string>	*map0 = new std::map<int, std::string>;
		(*map0)[0] = "a";
		(*map0)[1] = "b";
		(*map0)[2] = "c";
		(*map0)[3] = "d";
		printstdmap(*map0, "Map");

		std::map<int, std::string>	*map3 = new std::map<int, std::string>;
		std::map<int, std::string>	*map2 = new std::map<int, std::string>(*map0);
		*map3 = *map0;
		delete map0;
		printstdmap(*map2, "Map cpy");
		printstdmap(*map3, "Map assign");
		std::cout << "Size = " << map3->size() << std::endl << std::endl;
		std::cout << "Empty = " << map3->empty() << std::endl << std::endl;
		map3->clear();
		std::cout << "Size = " << map3->size() << std::endl << std::endl;
		std::cout << "Empty = " << map3->empty() << std::endl << std::endl;
		printstdmap(*map3, "Map clear");

		std::map<int, std::string>	map((*map2).begin(), (*map2).end());

		delete map2;
		delete map3;
		printstdmap(map, "Map iterator constructor");
		try
		{
			map.at(4);
		}
		catch(const std::exception &e)
		{
			std::cout << e.what() << std::endl << std::endl;
		}
		map.insert(std::make_pair(7, "h"));
		printstdmap(map, "Insert");
		std::map<int, std::string>	map4;
		map4[4] = "e";
		map4[5] = "f";
		map4[6] = "g";
		map.insert(map4.begin(), map4.end());
		printstdmap(map, "Insert iter");
		std::map<int, std::string>::iterator	it = map.begin();
		it++;
		it++;
		it++;
		it++;
		map.erase(it, map.end());
		printstdmap(map, "Erase iter");
		map.erase(2);
		printstdmap(map, "Erase key");
		it = map.begin();
		it++;
		map.erase(it);
		printstdmap(map, "Erase iter");

		map.clear();
		printstdmap(map, "Map");
		map4.swap(map);
		printstdmap(map, "Map");
		printstdmap(map4, "Map 4");

		std::cout << "Count = " << map.count(3) << std::endl;
		std::cout << "Count = " << map.count(4) << std::endl;
		std::cout << "Find(4) = {" << (*map.find(4)).first << "," << (*map.find(4)).second << "}" << std::endl;
		it = map.find(3);
		if (it == map.end())
			std::cout << "Find(3) = END" << std::endl;
		else
			std::cout << "Find(3) = END" << std::endl;
		std::cout << "Lower bound(4) = {" << (*map.lower_bound(4)).first << "," << (*map.lower_bound(4)).second << "}" << std::endl;
		std::cout << "Upper bound(4) = {" << (*map.upper_bound(4)).first << "," << (*map.upper_bound(4)).second << "}" << std::endl;
}
