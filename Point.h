#ifndef POINT_H
#define POINT_H

#include <iostream>

/**
 * @brief Represents a point in 2D space
 */
class Point
{
private:
	int _x, _y; // Coordinates
public:
	/**
	 * @brief Default constructor, initializes with (0,0)
	 * @return Instance of this class
	 */
	Point();

	/**
	 * @brief Primary constructor, initializes with given coordinates
	 * @param x 1st coordinate
	 * @param y 2nd coordinate
	 * @return Instance of this class
	 */
	Point(int x, int y);

	/**
	 * @brief Default destructor
	 */
	~Point();

	/**
	 * @brief Sets the coordinates of this point
	 * @param x 1st coordinate
	 * @param y 2nd coordinate
	 */
	void set(int x, int y);

	/**
	 * @return A string representing an instance of this class as the 2 coordinates separated by
	 * a delimiter
	 */
	std::string toString() const;

	/**
	 * @brief An input operator which receives an input stream formatted as "%d,%d" and
	 * initializes an instance of this class using the 2 extracted integers (x,y)
	 * @param input Input stream
	 * @param p Point to initialize
	 * @return The input stream at the end of the line
	 */
	friend std::istream &operator>>(std::istream &input, Point &p);

	/**
	 * @brief Checks whether points have equal coordinates
	 * @param p The other point for comparison
	 * @return True if equal, false otherwise
	 */
	bool operator==(const Point &p) const;

	/**
	 * @brief Checks whether this point is lesser than the other (by the x value first)
	 * @param p The other point for comparison
	 * @return True if this point is lesser than the other, false otherwise
	 */
	bool operator<(const Point &p) const;

	/**
	 * @return The x value of this point
	 */
	inline const int &getX() const
	{
		return _x;
	}

	/**
	 * @return The y value of this point
	 */
	inline const int &getY() const
	{
		return _y;
	}
};


#endif // POINT_H