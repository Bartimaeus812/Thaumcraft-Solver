#include "obsidian.h"
#include "findcommons.h"

using namespace std;

int main() {
    string input0, input1;
    int option0 = 1, option1;
    cout << "0: Load from file\n1: Reload and save\n? ";
    cin >> option1;
    Obsidian* ob;
    if (option1==1) {
        ob = new Obsidian("C:\\Users\\Danny\\Documents\\GitHub\\Thaumcraft-Solver\\Thaumcraft", false);
        ob->fileOutput("C:\\Users\\Danny\\Documents\\GitHub\\Thaumcraft-Solver\\network.txt");
    } else {
        ob = new Obsidian("C:\\Users\\Danny\\Documents\\GitHub\\Thaumcraft-Solver\\network.txt", true);
    }
    Network nodes(ob->getNodes());
    FindCommons fc(nodes);
    if (option1==1) {
        fc.calculateDistances();
        fc.outputHistory("C:\\Users\\Danny\\Documents\\GitHub\\Thaumcraft-Solver\\history.txt");
    } else {
        fc.inputHistory("C:\\Users\\Danny\\Documents\\GitHub\\Thaumcraft-Solver\\history.txt");
    }
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
