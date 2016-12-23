#pragma once

#include "henry.h"

namespace _lnkd_is_intersected {

    // define the node struct of links
    typedef struct Node {
        struct Node* next;
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
        // 定义几种链表情况
        // two links not intersect with each other, no circle
        /*Node link_1_n =
        {
            &(Node) { &(Node) { &(Node) { &(Node) { &(Node) { &(Node) { &(Node) { &(Node) { &end1 } } } } } } } } };
        Node link_2_n =
        {
            &(Node) { &(Node) { &(Node) { &(Node) { &(Node) { &(Node) { &(Node) { &(Node) { &end2 } } } } } } } } };

        // two links intersect with each other, no circle
        Node common_n = { &(Node) { &(Node) { &end1 } } };

        Node link_1_y = { &(Node) { &(Node) { &(Node) { &(Node) { &(Node) { &common_n } } } } } };
        Node link_2_y = { &(Node) { &(Node) { &(Node) { &(Node) { &(Node) { &common_n } } } } } };

        // two links, has circle, not intersected.
        Node circle1 = { &(Node) { &(Node) { &(Node) { &(Node) { &circle1 } } } } };
        Node link_c1_n = { &(Node) { &(Node) { &(Node) { &(Node) { &circle1 } } } } };

        Node circle2 = { &(Node) { &(Node) { &(Node) { &(Node) { &circle2 } } } } };
        Node link_c2_n = { &(Node) { &(Node) { &(Node) { &(Node) { &circle2 } } } } };

        // two links, has circle, intersected at a non-circle position
        Node common_c = { &(Node) { &(Node) { &(Node) { &(Node) { &common_c } } } } };
        Node common_part = { &(Node) { &common_c } };

        Node link_c1_y = { &(Node) { &(Node) { &common_part } } };
        Node link_c2_y = { &(Node) { &(Node) { &common_part } } };
        // two links, has common circle, but different 'joint-points'.

        Node jp1 = { NULL };
        Node jp2 = { NULL };
        // 'weave' the joint-points into a circle:
        jp1.next = &(Node) { &(Node) { &jp2 } };
        jp2.next = &(Node) { &jp1 };

        Node link_c1_y2 = { &(Node) { &(Node) { &(Node) { &(Node) { &jp1 } } } } };
        Node link_c2_y2 = { &(Node) { &(Node) { &(Node) { &(Node) { &jp2 } } } } };

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
