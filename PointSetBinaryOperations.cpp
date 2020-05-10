#include "PointSet.h"

/**
 * Main function for testing PointSet binary operations
 */
int main()
{
	PointSet set1, set2, set3;
	int i;
	std::cout << "Initializing 3 sets..." << std::endl;

	for (i = 0; i < 5; ++i)
	{
		set1.add(Point(i, i));
	}
	for (i = 2; i < 7; ++i)
	{
		set2.add(Point(i, i));
	}
	for (i = 4; i < 9; ++i)
	{
		set3.add(Point(i, i));
	}

	std::cout << "set1:\n" << set1.toString() << std::endl;
	std::cout << "set2:\n" << set2.toString() << std::endl;
	std::cout << "set3:\n" << set3.toString() << std::endl;

	std::cout << "set1 == set2: " << (set1 == set2 ? "True\n" : "False\n") << std::endl;
	std::cout << "set2 != set3: " << (set2 != set3 ? "True\n" : "False\n") << std::endl;
	std::cout << "set1 - set2:\n" << (set1 - set2).toString() << std::endl;
	std::cout << "set2 & set3:\n" << (set2 & set3).toString() << std::endl;
	std::cout << "Assigning set3 to set1 (invokes copy assignment)" << std::endl;
	set1 = set3;
	std::cout << "set1 == set3: " << (set1 == set3 ? "True" : "False") << std::endl;

	return EXIT_SUCCESS;
}