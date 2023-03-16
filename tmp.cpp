//
// Created by adam on 11.03.23.
//
#include <iostream>
#include <array>
#include <random>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <numeric>
#include <memory>

using vec2d = std::array<double, 2>;

vec2d operator-(vec2d a, vec2d b) { return {a[0] - b[0], a[1] - b[1]}; }

double len(vec2d a) { return std::sqrt(a[0] * a[0] + a[1] * a[1]); }

using problem_t = std::vector<vec2d>;

class solution_t : public std::vector<int> {
public:
    std::shared_ptr<problem_t> problem;

    solution_t(std::shared_ptr<problem_t> problem_) : problem(problem_) {}

    double goal() {
        double sum_distance = 0;
        for (int i = 0; i < size(); i++) {
            auto &p = *problem;
            auto &t = *this;
            sum_distance += len(p[t[i]] - p[t[(i + 1) % size()]]);
        }
        return sum_distance;
    }
};

std::ostream &operator<<(std::ostream &o, const vec2d v) {
    o << "[ ";
    for (auto e: v) o << e << " ";
    o << "]";
    return o;
}

std::ostream &operator<<(std::ostream &o, const problem_t v) {
    o << "{ ";
    for (auto e: v) o << e << " ";
    o << "}";
    return o;
}

std::ostream &operator<<(std::ostream &o, const solution_t v) {
    o << "{ ";
    for (auto e: v) o << e << " ";
    o << "}";
    return o;
}

std::random_device rd;
std::mt19937 rgen(rd());

solution_t random_modify(solution_t current_point) {
    using namespace std;
    uniform_int_distribution<int> distr(0, current_point.size() - 1);
    int a = distr(rgen);
    swap(current_point[a], current_point[(a + 1) % current_point.size()]);
    return current_point;
}

solution_t best_neighbour(solution_t current_point) {
    using namespace std;
    std::vector<solution_t> neighbours;
    for (int i = 0; i < current_point.size(); i++) {}
    return current_point;
}

solution_t brute_force(solution_t start_point) {
    auto solution = start_point;
    for (int i = 0; i < solution.size(); i++) { solution[i] = i; }
    auto best_solution = solution;
    int i = 0;
    do {
        if (solution.goal() <= best_solution.goal()) {
            best_solution = solution;
            std::cout << (i++) << " " << solution << "  " << solution.goal() << " *** " << best_solution << "  "
                      << best_solution.goal() << std::endl;
        }
    }
    while (std::next_permutation(solution.begin(), solution.end()));
    return best_solution;
}

solution_t random_hillclimb(solution_t solution) {
    for (int i = 0; i < 5040; i++) {
        auto new_solution = random_modify(solution);
        if (new_solution.goal() <= solution.goal()) {
            solution = new_solution;
            std::cout << i << " " << solution << "  " << solution.goal() << std::endl;
        }
    }
    return solution;
}

solution_t shortest_distance(solution_t solution) {
    solution_t result = solution;
    auto &problem = *solution.problem;
    solution.erase(solution.begin());
    for (int i = 1; i < result.size(); i++) {
        auto found = std::min_element(solution.begin(), solution.end(), [&](auto a, auto b) {
            double dist_a = len(problem[result[i - 1]] - problem[a]);
            double dist_b = len(problem[result[i - 1]] - problem[b]);
            return dist_a < dist_b;
        });
        result[i] = *found;
        solution.erase(found);
    }
    return result;
}

int main2() {
    using namespace std;
    problem_t tsp_problem = {{1.3, 1},
                             {2.4, 1},
                             {1.5, 2},
                             {3.1, 1},
                             {3.2, 7},
                             {3.3, 9},
                             {1.4, 4}};
    solution_t solution(make_shared<problem_t>(tsp_problem));
    for (int i = 0; i < tsp_problem.size(); i++) solution.push_back(i);
    std::shuffle(solution.begin(), solution.end(), rgen);
    std::cout << tsp_problem << std::endl;
    std::cout << solution << "Start:  " << solution.goal();
}