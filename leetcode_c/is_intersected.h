#pragma once

#include "henry.h"

namespace _lnkd_is_intersected {

    // define the node struct of links
    typedef struct Node {
        struct Node* next=NULL;
    } Node;

    int is_intersected(Node* p1, Node* p2) {
        Node* has_circle_1 = has_circle(p1);
        Node* has_circle_2 = has_circle(p2);

        if (has_circle_1) {
            if (has_circle_2) {
                Node* pp1 = has_circle_1;
                Node* pp2 = has_circle_2;
                if (pp1 == pp2 || pp1->next == pp2)
                    return 1;
                while (pp1->next != has_circle_1) {
                    pp1 = pp1->next;
                    pp2 = pp2->next->next;
                    if (pp1 == pp2)
                        return 1;
                }
                return 0;
            } else {
                return 0;
            }
        } else {
            if (has_circle_2) {
                return 0;
            } else {
                while (p1->next)
                    p1 = p1->next;
                while (p2->next)
                    p2 = p2->next;
                return p1 == p2;
            }
        }
        return 0;
    }

    Node* has_circle(Node* head) {
        Node* p1;
        Node* p2;
        p1 = p2 = head;
        if (p2->next != NULL) {
            p2 = p2->next;
        } else {
            return NULL;
        }
        while (p2->next != NULL && p2->next->next != NULL) {
            p1 = p1->next;
            p2 = p2->next->next;
            if (p1 == p2)
                return p1;
        }
        return NULL;
    }

    int test() {
        Node end1 = { NULL };
        Node end2 = { NULL };

        // no cycle
        {
          vector<Node> vn1(10);
          vector<Node> vn2(3);
          for (int i = 0; i < vn1.size()-1; i++)
            vn1[i].next = &vn1[i + 1];

          for (int i = 0; i < vn2.size() - 1; i++)
            vn2[i].next = &vn2[i + 1];
          vn2.back().next = &vn1[7];
        }

        {
          vector<Node> vn1(10);
          vector<Node> vn2(8);
          for (int i = 0; i < vn1.size() - 1; i++)
            vn1[i].next = &vn1[i + 1];

          for (int i = 0; i < vn2.size() - 1; i++)
            vn2[i].next = &vn2[i + 1];
        }


        // with cycle
        {// intersect at tail
          vector<Node> vn1(20);
          for (int i = 0; i < vn1.size() - 1; i++)
            vn1[i].next = &vn1[i + 1];
          vn1.back().next = &vn1[15];

          vector<Node> vn2(3);
          for (int i = 0; i < vn2.size() - 1; i++)
            vn2[i].next = &vn2[i + 1];
          vn2.back().next = &vn1[7];
        }

        {// intersect at cycle
          vector<Node> vn1(20);
          for (int i = 0; i < vn1.size() - 1; i++)
            vn1[i].next = &vn1[i + 1];
          vn1.back().next = &vn1[8];

          vector<Node> vn2(3);
          for (int i = 0; i < vn2.size() - 1; i++)
            vn2[i].next = &vn2[i + 1];
          vn2.back().next = &vn1[17];
        }

        // 定义几种链表情况
        // two links not intersect with each other, no circle
        /*

        if (is_intersected(&link_1_n, &link_2_n)) {
            printf("link_1_n and link_2_n Intersected!\n");
        }

        if (is_intersected(&link_1_y, &link_2_y)) {
            printf("link_1_y and link_2_y Intersected!\n");
        }

        if (is_intersected(&link_c1_n, &link_c2_n)) {
            printf("link_c1_n and link_c2_n Intersected!\n");
        }

        if (is_intersected(&link_c1_y, &link_c2_y)) {
            printf("link_c1_y and link_c2_y Intersected!\n");
        }

        if (is_intersected(&link_c1_y2, &link_c2_y2)) {
            printf("link_c1_y2 and link_c2_y2 Intersected!\n");
        }*/
        return 0;
    }
}
