#ifndef JSON_HPP
#define JSON_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <typeinfo>

#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/writer.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/document.h"

class toJson{
private:
    rapidjson::StringBuffer strBuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer;


public:
    toJson()
        : writer(strBuf)
    {}

void setWriter(rapidjson::StringBuffer strBuf){
    writer.Reset(strBuf);
}

void start()
{
    writer.StartObject();
}

void end()
{
    writer.EndObject();
}

bool insertInt(const char* key, int i)
{
    writer.Key(key);
    writer.Int(i);
    return true;
}

bool insertDouble(const char* key, double d)
{
    writer.Key(key);
    writer.Double(d);
    return true;
}

bool insertString(const char* key, std::string s)
{
    writer.Key(key);
    writer.String(s.c_str());
    return true;
}

bool insertStringObject(const char* key, std::map<std::string,std::string> m)
{
    writer.Key(key);
    writer.StartObject();
    std::map<std::string,std::string>::iterator iter = m.begin();
    while(iter != m.end())
    {
        writer.Key(iter->first.c_str());
        writer.Key(iter->second.c_str());
        iter++;
    }
    writer.EndObject();
    return true;
}

bool insertIntArray(const char* key, std::vector<int> v_i)
{
    writer.Key(key);
    writer.StartArray();
    std::vector<int>::iterator iter;
    while(iter != v_i.end())
    {
        writer.Key(key);
        writer.Int(*iter);
    }
    writer.EndArray();
    return true;
}

bool insertDoubleArray(const char* key, std::vector<double> v_d)
{
    writer.Key(key);
    writer.StartArray();
    std::vector<double>::iterator iter;
    while(iter != v_d.end())
    {
        writer.Key(key);
        writer.Double(*iter);
    }
    writer.EndArray();
    return true;
}

bool insertStringArray(const char* key, std::vector<std::string> v_s)
{
    writer.Key(key);
    writer.StartArray();
    std::vector<std::string>::iterator iter;
    while(iter != v_s.end())
    {
        writer.Key(key);
        writer.String((*iter).c_str());
    }
    writer.EndArray();
    return true;
}

std::string toString()
{
    return strBuf.GetString();
}
};


#endif
