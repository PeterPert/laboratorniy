#pragma once


template<typename T1, typename T2>
class Pair {
    private:
        T1 first;
        T2 second;
        
    public:
        Pair(T1 f, T2 s) : first(f), second(s) {}
        
        T1 getFirst() const {return first;}
        T2 getSecond() const {return second;}
        
        void setFirst(T1 f) {first = f;}
        void setSecond(T2 s) {second = s;}
};