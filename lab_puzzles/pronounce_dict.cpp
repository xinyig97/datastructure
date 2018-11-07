/**
 * @file pronounce_dict.cpp
 * Implementation of the PronounceDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "pronounce_dict.h"

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
 * Constructs a PronounceDict from a CMU pronunciation dictionary
 * file. See http://www.speech.cs.cmu.edu/cgi-bin/cmudict .
 * @param pronun_dict_filename Filename of the CMU pronunciation
 * dictionary.
 */
PronounceDict::PronounceDict(const string& pronun_dict_filename)
{
    ifstream pronun_dict_file(pronun_dict_filename);
    string line;
    if (pronun_dict_file.is_open()) {
        while (getline(pronun_dict_file, line)) {
            /* Used to break the line by whitespace. The CMU Dict does this for
             * separating words from their pronunciations. */
            stringstream line_ss(line);
            istream_iterator<string> line_begin(line_ss);
            istream_iterator<string> line_end;
            if (line[0] != '#' && *line_begin != ";;;") {
                /* Associate the word with the rest of the line
                 * (its pronunciation). */
                istream_iterator<string> temp_itr = line_begin;
                dict[*temp_itr] = vector<string>(++line_begin, line_end);
            }
        }
    }
    /* If it's not open then... well... just don't do anything for the sake
     * of simplicity. */
}

/**
 * Constructs a PronounceDict from a CMU std::map mapping the word
 * to a vector of strings which represent the pronunciation.
 * @param pronun_dict Maps a string word to a vector of strings
 * representing its pronunciation.
 */
PronounceDict::PronounceDict(const map<string, vector<string>>& pronun_dict)
    : dict(pronun_dict)
{
    /* Nothing to see here. */
}

/**
 * Uses the dictionary to determine if the two words are homophones.
 * @param word1 First word to be tested.
 * @param word2 Second word to be tested.
 * @return true if the two words are homophones, false otherwise (or
 * one or both words weren't in the dictionary).
 * Note: The word keys in the dictionary are stored in uppercase.
 */
bool PronounceDict::homophones(const string& word1, const string& word2) const
{
    /* Your code goes here! */
    // std::cout<<"all homophone"<<std::endl;
    string temp_1 = word1;
    string temp_2 = word2;
    // for(std::map<std::string, std::vector<std::string>>::const_iterator it = dict.begin(); it!=dict.end();it++){
    //   std::cout<<it->first<<":";
    //   std::vector<std::string> temp = it->second;
    //   for(std::vector<std::string>::iterator at = temp.begin(); at!=temp.end();at++){
    //     std::cout<<*at<<",";
    //   }
    //   std::cout<<std::endl;
    // }
    std::transform(word1.begin(),word1.end(),temp_1.begin(),::toupper);
    std::transform(word2.begin(),word2.end(),temp_2.begin(),::toupper);
    if(dict.find(temp_1)==dict.end() || dict.find(temp_2)==dict.end()){
      return false;
    }
    //print out the dict

    else{
      // std::cout<<"1"<<std::endl;
      std::vector<std::string> pf1 = (dict.find(temp_1))->second;
      // for(std::vector<std::string>::iterator it = pf1.begin(); it!=pf1.end();it++){
      //   std::cout<<*it<<",";
      // }
      // std::cout<<std::endl;
      //   std::cout<<"1"<<std::endl;
      std::vector<std::string> pf2 = (dict.find(temp_2))->second;
      // for(std::vector<std::string>::iterator it = pf2.begin(); it!=pf2.end();it++){
      //   std::cout<<*it<<",";
      // }
      for(std::vector<std::string>::iterator it = pf1.begin(); it!=pf1.end(); it++){
        for(std::vector<std::string>::iterator fi = pf2.begin(); fi!= pf2.end(); fi++){
          if(*it == *fi){
            return true;
          }
        }
      }
      return false;
    }

}
