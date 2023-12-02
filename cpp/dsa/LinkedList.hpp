
#include <memory>

template <typename T> class LinkedListItem;

template <typename T> class LinkedList
{
  public:
    LinkedList();

    std::shared_ptr<LinkedListItem<T> > get_head() const;

    void push(T &data);
    void insert(T &data, size_t index); // indices or iteratoreS?
    void pop();
    void remove(size_t index);
    ptrdiff_t find(const T &data) const;
    size_t size() const;
    T &get(size_t index) const;
    void reverse();
    std::ostream &print(std::ostream &out) const;

  private:
    std::shared_ptr<LinkedListItem<T> > head_;
};

template <typename T>
std::ostream &
operator<<(std::ostream &out, const LinkedList<T> &l)
{
    return l.print(out);
}

template <typename T> class LinkedListItem
{
  public:
    LinkedListItem(T &data);

    T &get_data();
    std::shared_ptr<LinkedListItem<T> > get_next() const;
    void set_next(std::shared_ptr<LinkedListItem<T> > next);

  private:
    T data_;
    std::shared_ptr<LinkedListItem<T> > next_;
};
