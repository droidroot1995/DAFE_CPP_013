//
//  allocations.hpp
//  Vector_1.0
//
//  Created by Bogdan Bochkarev on 12/10/20.
//  Copyright © 2020 Bogdan Bochkarev. All rights reserved.
//

#ifndef allocations_hpp
#define allocations_hpp

#include <stdio.h>

template<typename T>
class allocator
{
public:
    // ...
    T* allocate (int n);                // Выделение памяти для n объектов типа Т
    void deallocate (T* p, int n);        // Освобождение памяти, занятой n объектами типа Т с адреса р

    void construct (T* p, const T& v);    // Создание объекта типа Т созна чением v по адресу р
    void destroy (T* p);                // Уничтожение объекта Т по адресу р
};




#endif /* allocations_hpp */
