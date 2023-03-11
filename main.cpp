#include <iostream>
#include <vector>

using namespace std;

struct Item {
    double weight;
    double value;
};

double goal(const vector<Item> &item_list) {
    double value = 0;
    for (auto item: item_list) {
        value += item.value / item.weight;
    }

    return value;
}

vector<Item> brute_force(const vector<Item> &item_list, int knapsack_size) {
//    for
//    return item_list;
}

int main() {
    int knapsack_size = 3;
    vector<Item> knapsack;
    vector<Item> item_list = {
            {17, 0.1},
            {5,  11},
            {9,  20},
            {3,  3},
            {10, 5.5},
            {1,  1.3},
            {3,  12},
    };

    knapsack = brute_force(item_list, knapsack_size);

    cout << goal(knapsack);
}

