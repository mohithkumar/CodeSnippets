// STL-like generic Queue container using single-linked list

template<class T>
struct QueueNode
{
    T data;
    QueueNode* next;

  public:
    explicit QueueNode(T& d) : data(d), next(NULL) {}
    ~QueueNode() { next = NULL; }
};

// Elements are inserted to the back of the Q and removed from the front
// Front (Pop) -- -- -- -- -- -- Back (Push)
// Upon insertion, Front remains fixed while Back gets incremented
// Upon removal, Front gets incremented while Back remains fixed
template<class T>
class Queue
{
  public:
    Queue();
    ~Queue();
    void push(T& e);
    void pop();
    T& front();
    T& back();
    bool empty() const;
    size_t size() const;

  private:
    QueueNode<T>* frontEl;
    QueueNode<T>* backEl;

    size_t sSize;
};

template<class T>
Queue<T>::Queue() : frontEl(NULL), backEl(NULL), sSize(0)
{
}

template<class T>
Queue<T>::~Queue()
{
    while (frontEl != NULL)
    {
        QueueNode<T>* temp = frontEl;
        frontEl = frontEl->next;
        delete temp;
    }
    sSize = 0;
}

template<class T>
void Queue<T>::push(T& e)
{
    QueueNode<T>* p = new QueueNode<T>(e);
    if(frontEl == NULL)
        frontEl = p;
    else
        backEl->next = p;
    backEl = p;
    ++sSize;
}

template<class T>
void Queue<T>::pop()
{
    if (frontEl != NULL)
    {
        QueueNode<T>* temp = frontEl;
        frontEl = frontEl->next;
        delete temp;
        --sSize;
    }
}

template<class T>
T& Queue<T>::front()
{
    QueueNode<T>* p = frontEl;
    if (frontEl != NULL)
    {
        return p->data;
    }
}

template<class T>
T& Queue<T>::back()
{
    QueueNode<T>* p = backEl;
    if (backEl != NULL)
    {
        return p->data;
    }
}

template<class T>
bool Queue<T>::empty() const
{
    return ((frontEl == NULL) || (backEl == NULL));
}

template<class T>
size_t Queue<T>::size() const
{
    return sSize;
}

// Posted 12th March 2013 by Mohith Suryanarayan

