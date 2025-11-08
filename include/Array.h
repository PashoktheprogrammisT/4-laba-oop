#ifndef ARRAY_H
#define ARRAY_H

#include <memory>
#include <stdexcept>
#include <utility>
template<typename T>
class Array {
private:
    std::shared_ptr<T[]> data;  // Указатель на данные, shared_ptr для безопасности
    size_t capacity;  // Емкость массива, растет по мере нужды
    size_t size_;  // Текущий размер, не путать с capacity!

public:
    // Конструктор по умолчанию, пустой массив
    Array() : data(nullptr), capacity(0), size_(0) {
        // Ничего особого, просто инициализация
    }
    
    // Конструктор с начальной емкостью, если знаю заранее
    explicit Array(size_t initial_capacity) 
        : data(std::make_shared<T[]>(initial_capacity)), capacity(initial_capacity), size_(0) {
        // Выделяем память сразу, чтобы не ресайзить часто
    }
    
    // Копирующий конструктор, копируем все элементы
    Array(const Array& other) 
        : data(std::make_shared<T[]>(other.capacity)), capacity(other.capacity), size_(other.size_) {
        // Цикл для копирования, старый добрый способ
        for (size_t i = 0; i < size_; ++i) {
            data[i] = other.data[i];  // Копируем по одному
        }
    }
    
    // Перемещающий конструктор, забираем все у другого
    Array(Array&& other) noexcept 
        : data(std::move(other.data)), capacity(other.capacity), size_(other.size_) {
        // Обнуляем у другого, чтобы не было проблем
        other.capacity = 0;
        other.size_ = 0;
    }
    
    // Оператор присваивания, копируем
    Array& operator=(const Array& other) {
        if (this != &other) {  // Проверяем, не сам ли себе присваиваем
            auto new_data = std::make_shared<T[]>(other.capacity);  // Новый массив
            for (size_t i = 0; i < other.size_; ++i) {
                new_data[i] = other.data[i];  // Копируем элементы
            }
            data = std::move(new_data);  // Перемещаем указатель
            capacity = other.capacity;
            size_ = other.size_;
        }
        return *this;  // Возвращаем себя
    }
    
    // Перемещающий оператор присваивания
    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            data = std::move(other.data);  // Забираем данные
            capacity = other.capacity;
            size_ = other.size_;
            other.capacity = 0;  // Обнуляем у другого
            other.size_ = 0;
        }
        return *this;
    }
    
    // Добавление элемента по копии
    void push_back(const T& value) {
        if (size_ >= capacity) {  // Если места нет, ресайзим
            size_t new_cap = (capacity == 0) ? 1 : capacity * 2;  // Удваиваем или начинаем с 1
            resize(new_cap);
        }
        data[size_++] = value;  // Добавляем и увеличиваем размер
    }
    
    // Добавление по перемещению
    void push_back(T&& value) {
        if (size_ >= capacity) {
            size_t new_cap = (capacity == 0) ? 1 : capacity * 2;
            resize(new_cap);
        }
        data[size_++] = std::move(value);  // Перемещаем значение
    }
    
    // Удаление элемента по индексу
    void remove(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");  // Ошибка, если индекс неверный
        }
        
        // Сдвигаем элементы влево
        for (size_t i = index; i < size_ - 1; ++i) {
            data[i] = std::move(data[i + 1]);  // Перемещаем следующий
        }
        --size_;  // Уменьшаем размер
    }
    
    // Доступ к элементам, неконстантный
    T& operator[](size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];  // Возвращаем ссылку
    }
    
    // Доступ к элементам, константный
    const T& operator[](size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }
    
    // Геттеры для размера и емкости
    size_t size() const { return size_; }
    size_t getCapacity() const { return capacity; }
    bool empty() const { return size_ == 0; }
    
    // Очистка массива
    void clear() {
        data.reset();  // Освобождаем память
        capacity = 0;
        size_ = 0;
    }

private:
    // Приватный метод для изменения размера
    void resize(size_t new_capacity) {
        auto new_data = std::make_shared<T[]>(new_capacity);  // Новый массив
        
        // Перемещаем старые элементы
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = std::move(data[i]);  // Перемещаем по одному
        }
        
        data = std::move(new_data);  // Заменяем указатель
        capacity = new_capacity;  // Обновляем емкость
    }
};

#endif
