#include "param.hpp"

paramMap::paramMap(std::string file)
{
        filename = file;
}
paramMap::paramMap(std::string file, int r)
{
        isMPI = true;
        rank = r;
        filename = file;
}

bool paramMap::getParamInt(std::string parastr, int &Param)
{

        bool foundParam = getParamInt(parastr, Param, 0);
        if (!foundParam)
        {
                if (isMPI && (!rank))
                        throw(-1);
                if (isMPI == false)
                        throw(-1);
        }
        return foundParam;
}

bool paramMap::getParamInt(std::string parastr, int &Param, const int defaultVal)
{
        // std::cout<<"Looking for "<<parastr<<std::endl;
        std::fstream inFile;
        inFile.open(filename);
        std::string line;

        // std::stringstream token;

        while (!inFile.eof())
        {
                std::getline(inFile, line);
                // std::cout<<line<<std::endl;
                if (line.length() != 0)
                {
                        // find =
                        int eq = line.find("=");
                        // std::cout<<eq<<std::endl;
                        if (line.length() != eq)
                        {
                                // std::cout<<line.substr(0,eq)<<std::endl;
                                // token>>line.substr(0,eq);
                                std::string token = line.substr(0, eq);
                                token.erase(remove_if(token.begin(), token.end(), isspace), token.end());
                                if (parastr == token)
                                {
                                        //	std::cout<<"found"<<std::endl;
                                        token = line.substr(eq + 1);
                                        token.erase(remove_if(token.begin(), token.end(), isspace), token.end());
                                        Param = std::stoi(token, nullptr);
                                        return true;
                                }
                        }
                }
        }
        std::cout << "param not found " << parastr << std::endl;
        Param = defaultVal;
        return false;
}

bool paramMap::getParamDouble(std::string parastr, double &Param)
{

        bool foundParam = getParamDouble(parastr, Param, 0.0);
        if (!foundParam)
        {
                if (isMPI && (!rank))
                        throw(-1);
                if (isMPI == false)
                        throw(-1);
        }
        return foundParam;
}

bool paramMap::getParamDouble(std::string parastr, double &Param, const double defaultVal)
{
        std::fstream inFile;
        inFile.open(filename);
        std::string line;

        // std::stringstream token;

        while (!inFile.eof())
        {
                std::getline(inFile, line);
                // std::cout<<line<<std::endl;
                if (line.length() != 0)
                {
                        // find =
                        int eq = line.find("=");
                        // std::cout<<eq<<std::endl;
                        if (line.length() != eq)
                        {
                                std::string token = line.substr(0, eq);
                                token.erase(remove_if(token.begin(), token.end(), isspace), token.end());
                                if (parastr == token)
                                {
                                        // std::cout<<"found"<<std::endl;
                                        token = line.substr(eq + 1);
                                        token.erase(remove_if(token.begin(), token.end(), isspace), token.end());
                                        Param = std::stod(token, nullptr);
                                        return true;
                                }
                        }
                }
        }
        std::cout << "param not found " << parastr << std::endl;
        Param = defaultVal;
        return false;
}

bool paramMap::getParamString(std::string parastr, std::string &Param)
{

        bool foundParam = getParamString(parastr, Param, "");
        if (!foundParam)
        {
                if (isMPI && (!rank))
                        throw(-1);
                if (isMPI == false)
                        throw(-1);
        }
        return foundParam;
}

bool paramMap::getParamString(std::string parastr, std::string &Param, const std::string defaultVal)
{
        // std::cout<<"Looking for "<<parastr<<std::endl;

        std::fstream inFile;
        inFile.open(filename);
        std::string line;

        // std::stringstream token;

        while (!inFile.eof())
        {
                std::getline(inFile, line);
                // std::cout<<line<<std::endl;
                if (line.length() != 0)
                {
                        // find =
                        int eq = line.find("=");
                        // std::cout<<eq<<std::endl;
                        if (line.length() != eq)
                        {
                                std::string token = line.substr(0, eq);
                                token.erase(remove_if(token.begin(), token.end(), isspace), token.end());
                                if (parastr == token)
                                {
                                        // std::cout<<"found"<<std::endl;
                                        token = line.substr(eq + 1);
                                        token.erase(remove_if(token.begin(), token.end(), isspace), token.end());
                                        Param = token;
                                        return true;
                                }
                        }
                }
        }
        std::cout << "param not found " << parastr << std::endl;
        Param = defaultVal;
        return false;
}

bool paramMap::getParamBool(std::string parastr, bool &Param)
{

        bool foundParam = getParamBool(parastr, Param, false);
        if (!foundParam)
        {
                if (isMPI && (!rank))
                        throw(-1);
                if (isMPI == false)
                        throw(-1);
        }
        return foundParam;
}

bool paramMap::getParamBool(std::string parastr, bool &Param, const bool defaultVal)
{
        // std::cout<<"Looking for "<<parastr<<std::endl;

        std::fstream inFile;
        inFile.open(filename);
        std::string line;

        // std::stringstream token;

        while (!inFile.eof())
        {
                std::getline(inFile, line);
                // std::cout<<line<<std::endl;
                if (line.length() != 0)
                {
                        // find =
                        int eq = line.find("=");
                        // std::cout<<eq<<std::endl;
                        if (line.length() != eq)
                        {
                                std::string token = line.substr(0, eq);
                                token.erase(remove_if(token.begin(), token.end(), isspace), token.end());
                                if (parastr == token)
                                {
                                        // std::cout<<"found"<<std::endl;
                                        token = line.substr(eq + 1);
                                        token.erase(remove_if(token.begin(), token.end(), isspace), token.end());
                                        std::transform(token.begin(), token.end(), token.begin(), [](unsigned char c)
                                                       { return std::tolower(c); });
                                        if (token == "true")
                                                Param = true;
                                        else if (token == "false")
                                                Param = false;
                                        else
                                        {
                                                std::cout << "param not found " << parastr << std::endl;
                                                if (isMPI && (!rank))
                                                        throw(-1);
                                                if (isMPI == false)
                                                        throw(-1);
                                        }

                                        return true;
                                }
                        }
                }
        }
        std::cout << "param not found " << parastr << std::endl;
        Param = defaultVal;
        return false;
}
// std::string paramMap::buildString
