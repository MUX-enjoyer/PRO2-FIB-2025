#include <iostream>
#include <queue>
#include <sstream>
#include <string>
using namespace std;

/**
 * @brief Simula un algorisme "Round Robin" amb un vector de cues
 *
 * La funció itera circularment (és a dir, considerant l'element n-1 com l'inmediatament anterior al
 * 0) el vector de cues, i va afegint els elements que treu del capdavant de cada cua en una cua
 * resultat.
 *
 * @param  queues  Les cues d'entrada
 * 
 * @returns La cua resultant d'aplicar l'algorisme "Round Robin"
 */
queue<std::string> round_robin(vector<queue<std::string>>& queues) {
    queue<string> rr;
    while (!queues.empty()) {
        vector<queue<std::string>>::iterator it = queues.begin();
        while (it != queues.end()) {
            if (!it->empty()) {
                rr.push(it->front());
                it->pop();
                ++it;
            }
            else it = queues.erase(it);
        }
    }
    return rr;
}

queue<string> read_queue(string line) {
    queue<string> Q;
    string name;
    istringstream iss(line);
    while (iss >> name) {
        Q.push(name);
    }
    return Q;
}

bool read_queue_sequence(vector<queue<string>>& queues) {
    queues.clear();
    string line;
    while (getline(cin, line) && line != "---") {
        queues.push_back(read_queue(line));
    }
    return !queues.empty();
}

/**
 * @brief Aquesta funció *buida* la cua per poder mostrar-la per pantalla
 */
void show_queue(queue<string>& Q) {
    if (!Q.empty()) {
        cout << Q.front();
        Q.pop();
        while (!Q.empty()) {
            cout << ' ' << Q.front();
            Q.pop();
        }
    }
    cout << endl;
}

int main() {
    vector<queue<string>> queues;
    while (read_queue_sequence(queues)) {
        auto result = round_robin(queues);
        show_queue(result);
    }
}
