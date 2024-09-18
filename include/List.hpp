#pragma once

#include <cstddef>
#include <utility>
#include <vector>
namespace cpputil {

namespace list {

struct Void {};

template <typename T>
struct Node {
    Node() = default;
    Node(T&& value) {
        value = std::forward<T>(value);
    }
    T value;
    Node *nxt = nullptr;
    Node *pre = nullptr;
};

template <typename T>
class List {
  public:
    List(const List&) = delete;
    List& operator = (const List&) = delete;
    List(List&& list) {
        dummy_ = list.dummy_;
        size_ = list.size_;
        list.dummy_ = nullptr;
        list.size_ = 0;
    }
    List& operator = (List&& list) {
        dummy_ = list.dummy_;
        size_ = list.size_;
        list.dummy_ = nullptr;
        list.size_ = 0;
    }
    List() {
        dummy_ = new Node<T>();
        dummy_->nxt = dummy_;
        dummy_->pre = dummy_;
    }
    ~List() {
        std::vector<Node<T>*> nodes;
        nodes.reserve(size_ + 1);
        nodes.emplace_back(dummy_);
        for (auto i = dummy_->nxt; i != dummy_; i = i->nxt) {
            nodes.emplace_back(i);
        }
        for (auto x : nodes) {
            delete x;
        }
    }
    void pushFront(T&& value) {
        Node<T>* new_node = new Node<T>(std::forward<T>(value));
        new_node->nxt = dummy_->nxt;
        new_node->pre = dummy_;
        dummy_->nxt = new_node;
        if (dummy_->pre == dummy_) {
            dummy_->pre = new_node;
        }
        ++size_;
    }
    void pushBack(T&& value) {
        Node<T>* new_node = new Node<T>(std::forward<T>(value));
        new_node->pre = dummy_->pre;
        new_node->nxt = dummy_;
        dummy_->pre = new_node;
        if (dummy_->nxt == dummy_) {
            dummy_->nxt = new_node;
        }
        ++size_;
    }
    static void extract(Node<T>* node) {
        node->pre = node->nxt;
        node->nxt = node->pre;
    }
    size_t size() const {
        return size_;
    }
  private:
    Node<T>* dummy_;
    size_t size_;
};

} // list

} // cpputil