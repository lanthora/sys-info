#ifndef CPU_USAGE_H
#define CPU_USAGE_H

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <string>
#include <vector>

extern "C"
{
  void bind_cpu(int core);
}



struct cpu_usage_item
{
  std::string name;
  long long user;
  long long nice;
  long long system;
  long long idle;
  long long iowait;
  long long irq;
  long long softirq;

  friend std::istream &operator>>(std::istream &in, cpu_usage_item &item);
  void show() const;
  long long sum() const;
  double idle_percentage(cpu_usage_item const &another) const;
};

std::istream &operator>>(std::istream &in, cpu_usage_item &item);

struct cpu_usage
{
  cpu_usage_item total;
  std::vector<cpu_usage_item> cpu_usage_list;

  void tag();
  void show();
  void calculate(cpu_usage const &another);
};

#endif
