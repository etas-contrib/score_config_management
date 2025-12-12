[
    cc_library(
        name = "internal_config_provider_impl" + name,
        testonly = test_only,
        srcs = srcs,
        hdrs = hdrs,
        features = [
            "treat_warnings_as_errors",
            "additional_warnings",
            "strict_warnings",
        ],
        tags = ["FUSA"],
        visibility = [
            "//config_management/ConfigDaemon/test/xpad_ara_com_mock:__subpackages__",
            "//score/config_management/config_provider:__subpackages__",
        ],
        deps = [
            "//platform/aas/lib/concurrency:condition_variable",
            "//platform/aas/lib/concurrency/future",
            "@score-baselibs//score/json",
            "@score-baselibs//score/mw/log",
            "//score/config_management/config_provider/code/proxies:internal_config_provider",
        ] + dep,
    )
    for name, srcs, hdrs, test_only, dep in [
        (
            "_mw_com",
            ["mw_com/internal_config_provider_impl.cpp"],
            ["mw_com/internal_config_provider_impl.h"],
            False,
            [
                "//config_management/ConfigDaemon/code/services/details/mw_com/generated_service:internal_config_provider_type",
            ],
        ),
        (
            "_for_mw_com_unit_tests",
            ["mw_com/internal_config_provider_impl.cpp"],
            ["mw_com/internal_config_provider_impl.h"],
            False,
            [
                "//config_management/ConfigDaemon/code/services/details/mw_com/generated_service:internal_config_provider_type",
            ],
        ),
    ]
]

filegroup(
    name = "test_mw_com_config",
    srcs = ["mw_com/mw_com_config.json"],
    visibility = ["//score/config_management/config_provider:__subpackages__"],
)

cc_test(
    name = "unit_test_mw",
    srcs = [
        "mw_com/internal_config_provider_impl_test.cpp",
    ],
    data = [
        ":test_mw_com_config",
    ],
    features = [
        "treat_warnings_as_errors",
        "additional_warnings",
        "strict_warnings",
    ],
    tags = [
        "exclusive",  # Sandboxing is not properly working with LoLa message passing 2.0 (Ticket-217341)
        "unit",
    ],
    visibility = ["//score/config_management/config_provider/code/proxies:__pkg__"],
    deps = [
        ":internal_config_provider_impl_for_mw_com_unit_tests",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)
