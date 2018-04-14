package main

import com.natpryce.konfig.*

object server : PropertyGroup() {
    val port by intType
}

val config = EnvironmentVariables() overriding
    ConfigurationProperties.fromResource("defaults.properties")
