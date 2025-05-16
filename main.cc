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
    int option0 = 1, option1;
    cout << "Forms:\n0: exits\n1 number_of_nodes node0 node1 ...: finds potential common nodes\n2 nodeA nodeB: lists fastest paths between them\n";
    cin.clear();
    while (option0>0) {
        cout << "\n? ";
        cin >> option0;
        try {
            if (option0==1) {
                cin >> option1;
                for (int i = 0; i<option1; i++) {
                    cin >> input1;
                    fc.addNode(input1);
                }
                fc.calculateCommons();
                fc.displayCommons();
                fc.clearNodes();
            } else if (option0==2) {
                cin >> input0 >> input1;
                fc.oracle(input0, input1);
            }
        } catch (AspectSpelling e) {
            cout << "Spelling Error\n";
            cin.clear();
        }
    }
}
