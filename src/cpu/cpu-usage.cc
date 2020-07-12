#include "usage.h"
#include <memory>
#include <unistd.h>

int main()
{
  std::shared_ptr<cpu_usage> cu1, cu2;
  cu1 = std::make_shared<cpu_usage>();
  cu2 = std::make_shared<cpu_usage>();
  cu1->tag();
  while (true)
  {
    sleep(1);
    cu2->tag();
    cu1->calculate(*cu2);
    std::swap(cu1, cu2);
  }
}
