#ifndef MEM_USAGE_H
#define MEM_USAGE_H

struct mem_usage
{
  unsigned long long mem_total;
  unsigned long long mem_available;
  void tag();
  double mem_usage_percentage() const;
  void show() const;
};

#endif
