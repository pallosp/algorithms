load("@hedron_compile_commands//:refresh_compile_commands.bzl", "refresh_compile_commands")

# bazel run //:refresh_compile_commands
# to refresh code completion for bazel deps
refresh_compile_commands(
    name = "refresh_compile_commands",
    targets = {"//...": ""},
)
