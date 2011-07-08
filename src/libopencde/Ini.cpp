#include <opencde.h>

namespace OpenCDE
{

void Variable::setName(std::string name)
{
  this->name = name;
}

void Variable::setValue(std::string value)
{
  this->value = value;
}

std::string Variable::getName()
{
  return name;
}

std::string Variable::getValue()
{
  return value;
}

Section::Section()
{

}

Section::~Section()
{

}

void Section::setName(std::string name)
{
  this->name = name;
}

std::string Section::getName()
{
  return name;
}

Motif::auto_vector<Variable>* Section::getVariables()
{
  return &variables;
}

Group::Group()
{
  sections.add(new Section());
}

Group::~Group()
{

}

void Group::setName(std::string name)
{
  this->name = name;
}

std::string Group::getName()
{
  return name;
}

Motif::auto_vector<Section>* Group::getSections()
{
  return &sections;
}

Ini::Ini(std::string path)
{
  this->path = path;
  std::ifstream file;
  std::string line;

  groups.add(new Group());

  file.open(path.c_str());

  if(file.is_open() == false)
  {
    throw OpenCDEException("Failed to open the .ini file at '" + path + "' for reading");
  }

  while(file.eof() == false)
  {
    getline(file, line);
    line = removeWhitespace(line);

    if(line.length() == 0)
    {
      continue;
    }

    if(line[0] == '<')
    {
      groups.add(new Group());
      groups.at(groups.size() - 1)->setName(line.substr(1, line.length() - 2));
    }
    else if(line[0] == '[')
    {
      groups.at(groups.size() - 1)->getSections()->add(new Section());

      groups.at(groups.size() - 1)->getSections()->at(groups.at(groups.size() - 1)
        ->getSections()->size() - 1)->setName(line.substr(1, line.length() - 2));
    }
    else
    {
      groups.at(groups.size() - 1)->getSections()->at(groups.at(groups.size() - 1)
        ->getSections()->size() - 1)->getVariables()->add(new Variable());

      groups.at(groups.size() - 1)->getSections()->at(groups.at(groups.size() - 1)
        ->getSections()->size() - 1)->getVariables()->at(groups.at(groups.size() - 1)
        ->getSections()->at(groups.at(groups.size() - 1)->getSections()->size() - 1)
        ->getVariables()->size() - 1)->setName(line.substr(0, line.find_last_of('=')));

      groups.at(groups.size() - 1)->getSections()->at(groups.at(groups.size() - 1)
        ->getSections()->size() - 1)->getVariables()->at(groups.at(groups.size() - 1)
        ->getSections()->at(groups.at(groups.size() - 1)->getSections()->size() - 1)
        ->getVariables()->size() - 1)->setValue(line.substr(line.find_last_of('=') + 1));
    }
  }

  Group* group = NULL;
  Section* section = NULL;
  Variable* variable = NULL;

  for(int groupIndex = 0; groupIndex < groups.size(); groupIndex++)
  {group = groups.at(groupIndex);
    //std::cout << "Group: " << group->getName() << std::endl;

    for(int sectionIndex = 0; sectionIndex < group->getSections()->size(); sectionIndex++)
    {section = group->getSections()->at(sectionIndex);
      //std::cout << "  Section: " << section->getName() << std::endl;

      for(int variableIndex = 0; variableIndex < section->getVariables()->size(); variableIndex++)
      {variable = section->getVariables()->at(variableIndex);
        //std::cout << "    Variable: " << variable->getName() << " " << variable->getValue() << std::endl;
      }
    }
  }
}

Ini::~Ini()
{

}

Motif::auto_vector<Group>* Ini::getGroups()
{
  return &groups;
}

void Ini::getGroupNames(std::vector<std::string>* groupNames)
{
  for(int groupIndex = 0; groupIndex < groups.size(); groupIndex++)
  {
    groupNames->push_back(groups.at(groupIndex)->getName());
  }
}

void Ini::getSectionNames(std::string groupName, std::vector<std::string>* sectionNames)
{
  Group* group = NULL;

  for(int groupIndex = 0; groupIndex < groups.size(); groupIndex++)
  {
    if(groups.at(groupIndex)->getName() == groupName)
    {
      group = groups.at(groupIndex);
    }
  }

  if(group == NULL)
  {
    throw OpenCDEException("No such group '" + groupName + "'");
  }

  for(int sectionIndex = 0; sectionIndex < group->getSections()->size(); sectionIndex++)
  {
    sectionNames->push_back(group->getSections()->at(sectionIndex)->getName());
  }
}

void Ini::save()
{

}

std::string Ini::getValue(std::string groupName, std::string sectionName, std::string variableName)
{
  Group* group = NULL;
  Section* section = NULL;
  Variable* variable = NULL;

  for(int groupIndex = 0; groupIndex < groups.size(); groupIndex++)
  {
    group = groups.at(groupIndex);

    if(group->getName() == groupName)
    {
      for(int sectionIndex = 0; sectionIndex < group->getSections()->size(); sectionIndex++)
      {
        section = group->getSections()->at(sectionIndex);

        if(section->getName() == sectionName)
        {
          for(int variableIndex = 0; variableIndex < section->getVariables()->size(); variableIndex++)
          {
            variable = section->getVariables()->at(variableIndex);

            if(variable->getName() == variableName)
            {
              return variable->getValue();
            }
          }
        }
      }
    }
  }

  throw OpenCDEException("Failed to obtain '" + variableName + "' for '" + sectionName + " " + groupName + "' from the .ini file");
}

std::string Ini::getValue(std::string groupName, std::string sectionName, std::string variableName, std::string defaultValue)
{
  return "Fpup.t.xpm";
}

std::string Ini::removeWhitespace(std::string input)
{
  std::string outputFront;

  for(unsigned int index = 0; index < input.length(); index++)
  {
    if(input[index] == ' ')
    {
      // ignore
    }
    else if(input[index] == '\t')
    {
      // ignore
    }
    else
    {
      outputFront = input.substr(index);
      break;
    }
  }

  return outputFront;
}

}
