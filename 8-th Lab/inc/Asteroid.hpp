#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "SpaceGarbage.hpp"

namespace sf 
{

	class Asteroid : public SpaceGarbage 
	{
	public:
		Asteroid() = default;
		virtual ~Asteroid() {};
		void SpecialAbility() override
		{
			std::cout << "Asteroid SpecialAbility" << std::endl;
		}
	
	};
}
