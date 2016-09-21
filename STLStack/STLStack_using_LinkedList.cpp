// STL-like generic Stack container using Linked List
// Program:
 
template<class T>
struct StackNode
{
    T data;
    StackNode* next;

  public:
    explicit StackNode(T& d) : data(d), next(NULL) {}
    ~StackNode() { next = NULL; }
};


template<class T>
class Stack
{
  public:
    Stack();
    ~Stack();
    void push(T& e);
    void pop();
    T& top();
    bool empty() const;
    size_t size() const;

  private:
    StackNode<T>* topEle;
    size_t sSize;
};


template<class T>
Stack<T>::Stack() : topEle(NULL), sSize(0)
{
}


template<class T>
Stack<T>::~Stack()
{
    while (topEle != NULL)
    {
        StackNode<T>* temp = topEle;
        topEle = topEle->next;
        delete temp;
    }
    sSize = 0;
}


template<class T>
void Stack<T>::push(T& e)
{
    StackNode<T>* p = new StackNode<T>(e);
    if(topEle != NULL)
    {
        p->next = topEle;
    }
    topEle = p;
    ++sSize;
}


template<class T>
void Stack<T>::pop()
{
    if (topEle != NULL)
    {
        StackNode<T>* temp = topEle;
        topEle = topEle->next;
        delete temp;
        --sSize;
    }
}


template<class T>
T& Stack<T>::top()
{
    StackNode<T>* p = topEle;
    if (topEle != NULL)
    {
        return p->data;
    }
}


template<class T>
bool Stack<T>::empty()
{
    return (topEle == NULL);
}


template<class T>
size_t Stack<T>::size() const
{
    return sSize;
}

