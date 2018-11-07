/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <iterator>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstring>
#include <algorithm>

using std::string;
using std::map;
using std::vector;
using std::ifstream;
using std::istream;
using std::istream_iterator;
using std::stringstream;
/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
  ifstream anagram_dict_file(filename);
  string line;
  if (anagram_dict_file.is_open()) {
      while (getline(anagram_dict_file, line)) {
          /* Used to break the line by whitespace. The CMU Dict does this for
           * separating words from their pronunciations. */
           std::string temp = hash_(line);
           if(dict.find(temp)!=dict.end()){
             (dict.find(temp)->second).push_back(line);
           }
           else{
             vector<string> ran;
             ran.push_back(line);
             dict[temp]=ran;
           }
          }
      }
}

std::string AnagramDict::hash_(std::string temp) const{
  std::string sorted = temp;
  std::sort(sorted.begin(),sorted.end());
  return sorted;
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
    for(vector<string>::const_iterator it = words.begin(); it!=words.end(); it++){
      string temp = hash_(*it);
      if(dict.find(temp)!=dict.end()){
        (dict.find(temp)->second).push_back(*it);
      }
      else{
        vector<string> ran;
        ran.push_back(*it);
        dict[temp]=ran;
      }
    }
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    string key = hash_(word);
    if(dict.find(key)==dict.end()){
      return vector<string>();
    }
    else{
        return (dict.find(key)->second);
    }
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    vector<vector<string>> ana;
    for(map<string, vector<string>>::const_iterator it = dict.begin(); it!=dict.end(); it++){
      vector<string> temp = it->second;
      if(temp.size()>=2){
        ana.push_back(temp);
      }
    }
    return ana;
}
