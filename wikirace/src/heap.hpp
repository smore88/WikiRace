#include <cstddef>

template <class T, class Compare>
class heap;

template <class T, class Compare>
heap<T, Compare>::heap()
{
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems) 
{
    _elems.assign(elems.begin(), elems.end());
    for (unsigned int i_plus_one = parent(_elems.size() - 1) + 1; i_plus_one >= 1; --i_plus_one) {
        heapifyDown(i_plus_one - 1);
    }

}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    if (empty()) {
        return T();
    }

    T highest = _elems[0];
    std::swap(_elems[0], _elems[_elems.size() - 1]);
    _elems.pop_back();
    heapifyDown(0);
    
    return highest;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    if (empty()) {
        return T();
    }

    return _elems[0];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    _elems.push_back(elem);
    heapifyUp(_elems.size() - 1);
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t & idx, const T& elem)
{
    _elems[idx] = elem;
    if (higherPriority(_elems[idx], _elems[parent(idx)])) {
        heapifyUp(idx);
    } else {
        heapifyDown(idx);
    }
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    return _elems.empty();
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    return 0;
}


template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    return (2 * currentIdx) + 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    return (2 * currentIdx) + 2;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    if (currentIdx == 0) {
        return 0;
    }

    return (currentIdx - 1) / 2;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    return leftChild(currentIdx) < _elems.size();
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    if (rightChild(currentIdx) >= _elems.size()) {
        return leftChild(currentIdx);
    }

    if (higherPriority(_elems[leftChild(currentIdx)], _elems[rightChild(currentIdx)])) {
        return leftChild(currentIdx);
    }
    return rightChild(currentIdx);
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    if (hasAChild(currentIdx)) {
        int swapping_child = maxPriorityChild(currentIdx);
        if (!higherPriority(_elems[currentIdx], _elems[swapping_child])) {
            std::swap(_elems[currentIdx], _elems[swapping_child]);
            heapifyDown(swapping_child);
        }
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}