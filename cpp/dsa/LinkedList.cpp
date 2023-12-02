
#include "LinkedList.hpp"
#include <iostream>

template <typename T> LinkedListItem<T>::LinkedListItem(T &data)
{
    data_ = data;
}

template <typename T>
std::shared_ptr<LinkedListItem<T> >
LinkedListItem<T>::get_next() const
{
    return next_;
}

template <typename T>
void
LinkedListItem<T>::set_next(std::shared_ptr<LinkedListItem<T> > next)
{
    next_ = next;
}

template <typename T>
T &
LinkedListItem<T>::get_data()
{
    return data_;
}

template <typename T> LinkedList<T>::LinkedList() {}

template <typename T>
void
LinkedList<T>::push(T &data)
{
    std::shared_ptr<LinkedListItem<T> > oldhead = head_;
    head_ = std::make_shared(LinkedListItem<T>(data));
    head_.set_next(oldhead);
}

template <typename T>
void
LinkedList<T>::insert(T &data, size_t index)
{
    if (index == 0)
    {
        auto oldhead = head_;
        head_ = std::make_shared<LinkedListItem<T> >(data);
        if (oldhead != nullptr)
        {
            head_->set_next(oldhead);
        }
        return;
    }
    std::shared_ptr<LinkedListItem<T> > p = head_;
    std::shared_ptr<LinkedListItem<T> > prev;
    for (size_t i = 0; i < index; i++)
    {
        prev = p;
        p = p->get_next();
    }
    std::shared_ptr<LinkedListItem<T> > li
        = std::make_shared<LinkedListItem<T> >(data);
    prev->set_next(li);
    prev->get_next()->set_next(p);
}

template <typename T>
void
LinkedList<T>::pop()
{
    head_ = head_->get_next();
}

template <typename T>
void
LinkedList<T>::remove(size_t index)
{
    if (index == 0)
    {
        return pop();
    }
    std::shared_ptr<LinkedListItem<T> > p = head_;
    std::shared_ptr<LinkedListItem<T> > prev;
    for (size_t i = 0; i < index; i++)
    {
        prev = p;
        p = p->get_next();
    }
    prev->set_next(p->get_next());
}

template <typename T>
ptrdiff_t
LinkedList<T>::find(const T &data) const
{
    ptrdiff_t rv = -1;
    for (std::shared_ptr<LinkedListItem<T> > p = head_; p != NULL;
         p = p->get_next())
    {
        rv++;
        if (data == p->get_data())
        {
            return rv;
        }
    }
    return -1;
}

template <typename T>
size_t
LinkedList<T>::size() const
{
    size_t rv = 0;
    for (std::shared_ptr<LinkedListItem<T> > p = head_; p != nullptr;
         p = p->get_next())
    {
        rv++;
    }
    return rv;
}

template <typename T>
T &
LinkedList<T>::get(size_t index) const
{
    std::shared_ptr<LinkedListItem<T> > p = head_;
    for (size_t i = 0; i < index; i++)
    {
        p = p->get_next();
    }
    return p->get_data();
}

template <typename T>
void
LinkedList<T>::reverse()
{
    // TODO
}

template <typename T>
std::ostream &
LinkedList<T>::print(std::ostream &out) const
{
    out << "[";
    size_t i = 0;
    for (std::shared_ptr<LinkedListItem<T> > p = head_; p != nullptr;
         p = p->get_next())
    {
        if (i > 0)
        {
            out << ", ";
        }
        out << p->get_data();
        i++;
    }
    return out << "]";
}

int
main(int argc, char **argv)
{
    LinkedList<std::string> l;
    for (int i = 0; i < argc; i++)
    {
        std::string arg = argv[i];
        l.insert(arg, i);
    }
    // XXX: could be std::print in c++ 23
    std::cout << "list:" << l << std::endl;
    //
    l.reverse();
    std::cout << "reversed:" << l << std::endl;
    //
    std::cout << "size: " << l.size() << std::endl;
    if (l.size() >= 2)
    {
        std::string second = l.get(1);
        std::cout << "second: " << second << std::endl;
        l.remove(1);
        std::cout << "removed: " << l << std::endl;
    }
}
