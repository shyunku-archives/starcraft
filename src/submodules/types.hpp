#pragma once
#include <unordered_map>
#include <set>
#include <vector>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/sequenced_index.hpp>

using namespace boost::multi_index;
using namespace std;

struct Dimension {
	double w;
	double h;
};

struct Bounds {
	double x;
	double y;
	double w;
	double h;

	Bounds() : x(0), y(0), w(0), h(0) {}
	Bounds(double w, double h) : x(0), y(0), w(w), h(h) {}
	Bounds(double x, double y, double w, double h) : x(x), y(y), w(w), h(h) {}
};

class Cardinal {
public:
	double _top;
	double _bottom;
	double _left;
	double _right;

	Cardinal();
	Cardinal(double value);
	Cardinal(double top, double bottom);
	Cardinal(double top, double right, double bottom, double left);
	Cardinal all(double value);
	Cardinal vertical(double value);
	Cardinal horizontal(double value);
	Cardinal top(double value);
	Cardinal bottom(double value);
	Cardinal left(double value);
	Cardinal right(double value);
};

template <typename Key, typename Value>
struct KeyValuePair {
	Key key;
	Value value;
};

template <typename Key, typename Value>
class SequencedHashMap {
private:
	unordered_map<Key, Value> map;
	set<Key> keys;
public:
	SequencedHashMap() {}

	void set(Key key, Value value) {
		map.insert({ key, value });
		keys.insert(key);
	}

	void remove(Key key) {
		map.erase(key);
		keys.erase(key);
	}

	Value get(Key key) {
		return map[key];
	}

	vector<Value> getItems() {
		vector<Value> result;
		for (Key key : keys) {
			result.push_back({ key, map[key] });
		}
		return result;
	}	
};