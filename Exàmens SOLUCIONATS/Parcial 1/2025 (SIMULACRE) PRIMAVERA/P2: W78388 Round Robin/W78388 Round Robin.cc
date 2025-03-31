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