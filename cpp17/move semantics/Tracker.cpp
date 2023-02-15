#include <iostream>

class Tracker
{
public:
    Tracker() : id(s_id++) {
        std::cout << id << ": " << "constructed\n";
    }

    ~Tracker() {
        std::cout << id << ": " << "destroyed\n";
    }

    Tracker(const Tracker &o) : id(s_id++) {
        std::cout << id << ": " << "copy constructed from " << o.id << "\n";
    }

    Tracker(Tracker &&o) : id(o.id+1) {
        std::cout << id << ": " << "move constructed from " << o.id << "\n";
    }

    Tracker& operator=(const Tracker &o) {
        id = s_id++;
        std::cout << id << ": " << "copy assigned from " << o.id << "\n";
        return *this;
    }

    Tracker& operator=(Tracker &&o) {
        id = s_id++;
        std::cout << id << ": " << "move assigned from " << o.id << "\n";
        return *this;
    }
private:
    unsigned id;
    static unsigned s_id;
};

unsigned Tracker::s_id = 0;

//--- F {
void f_byvalue(Tracker t) {
    Tracker copy = t;
}

void f_byref(Tracker &t) {
    Tracker copy = t;
}

void f_byrref(Tracker &&t) {
    Tracker copy = t;
}

void f_byrref_move(Tracker &&t) {
    Tracker move = std::move(t);
}
//} ----------------------------------------------------------------------------

//--- get_a_tracker {
Tracker get_a_tracker_named() {
    Tracker t;
    return t;
}

Tracker get_a_tracker_anonymous() {
    return Tracker();
}

Tracker get_a_tracker_named_move() {
    Tracker t;
    return std::move(t);
}
//} ----------------------------------------------------------------------------

//--- tracker_in_a_jar {
std::pair<Tracker, int> tracker_in_a_jar0() {
    Tracker t;
    return {t, 0};
}

std::pair<Tracker, int> tracker_in_a_jar1() {
    Tracker t;
    return {std::move(t), 1};
}

std::pair<Tracker, int> tracker_in_a_jar2() {
    std::pair<Tracker, int> t {{}, 2};
    return t;
}
//} ----------------------------------------------------------------------------

int main()
{
    {
        //Tracker t;

        // Try out each variant, one by one.

        //f_byvalue(t);
        //f_byref(t);
        //f_byrref(t); // fails to compile
        //f_byrref(std::move(t)); // !!
        //f_byrref_move(std::move(t));

        // a lone std::move() ... does it move?
        //std::move(t);
    }

    // Try out each variant, one by one.
    // Did something surprise you ?

    //get_a_tracker_anonymous();
    //get_a_tracker_named();
    //get_a_tracker_named_move();

    //auto res = tracker_in_a_jar0();
    //auto res = tracker_in_a_jar1();
    //auto res = tracker_in_a_jar2(); // !!

    {
        //std::vector<Tracker> vec;
        
        // Try out push elements into the vector, one by one.
        
        //vec.push_back(Tracker());
        //vec.push_back(Tracker());
        //vec.push_back(Tracker());
        
        // What is the difference without declaring the move constructor?
    }
}
