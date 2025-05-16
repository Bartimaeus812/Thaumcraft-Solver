#include "obsidian.h"
#include "findcommons.h"

using namespace std;

int main() {
    string obsidian_path = "C:\\Users\\Danny\\Documents\\GitHub\\Thaumcraft-Solver\\Thaumcraft";
    Obsidian ob(obsidian_path, false);
    Network nodes(ob.getNodes());
    FindCommons fc(nodes);
//    fc.calculateDistances();
    fc.inputHistory("C:\\Users\\Danny\\Documents\\GitHub\\Thaumcraft-Solver\\history.txt");
    string input0, input1;
    int option;
    cout << "type \"exit\" to exit\n\n";
    cout << "Type two aspects\nExample: Ordo Herba\n";
    cin.clear();
    while (input0!="exit") {
        cout << "? ";
        cin >> input0;
        if (input0!="exit") {
            cin >> input1;
            fc.oracle(input0,input1);
        }
    }
}
