#include "PointSet.h"
#include <algorithm>
#include <sstream>

#define NOT_FOUND -1

#define DEFAULT_INIT_CAPACITY 10 // As Java's ArrayList
#define RESIZE_FACTOR 2

/**
	 * @brief Default constructor, initializes with a default capacity and with duplication check
	 * turned on
	 * @return An instance of this class
	 */
PointSet::PointSet() : _points(new Point[DEFAULT_INIT_CAPACITY]), _capacity(DEFAULT_INIT_CAPACITY),
                       _size(0), _checkDuplicate(true)
{
}

/**
	 * @brief Primary constructor, initializes with given capacity and with duplication check
	 * turned on unless false is passed
	 * @param capacity Initial capacity of the set (size of the array)
	 * @param checkDuplicate Determines whether the instance of this class should check for
	 * duplicates with every addition or not
	 * @return An instance of this class
	 */
PointSet::PointSet(int capacity, bool checkDuplicate) :
		_points(new Point[capacity]), _capacity(capacity), _size(0), _checkDuplicate(checkDuplicate)
{
}

/**
	 * @brief Copy constructor
	 * @param set Other set to copy from for initialization of this instance
	 * @return An instance of this class
	 */
PointSet::PointSet(const PointSet &set) : _size(0)
{
	operator=(set);
}

/**
	 * @brief Destructor, deletes the array this stores
	 */
PointSet::~PointSet()
{
	delete[] _points;
}

/**
	 * @param p Point to find in the array
	 * @return Index of the point in the array if it was found, -1 otherwise
	 */
int PointSet::indexOf(Point &p) const
{
	for (int i = 0; i < _size; ++i)
	{
		if (_points[i] == p)
		{
			return i;
		}
	}

	return NOT_FOUND;
}

/**
	 * @brief Adds a point to the set (checks for duplicates if the feature is enabled)
	 * @param p Point to add to the set
	 * @return True if point was added, false otherwise
	 */
bool PointSet::add(Point p)
{
	if (_checkDuplicate && indexOf(p) != NOT_FOUND)
	{
		return false;
	}
	if (_size == _capacity)
	{
		_fitCapacityTo(_capacity * RESIZE_FACTOR);
	}

	_points[_size++] = p;
	return true;
}

/**
	 * @brief Removes a point from the set
	 * @param p Point to remove
	 * @return True if the point was found and removed, false otherwise
	 */
bool PointSet::remove(Point &p)
{
	int existIndex = indexOf(p);

	if (existIndex != NOT_FOUND)
	{
		return false;
	}

	removeAt(existIndex);
	return true;
}

/**
	 * @brief Removes a point at an index
	 * @param i Index of the point to remove
	 */
void PointSet::removeAt(int removeIdx)
{
	--_size;

	for (int i = removeIdx; i < _size; ++i)
	{
		_points[i] = _points[i + 1];
	}

	if (_size <= _capacity / RESIZE_FACTOR && _size != 0)
	{
		_fitCapacityTo(_size);
	}
}

/**
	 * @brief Removes the last point added to the set (at index of _size - 1)
	 */
void PointSet::removeLast()
{
	removeAt(_size - 1);
}

/**
	 * @brief Resizes the array to fit a capacity
	 * @param newCapacity The capacity to fit to
	 */
void PointSet::_fitCapacityTo(int newCapacity)
{
	Point *newPoints = new Point[_capacity = newCapacity];
	std::copy_n(_points, _size, newPoints);
	delete[] _points;
	_points = newPoints;
}

/**
	 * @brief Shrinks _capacity (size of _points array) to _size (amount of points in the array)
	 */
void PointSet::shrinkToFit()
{
	if (_size != _capacity && _size != 0)
	{
		_fitCapacityTo(_size);
	}
}

/**
	 * @brief Sorts the set with the default comparator as '<'
	 * @param begin The index where to begin the sort
	 * @param end The index where to end the sort
	 */
void PointSet::sort(int begin, int end)
{
	std::sort(_points + begin, _points + end);
}

/**
	 * @brief Sorts the set with a given comparator
	 * @param begin The index where to begin the sort
	 * @param end The index where to end the sort
	 * @param compare Comparator to sort with
	 */
void PointSet::sort(int begin, int end, bool (*compare)(Point, Point))
{
	std::sort(_points + begin, _points + end, compare);
}

/**
	 * @brief Concatenates the representation of each point in the set
	 * @return The representation of the whole set
	 */
std::string PointSet::toString() const
{
	std::stringstream ss;

	for (int i = 0; i < _size; ++i)
	{
		ss << _points[i].toString();
	}

	return ss.str();
}

/**
	 * @brief Checks whether this and another set contain the same elements
	 * @param set The other set to compare with
	 * @return True if the sets contain exactly the same elements, false otherwise
	 */
bool PointSet::operator==(const PointSet &set) const
{
	if (_size != set._size)
	{
		return false;
	}
	for (int i = 0; i < _size; ++i)
	{
		if (set.indexOf(_points[i]) == NOT_FOUND)
		{
			return false;
		}
	}

	return true;
}

/**
	 * @brief Checks whether this and another set don't contain the same elements
	 * @param set The other set to compare with
	 * @return True if one set contains at least 1 element the other one doesn't, false otherwise
	 */
bool PointSet::operator!=(const PointSet &set) const
{
	return !(operator==(set));
}

/**
	 * @brief Subtracts another set from this set
	 * @param set Other set to subtract
	 * @return New set after subtraction
	 */
PointSet PointSet::operator-(const PointSet &set) const
{
	PointSet retSet(_capacity);

	if (this != &set)
	{
		for (int i = 0; i < _size; ++i)
		{
			Point p = _points[i];

			if (set.indexOf(p) == NOT_FOUND)
			{
				retSet.add(p);
			}
		}
	}

	return retSet;
}

/**
	 * @brief Intersects this and another set
	 * @param set Other set to intersect with this one
	 * @return New set representing the intersection
	 */
PointSet PointSet::operator&(const PointSet &set) const
{
	// Temporarily disables duplication check
	PointSet interSet(std::min(_size, set._size), false);

	for (int i = 0; i < set._size; ++i)
	{
		Point p = set._points[i];

		if (indexOf(p) != NOT_FOUND)
		{
			interSet.add(p);
		}
	}

	interSet._checkDuplicate = true;
	return interSet;
}

/**
	 * @brief Copy assignment operator
	 * @param set Other set to copy from
	 * @return This set
	 */
PointSet &PointSet::operator=(const PointSet &set)
{
	if (this != &set)
	{
		_capacity = set._capacity;
		_checkDuplicate = set._checkDuplicate;

		if (_size != set._size)
		{
			if (_size)
			{
				delete[] _points;
			}

			_size = set._size;
			_points = new Point[_capacity];
		}

		std::copy_n(set._points, _size, _points);
	}

	return *this;
}