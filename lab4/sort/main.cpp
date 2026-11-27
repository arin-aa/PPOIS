/**
 * @file main.cpp
 * @brief Demonstration of SmoothSorter and PancakeSorter on built-in types and
 * on Student.
 */
#include "PancakeSorter.h"
#include "SmoothSorter.h"
#include "Student.h"
#include <iostream>
#include <string>
#include <vector>

/**
 * @brief Prints a title followed by the elements of a container.
 * @tparam Container Any container that can be iterated with a range-based for.
 * @param title Text printed before the elements.
 * @param c Container to print.
 */
template <typename Container>
void print(const std::string &title, const Container &cont) {
  std::cout << title << ": ";
  for (const auto &x : cont)
    std::cout << x << " ";
  std::cout << "\n";
}

/**
 * @brief Program entry point. Runs the sorting demonstrations.
 *
 * Covers: std::vector<int>, a double array in descending order, Student objects
 * with the default comparator and with custom comparators (by name, by age),
 * and edge cases (empty and single-element vectors).
 *
 * @return 0 on normal termination.
 */
int main() {
  std::vector<int> nums{5, 2, 9, 1, 5, 6, 0, -3};
  SmoothSorter<int> smoothInt;
  smoothInt.sort(nums);
  print("Smoothsort, vector<int>", nums);

  double arr[] = {3.5, 1.2, 9.9, 4.4, 0.1};
  PancakeSorter<double, std::greater<double>> pancakeDesc;
  pancakeDesc.sort(arr, 5);
  print("Pancake, double[] (descending)", std::vector<double>(arr, arr + 5));

  std::vector<Student> students{{"Anna", 20, 4.5},
                                {"Boris", 19, 3.8},
                                {"Clara", 21, 4.9},
                                {"Dmitry", 20, 3.2},
                                {"Elena", 22, 4.1}};

  auto s1 = students;
  SmoothSorter<Student> smoothStudent;
  smoothStudent.sort(s1);
  print("Smoothsort, by grade", s1);

  auto s2 = students;
  PancakeSorter<Student> pancakeStudent;
  pancakeStudent.sort(s2);
  print("Pancake, by grade", s2);

  auto byNameDesc = [](const Student &a, const Student &b) {
    return a.getName() > b.getName();
  };
  auto s3 = students;
  SmoothSorter<Student, decltype(byNameDesc)> smoothByName(byNameDesc);
  smoothByName.sort(s3);
  print("Smoothsort, by name (descending)", s3);

  auto byAge = [](const Student &a, const Student &b) {
    return a.getAge() < b.getAge();
  };
  Student raw[] = {{"Anna", 20, 4.5},
                   {"Boris", 19, 3.8},
                   {"Clara", 21, 4.9},
                   {"Dmitry", 20, 3.2}};
  PancakeSorter<Student, decltype(byAge)> pancakeByAge(byAge);
  pancakeByAge.sort(raw, 4);
  print("Pancake, Student[] by age", std::vector<Student>(raw, raw + 4));

  std::vector<int> empty, one{42};
  smoothInt.sort(empty);
  smoothInt.sort(one);
  print("Empty and single-element vectors", one);
  return 0;
}