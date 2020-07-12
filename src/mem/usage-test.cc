#include "usage.h"
#include <memory>
#include <unistd.h>

int main()
{
  std::shared_ptr<mem_usage> mu;
  mu = std::make_shared<mem_usage>();
  while (true)
  {
    sleep(1);
    mu->tag();
    mu->show();
  }
}
