#include "evaluatePrefix.hh"

typedef BinTree<string> BT;

int main()
{
    string format;
    getline(cin, format);
    BinTree<string> t;
    t.setInputOutputFormat(format=="INLINEFORMAT"?  BT::INLINEFORMAT  :  BT::VISUALFORMAT);
    int n;
    while (cin >> t and not t.empty() and cin >> n) {
        string p;
        for (int repetitions = 0; repetitions < 500; repetitions++)
            p = evaluatePrefix(t, n);
    	cout << p << endl;
        cin.ignore();
  	}
}