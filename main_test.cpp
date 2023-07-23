//
// Created by Vital on 08.05.2023.
//
#include <iostream>
#include "gtest/gtest.h"
#include "include/InvertedIndex.h"
#include "include/SearchServer.h"
#include <vector>

using namespace std;

/*void TestInvertedIndexFunctionality(
        const vector<string> &docs,
        const vector<string> &requests,
        const vector<map<size_t,size_t>> &expected
) {
    vector<map<size_t,size_t>> result;

    InvertedIndex::getInstance().updateDocumentBase(docs);

    for(auto &request : requests) {
        map<size_t,size_t> word_count = InvertedIndex::getInstance().getWordCount(request);
        result.push_back(word_count);
    }
    ASSERT_EQ(result, expected);
}

TEST(TestCaseInvertedIndex, TestBasic) {
    const vector<string> docs = {
            "london is the capital of great britain",
            "big ben is the nickname for the Great bell of the striking clock"
    };
    const vector<string> requests = {"london", "the"};
    const vector<map<size_t,size_t>> expected = {
            {
                    {0, 1}
            }, {
                    {0, 1}, {1, 3}
            }
    };
    TestInvertedIndexFunctionality(docs, requests, expected);
}

TEST(TestCaseInvertedIndex, TestBasic2) {
    const vector<string> docs = {
            "milk milk milk milk water water water",
            "milk water water",
            "milk milk milk milk milk water water water water water",
            "americano cappuchino"
    };
    const vector<string> requests = {"milk", "water", "cappuchino"};
    const vector<map<size_t,size_t>> expected = {
            {
                    {0, 4}, {1, 1}, {2, 5}
            },
            {
                    {0, 3}, {1, 2}, {2, 5}
            },
            {
                    {3, 1}
            }
    };
    TestInvertedIndexFunctionality(docs, requests, expected);
}

TEST(TestCaseInvertedIndex, TestInvertedIndexMissingWord) {
    const vector<string> docs = {
            "a b c d e f g h i j k l",
            "statement"
    };
    const vector<string> requests = {"m", "statement"};
    const vector<map<size_t,size_t>> expected = {
            {
            }, {
                    {1, 1}
            }
    };
    TestInvertedIndexFunctionality(docs, requests, expected);
}

TEST(TestCaseInvertedIndex, TestInvertedIndexMissingWord2) {
    const vector<string> docs = {
            "a b c d e f g h i j k l",
            "statement"
    };
    const vector<string> requests = {"m", "statement"};
    const vector<map<size_t,size_t>> expected = {
            {
            }, {
                    {1, 1}
            }
    };
    TestInvertedIndexFunctionality(docs, requests, expected);
}*/

TEST(TestCaseSearchServer, TestSimple) {
    const vector<string> docs = {
            "milk milk milk milk water water water",
            "milk water water",
            "milk milk milk milk milk water water water water water",
            "americano cappuchino"
    };

    const vector<string> request = {"milk water", "cappuchino"}; // sugar

    vector<vector<pair<size_t, float>>> result;

    const vector<vector<pair<size_t, float>>> expected = {
                 {
                         {2, 1.0},
                         {0, 0.7},
                         {1, 0.3}
                 },
                 {
                 }
         };

    InvertedIndex::getInstance().updateDocumentBase(docs);

    auto resultAnswers = SearchEngine::getInstance().getAnswers(request);

    //cout << "resultAnswers: " << resultAnswers.size() << endl;
    for(auto &v: resultAnswers) {
        vector<pair<size_t,float>> buf;
        //cout << "v.second: " << v.second.size() << endl;
        for(auto &it: v.second) {
            buf.push_back(make_pair(it.ind, it.rankInd));
            //std::cout << "it.rankInd: " << it.rankInd;
        }
        result.push_back(buf);
    }

    ASSERT_EQ(result, expected);
    //ASSERT_EQ(1, 1);
}

int main(int argc, char **argv) {

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

