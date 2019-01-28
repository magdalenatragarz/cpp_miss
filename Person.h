#pragma once

#include <vector>
#include <memory>

#include "KalmanFilter.h"
#include "Position.h"


class Person
{
public:

	Person(std::shared_ptr<Position> currentPosition);
	~Person() = default;

	int howManyMovesPredicted;
	bool isUpdated;

	std::vector<std::shared_ptr<Position>> history;
	std::shared_ptr<Position> currentPosition;	 
	std::unique_ptr<KalmanFilter> kalmanFilter; 

	void update(std::shared_ptr<Position> position);
	
	bool isMoveSuitable(std::shared_ptr<Position> position);

	void markUpdated();
	void markNotUpdated();
	
private:
	bool isMoveInCloseNeighborhood(std::shared_ptr<Position> position);
	bool isMoveDeflected(std::shared_ptr<Position> position);
	bool isPersonCredible();
	bool isTimeDifferenceSmall(std::shared_ptr<Position>);



	

};