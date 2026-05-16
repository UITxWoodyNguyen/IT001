/**
 * ============================================================
 *  STL Containers — Hand-Rolled Implementation
 *  Only dependency: <iostream>
 *
 *  Containers implemented (matching cplusplus.com/reference/stl):
 *
 *  Sequence:
 *    Array<T,N>        – fixed-size array
 *    Vector<T>         – dynamic array
 *    Deque<T>          – double-ended queue (block-based)
 *    ForwardList<T>    – singly-linked list
 *    List<T>           – doubly-linked list
 *
 *  Container Adaptors:
 *    Stack<T>          – LIFO (backed by Deque)
 *    Queue<T>          – FIFO (backed by Deque)
 *    PriorityQueue<T>  – max-heap (backed by Vector)
 *
 *  Associative (ordered, Red-Black Tree):
 *    Set<K>            – unique keys
 *    Multiset<K>       – duplicate keys allowed
 *    Map<K,V>          – unique key→value pairs
 *    Multimap<K,V>     – duplicate keys allowed
 *
 *  Unordered Associative (hash table – separate chaining):
 *    UnorderedSet<K>
 *    UnorderedMultiset<K>
 *    UnorderedMap<K,V>
 *    UnorderedMultimap<K,V>
 * ============================================================
 */

#pragma once
#include <iostream>

namespace std_custom {

// ============================================================
//  Utilities (pair, initializer_list shim, move/forward)
// ============================================================

template<typename T>
struct remove_reference      { using type = T; };
template<typename T>
struct remove_reference<T&>  { using type = T; };
template<typename T>
struct remove_reference<T&&> { using type = T; };

template<typename T>
typename remove_reference<T>::type&& move(T&& t) noexcept {
    return static_cast<typename remove_reference<T>::type&&>(t);
}

template<typename T>
T&& forward(typename remove_reference<T>::type& t) noexcept {
    return static_cast<T&&>(t);
}

template<typename T>
void swap_val(T& a, T& b) noexcept {
    T tmp = move(a);
    a = move(b);
    b = move(tmp);
}

// ---- Pair --------------------------------------------------
template<typename F, typename S>
struct Pair {
    F first;
    S second;

    Pair() : first(), second() {}
    Pair(const F& f, const S& s) : first(f), second(s) {}
    Pair(F&& f, S&& s) : first(move(f)), second(move(s)) {}

    bool operator==(const Pair& o) const { return first == o.first && second == o.second; }
    bool operator!=(const Pair& o) const { return !(*this == o); }
    bool operator< (const Pair& o) const {
        return first < o.first || (!(o.first < first) && second < o.second);
    }
};

template<typename F, typename S>
Pair<F,S> make_pair(F&& f, S&& s) {
    return Pair<F,S>(forward<F>(f), forward<S>(s));
}

// ---- Default comparator ------------------------------------
template<typename T>
struct Less {
    bool operator()(const T& a, const T& b) const { return a < b; }
};

// ---- Default hash ------------------------------------------
template<typename T>
struct Hash {
    std::size_t operator()(const T& val) const {
        // FNV-1a style over raw bytes
        const unsigned char* p = reinterpret_cast<const unsigned char*>(&val);
        std::size_t h = 14695981039346656037ULL;
        for (std::size_t i = 0; i < sizeof(T); ++i) {
            h ^= p[i];
            h *= 1099511628211ULL;
        }
        return h;
    }
};

// Specialisation for const char* (pointer hashes the address, not ideal — string users should use std::string)
template<>
struct Hash<const char*> {
    std::size_t operator()(const char* s) const {
        std::size_t h = 14695981039346656037ULL;
        while (*s) {
            h ^= static_cast<unsigned char>(*s++);
            h *= 1099511628211ULL;
        }
        return h;
    }
};

template<typename T>
struct Equal {
    bool operator()(const T& a, const T& b) const { return a == b; }
};

// ============================================================
//  Raw memory helpers (no <memory>)
// ============================================================

template<typename T>
T* allocate(std::size_t n) {
    return reinterpret_cast<T*>(::operator new(n * sizeof(T)));
}

template<typename T>
void deallocate(T* p) {
    ::operator delete(p);
}

template<typename T>
void construct(T* p, const T& val) { new(p) T(val); }

template<typename T>
void construct(T* p, T&& val) { new(p) T(move(val)); }

template<typename T>
void destroy(T* p) { p->~T(); }

template<typename T>
void destroy_range(T* first, T* last) {
    for (; first != last; ++first) destroy(first);
}

// ============================================================
//  1. Array<T, N>  — fixed-size array
// ============================================================
template<typename T, std::size_t N>
class Array {
public:
    // ------ types ------
    using value_type      = T;
    using size_type       = std::size_t;
    using reference       = T&;
    using const_reference = const T&;
    using pointer         = T*;
    using const_pointer   = const T*;
    using iterator        = T*;
    using const_iterator  = const T*;

    T _data[N];   // aggregate – public for brace-init

    // ------ iterators ------
    iterator       begin()        noexcept { return _data; }
    iterator       end()          noexcept { return _data + N; }
    const_iterator begin()  const noexcept { return _data; }
    const_iterator end()    const noexcept { return _data + N; }
    const_iterator cbegin() const noexcept { return _data; }
    const_iterator cend()   const noexcept { return _data + N; }

    // ------ capacity ------
    constexpr size_type size()     const noexcept { return N; }
    constexpr size_type max_size() const noexcept { return N; }
    constexpr bool      empty()    const noexcept { return N == 0; }

    // ------ element access ------
    reference       operator[](size_type i)       { return _data[i]; }
    const_reference operator[](size_type i) const { return _data[i]; }

    reference at(size_type i) {
        if (i >= N) { std::cerr << "Array::at out of range\n"; __builtin_trap(); }
        return _data[i];
    }
    const_reference at(size_type i) const {
        if (i >= N) { std::cerr << "Array::at out of range\n"; __builtin_trap(); }
        return _data[i];
    }

    reference       front()       { return _data[0]; }
    const_reference front() const { return _data[0]; }
    reference       back()        { return _data[N-1]; }
    const_reference back()  const { return _data[N-1]; }
    pointer         data()        noexcept { return _data; }
    const_pointer   data()  const noexcept { return _data; }

    // ------ modifiers ------
    void fill(const T& v) { for (auto& e : *this) e = v; }

    void swap(Array& o) noexcept {
        for (size_type i = 0; i < N; ++i) swap_val(_data[i], o._data[i]);
    }
};

// ============================================================
//  2. Vector<T>  — dynamic contiguous array
// ============================================================
template<typename T>
class Vector {
public:
    using value_type      = T;
    using size_type       = std::size_t;
    using reference       = T&;
    using const_reference = const T&;
    using iterator        = T*;
    using const_iterator  = const T*;

private:
    T*        _data  = nullptr;
    size_type _size  = 0;
    size_type _cap   = 0;

    void _grow(size_type newcap) {
        T* nd = allocate<T>(newcap);
        for (size_type i = 0; i < _size; ++i) {
            construct(nd + i, move(_data[i]));
            destroy(_data + i);
        }
        deallocate(_data);
        _data = nd;
        _cap  = newcap;
    }

public:
    // ------ constructors / destructor ------
    Vector() = default;

    explicit Vector(size_type n, const T& val = T()) {
        _grow(n);
        for (size_type i = 0; i < n; ++i) construct(_data + i, val);
        _size = n;
    }

    Vector(const Vector& o) {
        _grow(o._size);
        for (size_type i = 0; i < o._size; ++i) construct(_data + i, o._data[i]);
        _size = o._size;
    }

    Vector(Vector&& o) noexcept
        : _data(o._data), _size(o._size), _cap(o._cap)
    { o._data = nullptr; o._size = o._cap = 0; }

    ~Vector() { clear(); deallocate(_data); }

    Vector& operator=(const Vector& o) {
        if (this == &o) return *this;
        Vector tmp(o); swap(tmp); return *this;
    }
    Vector& operator=(Vector&& o) noexcept {
        if (this == &o) return *this;
        Vector tmp(move(o)); swap(tmp); return *this;
    }

    // ------ iterators ------
    iterator       begin()        noexcept { return _data; }
    iterator       end()          noexcept { return _data + _size; }
    const_iterator begin()  const noexcept { return _data; }
    const_iterator end()    const noexcept { return _data + _size; }
    const_iterator cbegin() const noexcept { return _data; }
    const_iterator cend()   const noexcept { return _data + _size; }

    // ------ capacity ------
    size_type size()     const noexcept { return _size; }
    size_type capacity() const noexcept { return _cap; }
    bool      empty()    const noexcept { return _size == 0; }
    size_type max_size() const noexcept { return ~size_type(0); }

    void reserve(size_type n) { if (n > _cap) _grow(n); }

    void resize(size_type n, const T& val = T()) {
        if (n < _size) {
            destroy_range(_data + n, _data + _size);
            _size = n;
        } else {
            reserve(n);
            for (size_type i = _size; i < n; ++i) construct(_data + i, val);
            _size = n;
        }
    }

    void shrink_to_fit() {
        if (_size < _cap) _grow(_size == 0 ? 1 : _size);
    }

    // ------ element access ------
    reference       operator[](size_type i)       { return _data[i]; }
    const_reference operator[](size_type i) const { return _data[i]; }

    reference at(size_type i) {
        if (i >= _size) { std::cerr << "Vector::at out of range\n"; __builtin_trap(); }
        return _data[i];
    }
    const_reference at(size_type i) const {
        if (i >= _size) { std::cerr << "Vector::at out of range\n"; __builtin_trap(); }
        return _data[i];
    }

