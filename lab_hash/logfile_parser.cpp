/**
 * @file logfile_parser.cpp
 * Implementation of the LogfileParser class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Summer 2012
 */

#include "logfile_parser.h"
#include <iostream>
#include <iomanip>

using std::string;
using std::vector;
using std::ifstream;
using std::istringstream;

/**
 * Constructs a LogLine from a string (actual physical line in the
 * logfile).
 *
 * @param line The line in the file to extract info from.
 */
LogfileParser::LogLine::LogLine(const string& line)
{
    istringstream iss(line);
    iss >> customer;
    customer = customer.substr(1, customer.length() - 3);
    iss >> url;
    string dte = "";
    string dline;
    do {
        iss >> dline;
        dte += dline;
        dte += " ";
    } while (iss);

    dte = dte.substr(0, dte.length() - 6);
    std::tm tm = {};
    std::stringstream ss(dte);
    ss >> std::get_time(&tm, "%a %b %d %H:%M:%S %Y");
    date = time(NULL);
    // force correct DST
    tm.tm_isdst = 1;
    date = mktime(&tm);
}

/**
 * Constructs a new LogfileParser from the name of a log file.
 *
 * @param fname The name of the log file to open.
 */
LogfileParser::LogfileParser(const string& fname) : whenVisitedTable(256)
{
    SCHashTable<string, bool> pageVisitedTable(256);
    ifstream infile(fname.c_str());
    string line;
    while (infile.good()) {
        getline(infile, line);

        // if the line length is 0, move on to the next loop iteration
        if (line.length() == 0)
            continue;

        // otherwise parse the line and update the hash tables and vector
        LogLine ll(line);
//unique key would be concate string of names and urls
        string key = ll.customer + ll.url;
//if this url has already been visited, we dont add it on to the unique urls
//if not, we add it and mark it as not unique
        if(pageVisitedTable[ll.url] != true){
          uniqueURLs.push_back(ll.url);
          pageVisitedTable[ll.url] = true;
        }
//check if the table stores the latest visit dateVisited
//if yes, do nothing
//if no, update it
        if(whenVisitedTable[key] < ll.date){
        whenVisitedTable[key] = ll.date;
        }
      }
        /**
         * @todo Finish implementing this function.
         *
         * Given the LogLine above, you should be able to update the member
         * variable hash table and any other hash tables necessary to solve
         * this problem. This should also build the uniqueURLs member
         * vector as well.
         */
    infile.close();
}

/**
 * Determines if a given customer has ever visited the given url.
 *
 * @param customer The customer name.
 * @param url The url.
 * @return A boolean value indicating whether the customer visited the url.
 */
bool LogfileParser::hasVisited(const string& customer, const string& url) const
{

    /**
     * @todo Implement this function.
     */
     //check if the customer exist
     string key = customer + url;
     //only check if the key has already exist
     return(whenVisitedTable.keyExists(key));
     /*

    //(void) customer; // prevent warnings... When you implement this function, remove this line.
    //(void) url;      // prevent warnings... When you implement this function, remove this line.

    return false; // replaceme
    */
}

/**
 * Determines *when* a customer last visited a given url. If the customer
 * has not visited the given url, the output of this function should be the
 * default time_t.
 *
 * @param customer The customer name.
 * @param url The url.
 * @return A time_t representing when the customer last visited the given
 *  url.
 */
time_t LogfileParser::dateVisited(const string& customer,
                                  const string& url) const
{

    /**
     * @todo Implement this function.
     */
    string key = customer+url;
    //if the key has existed, return the time
    if(whenVisitedTable.keyExists(key) == true){
      time_t t = whenVisitedTable.find(key);
      return t;
    }
  //  (void) customer; // prevent warnings... When you implement this function, remove this line.
  //  (void) url;      // prevent warnings... When you implement this function, remove this line.
  //otherwise, return default value
    return time_t(); // replaceme
}

/**
 * Gets all of the unique urls that have been visited.
 *
 * @return A vector of urls that were visited in the logfile. Note
 *  that **there should be no duplicates in this vector**.
 */
vector<string> LogfileParser::uniquePages() const
{
    return uniqueURLs;
}
