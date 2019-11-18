/************************************************************************************
 * MIT License                                                                      *
 *                                                                                  *
 * Copyright (c) 2019 Alok Nigam                                                    *
 *                                                                                  *
 * Permission is hereby granted, free of charge, to any person obtaining a copy     *
 * of this software and associated documentation files (the "Software"), to deal    *
 * in the Software without restriction, including without limitation the rights     *
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell        *
 * copies of the Software, and to permit persons to whom the Software is            *
 * furnished to do so, subject to the following conditions:                         *
 *                                                                                  *
 * The above copyright notice and this permission notice shall be included in all   *
 * copies or substantial portions of the Software.                                  *
 *                                                                                  *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR       *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,         *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE      *
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER           *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,    *
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE    *
 * SOFTWARE.                                                                        *
 ************************************************************************************/

/* Copy Constructor */
template <typename T>
Tree<T>::Tree(const Tree<T>& to_copy) {
    m_root = new Node(*to_copy);
}

/* Move Constructor */
template <typename T>
Tree<T>::Tree(Tree<T>&& to_move) noexcept {
    m_root = to_move.m_root;
    to_move = nullptr;
}

template <typename T>
Tree<T>& Tree<T>::operator=(const Tree<T>& to_copy) {
    if(this == &to_copy)
        return *this;
    m_root = new Node(*to_copy.root);
    return *this;
}

/* Move Assignment */
template <typename T>
Tree<T>& Tree<T>::operator=(Tree<T>&& to_move) noexcept {
    m_root = to_move.m_root;
    to_move = nullptr;
    return *this;
}

template <typename T>
Tree<T>::~Tree() {
    delete m_root;
}

template <typename T>
void Tree<T>::insert(const T t) {
    Node* n = new Node(t);
    binaryInsert(m_root, n);
}

template <typename T> template <typename K>
typename Tree<T>::iterator Tree<T>::search(const K& key) {
    Node* p = binarySearch(m_root, key);
    if(p)
        return iterator(p);
    return iterator();
}

template <typename T>
T Tree<T>::iterator::operator*() const {
    if(m_st.empty())
        throw std::underflow_error("iterator is empty");
    return m_st.top()->data;
}

template <typename T>
bool Tree<T>::iterator::operator==(const iterator& iter) const {
    return this->m_st == iter.m_st;
}

template <typename T>
bool Tree<T>::iterator::operator!=(const iterator& iter) const {
    return !(*this == iter);
}

template <typename T>
T Tree<T>::iterator::operator->() const {
    if(m_st.empty())
        throw std::underflow_error("iterator is empty");
    return m_st.top()->data;
}

template <typename T>
typename Tree<T>::iterator& Tree<T>::iterator::operator++() {
    if(!m_st.empty()) {
        Node* curr = this->m_st.top()->right;
        this->m_st.pop();
        while(curr) {
            this->m_st.push(curr);
            curr = curr->left;
        }
    }
    return *this;
}

template <typename T>
typename Tree<T>::iterator Tree<T>::begin() const {
    iterator iter;
    Node* curr = m_root;
    while(curr) {
        iter.m_st.push(curr);
        curr = curr->left;
    }
    return iter;
}

template <typename T>
typename Tree<T>::iterator Tree<T>::end() const {
    static iterator iter;
    return iter;
}

/* Copy Constructor */
template<typename T>
Tree<T>::Node::Node(const Tree<T>::Node& to_copy) {
    if(std::is_pointer<T>::value)
        data = new std::remove_pointer<T>(*to_copy.data);
    else
        data = to_copy.data;

    left = to_copy.left ? new Node(*to_copy.left) : nullptr;
    right = to_copy.right ? new Node(*to_copy.right) : nullptr;
}

/* Move Constructor */
template<typename T>
Tree<T>::Node::Node(Tree<T>::Node&& to_move) noexcept {
    data = to_move.data;
    left = to_move.left;
    right = to_move.right;

    if(std::is_pointer<T>::value) {
        to_move.data = nullptr;
    }
    to_move.left = nullptr;
    to_move.right = nullptr;
}

template<typename T>
Tree<T>::Node::~Node() {
    delete left;
    delete right;
}

template<typename T>
typename Tree<T>::Node& Tree<T>::Node::operator=(const Tree<T>::Node& to_copy) {
    if(this == &to_copy)
        return *this;

    if(std::is_pointer<T>::value)
        data = new std::remove_pointer<T>(*to_copy.data);
    else
        data = to_copy.data;

    left = to_copy.left ? new Node(*to_copy.left) : nullptr;
    right = to_copy.right ? new Node(*to_copy.right) : nullptr;

    return *this;
}

/* Move Assignment */
template<typename T>
typename Tree<T>::Node& Tree<T>::Node::operator=(Tree<T>::Node&& to_move) noexcept {
    data = to_move.data;
    left = to_move.left;
    right = to_move.right;

    if(std::is_pointer<T>::value) {
        to_move.data = nullptr;
    }
    to_move.left = nullptr;
    to_move.right = nullptr;

    return *this;
}

/** @cond */
template <typename T>
static T& refObj(T& o) {return o;}
template <typename T>
static T& refObj(T* o) {return *o;}
/** @endcond */

template <typename T>
void Tree<T>::binaryInsert(Node*& root, const Node* data) {
    if(!root) {
        root = const_cast<Node*>(data);
        return;
    }
    if(refObj(root->data) > refObj(data->data))
        binaryInsert(root->left, data);
    else
        binaryInsert(root->right, data);
}

template <typename T> template <typename K>
typename Tree<T>::Node* Tree<T>::binarySearch(Node* root, K& key) const {
    if(!root)
        return nullptr;
    if(refObj(root->data) == key)
        return root;
    if(*root->data > key)
        return binarySearch(root->left, key);
    return binarySearch(root->right, key);
}
