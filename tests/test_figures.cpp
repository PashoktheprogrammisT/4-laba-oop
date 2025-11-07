#include <gtest/gtest.h>
#include <memory>
#include <cmath>
#include "Point.h"
#include "Figure.h"
#include "Triangle.h"
#include "Square.h"
#include "Octagon.h"
#include "Array.h"

// Тесты для Point
TEST(PointTest, DefaultConstructor) {
    Point<int> p;
    EXPECT_EQ(p.getX(), 0);
    EXPECT_EQ(p.getY(), 0);
}

TEST(PointTest, ParameterizedConstructor) {
    Point<double> p(3.5, 4.2);
    EXPECT_DOUBLE_EQ(p.getX(), 3.5);
    EXPECT_DOUBLE_EQ(p.getY(), 4.2);
}

TEST(PointTest, CopyConstructor) {
    Point<float> p1(1.1f, 2.2f);
    Point<float> p2(p1);
    EXPECT_FLOAT_EQ(p2.getX(), 1.1f);
    EXPECT_FLOAT_EQ(p2.getY(), 2.2f);
}

TEST(PointTest, AssignmentOperator) {
    Point<int> p1(10, 20);
    Point<int> p2;
    p2 = p1;
    EXPECT_EQ(p2.getX(), 10);
    EXPECT_EQ(p2.getY(), 20);
}

TEST(PointTest, EqualityOperator) {
    Point<double> p1(1.0, 2.0);
    Point<double> p2(1.0, 2.0);
    Point<double> p3(3.0, 4.0);
    
    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
}

TEST(PointTest, OutputOperator) {
    Point<int> p(5, 10);
    testing::internal::CaptureStdout();
    std::cout << p;
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "(5, 10)");
}

// Тесты для Triangle
TEST(TriangleTest, ConstructorAndArea) {
    Triangle<double> triangle(3.0);
    double expected_area = (std::sqrt(3.0) * 3.0 * 3.0) / 4.0;
    EXPECT_NEAR(triangle.getArea(), expected_area, 1e-10);
}

TEST(TriangleTest, Center) {
    Triangle<int> triangle(6);
    auto center = triangle.getCenter();
    EXPECT_NEAR(center.getX(), 0, 1e-10);
    EXPECT_NEAR(center.getY(), 0, 1e-10);
}

TEST(TriangleTest, VerticesCount) {
    Triangle<float> triangle(4.0f);
    EXPECT_EQ(triangle.getVertices().size(), 3);
}

TEST(TriangleTest, CopyConstructor) {
    Triangle<double> t1(5.0);
    Triangle<double> t2(t1);
    EXPECT_TRUE(t1 == t2);
}

TEST(TriangleTest, AssignmentOperator) {
    Triangle<int> t1(4);
    Triangle<int> t2(6);
    t2 = t1;
    EXPECT_TRUE(t1 == t2);
}

TEST(TriangleTest, DoubleConversion) {
    Triangle<double> triangle(2.0);
    double area = static_cast<double>(triangle);
    double expected_area = (std::sqrt(3.0) * 2.0 * 2.0) / 4.0;
    EXPECT_NEAR(area, expected_area, 1e-10);
}

// Тесты для Square
TEST(SquareTest, ConstructorAndArea) {
    Square<double> square(4.0);
    EXPECT_DOUBLE_EQ(square.getArea(), 16.0);
}

TEST(SquareTest, Center) {
    Square<int> square(5);
    auto center = square.getCenter();
    EXPECT_NEAR(center.getX(), 0, 1e-10);
    EXPECT_NEAR(center.getY(), 0, 1e-10);
}

TEST(SquareTest, VerticesCount) {
    Square<float> square(3.0f);
    EXPECT_EQ(square.getVertices().size(), 4);
}

TEST(SquareTest, CopyAndAssignment) {
    Square<double> s1(3.0);
    Square<double> s2(s1);
    Square<double> s3(5.0);
    s3 = s1;
    
    EXPECT_TRUE(s1 == s2);
    EXPECT_TRUE(s1 == s3);
}

// Тесты для Octagon
TEST(OctagonTest, ConstructorAndArea) {
    Octagon<double> octagon(2.0);
    double expected_area = 2.0 * (1.0 + std::sqrt(2.0)) * 4.0;
    EXPECT_NEAR(octagon.getArea(), expected_area, 1e-10);
}

TEST(OctagonTest, Center) {
    Octagon<int> octagon(3);
    auto center = octagon.getCenter();
    EXPECT_NEAR(center.getX(), 0, 1e-10);
    EXPECT_NEAR(center.getY(), 0, 1e-10);
}

TEST(OctagonTest, VerticesCount) {
    Octagon<float> octagon(2.0f);
    EXPECT_EQ(octagon.getVertices().size(), 8);
}

// Тесты для Array
TEST(ArrayTest, DefaultConstructor) {
    Array<int> arr;
    EXPECT_EQ(arr.size(), 0);
    EXPECT_TRUE(arr.empty());
}

TEST(ArrayTest, PushBackAndAccess) {
    Array<std::string> arr;
    arr.push_back("hello");
    arr.push_back("world");
    
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0], "hello");
    EXPECT_EQ(arr[1], "world");
}

TEST(ArrayTest, CopyConstructor) {
    Array<int> arr1;
    arr1.push_back(1);
    arr1.push_back(2);
    arr1.push_back(3);
    
    Array<int> arr2(arr1);
    EXPECT_EQ(arr2.size(), 3);
    EXPECT_EQ(arr2[0], 1);
    EXPECT_EQ(arr2[1], 2);
    EXPECT_EQ(arr2[2], 3);
}

