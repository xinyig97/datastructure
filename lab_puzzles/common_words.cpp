/**
 * @file common_words.cpp
 * Implementation of the CommonWords class.
 *
 * @author Zach Widder
 * @date Fall 2014
 */

#include "common_words.h"
#include<map>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

using std::string;
using std::vector;
using std::map;
using std::ifstream;
using std::cout;
using std::endl;
using std::feof;

string remove_punct(const string& str)
{
    string ret;
    std::remove_copy_if(str.begin(), str.end(), std::back_inserter(ret),
                        std::ptr_fun<int, int>(&std::ispunct));
    return ret;
}

CommonWords::CommonWords(const vector<string>& filenames)
{
    // initialize all member variables
    init_file_word_maps(filenames);
    init_common();
}

void CommonWords::init_file_word_maps(const vector<string>& filenames)
{
    // make the length of file_word_maps the same as the length of filenames
    file_word_maps.resize(filenames.size());

    // go through all files
    for (size_t i = 0; i < filenames.size(); i++) {
        // get the corresponding vector of words that represents the current
        // file
        vector<string> words = file_to_vector(filenames[i]);
        /* Your code goes here! */
        map<string,unsigned int> mapp;
        for(vector<string>::iterator it = words.begin(); it!=words.end(); it++){
            if(mapp.find(*it)!=mapp.end()){
              mapp[*it]++;
            }
            else{
              mapp[*it] = 1;
            }
        }
        file_word_maps.push_back(mapp);
    }
}

void CommonWords::init_common()
{
    /* Your code goes here! */

    for(vector<map<string, unsigned int>>::iterator it = file_word_maps.begin(); it!=file_word_maps.end();it++){
      map<string, unsigned int> temp = *it;
      for(map<string, unsigned int>::iterator j = temp.begin(); j!=temp.end(); j++){
        if(common.find(j->first) != common.end()){
          common[j->first] ++;
        }
        else{
          common[j->first] = 1;
        }
      }
    }
}

//helper functin
bool CommonWords::_is(vector<map<string,unsigned int>>::const_iterator temp, unsigned int thre, string word)const {
  if(temp == file_word_maps.end()){
    return true;
  }
  else{


      if(temp->find(word)->second < thre){
        return false;
      }
      else{
        temp++;
        return true&&_is(temp,thre,word);
      }
    }
}

/**
 * @param n The number of times to word has to appear.
 * @return A vector of strings. The vector contains all words that appear
 * in each file >= n times.
 */
vector<string> CommonWords::get_common_words(unsigned int n) const
{
    vector<string> out;
    /* Your code goes here! */
    for(map<string, unsigned int>::const_iterator it = common.begin(); it!=common.end();it++){

        vector<map<string,unsigned int>>::const_iterator af = file_word_maps.begin();
          while(af != file_word_maps.end()){
              if(af->find(it->first)==(*af).end()){
                af++;
              }
              else{
                break;
              }
        }
      if(af == file_word_maps.end()){
        continue;
      }
      else{
        if(_is(af,n,it->first) == true){
          out.push_back(it->first);
        }
      }
    }
    return out;
}

/**
 * Takes a filename and transforms it to a vector of all words in that file.
 * @param filename The name of the file that will fill the vector
 */
vector<string> CommonWords::file_to_vector(const string& filename) const
{
    ifstream words(filename);
    vector<string> out;

    if (words.is_open()) {
        std::istream_iterator<string> word_iter(words);
        while (!words.eof()) {
            out.push_back(remove_punct(*word_iter));
            ++word_iter;
        }
    }
    return out;
}
