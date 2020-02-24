#include <vector>
#include <set>
using namespace std;

/* The Main Priority Queue Interface. */

class PQueue {
  public:
    virtual ~PQueue() {};
    virtual void    Push(double d) = 0;
    virtual double  Pop()          = 0;
    virtual int     Size()         = 0;
    virtual bool    Empty()        = 0;
    virtual void    Print()        = 0;
};

/* PQueueSet: Implementing the priority 
   queue with a multiset */

class PQueueSet : public PQueue {
  public:
    void    Push(double d);
    double  Pop();
    int     Size();
    bool    Empty();
    void    Print();

    PQueueSet();
  protected:
    multiset <double> elements;
};

/* PQueueHeap: Implementing the priority 
   queue with a binary heap.  You'll note
   that there is a second constructor
   here that creates the priority queue
   from a vector of doubles. */

class PQueueHeap : public PQueue {
  public:
    void    Push(double d);
    double  Pop();
    int     Size();
    bool    Empty();
    void    Print();

    PQueueHeap();
    PQueueHeap(vector <double> &init);
  protected:
    vector <double> h;
    void Percolate_Down(int index);
};
