//
// <author> ravi.has.kiran@gmail.com
// Copyright (c) 2023. All rights reserved!
//

// valgrind --leak-check=full --show-leak-kinds=all ./sbarber_v
// valgrind --tool=helgrind ./sbarber_v

#include <iostream>
#include <bits/stdc++.h>
#include "BarberShop.hpp"
#include "Barber.hpp"
#include "Customer.hpp"

using namespace std;
static constexpr std::uint8_t MAX_CUSTOMERS    = 100;
static constexpr std::uint8_t MAX_AVAIL_CHAIRS = 10;

int main() {
    BarberShop bShop(MAX_AVAIL_CHAIRS);
    Barber     barber(bShop);

    // customers
    std::vector<Customer*> customers;
    customers.reserve(MAX_CUSTOMERS);
    
    // create 
    for(size_t i=0; i<MAX_CUSTOMERS; i++) {
        customers.emplace_back(new Customer("customer" + std::to_string(i), std::ref(bShop)));
    }

    // clear
    for(auto &cust : customers) {
        delete cust;
    }

    return 0;
}