TEST(ArrayTest, MoveConstructor) {
    Array<int> arr1;
    arr1.push_back(10);
    arr1.push_back(20);
    
    Array<int> arr2(std::move(arr1));
    EXPECT_EQ(arr2.size(), 2);
    EXPECT_EQ(arr2[0], 10);
    EXPECT_EQ(arr2[1], 20);
    EXPECT_EQ(arr1.size(), 0); // Проверяем, что исходный массив очищен
}

TEST(ArrayTest, AssignmentOperator) {
    Array<double> arr1;
    arr1.push_back(1.5);
    arr1.push_back(2.5);
    
    Array<double> arr2;
    arr2 = arr1;
    
    EXPECT_EQ(arr2.size(), 2);
    EXPECT_DOUBLE_EQ(arr2[0], 1.5);
    EXPECT_DOUBLE_EQ(arr2[1], 2.5);
}

TEST(ArrayTest, MoveAssignmentOperator) {
    Array<std::string> arr1;
    arr1.push_back("test");
    
    Array<std::string> arr2;
    arr2 = std::move(arr1);
    
    EXPECT_EQ(arr2.size(), 1);
    EXPECT_EQ(arr2[0], "test");
    EXPECT_EQ(arr1.size(), 0);
}

TEST(ArrayTest, RemoveElement) {
    Array<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    
    arr.remove(1); // Удаляем элемент с индексом 1 (значение 2)
    
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 3);
}

TEST(ArrayTest, OutOfRangeAccess) {
    Array<int> arr;
    arr.push_back(1);
    
    EXPECT_THROW(arr[1], std::out_of_range);
    EXPECT_THROW(arr.remove(2), std::out_of_range);
}

TEST(ArrayTest, ResizeWithMove) {
    Array<int> arr;
    // Добавляем элементы, чтобы вызвать ресайз
    for (int i = 0; i < 10; ++i) {
        arr.push_back(i);
    }
    
    EXPECT_EQ(arr.size(), 10);
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(arr[i], i);
    }
}

// Тесты для полиморфизма с фигурами
TEST(PolymorphismTest, FigurePointers) {
    Array<std::shared_ptr<Figure<double>>> figures;
    
    figures.push_back(std::make_shared<Triangle<double>>(3.0));
    figures.push_back(std::make_shared<Square<double>>(4.0));
    figures.push_back(std::make_shared<Octagon<double>>(2.0));
    
    EXPECT_EQ(figures.size(), 3);
    
    // Проверяем, что виртуальные методы работают корректно
    double total_area = 0.0;
    for (size_t i = 0; i < figures.size(); ++i) {
        total_area += figures[i]->getArea();
        auto center = figures[i]->getCenter();
        EXPECT_NEAR(center.getX(), 0.0, 1e-10);
        EXPECT_NEAR(center.getY(), 0.0, 1e-10);
    }
    
    EXPECT_GT(total_area, 0.0);
}

TEST(PolymorphismTest, DifferentTemplateTypes) {
    // Тестируем с разными скалярными типами
    Triangle<int> tri_int(5);
    Triangle<double> tri_double(5.0);
    Triangle<float> tri_float(5.0f);
    
    Square<int> sq_int(4);
    Square<double> sq_double(4.0);
    
    EXPECT_GT(tri_int.getArea(), 0);
    EXPECT_GT(tri_double.getArea(), 0);
    EXPECT_GT(tri_float.getArea(), 0);
    EXPECT_GT(sq_int.getArea(), 0);
    EXPECT_GT(sq_double.getArea(), 0);
}

// Тесты для концептов
TEST(ConceptTest, ScalarTypes) {
    // Эти типы должны компилироваться
    Point<int> p1;
    Point<double> p2;
    Point<float> p3;
    
    Triangle<int> t1(1);
    Triangle<double> t2(1.0);
    
    Square<float> s1(1.0f);
    Square<double> s2(1.0);
    
    SUCCEED(); // Если компилируется, тест проходит
}

// Интеграционные тесты
TEST(IntegrationTest, CompleteWorkflow) {
    Array<std::shared_ptr<Figure<int>>> figures;
    
    // Добавляем фигуры
    figures.push_back(std::make_shared<Triangle<int>>(6));
    figures.push_back(std::make_shared<Square<int>>(4));
    figures.push_back(std::make_shared<Octagon<int>>(3));
    
    // Проверяем добавление
    EXPECT_EQ(figures.size(), 3);
    
    // Проверяем площади
    double total_before = 0.0;
    for (size_t i = 0; i < figures.size(); ++i) {
        total_before += figures[i]->getArea();
    }
    
    // Удаляем одну фигуру
    figures.remove(1);
    EXPECT_EQ(figures.size(), 2);
    
    // Проверяем общую площадь после удаления
    double total_after = 0.0;
    for (size_t i = 0; i < figures.size(); ++i) {
        total_after += figures[i]->getArea();
    }
    
    EXPECT_LT(total_after, total_before);
}

TEST(IntegrationTest, TemplateSpecializations) {
    // Демонстрация работы с разными специализациями шаблонов
    Array<Figure<int>*> fig_ptr_array;
    Array<Triangle<double>> tri_array;
    Array<Square<float>> sq_array;
    
    // Добавляем элементы
    tri_array.push_back(Triangle<double>(3.0));
    sq_array.push_back(Square<float>(2.0f));
    
    EXPECT_EQ(tri_array.size(), 1);
    EXPECT_EQ(sq_array.size(), 1);
    EXPECT_GT(tri_array[0].getArea(), 0);
    EXPECT_GT(sq_array[0].getArea(), 0);
}
