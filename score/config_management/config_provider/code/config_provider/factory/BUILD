load("@score-baselibs//:bazel/unit_tests.bzl", "cc_unit_test_suites_for_host_and_qnx")

[
    cc_library(
        name = "factory" + name,
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
            "//platform/aas/pas/calibration_server/code:__subpackages__",
            "//config_management/ConfigDaemon/test:__subpackages__",
            "//score/config_management/config_provider:__subpackages__",
        ],
        deps = [
            "@score-baselibs//score/mw/log",
            "//platform/aas/mw/service:factory",
            "//score/config_management/config_provider/code/config_provider/details",
            "//score/config_management/config_provider/code/persistency/details:persistency_empty",
        ] + dep,
    )
    for name, test_only, srcs, hdrs, dep in [
        (
            "_mw_com",
            False,
            ["factory_mw_com.cpp"],
            ["factory_mw_com.h"],
            [
                "//score/config_management/config_provider/code/proxies/details:internal_config_provider_impl_mw_com",
                "//platform/aas/mw/service/backend/mw_com:single_instantiation_strategy",
            ],
        ),
        (
            "_mw_com_for_unit_tests",
            True,
            ["factory_mw_com.cpp"],
            ["factory_mw_com.h"],
            [
                "//score/config_management/config_provider/code/proxies/details:internal_config_provider_impl_for_mw_com_unit_tests",
                "//platform/aas/mw/service/backend/mw_com:single_instantiation_strategy",
            ],
        ),
    ]
]

filegroup(
    name = "test_mw_com_config",
    srcs = ["mw_com_config.json"],
)

cc_test(
    name = "unit_tests_mw_com",
    srcs = ["factory_mw_com_test.cpp"],
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
    visibility = [
        "//score/config_management/config_provider:__subpackages__",
    ],
    deps = [
        ":factory_mw_com_for_unit_tests",
        "//score/config_management/config_provider/code/persistency:mock",
        "@googletest//:gtest_main",
    ],
)

cc_unit_test_suites_for_host_and_qnx(
    name = "unit_tests",
    cc_unit_tests = [
        ":unit_tests_mw_com",
    ],
    visibility = ["//score/config_management/config_provider:__subpackages__"],
)
