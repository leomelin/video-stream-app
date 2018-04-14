package main

import org.http4k.routing.routes
import org.http4k.server.Jetty
import org.http4k.server.asServer

// Example here: https://github.com/http4k/http4k

fun main(args: Array<String>) {
    println("Server started in port ${config[server.port]}")
    routes(*getRoutes().toTypedArray()).asServer(Jetty(config[server.port])).start()
}

