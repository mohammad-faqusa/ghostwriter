// SPDX-License-Identifier: GPL-3.0-or-later

#include <QApplication>
#include <QTest>
#include <QTextCursor>

#include "../../src/editor/markdowneditor.h"
#include "../../src/editor/markdowndocument.h"
#include "../../src/editor/colorscheme.h"

using namespace ghostwriter;

class MarkdownEditorTest : public QObject
{
    Q_OBJECT

private slots:
    void nestedNumberedList();
    void nestedBulletList();
    void nestedTaskList();
    void topLevelListExit();
    void unrelatedListBoundary();
};

void MarkdownEditorTest::nestedNumberedList()
{
    MarkdownDocument document;
    ColorScheme colors{};

    MarkdownEditor editor(&document, colors);

    editor.setPlainText(
        "1. Java\n"
        "   1. Variables\n"
        "      1. int\n"
        "      2. double"
    );

    QTextCursor cursor = editor.textCursor();
    cursor.movePosition(QTextCursor::End);
    editor.setTextCursor(cursor);

    editor.show();
    editor.setFocus();

    QTest::keyClick(&editor, Qt::Key_Return);
    QTest::keyClick(&editor, Qt::Key_Return);

    const QString expected =
        "1. Java\n"
        "   1. Variables\n"
        "      1. int\n"
        "      2. double\n"
        "   2. ";

    QCOMPARE(editor.toPlainText(), expected);
}

void MarkdownEditorTest::nestedBulletList()
{
    MarkdownDocument document;
    ColorScheme colors{};
    MarkdownEditor editor(&document, colors);

    editor.setPlainText(
        "- Programming\n"
        "   - Java\n"
        "      - Variables"
    );

    QTextCursor cursor = editor.textCursor();
    cursor.movePosition(QTextCursor::End);
    editor.setTextCursor(cursor);

    editor.show();
    editor.setFocus();

    QTest::keyClick(&editor, Qt::Key_Return);
    QTest::keyClick(&editor, Qt::Key_Return);

    const QString expected =
        "- Programming\n"
        "   - Java\n"
        "      - Variables\n"
        "   - ";

    QCOMPARE(editor.toPlainText(), expected);
}

void MarkdownEditorTest::nestedTaskList()
{
    MarkdownDocument document;
    ColorScheme colors{};
    MarkdownEditor editor(&document, colors);

    editor.setPlainText(
        "- [ ] Learn Java\n"
        "   - [x] Learn variables\n"
        "      - [ ] Practice integers"
    );

    QTextCursor cursor = editor.textCursor();
    cursor.movePosition(QTextCursor::End);
    editor.setTextCursor(cursor);

    editor.show();
    editor.setFocus();

    QTest::keyClick(&editor, Qt::Key_Return);
    QTest::keyClick(&editor, Qt::Key_Return);

    const QString expected =
        "- [ ] Learn Java\n"
        "   - [x] Learn variables\n"
        "      - [ ] Practice integers\n"
        "   - [ ] ";

    QCOMPARE(editor.toPlainText(), expected);
}

void MarkdownEditorTest::topLevelListExit()
{
    MarkdownDocument document;
    ColorScheme colors{};
    MarkdownEditor editor(&document, colors);

    editor.setPlainText("- Java");

    QTextCursor cursor = editor.textCursor();
    cursor.movePosition(QTextCursor::End);
    editor.setTextCursor(cursor);

    editor.show();
    editor.setFocus();

    QTest::keyClick(&editor, Qt::Key_Return);
    QTest::keyClick(&editor, Qt::Key_Return);

    QCOMPARE(editor.toPlainText(), QString("- Java\n\n"));
}

void MarkdownEditorTest::unrelatedListBoundary()
{
    MarkdownDocument document;
    ColorScheme colors{};
    MarkdownEditor editor(&document, colors);

    editor.setPlainText(
        "1. Previous topic\n"
        "\n"
        "## New section\n"
        "\n"
        "   - Current item"
    );

    QTextCursor cursor = editor.textCursor();
    cursor.movePosition(QTextCursor::End);
    editor.setTextCursor(cursor);

    editor.show();
    editor.setFocus();

    QTest::keyClick(&editor, Qt::Key_Return);
    QTest::keyClick(&editor, Qt::Key_Return);

    const QString expected =
	    "1. Previous topic\n"
	    "\n"
	    "## New section\n"
	    "\n"
	    "   - Current item\n"
	    "   \n";

    QCOMPARE(editor.toPlainText(), expected);
}

QTEST_MAIN(MarkdownEditorTest)
#include "markdowneditortest.moc"
