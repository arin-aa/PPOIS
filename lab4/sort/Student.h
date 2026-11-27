/**
 * @file Student.h
 * @brief Declaration of the Student class used to demonstrate sorting of custom
 * objects.
 */
#pragma once
#include <iostream>
#include <string>
#include <utility>

/**
 * @class Student
 * @brief A student with a name, an age and an average grade.
 *
 * The default ordering (operator<) compares students by average grade.
 */
class Student {
private:
  std::string name;   ///< Student name.
  int age = 0;        ///< Student age in years.
  double grade = 0.0; ///< Average grade.

public:
  /** @brief Default constructor. */
  Student() = default;

  /**
   * @brief Constructs a student.
   * @param name Student name.
   * @param age Student age.
   * @param grade Average grade.
   */
  Student(std::string name, int age, double grade)
      : name(std::move(name)), age(age), grade(grade) {}

  /** @brief Returns the student name. */
  const std::string &getName() const { return name; }

  /** @brief Returns the student age. */
  int getAge() const { return age; }

  /** @brief Returns the average grade. */
  double getGrade() const { return grade; }

  /**
   * @brief Default ordering: by average grade.
   * @param other Student to compare with.
   * @return true if this student's grade is lower than the other's.
   */
  bool operator<(const Student &other) const { return grade < other.grade; }

  /**
   * @brief Writes a student to a stream as name(age, grade).
   * @param os Output stream.
   * @param s Student to print.
   * @return Reference to os.
   */
  friend std::ostream &operator<<(std::ostream &os, const Student &s) {
    return os << s.name << "(" << s.age << ", " << s.grade << ")";
  }
};