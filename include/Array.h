#ifndef ARRAY_H
#define ARRAY_H

#include <memory>
#include <stdexcept>
#include <utility>

template<typename T>
class Array {
private:
    std::shared_ptr<T[]> data;
    size_t capacity;
    size_t size_;

public:
    Array() : data(nullptr), capacity(0), size_(0) {}
    
    // Конструктор с начальной емкостью
    explicit Array(size_t initial_capacity) 
        : data(std::make_shared<T[]>(initial_capacity)), capacity(initial_capacity), size_(0) {}
    
    // Копирующий конструктор
    Array(const Array& other) 
        : data(std::make_shared<T[]>(other.capacity)), capacity(other.capacity), size_(other.size_) {
        for (size_t i = 0; i < size_; ++i) {
            data[i] = other.data[i];
        }
    }
    
    // Перемещающий конструктор
    Array(Array&& other) noexcept 
        : data(std::move(other.data)), capacity(other.capacity), size_(other.size_) {
        other.capacity = 0;
        other.size_ = 0;
    }
    
    // Оператор присваивания
    Array& operator=(const Array& other) {
        if (this != &other) {
            auto new_data = std::make_shared<T[]>(other.capacity);
            for (size_t i = 0; i < other.size_; ++i) {
                new_data[i] = other.data[i];
            }
            data = std::move(new_data);
            capacity = other.capacity;
            size_ = other.size_;
        }
        return *this;
    }
    
    // Перемещающий оператор присваивания
    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            data = std::move(other.data);
            capacity = other.capacity;
            size_ = other.size_;
            other.capacity = 0;
            other.size_ = 0;
        }
        return *this;
    }
    
    // Добавление элемента
    void push_back(const T& value) {
        if (size_ >= capacity) {
            resize(capacity == 0 ? 1 : capacity * 2);
        }
        data[size_++] = value;
    }
    
    void push_back(T&& value) {
        if (size_ >= capacity) {
            resize(capacity == 0 ? 1 : capacity * 2);
        }
        data[size_++] = std::move(value);
    }
    
    // Удаление элемента по индексу
    void remove(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        
        for (size_t i = index; i < size_ - 1; ++i) {
            data[i] = std::move(data[i + 1]);
        }
        --size_;
    }
    
    // Доступ к элементам
    T& operator[](size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }
    
    const T& operator[](size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }
    
    // Размер и емкость
    size_t size() const { return size_; }
    size_t getCapacity() const { return capacity; }
    bool empty() const { return size_ == 0; }
    
    // Очистка массива
    void clear() {
        data.reset();
        capacity = 0;
        size_ = 0;
    }

private:
    void resize(size_t new_capacity) {
        auto new_data = std::make_shared<T[]>(new_capacity);
        
        // Перемещаем элементы в новый массив
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = std::move(data[i]);
        }
        
        data = std::move(new_data);
        capacity = new_capacity;
    }
};

#endif
