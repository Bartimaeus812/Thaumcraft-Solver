#include "obsidian.h"
#include "findcommons.h"

using namespace std;

int main() {
    string obsidian_path = "C:\\Users\\Danny\\Documents\\GitHub\\Thaumcraft-Solver\\Thaumcraft";
    Obsidian ob(obsidian_path, false);
    Network nodes(ob.getNodes());
    FindCommons fc(nodes);
    fc.calculateDistances();
    fc.outputHistory("C:\\Users\\Danny\\Documents\\GitHub\\Thaumcraft-Solver\\history.txt");
    string input;
    int option;
    cout << "type \"exit\" to exit\n\n";
    cout << "options\n0: Herba\n1: Metallum\n2: Praecantatio\nType an aspect then a number\nExample: Ordo 2\n";
    cin.clear();
    while (input!="exit") {
        cout << "? ";
        cin >> input;
        if (input!="exit") {
            cin >> option;
            if (option==0) {
                fc.oracle(input,fc.tree::Herba);
            } else if (option==1) {
                fc.oracle(input,fc.tree::Metallum);
            } else if (option==2) {
                fc.oracle(input,fc.tree::Praecantatio);
            }
        }
    }
}
