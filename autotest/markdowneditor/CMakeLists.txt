# SPDX-License-Identifier: GPL-3.0-or-later

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Test)

ecm_add_test(
    markdowneditortest.cpp

    ../../src/editor/markdowneditor.cpp
    ../../src/editor/markdowndocument.cpp
    ../../src/editor/markdownhighlighter.cpp
    ../../src/editor/actions/inlinemarkuptoggle.cpp

    ../../src/markdown/cmarkgfmapi.cpp
    ../../src/markdown/markdownast.cpp
    ../../src/markdown/markdownnode.cpp
    ../../src/markdown/memoryarena.cpp

    LINK_LIBRARIES
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Test
        libcmark-gfm_static
        libcmark-gfm-extensions_static

    TEST_NAME markdowneditortest
)

target_include_directories(markdowneditortest PRIVATE
    "${CMAKE_SOURCE_DIR}"
    "${CMAKE_SOURCE_DIR}/src"
    "${CMAKE_BINARY_DIR}"
    "${CMAKE_BINARY_DIR}/3rdparty/cmark-gfm/src"
)