#include "usage.h"
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <istream>

const unsigned short print_len = 12;

void cpu_usage_item::show() const
{
  std::cout << std::setw(print_len) << this->name;
  std::cout << std::setw(print_len) << this->user;
  std::cout << std::setw(print_len) << this->nice;
  std::cout << std::setw(print_len) << this->system;
  std::cout << std::setw(print_len) << this->idle;
  std::cout << std::setw(print_len) << this->iowait;
  std::cout << std::setw(print_len) << this->irq;
  std::cout << std::setw(print_len) << this->softirq;
  std::cout << std::endl;
}

long long cpu_usage_item::sum() const
{
  return this->user + this->nice + this->system + this->idle + this->iowait + this->irq + this->softirq;
}

std::istream &operator>>(std::istream &in, cpu_usage_item &item)
{
  in >> item.name;
  if (item.name.substr(0, 3) != "cpu")
  {
    item.name = "end";
    return in;
  }
  in >> item.user;
  in >> item.nice;
  in >> item.system;
  in >> item.idle;
  in >> item.iowait;
  in >> item.irq;
  in >> item.softirq;

  char ch = '0';
  while (ch != '\n')
  {
    in.get(ch);
  }
  return in;
}

double cpu_usage_item::idle_percentage(cpu_usage_item const &another) const
{
  return (another.idle - this->idle) * 1.0 / (another.sum() - this->sum());
}

void cpu_usage::tag()
{
  cpu_usage_list.clear();
  std::ifstream ifs;
  ifs.open("/proc/stat", std::ios::in);
  ifs >> total;
  cpu_usage_item cui;
  while (true)
  {
    ifs >> cui;
    if (cui.name == "end")
    {
      break;
    }
    else
    {
      cpu_usage_list.push_back(cui);
    }
  }
  ifs.close();
}

void cpu_usage::show()
{
  std::string colnames[] = {"name", "user", "nice", "system", "idle", "iowait", "irq", "softirq"};
  for (auto colname : colnames)
  {
    std::cout << std::setw(print_len) << colname;
  }
  std::cout << std::endl;

  total.show();
  for (auto item : cpu_usage_list)
  {
    item.show();
  }
}

void cpu_usage::calculate(cpu_usage const &another)
{

  std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(2);
  std::cout << std::setw(print_len);
  std::cout << 100 * (1 - another.total.idle_percentage(this->total)) << "%";

  int core_num = std::min(another.cpu_usage_list.size(), this->cpu_usage_list.size());
  for (int i = 0; i < core_num; ++i)
  {
    std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(2);
    std::cout << std::setw(print_len);
    std::cout << 100 * (1 - another.cpu_usage_list[i].idle_percentage(this->cpu_usage_list[i])) << "%";
  }
  std::cout << std::endl;
}
