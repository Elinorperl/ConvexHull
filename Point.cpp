#include <sstream>
#include "Point.h"

#define DELIM ','

/**
	 * @brief Default constructor, initializes with (0,0)
	 * @return Instance of this class
	 */
Point::Point() : _x(0), _y(0)
{
}

/**
	 * @brief Primary constructor, initializes with given coordinates
	 * @param x 1st coordinate
	 * @param y 2nd coordinate
	 * @return Instance of this class
	 */
Point::Point(int x, int y) : _x(x), _y(y)
{
}

/**
	 * @brief Default destructor
	 */
Point::~Point()
{
}

/**
	 * @brief Sets the coordinates of this point
	 * @param x 1st coordinate
	 * @param y 2nd coordinate
	 */
void Point::set(int x, int y)
{
	_x = x;
	_y = y;
}

/**
	 * @return A string representing an instance of this class as the 2 coordinates separated by
	 * a delimiter
	 */
std::string Point::toString() const
{
	std::stringstream ss;
	ss << _x << DELIM << _y << std::endl;

	return ss.str();
}

/**
	 * @brief An input operator which receives an input stream formatted as "%d,%d" and
	 * initializes an instance of this class using the 2 extracted integers (x,y)
	 * @param input Input stream
	 * @param p Point to initialize
	 * @return The input stream at the end of the line
	 */
std::istream &operator>>(std::istream &input, Point &p)
{
	std::string str;
	std::getline(input, str, DELIM) >> p._y;
	p._x = std::atoi(str.c_str());

	return input;
}

/**
	 * @brief Checks whether points have equal coordinates
	 * @param p The other point for comparison
	 * @return True if equal, false otherwise
	 */
bool Point::operator==(const Point &p) const
{
	return _x == p._x && _y == p._y;
}

/**
	 * @brief Checks whether this point is lesser than the other (by the x value first)
	 * @param p The other point for comparison
	 * @return True if this point is lesser than the other, false otherwise
	 */
bool Point::operator<(const Point &p) const
{
	if (_x != p._x)
	{
		return _x < p._x;
	}

	return _y < p._y;
}