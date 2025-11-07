#ifndef FIGURE_H
#define FIGURE_H

#include "Point.h"
#include <vector>
#include <memory>
#include <iostream>

template<Scalar T>
class Figure {
protected:
    std::vector<std::unique_ptr<Point<T>>> vertices;

public:
    Figure() = default;
    virtual ~Figure() = default;
    
    // Виртуальные методы
    virtual Point<T> getCenter() const = 0;
    virtual double getArea() const = 0;
    virtual void printVertices() const = 0;
    virtual void readFromStream(std::istream& is) = 0;
    
    // Операторы
    virtual bool operator==(const Figure& other) const {
        if (vertices.size() != other.vertices.size()) return false;
        for (size_t i = 0; i < vertices.size(); ++i) {
            if (*vertices[i] != *other.vertices[i]) return false;
        }
        return true;
    }
    
    virtual operator double() const {
        return getArea();
    }
    
    // Дружественные операторы ввода/вывода
    friend std::ostream& operator<<(std::ostream& os, const Figure& figure) {
        figure.printVertices();
        return os;
    }
    
    friend std::istream& operator>>(std::istream& is, Figure& figure) {
        figure.readFromStream(is);
        return is;
    }
    
    // Получение вершин
    const std::vector<std::unique_ptr<Point<T>>>& getVertices() const {
        return vertices;
    }
};

#endif
