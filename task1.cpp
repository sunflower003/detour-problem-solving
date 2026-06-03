/* Solve using stl sequence container list:
Given an initial commute route and a sequence of these traffic updates, output the final sequence of roads the user will take.
​Connection to std::list: If this were a std::vector, inserting a 10-road detour in the middle of a 100-road trip would require
 shifting 50+ elements backward. A std::list can "splice" the detour in instantly
*/

#include <iostream>
#include <list>
#include <string>
#include <limits>
using namespace std;

class RoutePlanner {
private:
    list<string> route;
public:
    RoutePlanner() {
        int num_roads = 0;
        cout << "=== Route Initialization ===\n";
        cout << "Enter the number of roads in your initial route: ";
        cin >> num_roads;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        for (int i = 0; i < num_roads; ++i) {
          string road;
            cout << "Enter name for road #" << (i + 1) << ": ";
            getline(cin, road);
            route.push_back(road);
        }
       cout << "-> Initial route saved successfully!\n";
     cout << "===================\n\n";
    }
    void applyDetour(const string& blocked_road, const list<string>& detour) {
        auto it = route.begin();

        while (it != route.end()) {
            if (*it == blocked_road) {
                break;
            }
            ++it;
        }
        if (it != route.end()) {
            route.insert(it, detour.begin(), detour.end());
            route.erase(it);
            cout << "\n[Traffic Alert] Successfully routed around '" << blocked_road << "'.\n";
        } else {
            cout << "\n[Notice] Road '" << blocked_road << "' not found in current route. No detour needed.\n";
        }
    }
    void printRoute() const {
        if (route.empty()) {
            cout << "Route is empty.\n";
            return;
        }

       cout << "Current Route:\n";
        for (auto it = route.begin(); it != route.end(); ++it) {
         cout << "[ " << *it << " ]";
            if (next(it) != route.end()) {
                cout << " -> ";
            }
        }
       cout << "\n\n";
    }
};

int main() {
    RoutePlanner my_commute;
    my_commute.printRoute();
    string incident;
    cout << "Enter the blocked road to avoid: ";
    getline(cin, incident);
    int num_detour_roads = 0;
    cout << "How many roads are in the detour? ";
    cin >> num_detour_roads;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    list<string> detour_roads;
    for (int i = 0; i < num_detour_roads; ++i) {
        string detour_road;
        cout << "Enter detour road #" << (i + 1) << ": ";
        getline(cin, detour_road);
        detour_roads.push_back(detour_road);
    }
my_commute.applyDetour(incident, detour_roads);
    my_commute.printRoute();

    return 0;
}
