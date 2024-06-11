#ifndef CODEEDITOR_H
#define CODEEDITOR_H
#include <QPainter>
#include <QTextBlock>
#include <QPlainTextEdit>
#include<QFontMetrics>
typedef enum{
    BROWSE,
    EDIT,
}editorMode;

class CodeEditor : public QPlainTextEdit
{
     Q_OBJECT
public:
    CodeEditor(QWidget*parent=nullptr);
    void setMode(editorMode mode);
    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();
protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);
private:
    QWidget *lineNumberArea;
};
class LineNumberArea : public QWidget
{
public:
    LineNumberArea(CodeEditor *editor) : QWidget(editor) {
        codeEditor = editor;
    }

    QSize sizeHint() const Q_DECL_OVERRIDE {
        return QSize(codeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    CodeEditor *codeEditor;
};
#endif // CODEEDITOR_H
