#include "src/IpAddressSorter.hpp"

using namespace std;
int main()
{  
    IPAdressSorter sorter;
    sorter.fillAndSortIPs("ip_filter.tsv");
    //sorter.printInConsole();
    sorter.printIntoFile();
    sorter.filterAndPrintIntoFile(std::make_tuple<int, int, int, int>(1, 0, 0, 0));
    sorter.filterAndPrintIntoFile(std::make_tuple<int, int, int, int>(46, 70, 0, 0));
    sorter.filterAnyAndPrintIntoFile(46);
    return 0;
}
