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
TEST(PointTest, Constructors) {
    Point<int> p1; // По умолчанию (0,0)
    EXPECT_EQ(p1.getX(), 0);
    EXPECT_EQ(p1.getY(), 0);
    Point<double> p2(3.5, 4.2); // С параметрами
    EXPECT_DOUBLE_EQ(p2.getX(), 3.5);
    EXPECT_DOUBLE_EQ(p2.getY(), 4.2);
}
TEST(PointTest, Operators) {
    Point<int> p1(10, 20);
    Point<int> p2 = p1; // Копирование
    EXPECT_EQ(p2.getX(), 10);
    EXPECT_EQ(p2.getY(), 20);
    Point<double> p3(1.0, 2.0);
    Point<double> p4(1.0, 2.0);
    EXPECT_TRUE(p3 == p4); // Равенство
}
// Тесты для Triangle
TEST(TriangleTest, AreaAndCenter) {
    Triangle<double> t(3.0);
    double expected = (std::sqrt(3.0) * 9.0) / 4.0; // Формула площади
    EXPECT_NEAR(t.getArea(), expected, 1e-10);
    auto center = t.getCenter();
    EXPECT_NEAR(center.getX(), 0, 1e-10);
    EXPECT_NEAR(center.getY(), 0, 1e-10);
    EXPECT_EQ(t.getVertices().size(), 3); // 3 вершины
}
// Тесты для Square
TEST(SquareTest, AreaAndCenter) {
    Square<double> s(4.0);
    EXPECT_DOUBLE_EQ(s.getArea(), 16.0); // side^2
    auto center = s.getCenter();
    EXPECT_NEAR(center.getX(), 0, 1e-10);
    EXPECT_NEAR(center.getY(), 0, 1e-10);
    
    EXPECT_EQ(s.getVertices().size(), 4); // 4 вершины
}
// Тесты для Octagon
TEST(OctagonTest, AreaAndCenter) {
    Octagon<double> o(2.0);
    double expected = 2.0 * (1.0 + std::sqrt(2.0)) * 4.0; // Формула для восьмиугольника
    EXPECT_NEAR(o.getArea(), expected, 1e-10);
    auto center = o.getCenter();
    EXPECT_NEAR(center.getX(), 0, 1e-10);
    EXPECT_NEAR(center.getY(), 0, 1e-10);
    EXPECT_EQ(o.getVertices().size(), 8); // 8 вершин
}
// Тесты для Array
TEST(ArrayTest, BasicOperations) {
    Array<int> arr;
    EXPECT_TRUE(arr.empty()); // Пустой по умолчанию
    arr.push_back(1);
    arr.push_back(2);
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    arr.remove(0); // Удаляем первый
    EXPECT_EQ(arr.size(), 1);
    EXPECT_EQ(arr[0], 2);
}
TEST(ArrayTest, CopyAndMove) {
    Array<int> arr1;
    arr1.push_back(10);
    arr1.push_back(20);
    Array<int> arr2(arr1); // Копирование
    EXPECT_EQ(arr2.size(), 2);
    EXPECT_EQ(arr2[0], 10);
    Array<int> arr3(std::move(arr1)); // Перемещение
    EXPECT_EQ(arr3.size(), 2);
    EXPECT_EQ(arr1.size(), 0); // Исходный пуст
}
// Полиморфизм - разные фигуры в массиве
TEST(PolymorphismTest, FiguresInArray) {
    Array<std::shared_ptr<Figure<double>>> figures;
    figures.push_back(std::make_shared<Triangle<double>>(3.0));
    figures.push_back(std::make_shared<Square<double>>(4.0));
    figures.push_back(std::make_shared<Octagon<double>>(2.0));
    EXPECT_EQ(figures.size(), 3);
    
    double total_area = 0.0;
    for (size_t i = 0; i < figures.size(); ++i) {
        total_area += figures[i]->getArea(); // Суммируем площади
        auto center = figures[i]->getCenter();
        EXPECT_NEAR(center.getX(), 0.0, 1e-10); // Центры в (0,0)
        EXPECT_NEAR(center.getY(), 0.0, 1e-10);
    }
    EXPECT_GT(total_area, 0.0); // Общая площадь > 0
}
// Интеграционный тест - полный рабочий процесс
TEST(IntegrationTest, Workflow) {
    Array<std::shared_ptr<Figure<int>>> figures;
    figures.push_back(std::make_shared<Triangle<int>>(6));
    figures.push_back(std::make_shared<Square<int>>(4));
    figures.push_back(std::make_shared<Octagon<int>>(3));
    double total_before = 0.0;
    for (size_t i = 0; i < figures.size(); ++i) {
        total_before += figures[i]->getArea();
    }
    figures.remove(1); // Удаляем квадрат
    EXPECT_EQ(figures.size(), 2);
    double total_after = 0.0;
    for (size_t i = 0; i < figures.size(); ++i) {
        total_after += figures[i]->getArea();
    }
    EXPECT_LT(total_after, total_before); // Площадь уменьшилась
}
