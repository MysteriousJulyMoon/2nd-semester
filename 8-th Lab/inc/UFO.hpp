#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <SpaceObject.hpp>

namespace sf 
{
	class UFO : public SpaceObject
	{
	public:
		UFO() = default;
		virtual ~UFO() {};


		void Attack() override
		{
			std::cout << "UFO Attack" << std::endl;
		}

		void SpecialAbility() override
		{
			std::cout << "UFO SpecialAbility" << std::endl;
		}
	};
}