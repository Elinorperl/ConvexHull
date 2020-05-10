/**
 * @section ALGORITHM DESCRIPTION
 * Each point added to the set iff there's no other identical point in the set. During insertion,
 * the program keeps track of the pivot index (leftmost point).
 * Then, it swaps the pivot with the first indexed point and initializes the Graham Scan. A hull
 * is constructed which gets points pushed into it if they form a counter-clockwise turn with other
 * 2 points from the top of the stack. Points get popped off the stack while they form a clockwise
 * turn or a line with the top points. after it's done iterating over all the set's points, the
 * hull is sorted with the '<' operator as the comparator and gets printed.
 *
 * @section TIME COMPLEXITY
 * It's O(n * log(n)). Observe the loop in the Graham Scan function. It goes over n points and then
 * checks 3 points in a sub-loop which counts as O(log(n)).
 *
 * @source
 * http://www.geeksforgeeks.org/convex-hull-set-2-graham-scan/
 */

#include <algorithm>
#include <sstream>
#include "Point.h"
#include "PointSet.h"

#define MIN_SCAN_SIZE 2

#define CLOCKWISE 1
#define C_CLOCKWISE -1
#define COLLINEAR 0

#define RESULT_TITLE "result\n"

PointSet *set = nullptr;
int pivotIndex = 0;
Point pivot;

/**
 * @return -1 if a -> b -> c forms a counter-clockwise turn
 *         1 for a clockwise turn
 *         0 if they are collinear
 */
inline int ccw(Point a, Point b, Point c)
{
	int area = (b.getX() - a.getX()) * (c.getY() - a.getY()) -
	           (b.getY() - a.getY()) * (c.getX() - a.getX());
	return area > 0 ? C_CLOCKWISE : area < 0 ? CLOCKWISE : COLLINEAR;
}

/**
 * @return Square of Euclidean distance between 2 points
 */
inline int sqrDist(Point a, Point b)
{
	const int dx = a.getX() - b.getX(), dy = a.getY() - b.getY();
	return dx * dx + dy * dy;
}

/**
 * @brief Used as a comparator for sorting points according to polar order w.r.t the pivot
 */
inline bool polarOrder(Point a, Point b)
{
	const int order = ccw(pivot, a, b);

	if (order == COLLINEAR)
	{
		return sqrDist(pivot, a) < sqrDist(pivot, b);
	}

	return (order == C_CLOCKWISE);
}

/**
 * @brief Receives input from the user and adds the given points to the set
 * It's done recursively such that the set is initialized with an adequate capacity immediately
 * after the user is done and before the set gets filled with points
 * Also keeps track of the index of the pivot Point
 */
void initSetByInput()
{
	static int capacity = 0;
	Point p;

	if (std::cin >> p)
	{
		++capacity;
		initSetByInput();

		if (set->add(p) && p < (*set)[pivotIndex])
		{
			pivotIndex = set->size() - 1;
		}
	}
	else
	{
		set = new PointSet(capacity);
	}
}

/**
 * @brief Performs the graham scan algorithm
 * @return String of the convex hull's sorted points
 */
std::string grahamScan(const int origSetSize)
{
	// The pivot point must be first in the set
	std::swap((*set)[0], (*set)[pivotIndex]);
	pivot = (*set)[0];
	// Sorts in polar order w.r.t the pivot
	set->sort(1, origSetSize, polarOrder);

	PointSet hull(set->size(), false);
	// Adds first 2 points
	hull.add(pivot);
	hull.add((*set)[1]);

	for (int i = MIN_SCAN_SIZE; i < origSetSize; ++i)
	{
		Point p = (*set)[i];

		while (ccw(hull[-2], hull[-1], p) != C_CLOCKWISE)
		{
			hull.removeLast();
		}

		hull.add(p);
	}

	hull.sort(0, hull.size());
	std::stringstream ss;
	ss << RESULT_TITLE << hull.toString();

	return ss.str();
}

/**
 * @brief Responsible for starting the program (first user input and then graham scan)
 * Prints out the result
 * @return 0 when the program is finished
 */
int main()
{
	initSetByInput();
	set->shrinkToFit();
	const int size = set->size();

	if (size <= MIN_SCAN_SIZE)
	{
		set->sort(0, size);
		std::cout << RESULT_TITLE << set->toString();
		return EXIT_SUCCESS;
	}

	std::cout << grahamScan(size);
	delete set;

	return EXIT_SUCCESS;
}