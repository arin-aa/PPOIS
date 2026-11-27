#include <catch2/catch_test_macros.hpp>
#include "SmoothSorter.h"
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
    SmoothSorter<int> s;
    s.sort(v);
    return v==expected;
}

struct CountingLess{
    int* count;
    bool operator()(int a, int b) const{ ++*count; return a<b; }
};

}

TEST_CASE("SmoothSorter: trivial sizes") {
    SmoothSorter<int> s;

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

TEST_CASE("SmoothSorter: typical inputs") {
    SmoothSorter<int> s;

    SECTION("Example from the demo") {
        std::vector<int> v{5,2,9,1,5,6,0,-3};
        s.sort(v);
        REQUIRE(v==std::vector<int>{-3,0,1,2,5,5,6,9});
    }

    SECTION("Already sorted") {
        std::vector<int> v;
        for(int i=0;i<50;++i) v.push_back(i);
        auto expected=v;
        s.sort(v);
        REQUIRE(v==expected);
    }

    SECTION("Reverse order") {
        std::vector<int> v;
        for(int i=50;i>0;--i) v.push_back(i);
        s.sort(v);
        REQUIRE(std::is_sorted(v.begin(), v.end()));
        REQUIRE(v.front()==1);
        REQUIRE(v.back()==50);
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

TEST_CASE("SmoothSorter: all small sizes against std::sort") {
    for(std::size_t n=0;n<=130;++n){
        for(unsigned seed=0;seed<3;++seed){
            INFO("n=" << n << ", seed=" << seed);
            REQUIRE(matchesStdSort(randomVector(n, seed*1000+static_cast<unsigned>(n))));
        }
    }
}

TEST_CASE("SmoothSorter: sizes around Leonardo numbers") {
    const std::vector<std::size_t> leonardo{1,3,5,9,15,25,41,67,109,177,287,465};
    for(std::size_t L: leonardo){
        for(std::size_t n=L-1;n<=L+1;++n){
            INFO("n=" << n);
            REQUIRE(matchesStdSort(randomVector(n, static_cast<unsigned>(n))));
        }
    }
}

TEST_CASE("SmoothSorter: large inputs") {
    SECTION("Random") {
        REQUIRE(matchesStdSort(randomVector(5000, 42, -100000, 100000)));
    }

    SECTION("Almost sorted") {
        std::vector<int> v;
        for(int i=0;i<2000;++i) v.push_back(i);
        std::swap(v[10], v[1500]);
        std::swap(v[700], v[701]);
        REQUIRE(matchesStdSort(v));
    }

    SECTION("Organ pipe") {
        std::vector<int> v;
        for(int i=0;i<500;++i) v.push_back(i);
        for(int i=500;i>0;--i) v.push_back(i);
        REQUIRE(matchesStdSort(v));
    }
}

TEST_CASE("SmoothSorter: plain arrays") {
    SmoothSorter<int> s;

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

    SECTION("Array of doubles") {
        double arr[]={3.5,1.2,9.9,4.4,0.1};
        SmoothSorter<double> sd;
        sd.sort(arr, 5);
        REQUIRE(std::is_sorted(arr, arr+5));
    }
}

TEST_CASE("SmoothSorter: custom comparators") {
    SECTION("std::greater sorts in descending order") {
        SmoothSorter<int, std::greater<int>> s;
        auto v=randomVector(100, 9);
        s.sort(v);
        REQUIRE(std::is_sorted(v.begin(), v.end(), std::greater<int>()));
    }

    SECTION("Comparator is actually used") {
        int count=0;
        SmoothSorter<int, CountingLess> s(CountingLess{&count});
        std::vector<int> v{4,3,2,1};
        s.sort(v);
        REQUIRE(count>0);
        REQUIRE(std::is_sorted(v.begin(), v.end()));
    }
}

TEST_CASE("SmoothSorter: Student objects") {
    std::vector<Student> students{
        {"Anna", 20, 4.5}, {"Boris", 19, 3.8}, {"Clara", 21, 4.9},
        {"Dmitry", 20, 3.2}, {"Elena", 22, 4.1}, {"Fedor", 19, 4.5}
    };

    SECTION("Default order: by grade") {
        SmoothSorter<Student> s;
        s.sort(students);
        REQUIRE(std::is_sorted(students.begin(), students.end()));
        REQUIRE(students.front().getName()=="Dmitry");
        REQUIRE(students.back().getName()=="Clara");
    }

    SECTION("By name, descending") {
        auto byNameDesc=[](const Student& a, const Student& b){
            return a.getName()>b.getName();
        };
        SmoothSorter<Student, decltype(byNameDesc)> s(byNameDesc);
        s.sort(students);
        REQUIRE(students.front().getName()=="Fedor");
        REQUIRE(students.back().getName()=="Anna");
    }

    SECTION("By age, array") {
        auto byAge=[](const Student& a, const Student& b){
            return a.getAge()<b.getAge();
        };
        Student raw[]={{"Anna",20,4.5},{"Boris",19,3.8},{"Clara",21,4.9},{"Dmitry",20,3.2}};
        SmoothSorter<Student, decltype(byAge)> s(byAge);
        s.sort(raw, 4);
        REQUIRE(raw[0].getAge()==19);
        REQUIRE(raw[3].getAge()==21);
        REQUIRE(raw[1].getAge()==20);
        REQUIRE(raw[2].getAge()==20);
    }
}

TEST_CASE("SmoothSorter: strings") {
    SmoothSorter<std::string> s;
    std::vector<std::string> v{"pear","apple","fig","banana","apple"};
    s.sort(v);
    REQUIRE(v==std::vector<std::string>{"apple","apple","banana","fig","pear"});
}