    reference       front()       { return _data[0]; }
    const_reference front() const { return _data[0]; }
    reference       back()        { return _data[_size-1]; }
    const_reference back()  const { return _data[_size-1]; }
    T*              data()        noexcept { return _data; }
    const T*        data()  const noexcept { return _data; }

    // ------ modifiers ------
    void push_back(const T& val) {
        if (_size == _cap) _grow(_cap ? _cap * 2 : 1);
        construct(_data + _size++, val);
    }
    void push_back(T&& val) {
        if (_size == _cap) _grow(_cap ? _cap * 2 : 1);
        construct(_data + _size++, move(val));
    }

    void pop_back() {
        if (_size) destroy(_data + --_size);
    }

    iterator insert(iterator pos, const T& val) {
        size_type idx = pos - _data;
        if (_size == _cap) _grow(_cap ? _cap * 2 : 1);
        for (size_type i = _size; i > idx; --i) {
            construct(_data + i, move(_data[i-1]));
            destroy(_data + i - 1);
        }
        construct(_data + idx, val);
        ++_size;
        return _data + idx;
    }

    iterator erase(iterator pos) {
        size_type idx = pos - _data;
        destroy(_data + idx);
        for (size_type i = idx; i + 1 < _size; ++i) {
            construct(_data + i, move(_data[i+1]));
            destroy(_data + i + 1);
        }
        --_size;
        return _data + idx;
    }

    void clear() {
        destroy_range(_data, _data + _size);
        _size = 0;
    }

    void assign(size_type n, const T& val) {
        clear();
        resize(n, val);
    }

    void swap(Vector& o) noexcept {
        swap_val(_data, o._data);
        swap_val(_size, o._size);
        swap_val(_cap,  o._cap);
    }
};

// ============================================================
//  3. Deque<T>  — double-ended queue (block/chunk storage)
// ============================================================
template<typename T>
class Deque {
    static constexpr std::size_t BLOCK = 8;

    T**       _map     = nullptr;
    std::size_t _mapCap = 0;
    std::size_t _start  = 0;  // index into flattened array
    std::size_t _size   = 0;

    void _ensure_map(std::size_t n) {
        if (n <= _mapCap) return;
        std::size_t nc = n * 2 + 4;
        T** nm = allocate<T*>(nc);
        for (std::size_t i = 0; i < nc; ++i) nm[i] = nullptr;
        if (_map) {
            std::size_t oldBlocks = (_mapCap);
            for (std::size_t i = 0; i < oldBlocks; ++i) nm[i] = _map[i];
            deallocate(_map);
        }
        _map = nm;
        _mapCap = nc;
    }

    T& _at(std::size_t idx) const {
        std::size_t absIdx = _start + idx;
        std::size_t block  = absIdx / BLOCK;
        std::size_t offset = absIdx % BLOCK;
        return _map[block][offset];
    }

    void _ensure_block(std::size_t block) {
        _ensure_map(block + 1);
        if (!_map[block]) _map[block] = allocate<T>(BLOCK);
    }

public:
    using value_type      = T;
    using size_type       = std::size_t;
    using reference       = T&;
    using const_reference = const T&;

    Deque() = default;

    explicit Deque(size_type n, const T& val = T()) {
        for (size_type i = 0; i < n; ++i) push_back(val);
    }

    Deque(const Deque& o) {
        for (size_type i = 0; i < o._size; ++i) push_back(o[i]);
    }

    Deque(Deque&& o) noexcept
        : _map(o._map), _mapCap(o._mapCap), _start(o._start), _size(o._size)
    { o._map = nullptr; o._mapCap = o._start = o._size = 0; }

    ~Deque() { clear(); if (_map) { for (std::size_t i=0;i<_mapCap;i++) if(_map[i]) deallocate(_map[i]); deallocate(_map); } }

    Deque& operator=(const Deque& o) { Deque tmp(o); swap(tmp); return *this; }
    Deque& operator=(Deque&& o) noexcept { Deque tmp(move(o)); swap(tmp); return *this; }

    // iterators (simple pointer-like)
    struct iterator {
        Deque* dq; std::size_t idx;
        T& operator*()  const { return dq->_at(idx); }
        T* operator->() const { return &dq->_at(idx); }
        iterator& operator++() { ++idx; return *this; }
        iterator  operator++(int) { auto t=*this; ++idx; return t; }
        iterator& operator--() { --idx; return *this; }
        bool operator==(const iterator& o) const { return idx==o.idx; }
        bool operator!=(const iterator& o) const { return idx!=o.idx; }
    };
    struct const_iterator {
        const Deque* dq; std::size_t idx;
        const T& operator*()  const { return dq->_at(idx); }
        const T* operator->() const { return &dq->_at(idx); }
        const_iterator& operator++() { ++idx; return *this; }
        const_iterator  operator++(int) { auto t=*this; ++idx; return t; }
        const_iterator& operator--() { --idx; return *this; }
        bool operator==(const const_iterator& o) const { return idx==o.idx; }
        bool operator!=(const const_iterator& o) const { return idx!=o.idx; }
    };

    iterator       begin()        noexcept { return {this, 0}; }
    iterator       end()          noexcept { return {this, _size}; }
    const_iterator begin()  const noexcept { return {this, 0}; }
    const_iterator end()    const noexcept { return {this, _size}; }
    const_iterator cbegin() const noexcept { return {this, 0}; }
    const_iterator cend()   const noexcept { return {this, _size}; }

    size_type size()     const noexcept { return _size; }
    bool      empty()    const noexcept { return _size == 0; }
    size_type max_size() const noexcept { return ~size_type(0); }

    reference       operator[](size_type i)       { return _at(i); }
    const_reference operator[](size_type i) const { return _at(i); }

    reference at(size_type i) {
        if(i>=_size){std::cerr<<"Deque::at OOB\n";__builtin_trap();}
        return _at(i);
    }
    const_reference at(size_type i) const {
        if(i>=_size){std::cerr<<"Deque::at OOB\n";__builtin_trap();}
        return _at(i);
    }

    reference       front()       { return _at(0); }
    const_reference front() const { return _at(0); }
    reference       back()        { return _at(_size-1); }
    const_reference back()  const { return _at(_size-1); }

    void push_back(const T& val) {
        std::size_t abs = _start + _size;
        std::size_t blk = abs / BLOCK;
        _ensure_block(blk);
        construct(&_map[blk][abs % BLOCK], val);
        ++_size;
    }
    void push_back(T&& val) {
        std::size_t abs = _start + _size;
        std::size_t blk = abs / BLOCK;
        _ensure_block(blk);
        construct(&_map[blk][abs % BLOCK], move(val));
        ++_size;
    }

    void push_front(const T& val) {
        if (_start == 0) {
            // shift everything right by BLOCK
            std::size_t extra = _mapCap + 2;
            _ensure_map(_mapCap + extra);
            std::size_t shift = BLOCK;
            // move blocks up
            for (std::size_t i = (_start + _size + BLOCK - 1) / BLOCK + shift; i >= shift; --i) {
                _map[i] = (i >= shift) ? _map[i - shift] : nullptr;
            }
            for (std::size_t i = 0; i < shift; ++i) _map[i] = nullptr;
            _start += shift * BLOCK;
        }
        --_start;
        std::size_t blk = _start / BLOCK;
        _ensure_block(blk);
        construct(&_map[blk][_start % BLOCK], val);
        ++_size;
    }
    void push_front(T&& val) {
        if (_start == 0) {
            std::size_t shift = 2;
            _ensure_map(_mapCap + shift * 2);
            std::size_t totalBlocks = (_start + _size + BLOCK - 1) / BLOCK;
            for (std::size_t i = totalBlocks + shift - 1; i >= shift; --i)
                _map[i] = _map[i - shift];
            for (std::size_t i = 0; i < shift; ++i) _map[i] = nullptr;
            _start += shift * BLOCK;
        }
        --_start;
        std::size_t blk = _start / BLOCK;
        _ensure_block(blk);
        construct(&_map[blk][_start % BLOCK], move(val));
        ++_size;
    }

    void pop_back() {
        if (_size) {
            std::size_t abs = _start + --_size;
            destroy(&_map[abs/BLOCK][abs%BLOCK]);
        }
    }
    void pop_front() {
        if (_size) {
            destroy(&_map[_start/BLOCK][_start%BLOCK]);
            ++_start;
            --_size;
        }
    }

    void clear() {
        for (std::size_t i = 0; i < _size; ++i) {
            std::size_t abs = _start + i;
            destroy(&_map[abs/BLOCK][abs%BLOCK]);
        }
        _size = 0;
    }

    void resize(size_type n, const T& val = T()) {
        while (_size > n) pop_back();
        while (_size < n) push_back(val);
    }

    void assign(size_type n, const T& val) { clear(); for(size_type i=0;i<n;i++) push_back(val); }

    void swap(Deque& o) noexcept {
        swap_val(_map,    o._map);
        swap_val(_mapCap, o._mapCap);
        swap_val(_start,  o._start);
        swap_val(_size,   o._size);
    }

    void shrink_to_fit() {} // no-op for simplicity
};

// ============================================================
//  4. ForwardList<T>  — singly-linked list
// ============================================================
template<typename T>
class ForwardList {
    struct Node {
        T     val;
        Node* next;
        explicit Node(const T& v, Node* n=nullptr) : val(v), next(n) {}
        explicit Node(T&& v,      Node* n=nullptr) : val(move(v)), next(n) {}
    };

    Node* _head = nullptr;
    std::size_t _size = 0;

public:
    using value_type = T;
    using size_type  = std::size_t;

