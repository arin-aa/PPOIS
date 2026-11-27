#include <catch2/catch_test_macros.hpp>
#include "PancakeSorter.h"
#include "Student.h"

#include <algorithm>
#include <functional>
#include <random>
#include <string>
#include <vector>

namespace{

std::vector<int> randomVector(std::size_t n, unsigned seed, int lo=-50, int hi=50){
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> dist(lo, hi);
    std::vector<int> v(n);
    for(auto& x: v) x=dist(gen);
    return v;
}

bool matchesStdSort(std::vector<int> v){
    auto expected=v;
    std::sort(expected.begin(), expected.end());
    PancakeSorter<int> s;
    s.sort(v);
    return v==expected;
}

struct CountingLess{
    int* count;
    bool operator()(int a, int b) const{ ++*count; return a<b; }
};

}

TEST_CASE("PancakeSorter: trivial sizes") {
    PancakeSorter<int> s;

    SECTION("Empty vector") {
        std::vector<int> v;
        s.sort(v);
        REQUIRE(v.empty());
    }

    SECTION("Single element") {
        std::vector<int> v{42};
        s.sort(v);
        REQUIRE(v==std::vector<int>{42});
    }

    SECTION("Two elements, wrong order") {
        std::vector<int> v{2,1};
        s.sort(v);
        REQUIRE(v==std::vector<int>{1,2});
    }

    SECTION("Two elements, right order") {
        std::vector<int> v{1,2};
        s.sort(v);
        REQUIRE(v==std::vector<int>{1,2});
    }
}

TEST_CASE("PancakeSorter: flip branches") {
    PancakeSorter<int> s;

    SECTION("Maximum already at the end of the prefix (no flips)") {
        std::vector<int> v{1,2,3,4,5};
        s.sort(v);
        REQUIRE(v==std::vector<int>{1,2,3,4,5});
    }

    SECTION("Maximum at the front (only the second flip)") {
        std::vector<int> v{5,4,3,2,1};
        s.sort(v);
        REQUIRE(v==std::vector<int>{1,2,3,4,5});
    }

    SECTION("Maximum in the middle (both flips)") {
        std::vector<int> v{2,5,1,4,3};
        s.sort(v);
        REQUIRE(v==std::vector<int>{1,2,3,4,5});
    }
}

TEST_CASE("PancakeSorter: typical inputs") {
    PancakeSorter<int> s;

    SECTION("Example from the demo") {
        std::vector<int> v{5,2,9,1,5,6,0,-3};
        s.sort(v);
        REQUIRE(v==std::vector<int>{-3,0,1,2,5,5,6,9});
    }

    SECTION("All elements equal") {
        std::vector<int> v(20, 7);
        s.sort(v);
        REQUIRE(v==std::vector<int>(20, 7));
    }

    SECTION("Many duplicates") {
        REQUIRE(matchesStdSort(randomVector(200, 1, 0, 3)));
    }

    SECTION("Negative numbers") {
        std::vector<int> v{-1,-5,-3,-2,-4};
        s.sort(v);
        REQUIRE(v==std::vector<int>{-5,-4,-3,-2,-1});
    }

    SECTION("Sorting twice gives the same result") {
        std::vector<int> v=randomVector(60, 5);
        s.sort(v);
        auto once=v;
        s.sort(v);
        REQUIRE(v==once);
    }
}

TEST_CASE("PancakeSorter: all small sizes against std::sort") {
    for(std::size_t n=0;n<=60;++n){
        for(unsigned seed=0;seed<3;++seed){
            INFO("n=" << n << ", seed=" << seed);
            REQUIRE(matchesStdSort(randomVector(n, seed*1000+static_cast<unsigned>(n))));
        }
    }
}

