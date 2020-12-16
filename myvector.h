#ifndef myvector_h
#define myvector_h
#pragma once
#include <initializer_list>
#include <iterator>
#include <memory>

template <typename T, typename A = std::allocator<T>>
class myvector
{
    A alloc;
    int sz;
    T* elem;
    int space;

public:
    myvector();

    explicit myvector(int s);
    myvector(std::initializer_list<T> lst);

    myvector(const myvector& a);
    myvector& operator=(const myvector& a);

    myvector(myvector&& a);

    myvector operator=(myvector&& a);

    ~myvector() { delete[] elem; }

    T& operator[ ](int i) { return elem[i]; }

    int capacity() const { return space; }
    int size() const { return sz; }

    void reserve(int newalloc);

    void resize(int newsize, const T& val = T())
    {
        reserve(newsize);
        for (int i = sz; i < newsize; ++i)
            alloc.construct(&elem[i], val);
        for (int i = sz; i < newsize; ++i)
            alloc.destroy(&elem[i]);
        sz = newsize;
    }
    void push_back(const T& d);
};

template <typename T, typename A>
myvector<T,A>::myvector():
        sz{0}, elem{nullptr}, space{0} {}

template <typename T, typename A>
myvector<T,A>::myvector(int s):
        sz{s}, space{s},
        elem{new T[s]}
{
        for(int i=0; i<s; ++i)
            elem[i]=0;
}

template <typename T, typename A>
myvector<T,A>::myvector(std::initializer_list<T> lst):
        sz{ static_cast<int>(lst.size())},
        elem{new T[lst.size()]},
        space{sz}
{
        std::copy(lst.begin(), lst.end(), elem);
}

template <typename T, typename A>
myvector<T,A>::myvector(const myvector& a):
        sz{a.sz},
        elem{new T[a.sz]},
        space{sz}
{
        std::copy(a.elem, a.elem + a.sz, elem);
}

template <typename T, typename A>
myvector<T,A>& myvector<T,A>::operator=(const myvector& a)
{
        if (this == &a)
            return *this;
        if (a.sz <= space)
        {
            std::copy(a.elem, a.elem + a.sz, elem);
            sz = a.sz;
            return *this;
        }
        T* p = new T[a.size()];
        std::copy(a.elem, a.elem + a.sz, p);
        delete[] elem;
        elem = p;
        space = sz = a.sz;
        return *this;
}

template <typename T, typename A>
myvector<T,A>::myvector(myvector&& a):
        sz{a.sz}, elem{a.elem}, space{sz}
{
        a.sz = 0;
        a.elem = nullptr;
}

template <typename T, typename A>
myvector<T,A> myvector<T,A>::operator=(myvector&& a)
{
        delete[] elem;
        elem = a.elem;
        a.elem = nullptr;
        sz = a.sz;
        a.sz = 0;
        return *this;
}


template<typename T, typename A>
void myvector<T,A>::reserve(int newalloc)
{
        if (newalloc <= space) return;
        T* p = alloc.allocate(newalloc);
        for (int i = 0; i < sz; ++i)
            alloc.construct(&p[i], elem[i]);
        for (int i = 0; i < sz; ++i)
            alloc.destroy(&elem[i]);
        alloc.deallocate(elem, space);
        elem = p;
        space = newalloc;
}


template<typename T, typename A>
void myvector<T,A>::push_back(const T& d)
{
        if (!space)
            reserve(8);
        else if (sz == space)
            reserve(2*space);
        elem[sz] = d;
        ++sz;
}



#endif // myvector_h
