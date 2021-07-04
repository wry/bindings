import kotlinx.cinterop.*

import lar.*

fun main(args: Array<String>) = memScoped {
    val lar = Lar_new()

    val error = alloc<CPointerVar<ByteVar>>()
    val release = Lar_first_release_item(lar, "/tmp/releases.rss", error.ptr)

    if (release == null)
    {
        val error_str = error.value?.toKString() ?: ""
        println("Error : ${error_str}")
        return
    }

    val crelease = alloc<CRelease>()
    Release_copy_into(release, crelease.ptr)

    val title = crelease.title?.toKString() ?: ""
    val link = crelease.link?.toKString() ?: ""
    val description = crelease.description?.toKString() ?: ""
    val pub_date = crelease.pub_date?.toKString() ?: ""

    println("${title}, ${description}, ${link}, ${pub_date}")

    Release_delete(release)
    Lar_delete(lar)
}
