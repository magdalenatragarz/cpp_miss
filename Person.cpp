#include "Person.h"
#include "Position.h"

Person::Person(std::shared_ptr<Position> _currentPosition) :
	currentPosition(_currentPosition),
	howManyMovesPredicted(0),
	isUpdated(true),
	kalmanFilter()
{
	history.push_back(currentPosition);
	
}

void Person::update(std::shared_ptr<Position> position)
{
	currentPosition = position;
	history.push_back(position);
}

bool Person::isMoveSuitable(std::shared_ptr<Position> position)
{
	return false;
}

void Person::markUpdated()
{
	isUpdated = true;
}

void Person::markNotUpdated()
{
	isUpdated = false;
}

bool Person::isMoveInCloseNeighborhood(std::shared_ptr<Position> position)
{
	return false;
}

bool Person::isMoveDeflected(std::shared_ptr<Position> position)
{
	return false;
}

bool Person::isPersonCredible()
{
	return false;
}

bool Person::isTimeDifferenceSmall(std::shared_ptr<Position>)
{
	return false;
}
