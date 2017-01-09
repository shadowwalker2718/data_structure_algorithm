#include "henry.h"

#include "208_Implement_Trie_Prefix_Tree.h"
#include "391. Perfect Rectangle.h"
#include "394. Decode String.h"
#include "94. Binary Tree Inorder Traversal.h"
#include "388. Longest Absolute File Path.h"
#include "307. Range Sum Query - Mutable.h"
#include "208. Implement Trie (Prefix Tree).h"
#include "425. Word Squares.h"
#include "422. Valid Word Square.h"
#include "42. Trapping Rain Water.h"
#include "407. Trapping Rain Water II.h"

#include "bzoj1090.h"

#include "ksum.h"

#include "HDU 1254.h"
#include "361. Bomb Enemy.h"
#include "214. Shortest Palindrome.h"
#include "65. Valid Number.h"
#include "68. Text Justification.h"
#include "254. Factor Combinations.h"

#include "lnkd_midstack.h"
#include "serialize_tree.h"
#include "gg_findmaxwith1flip.h"
#include "IndexMaxPQ.h"
#include "skiplist.h"
#include "lnkd_addinterval.h"
#include "minwindowsub.h"
#include "149.h"

int main(int argc, char** argv) {
    _149::test();
    minwindowsub::test();

    _lnkd_totalcovered_length::test();

    _skiplist::test();

    _indexheap::test();
    _indexheap::test2();

    google::test();

    _lnkd_is_serialized_tree::test();
    _midstack::test();
    _254::test();
    _65::test();
    _68::test();
    _214::test();
    _361::test();
    _42::test();
    _42::test2();

	_208::test();
    _208_ext::test();
	_391::test();
    _394::test();
    _388::test();
    _307::test();
    _425::test();
    _425::test2();
    _425::test3();

    _422::test();

    _407::test();



    _bzoj1090::test();

    _ksum::test();
    _hdu_1254::test();
	return 0;
}

