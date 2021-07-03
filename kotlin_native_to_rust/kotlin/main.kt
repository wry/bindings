import kotlinx.cinterop.*
import ktr.*

fun main(args: Array<String>) {
    // ptr must be freed
    val item_ptr = ktr.first_crelease_item("/tmp/releases.rss")
    val item = item_ptr?.pointed

    val title = item?.title?.toKString() ?: ""
    val link = item?.link?.toKString() ?: ""
    val description = item?.description?.toKString() ?: ""
    val pub_date = item?.pub_date?.toKString() ?: ""

    println("${title}, ${description}, ${link}, ${pub_date}")

    // free ptr
    ktr.release_crelease_item(item_ptr)
}
