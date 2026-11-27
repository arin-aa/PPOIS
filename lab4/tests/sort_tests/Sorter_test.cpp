#include <catch2/catch_test_macros.hpp>
#include "Sorter.h"

#include <algorithm>
#include <functional>
#include <memory>
#include <vector>

namespace{

template <typename Cmp=std::less<int>>
class RecordingSorter : public Sorter<int, Cmp>{
public:
    int calls=0;
    int* lastBegin=nullptr;
    int* lastEnd=nullptr;

    explicit RecordingSorter(Cmp c=Cmp()):Sorter<int, Cmp>(c){}

    bool less(int a, int b) const{ return this->comp(a,b); }

protected:
    void sortRange(int* begin, int* end) override{
        ++calls;
        lastBegin=begin;
        lastEnd=end;
        std::sort(begin, end, this->comp);
    }
};

class DtorSorter : public Sorter<int>{
public:
    explicit DtorSorter(bool* flag):flag(flag){}
    ~DtorSorter() override{ *flag=true; }

protected:
    void sortRange(int*, int*) override{}

private:
    bool* flag;
};

}

TEST_CASE("Sorter: sort(std::vector) delegates to sortRange") {
    RecordingSorter<> s;

    SECTION("Empty vector is not passed to sortRange") {
        std::vector<int> v;
        s.sort(v);
        REQUIRE(s.calls==0);
    }

    SECTION("Single element is not passed to sortRange") {
        std::vector<int> v{42};
        s.sort(v);
        REQUIRE(s.calls==0);
        REQUIRE(v==std::vector<int>{42});
    }

    SECTION("Two or more elements are passed with the correct range") {
        std::vector<int> v{3,1,2};
        s.sort(v);
        REQUIRE(s.calls==1);
        REQUIRE(s.lastBegin==v.data());
        REQUIRE(s.lastEnd==v.data()+3);
        REQUIRE(v==std::vector<int>{1,2,3});
    }
}

TEST_CASE("Sorter: sort(T*, size) delegates to sortRange") {
    RecordingSorter<> s;

    SECTION("Null pointer is ignored") {
        int* p=nullptr;
        s.sort(p, 5);
        REQUIRE(s.calls==0);
    }

    SECTION("Size zero is ignored") {
        int arr[]={2,1};
        s.sort(arr, 0);
        REQUIRE(s.calls==0);
        REQUIRE(arr[0]==2);
    }

    SECTION("Size one is ignored") {
        int arr[]={2,1};
        s.sort(arr, 1);
        REQUIRE(s.calls==0);
        REQUIRE(arr[0]==2);
    }

    SECTION("Two or more elements are passed with the correct range") {
        int arr[]={5,4,3,2,1};
        s.sort(arr, 5);
        REQUIRE(s.calls==1);
        REQUIRE(s.lastBegin==arr);
        REQUIRE(s.lastEnd==arr+5);
        REQUIRE(std::is_sorted(arr, arr+5));
    }

    SECTION("Only the first size elements are sorted") {
        int arr[]={3,2,1,0};
        s.sort(arr, 3);
        REQUIRE(arr[0]==1);
        REQUIRE(arr[1]==2);
        REQUIRE(arr[2]==3);
        REQUIRE(arr[3]==0);
    }
}

TEST_CASE("Sorter: comparator is stored and used") {
    SECTION("Default comparator is std::less") {
        RecordingSorter<> s;
        REQUIRE(s.less(1,2));
        REQUIRE_FALSE(s.less(2,1));
    }

    SECTION("Custom comparator reverses the order") {
        RecordingSorter<std::greater<int>> s;
        std::vector<int> v{1,3,2};
        s.sort(v);
        REQUIRE(v==std::vector<int>{3,2,1});
        REQUIRE(s.less(2,1));
    }

    SECTION("Lambda comparator") {
        auto byAbs=[](int a, int b){ return std::abs(a)<std::abs(b); };
        RecordingSorter<decltype(byAbs)> s(byAbs);
        std::vector<int> v{-5,2,-1,4};
        s.sort(v);
        REQUIRE(v==std::vector<int>{-1,2,4,-5});
    }
}

TEST_CASE("Sorter: virtual destructor") {
    bool destroyed=false;
    {
        std::unique_ptr<Sorter<int>> p=std::make_unique<DtorSorter>(&destroyed);
        REQUIRE_FALSE(destroyed);
    }
    REQUIRE(destroyed);
}