#include <ktcpp.h>

int main()
{
  Ktcpp * diz = Ktcpp_new();

  Ktcpp_load(diz,"/tmp/releases.rss");
  Ktcpp_select_nodes(diz, "//channel/item[description[contains(text(),\"iOS\") or contains(text(),\"iPadOS\")]][1]");

  Ktcpp_delete(diz);
  return 0;
}
