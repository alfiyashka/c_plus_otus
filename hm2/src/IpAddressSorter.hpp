#ifndef IP_ADDR_SORTER
#define IP_ADDR_SORTER

#include <tuple>
#include <string>
#include <set>

typedef std::tuple<int, int, int, int> ipAddress;

inline auto compareIPs = [](const ipAddress& ip1, const ipAddress& ip2)
   {   return ip1 > ip2;  };

class IPAdressSorter
{
public:
    typedef std::multiset<ipAddress, decltype(compareIPs)> ipSet_t;
   
private:
    /* checks condition to find a value from multiset
    * @param filter  key object to search
    * @param element element from multiset
    */
    auto checkFilterCondition(const ipAddress& filter, const ipAddress& element) const;
    
    /* fills ip address's tuple object by index
    * @param ip  ip address's tuple object
    * @param value  value to insert
    * @param index  ip address's tuple object index
    */
    void fillIpAddress(ipAddress& ip, const std::string &value, const int index) const;
    
    /* splits string by delimiter character.
    * @param s  a string value
    * @param delim   a delimiter character
    * @return ip address's tuple object 
    */
    auto split(const std::string &s, char delim);

    /* result filename */
    static const char* RESULT_FILE_NAME;
    
    /* stores sorted IPs */
    ipSet_t m_ipAddrSet;
public:
    IPAdressSorter(): m_ipAddrSet(compareIPs)
    {
    }
    /* to sort data uses std::multiset. Function parse input file and fill multiset
    * @param filepath input file 
    */
    void fillAndSortIPs(const std::string& filepath);

    /*
    * prints all data from multi set to console
    */
    void printInConsole() const;

    /*
    * prints all data from multi set into a result file (@RESULT_FILE_NAME)
    */
    void printIntoFile() const;

    /*
    * filter data by key and print result into a result file (@RESULT_FILE_NAME)
    * @param findId key to find
    */
    void filterAndPrintIntoFile(const ipAddress& findId) const;

    /*
    * filter data by value and print result into a result file (@RESULT_FILE_NAME)
    * @param value value to find
    */
    void filterAnyAndPrintIntoFile(const int value) const;

    /*
    * clear all results from multi set map
    */
    void cleanResult() { m_ipAddrSet.clear(); }

};


#endif