    struct iterator {
        Node* ptr;
        T& operator*()  const { return ptr->val; }
        T* operator->() const { return &ptr->val; }
        iterator& operator++() { ptr = ptr->next; return *this; }
        iterator  operator++(int) { auto t=*this; ptr=ptr->next; return t; }
        bool operator==(const iterator& o) const { return ptr==o.ptr; }
        bool operator!=(const iterator& o) const { return ptr!=o.ptr; }
    };
    struct const_iterator {
        const Node* ptr;
        const T& operator*()  const { return ptr->val; }
        const T* operator->() const { return &ptr->val; }
        const_iterator& operator++() { ptr = ptr->next; return *this; }
        const_iterator  operator++(int) { auto t=*this; ptr=ptr->next; return t; }
        bool operator==(const const_iterator& o) const { return ptr==o.ptr; }
        bool operator!=(const const_iterator& o) const { return ptr!=o.ptr; }
    };

    ForwardList() = default;

    explicit ForwardList(size_type n, const T& val = T()) {
        for (size_type i = 0; i < n; ++i) push_front(val);
    }

    ForwardList(const ForwardList& o) {
        // build reversed then reverse
        Node* tail = nullptr;
        for (Node* p = o._head; p; p = p->next) {
            Node* n = new Node(p->val);
            if (!tail) { _head = tail = n; }
            else       { tail->next = n; tail = n; }
        }
        _size = o._size;
    }

    ForwardList(ForwardList&& o) noexcept : _head(o._head), _size(o._size)
    { o._head = nullptr; o._size = 0; }

    ~ForwardList() { clear(); }

    ForwardList& operator=(const ForwardList& o) { ForwardList tmp(o); swap(tmp); return *this; }
    ForwardList& operator=(ForwardList&& o) noexcept { ForwardList tmp(move(o)); swap(tmp); return *this; }

    iterator       begin()        noexcept { return {_head}; }
    iterator       end()          noexcept { return {nullptr}; }
    const_iterator begin()  const noexcept { return {_head}; }
    const_iterator end()    const noexcept { return {nullptr}; }
    const_iterator cbegin() const noexcept { return {_head}; }
    const_iterator cend()   const noexcept { return {nullptr}; }

    bool        empty()    const noexcept { return _size == 0; }
    size_type   max_size() const noexcept { return ~size_type(0); }

    T&       front()       { return _head->val; }
    const T& front() const { return _head->val; }

    void push_front(const T& val) { _head = new Node(val, _head); ++_size; }
    void push_front(T&& val)      { _head = new Node(move(val), _head); ++_size; }

    void pop_front() {
        if (_head) { Node* old=_head; _head=_head->next; delete old; --_size; }
    }

    // insert_after: returns iterator to inserted
    iterator insert_after(iterator pos, const T& val) {
        Node* n = new Node(val, pos.ptr->next);
        pos.ptr->next = n;
        ++_size;
        return {n};
    }

    // erase_after
    iterator erase_after(iterator pos) {
        if (pos.ptr && pos.ptr->next) {
            Node* del = pos.ptr->next;
            pos.ptr->next = del->next;
            delete del;
            --_size;
            return {pos.ptr->next};
        }
        return end();
    }

    void clear() {
        while (_head) pop_front();
    }

    void resize(size_type n, const T& val = T()) {
        // Count existing
        size_type cur = 0; Node* p = _head; Node* last = nullptr;
        while (p) { cur++; last = p; p = p->next; }
        while (cur > n) { pop_front(); cur--; }
        while (cur < n) {
            Node* nd = new Node(val);
            if (!last) { _head = nd; }
            else       { last->next = nd; }
            last = nd;
            ++cur;
        }
        _size = n;
    }

    void assign(size_type n, const T& val) { clear(); for(size_type i=0;i<n;i++) push_front(val); }

    void remove(const T& val) {
        while (_head && _head->val == val) pop_front();
        for (Node* p = _head; p && p->next; ) {
            if (p->next->val == val) {
                Node* del = p->next;
                p->next = del->next;
                delete del;
                --_size;
            } else p = p->next;
        }
    }

    template<typename Pred>
    void remove_if(Pred pred) {
        while (_head && pred(_head->val)) pop_front();
        for (Node* p = _head; p && p->next; ) {
            if (pred(p->next->val)) {
                Node* del = p->next;
                p->next = del->next;
                delete del;
                --_size;
            } else p = p->next;
        }
    }

    void reverse() {
        Node* prev = nullptr;
        Node* cur  = _head;
        while (cur) {
            Node* nx = cur->next;
            cur->next = prev;
            prev = cur;
            cur = nx;
        }
        _head = prev;
    }

    void unique() {
        for (Node* p = _head; p && p->next; ) {
            if (p->val == p->next->val) {
                Node* del = p->next;
                p->next = del->next;
                delete del;
                --_size;
            } else p = p->next;
        }
    }

    void sort() {
        // insertion sort (O(n²) but no extra includes)
        if (!_head || !_head->next) return;
        Node* sorted = nullptr;
        Node* cur = _head;
        while (cur) {
            Node* nx = cur->next;
            if (!sorted || cur->val < sorted->val) {
                cur->next = sorted; sorted = cur;
            } else {
                Node* s = sorted;
                while (s->next && s->next->val <= cur->val) s = s->next;
                cur->next = s->next; s->next = cur;
            }
            cur = nx;
        }
        _head = sorted;
    }

    void merge(ForwardList& o) {
        // merge two sorted lists
        Node dummy(T{}); Node* tail = &dummy;
        Node* a = _head; Node* b = o._head;
        while (a && b) {
            if (a->val <= b->val) { tail->next=a; a=a->next; }
            else                  { tail->next=b; b=b->next; }
            tail = tail->next;
        }
        tail->next = a ? a : b;
        _head = dummy.next;
        _size += o._size;
        o._head = nullptr; o._size = 0;
    }

    void swap(ForwardList& o) noexcept {
        swap_val(_head, o._head);
        swap_val(_size, o._size);
    }
};

// ============================================================
//  5. List<T>  — doubly-linked list
// ============================================================
template<typename T>
class List {
    struct Node {
        T     val;
        Node* prev;
        Node* next;
        explicit Node(const T& v) : val(v), prev(nullptr), next(nullptr) {}
        explicit Node(T&& v)      : val(move(v)), prev(nullptr), next(nullptr) {}
    };

    Node*       _sentinel; // dummy head/tail node
    std::size_t _size = 0;

    Node* _make_sentinel() {
        Node* s = allocate<Node>(1);
        s->prev = s; s->next = s;
        return s;
    }

public:
    using value_type = T;
    using size_type  = std::size_t;

    struct iterator {
        Node* ptr;
        T& operator*()  const { return ptr->val; }
        T* operator->() const { return &ptr->val; }
        iterator& operator++() { ptr=ptr->next; return *this; }
        iterator  operator++(int) { auto t=*this; ptr=ptr->next; return t; }
        iterator& operator--() { ptr=ptr->prev; return *this; }
        iterator  operator--(int) { auto t=*this; ptr=ptr->prev; return t; }
        bool operator==(const iterator& o) const { return ptr==o.ptr; }
        bool operator!=(const iterator& o) const { return ptr!=o.ptr; }
    };
    struct const_iterator {
        const Node* ptr;
        const T& operator*()  const { return ptr->val; }
        const T* operator->() const { return &ptr->val; }
        const_iterator& operator++() { ptr=ptr->next; return *this; }
        const_iterator  operator++(int) { auto t=*this; ptr=ptr->next; return t; }
        const_iterator& operator--() { ptr=ptr->prev; return *this; }
        bool operator==(const const_iterator& o) const { return ptr==o.ptr; }
        bool operator!=(const const_iterator& o) const { return ptr!=o.ptr; }
    };

    List() : _sentinel(_make_sentinel()) {}

    explicit List(size_type n, const T& val = T()) : List() {
        for (size_type i=0;i<n;i++) push_back(val);
    }

    List(const List& o) : List() {
        for (const auto& v : o) push_back(v);
    }
    List(List&& o) noexcept : _sentinel(o._sentinel), _size(o._size) {
        o._sentinel = o._make_sentinel(); o._size = 0;
    }

    ~List() { clear(); deallocate(_sentinel); }

    List& operator=(const List& o) { List tmp(o); swap(tmp); return *this; }
    List& operator=(List&& o) noexcept { List tmp(move(o)); swap(tmp); return *this; }

    iterator       begin()        noexcept { return {_sentinel->next}; }
    iterator       end()          noexcept { return {_sentinel}; }
    const_iterator begin()  const noexcept { return {_sentinel->next}; }
    const_iterator end()    const noexcept { return {_sentinel}; }
    const_iterator cbegin() const noexcept { return {_sentinel->next}; }
    const_iterator cend()   const noexcept { return {_sentinel}; }

    size_type size()     const noexcept { return _size; }
    bool      empty()    const noexcept { return _size == 0; }
    size_type max_size() const noexcept { return ~size_type(0); }

    T&       front()       { return _sentinel->next->val; }
    const T& front() const { return _sentinel->next->val; }
    T&       back()        { return _sentinel->prev->val; }
    const T& back()  const { return _sentinel->prev->val; }

    void _insert_before(Node* pos, Node* nd) {
        nd->next = pos;
        nd->prev = pos->prev;
        pos->prev->next = nd;
        pos->prev = nd;
        ++_size;
    }

    void push_back(const T& val) { _insert_before(_sentinel, new Node(val)); }
    void push_back(T&& val)      { _insert_before(_sentinel, new Node(move(val))); }
    void push_front(const T& val){ _insert_before(_sentinel->next, new Node(val)); }
    void push_front(T&& val)     { _insert_before(_sentinel->next, new Node(move(val))); }