TEST_CASE("PancakeSorter: larger inputs") {
    SECTION("Random") {
        REQUIRE(matchesStdSort(randomVector(300, 42, -1000, 1000)));
    }

    SECTION("Reverse order") {
        std::vector<int> v;
        for(int i=300;i>0;--i) v.push_back(i);
        REQUIRE(matchesStdSort(v));
    }

    SECTION("Organ pipe") {
        std::vector<int> v;
        for(int i=0;i<150;++i) v.push_back(i);
        for(int i=150;i>0;--i) v.push_back(i);
        REQUIRE(matchesStdSort(v));
    }
}

TEST_CASE("PancakeSorter: plain arrays") {
    PancakeSorter<int> s;

    SECTION("Array of ints") {
        int arr[]={9,8,7,1,2,3,0};
        s.sort(arr, 7);
        REQUIRE(std::is_sorted(arr, arr+7));
        REQUIRE(arr[0]==0);
        REQUIRE(arr[6]==9);
    }

    SECTION("Null pointer and tiny sizes are ignored") {
        int* p=nullptr;
        s.sort(p, 10);
        int arr[]={2,1};
        s.sort(arr, 1);
        REQUIRE(arr[0]==2);
        REQUIRE(arr[1]==1);
    }

    SECTION("Descending array of doubles") {
        double arr[]={3.5,1.2,9.9,4.4,0.1};
        PancakeSorter<double, std::greater<double>> sd;
        sd.sort(arr, 5);
        REQUIRE(std::is_sorted(arr, arr+5, std::greater<double>()));
        REQUIRE(arr[0]==9.9);
    }
}

TEST_CASE("PancakeSorter: custom comparators") {
    SECTION("std::greater sorts in descending order") {
        PancakeSorter<int, std::greater<int>> s;
        auto v=randomVector(100, 9);
        s.sort(v);
        REQUIRE(std::is_sorted(v.begin(), v.end(), std::greater<int>()));
    }

    SECTION("Comparator is actually used") {
        int count=0;
        PancakeSorter<int, CountingLess> s(CountingLess{&count});
        std::vector<int> v{4,3,2,1};
        s.sort(v);
        REQUIRE(count>0);
        REQUIRE(std::is_sorted(v.begin(), v.end()));
    }
}

TEST_CASE("PancakeSorter: Student objects") {
    std::vector<Student> students{
        {"Anna", 20, 4.5}, {"Boris", 19, 3.8}, {"Clara", 21, 4.9},
        {"Dmitry", 20, 3.2}, {"Elena", 22, 4.1}, {"Fedor", 19, 4.5}
    };

    SECTION("Default order: by grade") {
        PancakeSorter<Student> s;
        s.sort(students);
        REQUIRE(std::is_sorted(students.begin(), students.end()));
        REQUIRE(students.front().getName()=="Dmitry");
        REQUIRE(students.back().getName()=="Clara");
    }

    SECTION("By name, descending") {
        auto byNameDesc=[](const Student& a, const Student& b){
            return a.getName()>b.getName();
        };
        PancakeSorter<Student, decltype(byNameDesc)> s(byNameDesc);
        s.sort(students);
        REQUIRE(students.front().getName()=="Fedor");
        REQUIRE(students.back().getName()=="Anna");
    }

    SECTION("By age, array") {
        auto byAge=[](const Student& a, const Student& b){
            return a.getAge()<b.getAge();
        };
        Student raw[]={{"Anna",20,4.5},{"Boris",19,3.8},{"Clara",21,4.9},{"Dmitry",20,3.2}};
        PancakeSorter<Student, decltype(byAge)> s(byAge);
        s.sort(raw, 4);
        REQUIRE(raw[0].getAge()==19);
        REQUIRE(raw[3].getAge()==21);
        REQUIRE(raw[1].getAge()==20);
        REQUIRE(raw[2].getAge()==20);
    }
}

TEST_CASE("PancakeSorter: strings") {
    PancakeSorter<std::string> s;
    std::vector<std::string> v{"pear","apple","fig","banana","apple"};
    s.sort(v);
    REQUIRE(v==std::vector<std::string>{"apple","apple","banana","fig","pear"});
}