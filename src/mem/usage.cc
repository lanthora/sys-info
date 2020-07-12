#include "usage.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <iomanip>

const unsigned int BUFFER_SIZE = 64;

void mem_usage::tag()
{
  this->mem_available = 0ULL;
  this->mem_total = 0ULL;
  std::ifstream ifs;
  ifs.open("/proc/meminfo");

  char line[BUFFER_SIZE];
  while (mem_available == 0ULL || mem_total == 0ULL)
  {
    ifs.getline(line, BUFFER_SIZE - 1);
    if (!std::strncmp("MemTotal:", line, std::strlen("MemTotal:")))
    {
      line[strlen(line) - 2] = '\0';
      this->mem_total = atoi(line + strlen("MemTotal:"));
    }
    else if (!std::strncmp("MemAvailable:", line, std::strlen("MemAvailable:")))
    {
      line[strlen(line) - 2] = '\0';
      this->mem_available = atoi(line + strlen("MemAvailable:"));
    }
    else
    {
      continue;
    }
  }
  ifs.close();
}

double mem_usage::mem_usage_percentage() const
{
  return 1 - (1.0 * this->mem_available / this->mem_total);
}

void mem_usage::show() const
{
  std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(2);
  std::cout << std::setw(8);
  std::cout << 100 * this->mem_usage_percentage() << "%" << std::endl;
}
