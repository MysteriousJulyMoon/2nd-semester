#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <SpaceObject.hpp>

namespace sf
{
	class Destroyer : public SpaceObject
	{
	public:
		Destroyer() = default;
		virtual ~Destroyer() {};

		void Attack() override
		{
			std::cout << "Destroyer Attack" << std::endl;
		}

		void SpecialAbility() override
		{
			std::cout << "Destroyer SpecialAbility" << std::endl;
		}
	};
}