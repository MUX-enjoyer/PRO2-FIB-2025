#ifndef BINTREE_HH
#define BINTREE_HH

#include <cassert>
#include <memory>

namespace pro2 {

/**
 * @file BinTree.hh
 * @class BinTree
 *
 * @brief Una classe que representa un arbre binari.
 *
 * Un arbre binari pot estar buit, o contenir un valor de qualsevol tipus (`T`) així com dos
 * subarbres, `left` i `right`.
 *
 * Si un arbre binari està buit, el mètode `empty` retornarà `true`.
 *
 * Si no ho està, el seu valor es pot accedir amb el mètode `value`, i
 * ambdues branques amb els mètodes `left` i `right`, que retornen els subarbres.
 *
 * Exemple:
 * ```c++
 * BinTree<int> a; // arbre buit
 * BinTree<int> b(1); // arbre només amb un valor però amb les branques buides
 * BinTree<int> c(0, a, b); // arbre amb un 0 i `a` i `b` com a subbranques.
 * ```
 */
template <typename T>
class BinTree {
 private:
    /**
     * @brief Estructura que conté la informació del node
     *
     * Cada node té un valor i dos punters a les branques (si n'hi ha).
     * Com que cada punter pot ser `nullptr`, cadascuna de les branques pot estar buida.
     *
     * `std::shared_pointer` s'utilitza aquí perquè fa recompte de referències i
     * un `Node_` serà alliberat de la memòria un cop cap punter hi apunti.
     */
    struct Node_ {
        T                      value;
        std::shared_ptr<Node_> left;
        std::shared_ptr<Node_> right;

        Node_(const T& value, std::shared_ptr<Node_> left, std::shared_ptr<Node_> right)
            : value(value), left(left), right(right) {}
    };

    /**
     * @brief Punter al node de l'arbre
     */
    std::shared_ptr<Node_> pnode_;

    /**
     * @brief Construeix un arbre a partir d'un punter a node.
     *
     * Aquest constructor és privat per no exposar el punter.
     */
    BinTree(std::shared_ptr<Node_> pnode) : pnode_(pnode) {}

 public:
    /**
     * @brief Construeix un arbre buit. Θ(1).
     */
    BinTree() : pnode_(nullptr) {}

    /**
     * @brief Construeix un arbre com a còpia d'un altre arbre. Θ(1).
     *
     * @param t El `BinTree` del qual copiar.
     */
    BinTree(const BinTree& t) {
        pnode_ = t.pnode_;
    }

    /**
     * @brief Construeix un arbre amb un valor `x` i sense subarbres. Θ(1).
     *
     * @param value El valor a mantenir a l'arrel del nou arbre.
     */
    explicit BinTree(const T& value) {
        pnode_ = std::make_shared<Node_>(value, nullptr, nullptr);
    }

    /**
     * @brief Construeix un arbre amb un valor `x` i dos subarbres `left` i `right`. Θ(1).
     *
     * @param value El valor a mantenir a l'arrel del nou arbre.
     * @param left El `left` subarbre en el nou arbre.
     * @param right El `right` subarbre en el nou arbre.
     */
    explicit BinTree(const T& value, const BinTree& left, const BinTree& right) {
        pnode_ = std::make_shared<Node_>(value, left.pnode_, right.pnode_);
    }

    /**
     * @brief Assigna l'arbre `t` a aquest arbre, i retorna l'objecte mateix. Θ(1).
     *
     * @param other L'arbre a assignar (substituirà l'antic).
     */
    BinTree& operator=(const BinTree& other) {
        pnode_ = other.pnode_;
        return *this;
    }

    /**
     * @brief Retorna `true` si aquest arbre està buit, `false` en cas contrari. Θ(1).
     */
    bool empty() const {
        return pnode_ == nullptr;
    }

    /**
     * @brief Retorna el subarbre esquerre d'aquest arbre. Abort si està buit. Θ(1).
     *
     * @pre El `BinTree` no està buit.
     */
    BinTree left() const {
        assert(not empty());
        return BinTree(pnode_->left);
    }

    /**
     * @brief Retorna el subarbre dret d'aquest arbre. Abort si està buit. Θ(1).
     *
     * @pre El `BinTree` no està buit.
     */
    BinTree right() const {
        assert(not empty());
        return BinTree(pnode_->right);
    }

    /**
     * @brief Retorna el valor d'aquest arbre. Abort si està buit. Θ(1).
     *
     * @pre El `BinTree` no està buit.
     */
    const T& value() const {
        assert(not empty());
        return pnode_->value;
    }
};

}  // namespace pro2

#endif