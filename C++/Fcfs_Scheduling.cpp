#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::get;
using std::left;
using std::make_tuple;
using std::priority_queue;
using std::rand;
using std::srand;
using std::tuple;
using std::unordered_set;
using std::vector;

template <typename S, typename T, typename E>
bool sortcol(tuple<S, T, E>& t1, tuple<S, T, E>& t2){
	if(get<1>(t1) < get<1>(t2)) {
		return true;
	} else if(get<1>(t1) == get<1>(t2) && get<0>(t1) < get<0>(t2)) {
		return true;
	}
	return false;
}
template <typename S, typename T, typename E>
class Compare {
	public:
		bool operator()(tuple<S, T, E, double, double, double>& t1, tuple<S, T, E, double, double, double>& t2) {
			if(get<1>(t2) < get<1>(t1)) {
				return true;
			} else if(get<1>(t2) == get<1>(t1)) {
				return get<0>(t2) < get<0>(t1);
			}
			return false;
		}
};
template <typename S, typename T, typename E>
class FCFS{
	priority_queue<tuple<S, T, E, double, double, double>, vector<tuple<S, T, E, double, double, double>>, Compare<S, T, E>> schedule;
	vector<tuple<S, T, E, double, double, double>> result;
	unordered_set<S> idList;
	public:
		void addProcess(S id, T arrival, E burst) {
			if(idList.find(id) == idList.end()) {
				tuple<S, T, E, double, double, double> t = make_tuple(id, arrival, burst, 0, 0, 0);
				schedule.push(t);
				idList.insert(id);
			}
		}
		vector<tuple<S, T, E, double, double, double>> scheduleForFcfs() {
			double timeElapsed = 0;
			while(!schedule.empty()) {
				tuple<S, T, E, double, double, double> cur = schedule.top();
				if(get<1>(cur) > timeElapsed) {
					timeElapsed += get<1>(cur) - timeElapsed;
				}
				timeElapsed += get<2>(cur);
				get<3>(cur) = timeElapsed;
				get<4>(cur) = get<3>(cur) - get<1>(cur);
				get<5>(cur) = get<4>(cur) - get<2>(cur);
				result.push_back(cur);
				schedule.pop();
			}
			return result;
		}
		void printResult() {
			cout << "Status of all the proceses post completion is as follows:" << endl;
			cout << std::setw(17) << left << "Process ID" << std::setw(17) << left << "Arrival Time" << std::setw(17) << left << "Burst Time" << std::setw(17) << left << "Completion Time" << std::setw(17) << left << "Turnaround Time" << std::setw(17) << left << "Waiting Time" << endl;
			for(size_t i{}; i < result.size(); i++) {
				cout << std::setprecision(2) << std::fixed << std::setw(17) << left
                 	<< get<0>(result[i]) << std::setw(17) << left
                 	<< get<1>(result[i]) << std::setw(17) << left
                 	<< get<2>(result[i]) << std::setw(17) << left
                 	<< get<3>(result[i]) << std::setw(17) << left
                 	<< get<4>(result[i]) << std::setw(17) << left
                 	<< get<5>(result[i]) << endl;
			}
		}
};
template <typename S, typename T, typename E>
vector<tuple<S, T, E, double, double, double>> get_final_status(vector<tuple<uint32_t, uint32_t, uint32_t>> input) {
	sort(input.begin(), input.end(), sortcol<S, T, E>);
	vector<tuple<S, T, E, double, double, double>> result(input.size());
	double timeElapsed = 0;
	for(size_t i{}; i < input.size(); i++) {
		T arrival = get<1>(input[i]);
		E burst = get<2>(input[i]);
		if(arrival > timeElapsed) {
			timeElapsed += arrival - timeElapsed;
		}
		timeElapsed += burst;
		double completion = timeElapsed;
		double turnaround = completion - arrival;
		double waiting = turnaround - burst;
		get<0>(result[i]) = get<0>(input[i]);
		get<1>(result[i]) = arrival;
		get<2>(result[i]) = burst;
		get<3>(result[i]) = completion;
		get<4>(result[i]) = turnaround;
		get<5>(result[i]) = waiting;
	}
	return result;
}
static void test() {
	for(int i{}; i < 1000; i++) {
		srand(time(nullptr));
		uint32_t n = 1 + rand() % 1000;
		FCFS<uint32_t, uint32_t, uint32_t> readyQueue;
		vector<tuple<uint32_t, uint32_t, uint32_t>> input(n);
		for(uint32_t i{}; i < n; i++) {
			get<0>(input[i]) = i;
			srand(time(nullptr));
			get<1>(input[i]) = 1 + rand() % 10000;
			srand(time(nullptr));
			get<2>(input[i]) = 1 + rand() % 10000;
		}
		for(uint32_t i{}; i < n; i++) {
			readyQueue.addProcess(get<0>(input[i]), get<1>(input[i]), get<2>(input[i]));
		}
		vector<tuple<uint32_t, uint32_t, uint32_t, double, double, double>> res = get_final_status<uint32_t, uint32_t, uint32_t>(input);
		assert(res == readyQueue.scheduleForFcfs());
	}
	cout << "All the tests have successfully passed!" << endl;
}
int main() {
	test();
	return 0;
}