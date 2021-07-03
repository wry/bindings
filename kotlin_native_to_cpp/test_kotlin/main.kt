import ktcpp.*

fun main(args: Array<String>) {
    val diz = Ktcpp_new()

    Ktcpp_load(diz,"/tmp/releases.rss")
    Ktcpp_select_nodes(diz, "//channel/item[description[contains(text(),\"iOS\") or contains(text(),\"iPadOS\")]][1]")

    Ktcpp_delete(diz)
}
