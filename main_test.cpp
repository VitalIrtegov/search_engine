//
// Created by Vital on 08.05.2023.
//
#include <iostream>
#include "gtest/gtest.h"
#include "include/searchFiles.h"
#include "include/InvertedIndex.h"
#include "include/ConvertJSON.h"

using namespace std;
//typedef std::vector<std::pair<std::string, std::vector<RelativeIndex>>> myRes;

void TestInvertedIndexFunctionality(
        const vector<string>& docs,
        const vector<string>& requests,
        const std::vector<map<size_t,size_t>>& expected
) {
    std::vector<map<size_t,size_t>> result;
    InvertedIndex idx;
    idx.updateDocumentBase(docs);
    for(auto& request : requests) {
        map<size_t,size_t> word_count = idx.getWordCount(request);
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
            }, {{
                        0, 1}, {1, 3}
            }
    };
    TestInvertedIndexFunctionality(docs, requests, expected);
}
TEST(TestCaseInvertedIndex, TestBasic2) {
    const vector<string> docs = {
            "milk milk milk milk water water water",
            "milk water water",
            "milk milk milk milk milk water water water water water",
            "americano cappuccino"
    };
    const vector<string> requests = {"milk", "water", "cappuchino"};
    const vector<map<size_t,size_t>> expected = {
            {
                    {0, 4}, {1, 1}, {2, 5}
            },
            {
                    {0, 2}, {1, 2}, {2, 5}
            },
            {
                    {3, 1}
            }
    };
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


/*
TEST(TestCaseSearchServer, TestSimple) {
    const vector<string> docs = {
            "milk milk milk milk water water water",
            "milk water water",
            "milk milk milk milk milk water water water water water",
            "americano cappuccino"
    };
    const vector<string> request = {"milk water", "sugar"};
    const std::vector<vector<size_t,float>> expected = {
            {
                    {2, 1},
                    {0, 0.7},
                    {1, 0.3}
            },
            {
            }
    };
    InvertedIndex idx;
    idx.updateDocumentBase(docs);
    SearchEngine srv;
    std::vector<vector<RelativeIndex>> result;

    myRes result1 = srv.search(request);

    for(auto& v:result1)
        result.push_back(v.second);

    ASSERT_EQ(result, expected);
}

*/



int main(int argc, char **argv) {

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