    void pop_back()  { if(_size){ Node* n=_sentinel->prev; n->prev->next=_sentinel; _sentinel->prev=n->prev; delete n; --_size; } }
    void pop_front() { if(_size){ Node* n=_sentinel->next; _sentinel->next=n->next; n->next->prev=_sentinel; delete n; --_size; } }

    iterator insert(iterator pos, const T& val) {
        Node* nd = new Node(val);
        _insert_before(pos.ptr, nd);
        return {nd};
    }

    iterator erase(iterator pos) {
        Node* nx = pos.ptr->next;
        pos.ptr->prev->next = pos.ptr->next;
        pos.ptr->next->prev = pos.ptr->prev;
        delete pos.ptr;
        --_size;
        return {nx};
    }

    void clear() { while (!empty()) pop_back(); }

    void resize(size_type n, const T& val = T()) {
        while (_size > n) pop_back();
        while (_size < n) push_back(val);
    }

    void assign(size_type n, const T& val) { clear(); for(size_type i=0;i<n;i++) push_back(val); }

    void remove(const T& val) {
        for (auto it=begin(); it!=end(); ) {
            if (*it == val) it = erase(it);
            else ++it;
        }
    }

    template<typename Pred>
    void remove_if(Pred pred) {
        for (auto it=begin(); it!=end(); ) {
            if (pred(*it)) it = erase(it);
            else ++it;
        }
    }

    void reverse() {
        Node* cur = _sentinel;
        do { swap_val(cur->prev, cur->next); cur = cur->prev; }
        while (cur != _sentinel);
    }

    void unique() {
        for (auto it=begin(); it!=end(); ) {
            auto nx = it; ++nx;
            if (nx != end() && *it == *nx) erase(nx);
            else ++it;
        }
    }

    void sort() {
        if (_size <= 1) return;
        // merge-sort via splitting
        List a, b;
        std::size_t half = _size / 2, i = 0;
        for (auto it=begin(); it!=end(); ++it, ++i) {
            if (i < half) a.push_back(*it);
            else          b.push_back(*it);
        }
        a.sort(); b.sort();
        a.merge(b);
        *this = move(a);
    }

    void merge(List& o) {
        auto it_a = begin();
        auto it_b = o.begin();
        while (it_a != end() && it_b != o.end()) {
            if (*it_b < *it_a) {
                auto nx = it_b; ++nx;
                // splice node
                Node* nd = it_b.ptr;
                nd->prev->next = nd->next;
                nd->next->prev = nd->prev;
                --o._size;
                _insert_before(it_a.ptr, nd);
                it_b = nx;
            } else ++it_a;
        }
        while (it_b != o.end()) {
            push_back(*it_b);
            it_b = o.erase(it_b);
        }
    }

    void splice(iterator pos, List& o) {
        if (o.empty()) return;
        Node* first = o._sentinel->next;
        Node* last  = o._sentinel->prev;
        // detach from o
        o._sentinel->next = o._sentinel;
        o._sentinel->prev = o._sentinel;
        // attach before pos
        first->prev = pos.ptr->prev;
        pos.ptr->prev->next = first;
        last->next = pos.ptr;
        pos.ptr->prev = last;
        _size += o._size;
        o._size = 0;
    }

    void swap(List& o) noexcept {
        swap_val(_sentinel, o._sentinel);
        swap_val(_size,     o._size);
    }
};

// ============================================================
//  6. Stack<T>  — LIFO adaptor over Deque
// ============================================================
template<typename T, typename Container = Deque<T>>
class Stack {
    Container _c;
public:
    using value_type      = T;
    using size_type       = typename Container::size_type;
    using reference       = typename Container::reference;
    using const_reference = typename Container::const_reference;

    explicit Stack(const Container& c = Container()) : _c(c) {}

    bool        empty() const noexcept { return _c.empty(); }
    size_type   size()  const noexcept { return _c.size(); }
    reference       top()       { return _c.back(); }
    const_reference top() const { return _c.back(); }
    void push(const T& val)  { _c.push_back(val); }
    void push(T&& val)       { _c.push_back(move(val)); }
    void pop()               { _c.pop_back(); }
    void swap(Stack& o) noexcept { _c.swap(o._c); }

    bool operator==(const Stack& o) const { return _c == o._c; }
    bool operator!=(const Stack& o) const { return !(*this == o); }
};

// ============================================================
//  7. Queue<T>  — FIFO adaptor over Deque
// ============================================================
template<typename T, typename Container = Deque<T>>
class Queue {
    Container _c;
public:
    using value_type      = T;
    using size_type       = typename Container::size_type;
    using reference       = typename Container::reference;
    using const_reference = typename Container::const_reference;

    explicit Queue(const Container& c = Container()) : _c(c) {}

    bool        empty() const noexcept { return _c.empty(); }
    size_type   size()  const noexcept { return _c.size(); }
    reference       front()       { return _c.front(); }
    const_reference front() const { return _c.front(); }
    reference       back()        { return _c.back(); }
    const_reference back()  const { return _c.back(); }
    void push(const T& val) { _c.push_back(val); }
    void push(T&& val)      { _c.push_back(move(val)); }
    void pop()              { _c.pop_front(); }
    void swap(Queue& o) noexcept { _c.swap(o._c); }
};

// ============================================================
//  8. PriorityQueue<T>  — max-heap over Vector
// ============================================================
template<typename T, typename Container = Vector<T>, typename Compare = Less<T>>
class PriorityQueue {
    Container _c;
    Compare   _cmp;

    void _sift_up(std::size_t i) {
        while (i > 0) {
            std::size_t parent = (i-1)/2;
            if (_cmp(_c[i], _c[parent])) break;
            swap_val(_c[i], _c[parent]);
            i = parent;
        }
    }
    void _sift_down(std::size_t i) {
        std::size_t n = _c.size();
        while (true) {
            std::size_t largest = i;
            std::size_t l = 2*i+1, r = 2*i+2;
            if (l < n && _cmp(_c[largest], _c[l])) largest = l;
            if (r < n && _cmp(_c[largest], _c[r])) largest = r;
            if (largest == i) break;
            swap_val(_c[i], _c[largest]);
            i = largest;
        }
    }

public:
    using value_type = T;
    using size_type  = typename Container::size_type;

    PriorityQueue() = default;
    explicit PriorityQueue(const Compare& cmp) : _cmp(cmp) {}

    bool      empty() const noexcept { return _c.empty(); }
    size_type size()  const noexcept { return _c.size(); }

    const T& top() const { return _c.front(); }

    void push(const T& val) {
        _c.push_back(val);
        _sift_up(_c.size()-1);
    }
    void push(T&& val) {
        _c.push_back(move(val));
        _sift_up(_c.size()-1);
    }

    void pop() {
        if (_c.empty()) return;
        swap_val(_c[0], _c[_c.size()-1]);
        _c.pop_back();
        if (!_c.empty()) _sift_down(0);
    }

    void swap(PriorityQueue& o) noexcept {
        _c.swap(o._c);
        swap_val(_cmp, o._cmp);
    }
};

// ============================================================
//  Red-Black Tree  (used by Set, Multiset, Map, Multimap)
// ============================================================
enum class RBColor { RED, BLACK };

template<typename T>
struct RBNode {
    T        val;
    RBColor  color = RBColor::RED;
    RBNode*  parent = nullptr;
    RBNode*  left   = nullptr;
    RBNode*  right  = nullptr;

    explicit RBNode(const T& v) : val(v) {}
    explicit RBNode(T&& v)      : val(move(v)) {}
};

template<typename T, typename Compare = Less<T>, bool Multi = false>
class RBTree {
public:
    using Node      = RBNode<T>;
    using size_type = std::size_t;

private:
    Node*     _nil;    // sentinel nil node
    Node*     _root;
    size_type _size = 0;
    Compare   _cmp;

    Node* _make_nil() {
        Node* n = allocate<Node>(1);
        n->color  = RBColor::BLACK;
        n->parent = n->left = n->right = n;
        return n;
    }

