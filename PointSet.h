#ifndef POINTSET_H
#define POINTSET_H

#include "Point.h"

/**
 * @brief A set of 2D points
 */
class PointSet
{
private:
	Point *_points; // Array of points
	int _capacity, _size; // For all cases: _capacity > 0 && _capacity >= _size
	bool _checkDuplicate;

	/**
	 * @brief Resizes the array to fit a capacity
	 * @param newCapacity The capacity to fit to
	 */
	void _fitCapacityTo(int newCapacity);

public:
	/**
	 * @brief Default constructor, initializes with a default capacity and with duplication check
	 * turned on
	 * @return An instance of this class
	 */
	PointSet();

	/**
	 * @brief Primary constructor, initializes with given capacity and with duplication check
	 * turned on unless false is passed
	 * @param capacity Initial capacity of the set (size of the array)
	 * @param checkDuplicate Determines whether the instance of this class should check for
	 * duplicates with every addition or not
	 * @return An instance of this class
	 */
	PointSet(int capacity, bool checkDuplicate = true);

	/**
	 * @brief Copy constructor
	 * @param set Other set to copy from for initialization of this instance
	 * @return An instance of this class
	 */
	PointSet(const PointSet &set);

	/**
	 * @brief Destructor, deletes the array this stores
	 */
	~PointSet();

	/**
	 * @param p Point to find in the array
	 * @return Index of the point in the array if it was found, -1 otherwise
	 */
	int indexOf(Point &p) const;

	/**
	 * @brief Adds a point to the set (checks for duplicates if the feature is enabled)
	 * @param p Point to add to the set
	 * @return True if point was added, false otherwise
	 */
	bool add(Point p);

	/**
	 * @brief Removes a point from the set
	 * @param p Point to remove
	 * @return True if the point was found and removed, false otherwise
	 */
	bool remove(Point &p);

	/**
	 * @brief Removes a point at an index
	 * @param i Index of the point to remove
	 */
	void removeAt(int i);

	/**
	 * @brief Removes the last point added to the set (at index of _size - 1)
	 */
	void removeLast();

	/**
	 * @brief Shrinks _capacity (size of _points array) to _size (amount of points in the array)
	 */
	void shrinkToFit();

	/**
	 * @brief Sorts the set with the default comparator as '<'
	 * @param begin The index where to begin the sort
	 * @param end The index where to end the sort
	 */
	void sort(int begin, int end);

	/**
	 * @brief Sorts the set with a given comparator
	 * @param begin The index where to begin the sort
	 * @param end The index where to end the sort
	 * @param compare Comparator to sort with
	 */
	void sort(int begin, int end, bool (*compare)(Point a, Point b));

	/**
	 * @brief Concatenates the representation of each point in the set
	 * @return The representation of the whole set
	 */
	std::string toString() const;

	/**
	 * @brief Checks whether this and another set contain the same elements
	 * @param set The other set to compare with
	 * @return True if the sets contain exactly the same elements, false otherwise
	 */
	bool operator==(const PointSet &set) const;

	/**
	 * @brief Checks whether this and another set don't contain the same elements
	 * @param set The other set to compare with
	 * @return True if one set contains at least 1 element the other one doesn't, false otherwise
	 */
	bool operator!=(const PointSet &set) const;

	/**
	 * @brief Subtracts another set from this set
	 * @param set Other set to subtract
	 * @return New set after subtraction
	 */
	PointSet operator-(const PointSet &set) const;

	/**
	 * @brief Intersects this and another set
	 * @param set Other set to intersect with this one
	 * @return New set representing the intersection
	 */
	PointSet operator&(const PointSet &set) const;

	/**
	 * @brief Copy assignment operator
	 * @param set Other set to copy from
	 * @return This set
	 */
	PointSet &operator=(const PointSet &set);

	/**
	 * @brief Operator for easy (cyclic too) index-based access to points of this set
	 * @param i Index of requested point
	 * @return Point at the given index
	 */
	inline Point &operator[](const int i)
	{
		return i >= 0 ? _points[i] : _points[_size + i];
	}

	/**
	 * @return Size of this set i.e. the amount of points this set contains
	 */
	inline int size() const
	{
		return _size;
	}

	/**
	 * @return Capacity of this set i.e. the size of _points
	 */
	inline int capacity() const
	{
		return _capacity;
	}
};


#endif // POINTSET_H