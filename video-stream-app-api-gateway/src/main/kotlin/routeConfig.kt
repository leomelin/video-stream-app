package main

import org.http4k.client.OkHttp
import org.http4k.core.HttpHandler
import org.http4k.core.Method.GET
import org.http4k.core.Method.POST
import org.http4k.core.Request
import org.http4k.core.Response
import org.http4k.core.Status.Companion.OK
import org.http4k.core.Uri
import org.http4k.routing.bind

fun getRoutes() = listOf(
    "/ping" bind GET to { _: Request -> Response(OK).body("pong!") },
    "/youtube-integrator" bind POST to { req -> proxy(req, "http://localhost:8099") },
    "/youtube-integrator" bind GET to { req -> proxy(req, "http://localhost:8099") },
    "/obs-commander" bind POST to { req -> proxy(req, "http://localhost:3002/graphql") },
    "/obs-commander" bind GET to { req -> proxy(req, "http://localhost:3002/graphql") }
)

fun proxy(req: Request, uri: String): Response {
    val client: HttpHandler = OkHttp()
    return client(Request(req.method, Uri.of(uri)).body(req.body).headers(req.headers))
}

