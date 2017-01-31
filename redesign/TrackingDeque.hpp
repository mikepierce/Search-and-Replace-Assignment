
// Mike Pierce
// TrackingDeque.hpp



#ifndef TRACKINGDEQUE_H
#define TRACKINGDEQUE_H

#include <deque>
#include <iostream>



// TrackingDeque class declaration
template <typename TYPE> class TrackingDeque : public std::deque<TYPE> {
    public:
        TrackingDeque();
        ~TrackingDeque();
        void push_back(const TYPE&);
        void push_back(TYPE&&);
        void push_front(const TYPE&);
        void push_front(TYPE&&);
    private:
        void setheld();
        unsigned held;
};

// TrackingDeque constructor
template <typename TYPE> TrackingDeque<TYPE>::TrackingDeque() 
: std::deque<TYPE>(), held(0) {
}

// TrackingDeque<TYPE> destructor
template <typename TYPE> TrackingDeque<TYPE>::~TrackingDeque() {
    std::cout << "--> " << held << " <--" << std::endl;
}

// Wrapping a selection of deque's member functions
template <typename TYPE> void TrackingDeque<TYPE>::push_back(const TYPE& T) 
    //{std::deque<TYPE>::push_back(T); /**/std::cerr << "  deck.push_back(" << T << ")" << std::endl;/**/ setheld();}
    {std::deque<TYPE>::push_back(T); setheld();}
template <typename TYPE> void TrackingDeque<TYPE>::push_back(TYPE&& T) 
    //{std::deque<TYPE>::push_back(T); /**/std::cerr << "  deck.push_back(" << T << ")" << std::endl;/**/ setheld();}
    {std::deque<TYPE>::push_back(T); setheld();}
template <typename TYPE> void TrackingDeque<TYPE>::push_front(const TYPE& T) 
    {std::deque<TYPE>::push_front(T); setheld();}
template <typename TYPE> void TrackingDeque<TYPE>::push_front(TYPE&& T) 
    {std::deque<TYPE>::push_front(T); setheld();}

// TrackingDeque<TYPE> setheld
template <typename TYPE> void TrackingDeque<TYPE>::setheld() {
    unsigned size = std::deque<TYPE>::size();
    held = ((size > held) ? size : held);
}




#endif /*TRACKINGDEQUE_H*/

