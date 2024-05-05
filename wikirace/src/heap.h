#pragma once

#include <iostream>
#include <vector>

template <class T, class Compare = std::less<T>>
class heap
{
  public:
    // Empty heap constructor
    heap();

    // Construct heap from vector
    heap(const std::vector<T>& elems);

    // Removes the element with highest priority according to the higherPriority() functor.
    T pop();

    // Returns, but does not remove, the element with highest priority.
    T peek() const;

    // Inserts the given element into the heap, restoring the heap property after the insert as appropriate.
    void push(const T& elem);

    // Updates the element at the provided index of the heap array. Restoring the heap property after the update as appropriate.
    void updateElem(const size_t & idx, const T& elem);

    bool empty() const;

    // Gets the vector of elems
    void getElems(std::vector<T> & heaped) const;

  private:
    // 0-based heap
    std::vector<T> _elems;

    /**
     * Comparison functor. This functor takes two parameters and returns true
     * if the first parameter has a higher priority than the second.
     *
     * Compare is a template parameter and defaults to std::less, which creates
     * a min-heap. So, if `T = int` and `a = 3` and `b = 5`,
     * `higherPriority(a, b) = true` (`a < b`, so `a` has higher priority) and
     * `higherPriority(b, a) = false` (`b > a`, so `b` has lower priority)
     */
    Compare higherPriority;

    size_t root() const;

    size_t leftChild(size_t currentIdx) const;

    size_t rightChild(size_t currentIdx) const;

    size_t parent(size_t currentIdx) const;

    bool hasAChild(size_t currentIdx) const;

    size_t maxPriorityChild(size_t currentIdx) const;

    void heapifyDown(size_t currentIdx);

    void heapifyUp(size_t currentIdx);
};
#include "heap.hpp"
