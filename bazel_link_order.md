# Why `deps` order matters for linking in Bazel

There are two separate layers to this question: what GNU ld does with archives,
and what Bazel does with `deps`.

---

## Layer 1: GNU ld archive scanning (well-documented)

When the GNU linker processes a static archive (`.a` file), it does **not**
unconditionally include everything in it. It scans the archive's symbol index
and extracts only those member object files whose symbols resolve a
currently-undefined reference. This scan happens in the order archives appear
on the linker command line. A consequence: the first archive that provides a
symbol for a pending undefined reference **"wins"** — a later archive that also
defines the same symbol is not extracted for that symbol.

The authoritative source for this is the **GNU Binutils ld manual**, specifically
the description of the `-l` / `--library` option:

> <https://sourceware.org/binutils/docs/ld/Options.html>

Search for "archive" in that page. The relevant paragraph (paraphrased from the
manual) says: the linker searches each archive once, in the order it appears,
extracting object modules that define symbols that have so far been referenced
but not defined. For cyclic dependencies between archives you need
`--start-group`/`--end-group` (which causes the group to be scanned repeatedly
until no new members are extracted), but **"first definition encountered wins"**
still holds.

---

## Layer 2: Bazel deps → linker command order (observable, not explicitly documented)

Bazel's `cc_test`/`cc_binary` rules collect libraries from the transitive `deps`
graph and pass them to the linker. For direct deps at the same level in your
`deps` list, Bazel preserves their listed order in the generated link command.
Bazel's C++ reference at <https://bazel.build/reference/be/c-cpp#cc_test> does
**not** explicitly guarantee this ordering, but you can verify it yourself:

```sh
bazel aquery 'deps(//score/config_management/config_daemon/code:main_function_test)' \
  --output=text 2>/dev/null | grep -A5 "CppLink"
```

This shows the exact link command Bazel generates, confirming whether `deps`
order maps to link argument order.

---

## Applying both layers to the two targets in this project

| Target | Order in `deps` | Effect |
|---|---|---|
| `main_function_test` | `lifecycle_mock_cc` **before** `lifecycle_cc` | Mock's `.cpp` is extracted first (satisfies `LifeCycleManager::run()` undefined ref); real lib comes later, that symbol is already defined → real lib's object **not** extracted. Mock wins. |
| `unit_test` | `lifecycle_cc` **before** `lifecycle_mock_cc` | Real lib extracted first; when mock is processed, the conflicting symbols are already defined → mock's conflicting objects not extracted. Real lib wins. |

This is the same **"first match wins"** GNU ld rule in both cases — just with the
ordering flipped to get the desired outcome.
