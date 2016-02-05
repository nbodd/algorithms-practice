//
//  linked_list.cpp
//  algorithms
//
//  Created by Nick on 2/3/16.
//  Copyright © 2016 Nick. All rights reserved.
//

#include <iostream>

using namespace std;

typedef int ListNodeType;

struct ListNode {
    ListNodeType data;
    shared_ptr<ListNode> next;
    
    ListNode(ListNodeType _data, shared_ptr<ListNode> ptr) :
        data(_data), next(ptr) {
    }
};

void print_list(shared_ptr<ListNode> list) {
    cout << "LIST : ";
    while (list != nullptr) {
        cout << list->data << " -> ";
        list = list->next;
    }
    cout << endl;
}

//A & B are already sorted
shared_ptr<ListNode> merge_lists(shared_ptr<ListNode> A, shared_ptr<ListNode> B) {
    if (A == nullptr) {
        return B;
    } else if (B == nullptr) {
        return A;
    } else {
        shared_ptr<ListNode> pA = A;
        shared_ptr<ListNode> pB = B;
        shared_ptr<ListNode> pC = nullptr;
        
        if (pA->data < pB->data) {
            pC = pA;
            pA = pA->next;
        } else {
            pC = pB;
            pB = pB->next;
        }
        
        shared_ptr<ListNode> result = pC;
        while (pA != nullptr && pB != nullptr) {
            
            if (pA->data < pB->data) {
                pC->next = pA;
                pA = pA->next;
            } else {
                pC->next = pB;
                pB = pB->next;
            }
            pC = pC->next;
        }
        
        while (pA != nullptr) {
            pC->next = pA;
            pA = pA->next;
            pC = pC->next;
        }
        
        while (pB != nullptr) {
            pC->next = pB;
            pB = pB->next;
            pC = pC->next;
        }
        
        return result;
        
    }
}

void merge_lists_test() {
    shared_ptr<ListNode> A = nullptr;
    shared_ptr<ListNode> B = nullptr;
    cout << (merge_lists(nullptr, nullptr) == nullptr ? "NULL PTR" : "WRONG ANSWER") << endl;
    
    shared_ptr<ListNode> C = nullptr;
    shared_ptr<ListNode> D3 = make_shared<ListNode>(9, nullptr);
    shared_ptr<ListNode> D2 = make_shared<ListNode>(6, D3);
    shared_ptr<ListNode> D1 = make_shared<ListNode>(5, D2);
    shared_ptr<ListNode> D0 = make_shared<ListNode>(3, D1);
    
    print_list(merge_lists(nullptr, D0));
    
    shared_ptr<ListNode> E3 = make_shared<ListNode>(12, nullptr);
    shared_ptr<ListNode> E2 = make_shared<ListNode>(4, E3);
    shared_ptr<ListNode> E1 = make_shared<ListNode>(2, E2);
    shared_ptr<ListNode> E0 = make_shared<ListNode>(1, E1);
    
    print_list(merge_lists(E0, nullptr));
    
    print_list(merge_lists(E0, D0));
}

shared_ptr<ListNode> detect_loop(shared_ptr<ListNode> list) {
    shared_ptr<ListNode> slow = list;
    shared_ptr<ListNode> fast = list;
    shared_ptr<ListNode> meetNode = nullptr;
    
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        
        if (slow == fast) {
            meetNode = slow;
            break;
        }
    }
    
    if (fast == nullptr || fast->next == nullptr) {
        return nullptr;
    }
    
    int radius = 0;
    do {
        slow = slow->next;
        radius++;
    } while (slow != meetNode);
    
    slow = list;
    fast = list;
    
    int count = 0;
    while (count < radius) {
        fast = fast->next;
        count++;
    }
    
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }
    
    return slow;
    
}

void loop_tests() {
    
    cout << (detect_loop(nullptr) == nullptr ? "NULL PTR" : "WRONG ANSWER") << endl;
    
    shared_ptr<ListNode> C = nullptr;
    shared_ptr<ListNode> D3 = make_shared<ListNode>(9, nullptr);
    shared_ptr<ListNode> D2 = make_shared<ListNode>(6, D3);
    shared_ptr<ListNode> D1 = make_shared<ListNode>(5, D2);
    shared_ptr<ListNode> D0 = make_shared<ListNode>(3, D1);
    
    cout << (detect_loop(D0) == nullptr ? "NO LOOP" : "WRONG ANSWER") << endl;
    
    shared_ptr<ListNode> list[100];
    for (int i=0; i<100; ++i) {
        list[i] = make_shared<ListNode>(i, nullptr);
    }
    
    for (int i=0; i<99; ++i) {
        list[i]->next = list[i+1];
    }
    
    list[99]->next = list[10];
    cout << (detect_loop(list[0])->data == list[10]->data ? "CORRECT" : "WRONG ANSWER") << endl;
    
    list[99]->next = list[0];
    cout << (detect_loop(list[0])->data == list[0]->data ? "CORRECT" : "WRONG ANSWER") << endl;
    
    list[99]->next = list[95];
    cout << (detect_loop(list[0])->data == list[95]->data ? "CORRECT" : "WRONG ANSWER") << endl;
    
    list[99]->next = list[85];
    cout << (detect_loop(list[0])->data == list[85]->data ? "CORRECT" : "WRONG ANSWER") << endl;
    
    list[99]->next = list[15];
    cout << (detect_loop(list[0])->data == list[15]->data ? "CORRECT" : "WRONG ANSWER") << endl;
    
    list[99]->next = list[50];
    cout << (detect_loop(list[0])->data == list[50]->data ? "CORRECT" : "WRONG ANSWER") << endl;
    
}

int linked_list_main() {
    
    //merge_lists_test();
    loop_tests();
    
    return 0;
}