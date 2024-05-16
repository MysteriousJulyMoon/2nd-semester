#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "SpaceGarbage.hpp"

namespace sf
{

	class Comet : public SpaceGarbage
	{
	public:
		Comet() = default;
		virtual ~Comet() {};
		void SpecialAbility() override
		{
			std::cout << "Comet SpecialAbility" << std::endl;
		}

	};
}
