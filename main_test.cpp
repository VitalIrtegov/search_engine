//
// Created by Vital on 08.05.2023.
//
#include <iostream>
#include "gtest/gtest.h"
#include "include/InvertedIndex.h"
#include "include/SearchServer.h"
#include <boost/tokenizer.hpp>
#include <set>
#include <vector>

using namespace std;

void TestInvertedIndexFunctionality(
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
}

void requestCount(string &line, set<string> &words) {
    typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
    boost::char_separator<char> sep("-);|(, :\"\'./[]!_?><%");

    std::for_each(line.begin(), line.end(), [](char &c) { c = ::tolower(static_cast<unsigned char>(c)); });
    tokenizer tokens(line, sep);

    for (tokenizer::iterator iter = tokens.begin(); iter != tokens.end(); ++iter)
        words.insert(*iter);
}

TEST(TestCaseSearchServer, TestSimple) {
    const vector<string> docs = {
            "milk milk milk milk water water water",
            "milk water water",
            "milk milk milk milk milk water water water water water",
            "americano cappuchino"
    };

    const vector<string> request = {"milk water", "sugar"};

    std::set<std::string> words;

    for(auto i: request)
        requestCount(i, words);

    SearchEngine::getInstance().setMaxResponse(words.size());

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

    for(auto &v: resultAnswers) {
        vector<pair<size_t,float>> buf;
        for(auto &it: v.second) {
            buf.push_back(make_pair(it.ind, it.rankInd));
        }
        result.push_back(buf);
    }

    ASSERT_EQ(result, expected);
}


int main(int argc, char **argv) {

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