    void _rotate_left(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != _nil) y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == _nil)            _root = y;
        else if (x == x->parent->left)    x->parent->left  = y;
        else                              x->parent->right = y;
        y->left   = x;
        x->parent = y;
    }

    void _rotate_right(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        if (y->right != _nil) y->right->parent = x;
        y->parent = x->parent;
        if (x->parent == _nil)            _root = y;
        else if (x == x->parent->right)   x->parent->right = y;
        else                              x->parent->left  = y;
        y->right  = x;
        x->parent = y;
    }

    void _insert_fixup(Node* z) {
        while (z->parent->color == RBColor::RED) {
            if (z->parent == z->parent->parent->left) {
                Node* y = z->parent->parent->right;
                if (y->color == RBColor::RED) {
                    z->parent->color          = RBColor::BLACK;
                    y->color                  = RBColor::BLACK;
                    z->parent->parent->color  = RBColor::RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) { z=z->parent; _rotate_left(z); }
                    z->parent->color         = RBColor::BLACK;
                    z->parent->parent->color = RBColor::RED;
                    _rotate_right(z->parent->parent);
                }
            } else {
                Node* y = z->parent->parent->left;
                if (y->color == RBColor::RED) {
                    z->parent->color          = RBColor::BLACK;
                    y->color                  = RBColor::BLACK;
                    z->parent->parent->color  = RBColor::RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) { z=z->parent; _rotate_right(z); }
                    z->parent->color         = RBColor::BLACK;
                    z->parent->parent->color = RBColor::RED;
                    _rotate_left(z->parent->parent);
                }
            }
        }
        _root->color = RBColor::BLACK;
    }

    void _transplant(Node* u, Node* v) {
        if (u->parent == _nil)           _root = v;
        else if (u == u->parent->left)   u->parent->left  = v;
        else                             u->parent->right = v;
        v->parent = u->parent;
    }

    Node* _minimum(Node* x) const {
        while (x->left != _nil) x = x->left;
        return x;
    }
    Node* _maximum(Node* x) const {
        while (x->right != _nil) x = x->right;
        return x;
    }

    void _delete_fixup(Node* x) {
        while (x != _root && x->color == RBColor::BLACK) {
            if (x == x->parent->left) {
                Node* w = x->parent->right;
                if (w->color == RBColor::RED) {
                    w->color = RBColor::BLACK;
                    x->parent->color = RBColor::RED;
                    _rotate_left(x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == RBColor::BLACK && w->right->color == RBColor::BLACK) {
                    w->color = RBColor::RED; x = x->parent;
                } else {
                    if (w->right->color == RBColor::BLACK) {
                        w->left->color = RBColor::BLACK;
                        w->color = RBColor::RED;
                        _rotate_right(w); w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = RBColor::BLACK;
                    w->right->color  = RBColor::BLACK;
                    _rotate_left(x->parent); x = _root;
                }
            } else {
                Node* w = x->parent->left;
                if (w->color == RBColor::RED) {
                    w->color = RBColor::BLACK;
                    x->parent->color = RBColor::RED;
                    _rotate_right(x->parent);
                    w = x->parent->left;
                }
                if (w->right->color == RBColor::BLACK && w->left->color == RBColor::BLACK) {
                    w->color = RBColor::RED; x = x->parent;
                } else {
                    if (w->left->color == RBColor::BLACK) {
                        w->right->color = RBColor::BLACK;
                        w->color = RBColor::RED;
                        _rotate_left(w); w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = RBColor::BLACK;
                    w->left->color   = RBColor::BLACK;
                    _rotate_right(x->parent); x = _root;
                }
            }
        }
        x->color = RBColor::BLACK;
    }

    void _destroy(Node* x) {
        if (x == _nil) return;
        _destroy(x->left);
        _destroy(x->right);
        delete x;
    }

    Node* _copy(Node* x, Node* par, Node* o_nil) {
        if (x == o_nil) return _nil;
        Node* nd = new Node(x->val);
        nd->color  = x->color;
        nd->parent = par;
        nd->left   = _copy(x->left,  nd, o_nil);
        nd->right  = _copy(x->right, nd, o_nil);
        return nd;
    }

public:
    struct iterator {
        Node* ptr;
        Node* nil_sentinel;
        const T& operator*()  const { return ptr->val; }
        const T* operator->() const { return &ptr->val; }
        iterator& operator++() {
            if (ptr->right != nil_sentinel) {
                ptr = ptr->right;
                while (ptr->left != nil_sentinel) ptr = ptr->left;
            } else {
                Node* y = ptr->parent;
                while (y != nil_sentinel && ptr == y->right) { ptr=y; y=y->parent; }
                ptr = y;
            }
            return *this;
        }
        iterator operator++(int) { auto t=*this; ++*this; return t; }
        iterator& operator--() {
            if (ptr->left != nil_sentinel) {
                ptr = ptr->left;
                while (ptr->right != nil_sentinel) ptr = ptr->right;
            } else {
                Node* y = ptr->parent;
                while (y != nil_sentinel && ptr == y->left) { ptr=y; y=y->parent; }
                ptr = y;
            }
            return *this;
        }
        bool operator==(const iterator& o) const { return ptr==o.ptr; }
        bool operator!=(const iterator& o) const { return ptr!=o.ptr; }
    };
    using const_iterator = iterator; // const semantics through const T& in val access

    RBTree() : _nil(_make_nil()), _root(nullptr) {
        _root = _nil;
    }
    explicit RBTree(const Compare& cmp) : _nil(_make_nil()), _root(nullptr), _cmp(cmp) {
        _root = _nil;
    }

    RBTree(const RBTree& o) : _nil(_make_nil()), _root(nullptr), _cmp(o._cmp) {
        _root = _copy(o._root, _nil, o._nil);
        _size = o._size;
    }

    RBTree(RBTree&& o) noexcept
        : _nil(o._nil), _root(o._root), _size(o._size), _cmp(move(o._cmp))
    {
        Node* new_nil = o._make_nil();
        o._nil = new_nil;
        o._root = new_nil;
        o._size = 0;
    }

    ~RBTree() { _destroy(_root); deallocate(_nil); }

    RBTree& operator=(const RBTree& o) { RBTree tmp(o); swap(tmp); return *this; }
    RBTree& operator=(RBTree&& o) noexcept { RBTree tmp(move(o)); swap(tmp); return *this; }

    iterator begin() const {
        Node* n = _root;
        while (n != _nil && n->left != _nil) n = n->left;
        return {n, _nil};
    }
    iterator end() const { return {_nil, _nil}; }
    iterator cbegin() const { return begin(); }
    iterator cend()   const { return end(); }

    size_type size()     const noexcept { return _size; }
    bool      empty()    const noexcept { return _size == 0; }
    size_type max_size() const noexcept { return ~size_type(0); }

    // returns iterator to inserted (or existing if !Multi)
    iterator insert(const T& val) {
        Node* z = new Node(val);
        z->left = z->right = z->parent = _nil;
        Node* y = _nil;
        Node* x = _root;
        while (x != _nil) {
            y = x;
            if (!Multi && !_cmp(val, x->val) && !_cmp(x->val, val)) {
                // key already exists → don't insert
                delete z;
                return {x, _nil};
            }
            if (_cmp(val, x->val)) x = x->left;
            else                   x = x->right;
        }
        z->parent = y;
        if (y == _nil)               _root = z;
        else if (_cmp(val, y->val))  y->left  = z;
        else                         y->right = z;
        z->color = RBColor::RED;
        _insert_fixup(z);
        ++_size;
        return {z, _nil};
    }

    iterator insert(T&& val) { return insert(static_cast<const T&>(val)); }

    std::size_t erase(const T& val) {
        std::size_t removed = 0;
        while (true) {
            iterator it = find(val);
            if (it == end()) break;
            erase_iter(it);
            ++removed;
            if (!Multi) break;
        }
        return removed;
    }

    void erase_iter(iterator it) {
        Node* z = it.ptr;
        if (z == _nil) return;
        Node* y = z;
        Node* x;
        RBColor y_orig = y->color;
        if (z->left == _nil) {
            x = z->right; _transplant(z, z->right);
        } else if (z->right == _nil) {
            x = z->left;  _transplant(z, z->left);
        } else {
            y = _minimum(z->right);
            y_orig = y->color;
            x = y->right;
            if (y->parent == z) x->parent = y;
            else { _transplant(y, y->right); y->right = z->right; y->right->parent = y; }
            _transplant(z, y);
            y->left = z->left; y->left->parent = y;
            y->color = z->color;
        }
        delete z;
        --_size;
        if (y_orig == RBColor::BLACK) _delete_fixup(x);
    }

    iterator find(const T& val) const {
        Node* x = _root;
        while (x != _nil) {
            if      (_cmp(val, x->val)) x = x->left;
            else if (_cmp(x->val, val)) x = x->right;
            else return {x, _nil};
        }
        return end();
    }

    size_type count(const T& val) const {
        if (!Multi) return find(val) != end() ? 1 : 0;
        size_type c = 0;
        for (auto it=lower_bound(val); it!=end() && !_cmp(val,*it); ++it) ++c;
        return c;
    }

    iterator lower_bound(const T& val) const {
        Node* x = _root; Node* res = _nil;
        while (x != _nil) {
            if (!_cmp(x->val, val)) { res = x; x = x->left; }
            else                     x = x->right;
        }
        return {res, _nil};
    }

    iterator upper_bound(const T& val) const {
        Node* x = _root; Node* res = _nil;
        while (x != _nil) {
            if (_cmp(val, x->val)) { res = x; x = x->left; }
            else                    x = x->right;
        }
        return {res, _nil};
    }

    Pair<iterator,iterator> equal_range(const T& val) const {
        return {lower_bound(val), upper_bound(val)};
    }

    void clear() { _destroy(_root); _root = _nil; _size = 0; }

    void swap(RBTree& o) noexcept {
        swap_val(_nil,  o._nil);
        swap_val(_root, o._root);
        swap_val(_size, o._size);
        swap_val(_cmp,  o._cmp);
    }

    Compare key_comp()   const { return _cmp; }
    Compare value_comp() const { return _cmp; }
};

// ============================================================
//  9. Set<K>
// ============================================================
template<typename K, typename Compare = Less<K>>
class Set {
    RBTree<K,Compare,false> _tree;
public:
    using key_type       = K;
    using value_type     = K;
    using size_type      = std::size_t;
    using iterator       = typename RBTree<K,Compare,false>::iterator;
    using const_iterator = iterator;

    Set() = default;
    explicit Set(const Compare& cmp) : _tree(cmp) {}

    iterator       begin()  const { return _tree.begin(); }
    iterator       end()    const { return _tree.end(); }
    const_iterator cbegin() const { return _tree.cbegin(); }
    const_iterator cend()   const { return _tree.cend(); }

    size_type size()     const noexcept { return _tree.size(); }
    bool      empty()    const noexcept { return _tree.empty(); }
    size_type max_size() const noexcept { return _tree.max_size(); }

    Pair<iterator,bool> insert(const K& val) {
        size_type before = _tree.size();
        iterator it = _tree.insert(val);
        return {it, _tree.size() > before};
    }
    size_type   erase(const K& val)        { return _tree.erase(val); }
    void        erase(iterator it)         { _tree.erase_iter(it); }
    iterator    find(const K& val)  const  { return _tree.find(val); }
    size_type   count(const K& val) const  { return _tree.count(val); }
    iterator    lower_bound(const K& v) const { return _tree.lower_bound(v); }
    iterator    upper_bound(const K& v) const { return _tree.upper_bound(v); }
    Pair<iterator,iterator> equal_range(const K& v) const { return _tree.equal_range(v); }
    void        clear()                    { _tree.clear(); }
    void        swap(Set& o) noexcept      { _tree.swap(o._tree); }
    Compare     key_comp()   const         { return _tree.key_comp(); }
    Compare     value_comp() const         { return _tree.value_comp(); }
};

// ============================================================
// 10. Multiset<K>
// ============================================================
template<typename K, typename Compare = Less<K>>
class Multiset {
    RBTree<K,Compare,true> _tree;
public:
    using key_type       = K;
    using value_type     = K;
    using size_type      = std::size_t;
    using iterator       = typename RBTree<K,Compare,true>::iterator;
    using const_iterator = iterator;

    Multiset() = default;
    explicit Multiset(const Compare& cmp) : _tree(cmp) {}

    iterator begin()  const { return _tree.begin(); }
    iterator end()    const { return _tree.end(); }
    iterator cbegin() const { return _tree.cbegin(); }
    iterator cend()   const { return _tree.cend(); }

    size_type size()     const noexcept { return _tree.size(); }
    bool      empty()    const noexcept { return _tree.empty(); }
    size_type max_size() const noexcept { return _tree.max_size(); }

    iterator  insert(const K& val)       { return _tree.insert(val); }
    size_type erase(const K& val)        { return _tree.erase(val); }
    void      erase(iterator it)         { _tree.erase_iter(it); }
    iterator  find(const K& val)  const  { return _tree.find(val); }
    size_type count(const K& val) const  { return _tree.count(val); }
    iterator  lower_bound(const K& v) const { return _tree.lower_bound(v); }
    iterator  upper_bound(const K& v) const { return _tree.upper_bound(v); }
    Pair<iterator,iterator> equal_range(const K& v) const { return _tree.equal_range(v); }
    void      clear()                    { _tree.clear(); }
    void      swap(Multiset& o) noexcept { _tree.swap(o._tree); }
    Compare   key_comp()   const         { return _tree.key_comp(); }
    Compare   value_comp() const         { return _tree.value_comp(); }
};

// ============================================================
// 11. Map<K,V>   — unique keys, ordered
// ============================================================
template<typename K, typename V, typename Compare = Less<K>>
class Map {
    struct KVCompare {
        Compare cmp;
        bool operator()(const Pair<K,V>& a, const Pair<K,V>& b) const {
            return cmp(a.first, b.first);
        }
        bool operator()(const Pair<K,V>& a, const K& b) const { return cmp(a.first, b); }
        bool operator()(const K& a, const Pair<K,V>& b) const { return cmp(a, b.first); }
    };

    RBTree<Pair<K,V>, KVCompare, false> _tree;

public:
    using key_type    = K;
    using mapped_type = V;
    using value_type  = Pair<K,V>;
    using size_type   = std::size_t;
    using iterator    = typename RBTree<value_type,KVCompare,false>::iterator;
    using const_iterator = iterator;

    Map() = default;

    iterator begin()  const { return _tree.begin(); }
    iterator end()    const { return _tree.end(); }
    iterator cbegin() const { return _tree.cbegin(); }
    iterator cend()   const { return _tree.cend(); }

    size_type size()     const noexcept { return _tree.size(); }
    bool      empty()    const noexcept { return _tree.empty(); }
    size_type max_size() const noexcept { return _tree.max_size(); }

    V& operator[](const K& key) {
        auto it = _tree.find({key, V{}});
        if (it == _tree.end()) {
            it = _tree.insert({key, V{}});
        }
        return const_cast<V&>(it->second);
    }

    V& at(const K& key) {
        auto it = _tree.find({key, V{}});
        if (it == _tree.end()) { std::cerr << "Map::at key not found\n"; __builtin_trap(); }
        return const_cast<V&>(it->second);
    }
    const V& at(const K& key) const {
        auto it = _tree.find({key, V{}});
        if (it == _tree.end()) { std::cerr << "Map::at key not found\n"; __builtin_trap(); }
        return it->second;
    }

    Pair<iterator,bool> insert(const value_type& val) {
        size_type before = _tree.size();
        iterator it = _tree.insert(val);
        return {it, _tree.size() > before};
    }

    size_type erase(const K& key)   { return _tree.erase({key, V{}}); }
    void      erase(iterator it)    { _tree.erase_iter(it); }

    iterator find(const K& key) const {
        return _tree.find({key, V{}});
    }
    size_type count(const K& key) const {
        return _tree.count({key, V{}});
    }
    iterator lower_bound(const K& key) const { return _tree.lower_bound({key, V{}}); }
    iterator upper_bound(const K& key) const { return _tree.upper_bound({key, V{}}); }
    Pair<iterator,iterator> equal_range(const K& key) const { return _tree.equal_range({key, V{}}); }

    void clear()              { _tree.clear(); }
    void swap(Map& o) noexcept{ _tree.swap(o._tree); }
    Compare key_comp()   const{ return Compare{}; }
};

// ============================================================
// 12. Multimap<K,V>
// ============================================================
template<typename K, typename V, typename Compare = Less<K>>
class Multimap {
    struct KVCompare {
        Compare cmp;
        bool operator()(const Pair<K,V>& a, const Pair<K,V>& b) const {
            return cmp(a.first, b.first);
        }
    };

    RBTree<Pair<K,V>, KVCompare, true> _tree;

public:
    using key_type    = K;
    using mapped_type = V;
    using value_type  = Pair<K,V>;
    using size_type   = std::size_t;
    using iterator    = typename RBTree<value_type,KVCompare,true>::iterator;
    using const_iterator = iterator;

    Multimap() = default;

    iterator begin()  const { return _tree.begin(); }
    iterator end()    const { return _tree.end(); }
    iterator cbegin() const { return _tree.cbegin(); }
    iterator cend()   const { return _tree.cend(); }

    size_type size()     const noexcept { return _tree.size(); }
    bool      empty()    const noexcept { return _tree.empty(); }
    size_type max_size() const noexcept { return _tree.max_size(); }

    iterator  insert(const value_type& val) { return _tree.insert(val); }
    size_type erase(const K& key)           { return _tree.erase({key, V{}}); }
    void      erase(iterator it)            { _tree.erase_iter(it); }
    iterator  find(const K& key) const      { return _tree.find({key, V{}}); }
    size_type count(const K& key) const     { return _tree.count({key, V{}}); }
    Pair<iterator,iterator> equal_range(const K& key) const { return _tree.equal_range({key, V{}}); }
    void      clear()                       { _tree.clear(); }
    void      swap(Multimap& o) noexcept    { _tree.swap(o._tree); }
};

// ============================================================
//  Hash Table  (separate chaining, open-addressing optional)
//  Used by UnorderedSet, UnorderedMultiset, UnorderedMap, UnorderedMultimap
// ============================================================
template<typename T,
         typename Hash_    = Hash<T>,
         typename Equal_   = Equal<T>,
         bool    Multi     = false>
class HashTable {
    static constexpr std::size_t INITIAL_BUCKETS = 16;
    static constexpr float       MAX_LOAD        = 0.75f;

    struct HNode {
        T      val;
        HNode* next = nullptr;
        explicit HNode(const T& v) : val(v) {}
        explicit HNode(T&& v)      : val(move(v)) {}
    };

    HNode**     _buckets     = nullptr;
    std::size_t _bucket_cnt  = 0;
    std::size_t _size        = 0;
    Hash_       _hash;
    Equal_      _eq;

    void _alloc_buckets(std::size_t n) {
        _buckets = allocate<HNode*>(n);
        for (std::size_t i=0; i<n; ++i) _buckets[i] = nullptr;
        _bucket_cnt = n;
    }

    void _rehash(std::size_t n) {
        HNode** old = _buckets;
        std::size_t old_cnt = _bucket_cnt;
        _alloc_buckets(n);
        _size = 0;
        for (std::size_t i=0; i<old_cnt; ++i) {
            HNode* cur = old[i];
            while (cur) {
                HNode* nx = cur->next;
                std::size_t b = _hash(cur->val) % _bucket_cnt;
                cur->next = _buckets[b];
                _buckets[b] = cur;
                ++_size;
                cur = nx;
            }
        }
        deallocate(old);
    }

    void _maybe_rehash() {
        if (_size+1 > static_cast<std::size_t>(_bucket_cnt * MAX_LOAD))
            _rehash(_bucket_cnt * 2);
    }

public:
    struct iterator {
        HNode**     buckets;
        std::size_t bucket_cnt;
        std::size_t bkt;
        HNode*      node;

        void _advance() {
            while (!node && bkt + 1 < bucket_cnt) {
                ++bkt; node = buckets[bkt];
            }
        }

        const T& operator*()  const { return node->val; }
        const T* operator->() const { return &node->val; }
        iterator& operator++() {
            node = node->next;
            if (!node) { ++bkt; node = nullptr; _advance(); }
            return *this;
        }
        iterator operator++(int) { auto t=*this; ++*this; return t; }
        bool operator==(const iterator& o) const { return node==o.node && bkt==o.bkt; }
        bool operator!=(const iterator& o) const { return !(*this==o); }
    };
    using const_iterator = iterator;

    HashTable() { _alloc_buckets(INITIAL_BUCKETS); }

    HashTable(const HashTable& o) {
        _alloc_buckets(o._bucket_cnt);
        _hash = o._hash; _eq = o._eq;
        for (std::size_t i=0; i<o._bucket_cnt; ++i) {
            for (HNode* p=o._buckets[i]; p; p=p->next) insert(p->val);
        }
    }

    HashTable(HashTable&& o) noexcept
        : _buckets(o._buckets), _bucket_cnt(o._bucket_cnt), _size(o._size),
          _hash(move(o._hash)), _eq(move(o._eq))
    {
        o._buckets = nullptr; o._bucket_cnt = o._size = 0;
        o._alloc_buckets(INITIAL_BUCKETS);
    }

    ~HashTable() {
        if (!_buckets) return;
        for (std::size_t i=0; i<_bucket_cnt; ++i) {
            HNode* p = _buckets[i];
            while (p) { HNode* nx=p->next; delete p; p=nx; }
        }
        deallocate(_buckets);
    }

    HashTable& operator=(const HashTable& o) { HashTable tmp(o); swap(tmp); return *this; }
    HashTable& operator=(HashTable&& o) noexcept { HashTable tmp(move(o)); swap(tmp); return *this; }

    iterator begin() const {
        iterator it{_buckets, _bucket_cnt, 0, _buckets ? _buckets[0] : nullptr};
        if (!it.node) it._advance();
        return it;
    }
    iterator end() const {
        return {_buckets, _bucket_cnt, _bucket_cnt, nullptr};
    }

    std::size_t size()        const noexcept { return _size; }
    bool        empty()       const noexcept { return _size == 0; }
    std::size_t max_size()    const noexcept { return ~std::size_t(0); }
    std::size_t bucket_count()const noexcept { return _bucket_cnt; }
    float       load_factor() const noexcept { return _bucket_cnt ? float(_size)/_bucket_cnt : 0.f; }
    float       max_load_factor() const      { return MAX_LOAD; }
    std::size_t bucket(const T& v) const     { return _hash(v) % _bucket_cnt; }
    std::size_t bucket_size(std::size_t b) const {
        std::size_t c=0; for(HNode* p=_buckets[b];p;p=p->next) ++c; return c;
    }
    std::size_t max_bucket_count() const { return ~std::size_t(0); }

    void reserve(std::size_t n) {
        std::size_t nb = static_cast<std::size_t>(n / MAX_LOAD) + 1;
        if (nb > _bucket_cnt) _rehash(nb);
    }

    void rehash(std::size_t n) { if (n > _bucket_cnt) _rehash(n); }

    iterator insert(const T& val) {
        if (!Multi) {
            auto it = find(val);
            if (it != end()) return it;
        }
        _maybe_rehash();
        std::size_t b = _hash(val) % _bucket_cnt;
        HNode* nd = new HNode(val);
        nd->next = _buckets[b];
        _buckets[b] = nd;
        ++_size;
        return {_buckets, _bucket_cnt, b, nd};
    }

    iterator find(const T& val) const {
        std::size_t b = _hash(val) % _bucket_cnt;
        for (HNode* p=_buckets[b]; p; p=p->next)
            if (_eq(p->val, val)) return {_buckets, _bucket_cnt, b, p};
        return end();
    }

    std::size_t erase(const T& val) {
        std::size_t b = _hash(val) % _bucket_cnt;
        HNode* prev = nullptr; HNode* p = _buckets[b];
        std::size_t removed = 0;
        while (p) {
            if (_eq(p->val, val)) {
                HNode* nx = p->next;
                if (prev) prev->next = nx; else _buckets[b] = nx;
                delete p; p = nx;
                ++removed; --_size;
                if (!Multi) break;
            } else { prev = p; p = p->next; }
        }
        return removed;
    }

    void erase(iterator it) {
        if (it == end()) return;
        std::size_t b = it.bkt;
        HNode* prev = nullptr;
        for (HNode* p=_buckets[b]; p; p=p->next) {
            if (p == it.node) {
                if (prev) prev->next = p->next; else _buckets[b] = p->next;
                delete p; --_size; return;
            }
            prev = p;
        }
    }

    std::size_t count(const T& val) const {
        if (!Multi) return find(val) != end() ? 1 : 0;
        std::size_t b = _hash(val) % _bucket_cnt;
        std::size_t c = 0;
        for (HNode* p=_buckets[b]; p; p=p->next)
            if (_eq(p->val, val)) ++c;
        return c;
    }

    Pair<iterator,iterator> equal_range(const T& val) const {
        iterator first = find(val);
        if (first == end()) return {end(), end()};
        iterator last = first; ++last;
        if (Multi) {
            while (last != end() && _eq(*last, val)) ++last;
        }
        return {first, last};
    }

    void clear() {
        for (std::size_t i=0; i<_bucket_cnt; ++i) {
            HNode* p=_buckets[i];
            while (p) { HNode* nx=p->next; delete p; p=nx; }
            _buckets[i] = nullptr;
        }
        _size = 0;
    }

    void swap(HashTable& o) noexcept {
        swap_val(_buckets,    o._buckets);
        swap_val(_bucket_cnt, o._bucket_cnt);
        swap_val(_size,       o._size);
        swap_val(_hash,       o._hash);
        swap_val(_eq,         o._eq);
    }

    Hash_  hash_function() const { return _hash; }
    Equal_ key_eq()        const { return _eq; }
};

// ============================================================
// 13. UnorderedSet<K>
// ============================================================
template<typename K,
         typename Hash_  = Hash<K>,
         typename Equal_ = Equal<K>>
class UnorderedSet {
    HashTable<K, Hash_, Equal_, false> _ht;
public:
    using key_type       = K;
    using value_type     = K;
    using size_type      = std::size_t;
    using iterator       = typename HashTable<K,Hash_,Equal_,false>::iterator;
    using const_iterator = iterator;

    UnorderedSet() = default;

    iterator begin()  const { return _ht.begin(); }
    iterator end()    const { return _ht.end(); }
    iterator cbegin() const { return _ht.begin(); }
    iterator cend()   const { return _ht.end(); }

    size_type size()     const noexcept { return _ht.size(); }
    bool      empty()    const noexcept { return _ht.empty(); }
    size_type max_size() const noexcept { return _ht.max_size(); }

    Pair<iterator,bool> insert(const K& val) {
        size_type before = _ht.size();
        iterator it = _ht.insert(val);
        return {it, _ht.size() > before};
    }
    size_type erase(const K& val)   { return _ht.erase(val); }
    void      erase(iterator it)    { _ht.erase(it); }
    iterator  find(const K& val)    const { return _ht.find(val); }
    size_type count(const K& val)   const { return _ht.count(val); }
    Pair<iterator,iterator> equal_range(const K& val) const { return _ht.equal_range(val); }
    void      clear()               { _ht.clear(); }
    void      swap(UnorderedSet& o) noexcept { _ht.swap(o._ht); }
    void      reserve(size_type n)  { _ht.reserve(n); }
    void      rehash(size_type n)   { _ht.rehash(n); }
    size_type bucket_count()        const { return _ht.bucket_count(); }
    size_type bucket_size(size_type b) const { return _ht.bucket_size(b); }
    size_type bucket(const K& v)    const { return _ht.bucket(v); }
    float     load_factor()         const { return _ht.load_factor(); }
    float     max_load_factor()     const { return _ht.max_load_factor(); }
    size_type max_bucket_count()    const { return _ht.max_bucket_count(); }
    Hash_     hash_function()       const { return _ht.hash_function(); }
    Equal_    key_eq()              const { return _ht.key_eq(); }
};

// ============================================================
// 14. UnorderedMultiset<K>
// ============================================================
template<typename K,
         typename Hash_  = Hash<K>,
         typename Equal_ = Equal<K>>
class UnorderedMultiset {
    HashTable<K, Hash_, Equal_, true> _ht;
public:
    using key_type       = K;
    using value_type     = K;
    using size_type      = std::size_t;
    using iterator       = typename HashTable<K,Hash_,Equal_,true>::iterator;

    UnorderedMultiset() = default;

    iterator begin()  const { return _ht.begin(); }
    iterator end()    const { return _ht.end(); }

    size_type size()     const noexcept { return _ht.size(); }
    bool      empty()    const noexcept { return _ht.empty(); }

    iterator  insert(const K& val)  { return _ht.insert(val); }
    size_type erase(const K& val)   { return _ht.erase(val); }
    void      erase(iterator it)    { _ht.erase(it); }
    iterator  find(const K& val)    const { return _ht.find(val); }
    size_type count(const K& val)   const { return _ht.count(val); }
    Pair<iterator,iterator> equal_range(const K& v) const { return _ht.equal_range(v); }
    void      clear()               { _ht.clear(); }
    void      swap(UnorderedMultiset& o) noexcept { _ht.swap(o._ht); }
    void      reserve(size_type n)  { _ht.reserve(n); }
    void      rehash(size_type n)   { _ht.rehash(n); }
    size_type bucket_count()        const { return _ht.bucket_count(); }
    float     load_factor()         const { return _ht.load_factor(); }
    Hash_     hash_function()       const { return _ht.hash_function(); }
    Equal_    key_eq()              const { return _ht.key_eq(); }
};

// ============================================================
// 15. UnorderedMap<K,V>
// ============================================================
template<typename K, typename V,
         typename Hash_  = Hash<K>,
         typename Equal_ = Equal<K>>
class UnorderedMap {
    struct KVHash {
        Hash_ h;
        std::size_t operator()(const Pair<K,V>& kv) const { return h(kv.first); }
    };
    struct KVEqual {
        Equal_ eq;
        bool operator()(const Pair<K,V>& a, const Pair<K,V>& b) const { return eq(a.first, b.first); }
    };

    HashTable<Pair<K,V>, KVHash, KVEqual, false> _ht;

public:
    using key_type       = K;
    using mapped_type    = V;
    using value_type     = Pair<K,V>;
    using size_type      = std::size_t;
    using iterator       = typename HashTable<value_type,KVHash,KVEqual,false>::iterator;
    using const_iterator = iterator;

    UnorderedMap() = default;

    iterator begin()  const { return _ht.begin(); }
    iterator end()    const { return _ht.end(); }
    iterator cbegin() const { return _ht.begin(); }
    iterator cend()   const { return _ht.end(); }

    size_type size()     const noexcept { return _ht.size(); }
    bool      empty()    const noexcept { return _ht.empty(); }
    size_type max_size() const noexcept { return _ht.max_size(); }

    V& operator[](const K& key) {
        auto it = _ht.find({key, V{}});
        if (it == _ht.end()) it = _ht.insert({key, V{}});
        return const_cast<V&>(it->second);
    }

    V& at(const K& key) {
        auto it = _ht.find({key, V{}});
        if (it == _ht.end()) { std::cerr << "UnorderedMap::at key not found\n"; __builtin_trap(); }
        return const_cast<V&>(it->second);
    }

    Pair<iterator,bool> insert(const value_type& val) {
        size_type before = _ht.size();
        iterator it = _ht.insert(val);
        return {it, _ht.size() > before};
    }
    size_type erase(const K& key)      { return _ht.erase({key, V{}}); }
    void      erase(iterator it)       { _ht.erase(it); }
    iterator  find(const K& key) const { return _ht.find({key, V{}}); }
    size_type count(const K& key) const{ return _ht.count({key, V{}}); }
    Pair<iterator,iterator> equal_range(const K& key) const { return _ht.equal_range({key, V{}}); }
    void      clear()                  { _ht.clear(); }
    void      swap(UnorderedMap& o) noexcept { _ht.swap(o._ht); }
    void      reserve(size_type n)     { _ht.reserve(n); }
    void      rehash(size_type n)      { _ht.rehash(n); }
    size_type bucket_count()           const { return _ht.bucket_count(); }
    float     load_factor()            const { return _ht.load_factor(); }
    Hash_     hash_function()          const { return Hash_{}; }
    Equal_    key_eq()                 const { return Equal_{}; }
};

// ============================================================
// 16. UnorderedMultimap<K,V>
// ============================================================
template<typename K, typename V,
         typename Hash_  = Hash<K>,
         typename Equal_ = Equal<K>>
class UnorderedMultimap {
    struct KVHash {
        Hash_ h;
        std::size_t operator()(const Pair<K,V>& kv) const { return h(kv.first); }
    };
    struct KVEqual {
        Equal_ eq;
        bool operator()(const Pair<K,V>& a, const Pair<K,V>& b) const { return eq(a.first, b.first); }
    };

    HashTable<Pair<K,V>, KVHash, KVEqual, true> _ht;

public:
    using key_type       = K;
    using mapped_type    = V;
    using value_type     = Pair<K,V>;
    using size_type      = std::size_t;
    using iterator       = typename HashTable<value_type,KVHash,KVEqual,true>::iterator;

    UnorderedMultimap() = default;

    iterator begin()  const { return _ht.begin(); }
    iterator end()    const { return _ht.end(); }

    size_type size()     const noexcept { return _ht.size(); }
    bool      empty()    const noexcept { return _ht.empty(); }

    iterator  insert(const value_type& val) { return _ht.insert(val); }
    size_type erase(const K& key)           { return _ht.erase({key, V{}}); }
    void      erase(iterator it)            { _ht.erase(it); }
    iterator  find(const K& key) const      { return _ht.find({key, V{}}); }
    size_type count(const K& key) const     { return _ht.count({key, V{}}); }
    Pair<iterator,iterator> equal_range(const K& key) const { return _ht.equal_range({key, V{}}); }
    void      clear()                       { _ht.clear(); }
    void      swap(UnorderedMultimap& o) noexcept { _ht.swap(o._ht); }
    void      reserve(size_type n)          { _ht.reserve(n); }
    void      rehash(size_type n)           { _ht.rehash(n); }
    size_type bucket_count()                const { return _ht.bucket_count(); }
    float     load_factor()                 const { return _ht.load_factor(); }
};

} // namespace std_custom

// ============================================================
//  Demo / Smoke-test
// ============================================================
int main() {
    using namespace std_custom;
    using std::cout;

    cout << "===== STL Containers – Custom Implementation =====\n\n";

    // --- Array ---
    cout << "[Array<int,5>]\n";
    Array<int,5> arr = {10, 20, 30, 40, 50};
    for (auto v : arr) cout << v << ' ';
    cout << "\n  size=" << arr.size() << "  front=" << arr.front() << "  back=" << arr.back() << "\n\n";

    // --- Vector ---
    cout << "[Vector<int>]\n";
    Vector<int> vec;
    for (int i=1; i<=6; ++i) vec.push_back(i*10);
    vec.insert(vec.begin()+2, 25);
    vec.erase(vec.begin()+4);
    for (auto v : vec) cout << v << ' ';
    cout << "\n  size=" << vec.size() << "  cap=" << vec.capacity() << "\n\n";

    // --- Deque ---
    cout << "[Deque<int>]\n";
    Deque<int> dq;
    for (int i=1; i<=4; ++i) dq.push_back(i);
    dq.push_front(0);
    dq.pop_back();
    for (std::size_t i=0; i<dq.size(); ++i) cout << dq[i] << ' ';
    cout << "\n  size=" << dq.size() << "\n\n";

    // --- ForwardList ---
    cout << "[ForwardList<int>]\n";
    ForwardList<int> fl;
    for (int i=5; i>=1; --i) fl.push_front(i);
    fl.remove(3);
    for (auto v : fl) cout << v << ' ';
    cout << "\n\n";

    // --- List ---
    cout << "[List<int>]\n";
    List<int> lst;
    for (int i=1; i<=5; ++i) lst.push_back(i*10);
    lst.push_front(5);
    lst.reverse();
    lst.sort();
    for (auto v : lst) cout << v << ' ';
    cout << "\n  size=" << lst.size() << "\n\n";

    // --- Stack ---
    cout << "[Stack<int>]\n";
    Stack<int> stk;
    for (int i=1; i<=5; ++i) stk.push(i);
    while (!stk.empty()) { cout << stk.top() << ' '; stk.pop(); }
    cout << "\n\n";

    // --- Queue ---
    cout << "[Queue<int>]\n";
    Queue<int> q;
    for (int i=1; i<=5; ++i) q.push(i);
    while (!q.empty()) { cout << q.front() << ' '; q.pop(); }
    cout << "\n\n";

    // --- PriorityQueue ---
    cout << "[PriorityQueue<int> – max-heap]\n";
    PriorityQueue<int> pq;
    for (int v : {3,1,4,1,5,9,2,6}) pq.push(v);
    while (!pq.empty()) { cout << pq.top() << ' '; pq.pop(); }
    cout << "\n\n";

    // --- Set ---
    cout << "[Set<int>]\n";
    Set<int> s;
    for (int v : {5,3,7,3,1,9,5}) s.insert(v);
    for (auto v : s) cout << v << ' ';
    cout << "\n  count(3)=" << s.count(3) << "  count(4)=" << s.count(4) << "\n\n";

    // --- Multiset ---
    cout << "[Multiset<int>]\n";
    Multiset<int> ms;
    for (int v : {5,3,7,3,1,9,5}) ms.insert(v);
    for (auto v : ms) cout << v << ' ';
    cout << "\n  count(3)=" << ms.count(3) << "  count(5)=" << ms.count(5) << "\n\n";

    // --- Map ---
    cout << "[Map<int,int>]\n";
    Map<int,int> m;
    m[1]=10; m[2]=20; m[3]=30;
    m.insert({4,40});
    m.erase(2);
    for (auto it=m.begin(); it!=m.end(); ++it)
        cout << it->first << "->" << it->second << "  ";
    cout << "\n  m[3]=" << m.at(3) << "  size=" << m.size() << "\n\n";

    // --- Multimap ---
    cout << "[Multimap<int,int>]\n";
    Multimap<int,int> mm;
    mm.insert({1,10}); mm.insert({1,20}); mm.insert({2,30});
    for (auto it=mm.begin(); it!=mm.end(); ++it)
        cout << it->first << "->" << it->second << "  ";
    cout << "\n  count(1)=" << mm.count(1) << "\n\n";

    // --- UnorderedSet ---
    cout << "[UnorderedSet<int>]\n";
    UnorderedSet<int> us;
    for (int v : {5,3,7,3,1,9,5}) us.insert(v);
    cout << "  size=" << us.size() << "  count(3)=" << us.count(3) << "  count(4)=" << us.count(4) << "\n\n";

    // --- UnorderedMultiset ---
    cout << "[UnorderedMultiset<int>]\n";
    UnorderedMultiset<int> ums;
    for (int v : {5,3,7,3,1,9,5}) ums.insert(v);
    cout << "  size=" << ums.size() << "  count(3)=" << ums.count(3) << "  count(5)=" << ums.count(5) << "\n\n";

    // --- UnorderedMap ---
    cout << "[UnorderedMap<int,int>]\n";
    UnorderedMap<int,int> um;
    um[1]=100; um[2]=200; um[3]=300;
    um.erase(2);
    cout << "  size=" << um.size()
         << "  um[1]=" << um.at(1)
         << "  um[3]=" << um.at(3) << "\n\n";

    // --- UnorderedMultimap ---
    cout << "[UnorderedMultimap<int,int>]\n";
    UnorderedMultimap<int,int> umm;
    umm.insert({1,10}); umm.insert({1,20}); umm.insert({2,30});
    cout << "  size=" << umm.size() << "  count(1)=" << umm.count(1) << "\n\n";

    cout << "===== All containers OK =====\n";
    return 0;
}