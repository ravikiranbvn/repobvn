// referece: https://semblie.com/modern-c-in-embedded-development-strong-types-and-user-defined-literals/

#include <iostream>
#include <cmath>
#include <cstring>
// #include <chrono>

// using namespace std::chrono_literals;
using namespace std;

class Time {
private:
	float time_in_ms_;
public:
	explicit Time(float time_in_ms) : time_in_ms_(time_in_ms){}
	uint16_t get() { return time_in_ms_;}
};

class ConnL {
private:
	Time time_;
public:
	explicit ConnL(Time time) : time_(time.get()/0.625f){}
	Time & get() {return time_;}
};

class ConnP {
private:
	Time time_;
public:
	explicit ConnP(Time time) : time_(time.get()/0.625f){}
	Time & get() {return time_;}
};

int main()
{
// usage example 
// tBleStatus status = aci_gap_create_connection(ConnL(Time(80)), 
// ConnL(Time(120)), PUBLIC_ADDR, mac_addr, ConnP(Time(50)), ConnP(Time(60)), 0, SUPERV_TIMEOUT, ConnL(Time(10)), ConnL(Time(15))); 

	ConnL cl(Time(80));
	ConnP cp(Time(50));

	Time cl_time(cl.get());
	Time cp_time(cp.get());

	std::cout << cl_time.get() << " " << cp_time.get() << "\n";

	return 0;
}




// Time operator"" _min(float time) {
//     return Time(time*1000*60);
// }

// Time operator+(const Time& a, const Time& b) {
// 	return Time(a.get()+b.get());
// }

// void setAlarmIn(Time time); 

// setAlarmIn(5min+30s);
