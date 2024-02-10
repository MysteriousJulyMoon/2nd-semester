
#include <iostream>
#include <cmath>
using namespace std;


struct Point 
{
	int x;          //Поля
	int y;
};

class RectPlus 
{
	int m_a, m_b; 
public:
	RectPlus() = default;
	RectPlus(int a, int b) 
	{
		setA(a);
		setB(b);
	}

	void setA(int a)
	{
		if (a < 0)
			std::cout << "Negative A" << std::endl;
		m_a = a;
	}

	void setB(int b)
	{
		if (b < 0)
			std::cout << "Negative B" << std::endl;
		m_b = b;
	}

	int Perimeter()
	{
		return 2 * (m_a + m_b);
	}

	int Square()
	{
		return 2 * (m_a * m_b);
	}

	float Diagonal()
	{
		return sqrt(m_a * m_a + m_b * m_b);
	}

};




int main()
{
	RectPlus r;

	r.setA(1);
	r.setB(2);
	std::cout << r.Perimeter() << std::endl;
	std::cout << r.Square() << std::endl;
	std::cout << r.Diagonal() << std::endl;

	return 0;
}
