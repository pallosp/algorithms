package(default_visibility = ["//:__subpackages__"])

cc_library(
    name = "convex_hull",
    srcs = ["convex_hull.cc"],
    hdrs = ["convex_hull.h"],
    deps = [
        ":point",
        ":polygon",
    ],
)

cc_library(
    name = "point",
    hdrs = ["point.h"],
)

cc_library(
    name = "polygon",
    srcs = ["polygon.cc"],
    hdrs = ["polygon.h"],
    deps = [":point"],
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
