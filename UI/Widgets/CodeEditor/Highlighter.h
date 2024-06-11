#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H
#include<QRegularExpression>
#include <QSyntaxHighlighter>
#include<QColor>
class XScriptHighlighter : public QSyntaxHighlighter
{
public:

    XScriptHighlighter(QTextDocument *parent = 0);

protected:
    void highlightBlock(const QString &text) Q_DECL_OVERRIDE;
private:
    struct HighlightingRule
    {
        QRegularExpression pattern;
        QTextCharFormat format;
    };
    QRegularExpression  commentStartExpression;
    QRegularExpression  commentEndExpression;
    QVector<HighlightingRule> highlightingRules;

    //关键字
    QTextCharFormat keywordFormat;
    //控件
    QTextCharFormat control_port_Format;
    QTextCharFormat control_chart_Format;
    QTextCharFormat control_input_Format;
    QTextCharFormat control_switchbutton_Format;
    QTextCharFormat control_button_Format;
    QTextCharFormat control_label_Format;
    //操作符
    QTextCharFormat operate_Format;


    QTextCharFormat singleLineKey;
    QTextCharFormat singleLineValue;

    QTextCharFormat singleLineCommentFormat;

    QTextCharFormat quotationFormat;
    QTextCharFormat functionFormat;
};

#endif // HIGHLIGHTER_H
