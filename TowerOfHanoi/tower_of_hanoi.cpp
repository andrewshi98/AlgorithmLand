#include <stdio.h>
#include <iostream>
#include <vector>
#include <stack>
#include <map>

using namespace std;

vector<stack<int>> tower;
map<int, int> loc_map;

void toh(int from, int to, int level);
void push(int location, int level);
void pop(int location);

int main()
{
    int size = 3;
    for (int i = 0; i < 3; i++) {
        stack<int> st;
        tower.push_back(st);
    }
    
    for (int i = size - 1; i >= 0; i -= 1) {
        push(0, i);
    }
    
    for (int i = size - 1; i >= 0; i--) {
        int level_loc = loc_map[i];
        toh(level_loc, 2, i);
    }

    return 0;
}

void pop(int location) {
    tower[location].pop();
}

void push(int location, int level) {
    tower[location].push(level);
    loc_map[level] = location;
}

int locate(int level) {
    return loc_map[level];
}

void toh(int from, int to, int level) {
    if (level != 0) {
        int stash_loc = 0;
        for (int i = 0; i < 3; i++) {
            if (from != i && to != i) {
                stash_loc = i;
            }
        }
        for (int i = level - 1; i >= 0; i--) {
            int location = locate(i);
            if (location != stash_loc) {
                toh(location, stash_loc, i);
            }
        }
    }
    // Otherwise, always available
    pop(from);
    push(to, level);
    printf("Moved %d from %d to %d.\n", level, from, to);
}
