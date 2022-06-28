//
//  Oğuz Akın
//  22002893

#ifndef CS201_HW4_INTERVAL_H
#define CS201_HW4_INTERVAL_H


class Interval {
public:
    explicit Interval(int start = 0, int end = 0) {
        this->start = start;
        this->end = end;
    }
    int start,end;
};


#endif //CS201_HW4_INTERVAL_H
