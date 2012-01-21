#ifndef OPENCDE_INI_H
#define OPENCDE_INI_H

#include <opencde.h>

namespace OpenCDE
{

class Variable
{
private:
  std::string name;
  std::string value;

public:
  void setName(std::string name);
  void setValue(std::string value);
  std::string getName();
  std::string getValue();

};

class Section
{
private:
  std::string name;
  Motif::auto_vector<Variable> variables;

public:
  Section();
  ~Section();

  std::string getName();
  void setName(std::string name);
  Motif::auto_vector<Variable>* getVariables();

};

class Group
{
private:
  std::string name;
  Motif::auto_vector<Section> sections;

public:
  Group();
  ~Group();

  std::string getName();
  void setName(std::string name);
  Motif::auto_vector<Section>* getSections();

};

class Ini
{
private:
  std::string path;
  Motif::auto_vector<Group> groups;

  std::string removeWhitespace(std::string input);

public:
  Ini(std::string path);
  ~Ini();

  Motif::auto_vector<Group>* getGroups();
  void getGroupNames(std::vector<std::string>* groupNames);
  void getSectionNames(std::string groupName, std::vector<std::string>* sectionNames);
  void save();
  std::string getValue(std::string groupName, std::string sectionName, std::string variableName); // throws
  std::string getValue(std::string groupName, std::string sectionName, std::string variableName, std::string defaultValue);

};

}

#endif

