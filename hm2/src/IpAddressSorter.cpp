#include "IpAddressSorter.hpp"

#include <sstream>
#include <ostream>
#include <fstream>
#include <iostream>
#include <algorithm>

void IPAdressSorter::fillIpAddress(ipAddress& ip, const std::string &value, const int index) const
{
    if (index < 0)
    {
        throw std::runtime_error("parser error: ip part index is incorrect");
    }
    if (index >= 4)
    {
        throw std::runtime_error("parser error: ip parts is more than available( > 4)");
    }
    if (value.empty())
    {
        throw std::runtime_error("parser error: ip part value is empty");
    }

    auto ipPart = std::atoi(value.c_str());
    if (ipPart < 0 || ipPart > 255)
    {
        const std::string error("parser error: ip part value is incorrect" + value);
        throw std::runtime_error(error.c_str());
    }
    switch (index)
    {
        case 0:
            std::get<0>(ip) = ipPart;
            break;
        case 1:
            std::get<1>(ip) = ipPart;
            break;
        case 2:
            std::get<2>(ip) = ipPart;
            break;
        case 3:
            std::get<3>(ip) = ipPart;
            break;
    }
}

auto IPAdressSorter::split(const std::string &line, char delim) {
    std::stringstream ss(line);
    ipAddress ip;
    std::string ipPart;
    int index = 0;
    while (std::getline(ss, ipPart, '.'))
    {
        fillIpAddress(ip, ipPart, index);
        index ++;
    }
    return ip;
}

void IPAdressSorter::fillAndSortIPs(const std::string& filepath)
{
    if (filepath.empty())
    {
        throw std::runtime_error("filepath is empty");
    }
    std::ifstream in("ip_filter.tsv");
    if (in.is_open())
    {
        std::string line;
        while (std::getline(in, line))
        {
            auto ipAddrPartPos = line.find('\t');
            if (ipAddrPartPos > 0 && ipAddrPartPos < line.size())
            {
                auto ipAddrPart = line.substr(0, ipAddrPartPos);
                m_ipAddrSet.insert(split(ipAddrPart, '.'));
            }           
        }
    }
    in.close();
}

void IPAdressSorter::printInConsole() const
{
    if (m_ipAddrSet.empty())
    {
        std::cout<<"There are no IPs in IPs map."<<std::endl;
        return;
    }
    for (auto ipAddr : m_ipAddrSet)
    {
        std::cout << std::get<0>(ipAddr) << "."
                 << std::get<1>(ipAddr) << "."
                 << std::get<2>(ipAddr) << "."
                 << std::get<3>(ipAddr) << std::endl;
    }
}

const char* IPAdressSorter::RESULT_FILE_NAME = "sortedIps.txt";

void IPAdressSorter::printIntoFile() const
{
    if (m_ipAddrSet.empty())
    {
        std::cout<<"Result set is empty";
        return;
    }
    std::ofstream resFile;
    resFile.open(RESULT_FILE_NAME);
    
    for (auto ipAddr : m_ipAddrSet)
    {
        resFile << std::get<0>(ipAddr) << "."
            << std::get<1>(ipAddr) << "."
            << std::get<2>(ipAddr) << "."
            << std::get<3>(ipAddr) << "\n";
    }
    resFile.close();
}



auto IPAdressSorter::checkFilterCondition(const ipAddress& filter, const ipAddress& element) const
{
    if (std::get<0>(filter) > 0 
        && std::get<1>(filter) == 0
        && std::get<2>(filter) == 0
        && std::get<3>(filter) == 0)
    {
        return std::get<0>(filter) == std::get<0>(element);
    }
    else if (std::get<0>(filter) > 0 
        && std::get<1>(filter) > 0
        && std::get<2>(filter) == 0
        && std::get<3>(filter) == 0)
    {
        return std::get<0>(filter) == std::get<0>(element)
            && std::get<1>(filter) == std::get<1>(element);
    }
    else if (std::get<0>(filter) > 0 
        && std::get<1>(filter) > 0
        && std::get<2>(filter) > 0
        && std::get<3>(filter) == 0)
    {
        return std::get<0>(filter) == std::get<0>(element)
            && std::get<1>(filter) == std::get<1>(element)
            && std::get<2>(filter) == std::get<2>(element);
    }
    else
    {
        return filter == element;
    }

}


void IPAdressSorter::filterAndPrintIntoFile(const ipAddress& findIP) const
{
    auto result = std::find_if(m_ipAddrSet.begin(), m_ipAddrSet.end(), [this, & findIP](const auto& element)
        {
            return this->checkFilterCondition(findIP, element);
        });

    if (result == m_ipAddrSet.end())
    {
        std::cout<<"No elements found";
        return;
    }
    std::ofstream resFile;
    resFile.open(RESULT_FILE_NAME, std::ios_base::app);    
    for (auto ipAddr = result; ipAddr != m_ipAddrSet.end(); ++ipAddr)
    {
        if (IPAdressSorter::checkFilterCondition(findIP, *ipAddr))
        {
            resFile << std::get<0>(*ipAddr) << "."
                 << std::get<1>(*ipAddr) << "."
                 << std::get<2>(*ipAddr) << "."
                 << std::get<3>(*ipAddr) << "\n";           
        }

    }
    resFile.close();
}

void IPAdressSorter::filterAnyAndPrintIntoFile(const int value) const
{
    std::ofstream resFile;
    resFile.open(RESULT_FILE_NAME, std::ios_base::app);    
    for (auto ipAddr : m_ipAddrSet)
    {
        if (std::get<0>(ipAddr) == value
            || std::get<1>(ipAddr) == value
            || std::get<2>(ipAddr) == value
            || std::get<3>(ipAddr) == value)
        {
            resFile << std::get<0>(ipAddr) << "."
                 << std::get<1>(ipAddr) << "."
                 << std::get<2>(ipAddr) << "."
                 << std::get<3>(ipAddr) << "\n";           
        }

    }
    resFile.close();
}
