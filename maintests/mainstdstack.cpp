/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainstdstack.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopez-f <jlopez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:30:08 by jlopez-f          #+#    #+#             */
/*   Updated: 2023/01/26 18:45:33 by jlopez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../stack.hpp"
#include <stack>
#include <string>
#include <iostream>

int	main()
{
	std::stack<int>	stk;

	std::cout << "Size = " << stk.size() << std::endl;
	std::cout << "Empty = " << stk.empty() << std::endl;
	stk.push(0);
	stk.push(1);
	stk.push(2);
	stk.push(3);
	std::cout << "Size = " << stk.size() << std::endl;
	std::cout << "Empty = " << stk.empty() << std::endl;
	std::cout << "Top = " << stk.top() << std::endl;
	stk.pop();
	stk.pop();
	std::cout << "Top = " << stk.top() << std::endl;
}
