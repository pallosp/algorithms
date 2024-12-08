package(default_visibility = ["//:__subpackages__"])

cc_library(
    name = "point",
    hdrs = ["point.h"],
)

cc_library(
    name = "primes",
    srcs = ["primes.cc"],
    hdrs = ["primes.h"],
)

cc_binary(
    name = "primes_demo",
    srcs = ["primes_demo.cc"],
    deps = [":primes"],
)
