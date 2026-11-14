/**
 * @file Fan.h
 * @brief Declaration of the Fan class.
 */
#pragma once
#include "Component.h"

/**
 * @class Fan
 * @brief Fan class.
 */
class Fan:public Component{
private:
    int rpm;///<Rotation speed.
    int sizeMm;///<Fan size in mm.

public:
/**
 * @brief Default constructor.
 */
    Fan();

/**
 * @brief Constructor with parameters.
 * @param sizeMm Size.
 * @param rpm Initial speed.
 */
    Fan(int sizeMm,int rpm);

/**
 * @brief Changes the rotation speed.
 * @param delta Increase/decrease in RPM.
 * @return Resulting speed.
 */
    int accelerate(int delta);

/**
 * @brief Calculates the airflow.
 * @return Airflow.
 */
    int airflow();
};