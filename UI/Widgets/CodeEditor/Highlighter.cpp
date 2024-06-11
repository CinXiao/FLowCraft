#include "Highlighter.h"

XScriptHighlighter::XScriptHighlighter(QTextDocument *parent) : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    //关键字
    keywordFormat.setForeground(QColor("#C0392B"));
    QStringList keywordPatterns;

    keywordPatterns<< "\\bIF\\b" << "\\bRETURN\\b" << "\\bRETURN\\b"<< "\\bPC\\b" << "\\bGOTO:.+\\b" << ".+::";
    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }



    control_port_Format.setFontWeight(QFont::Bold);
    control_port_Format.setForeground(QColor("#6A5ACD"));
    rule.pattern = QRegularExpression("\\bport(\\d+)");
    rule.format = control_port_Format;
    highlightingRules.append(rule);

    control_chart_Format.setFontWeight(QFont::Bold);
    control_chart_Format.setForeground(QColor("#2E8B57"));
    rule.pattern = QRegularExpression("\\bchart(\\d+)");
    rule.format = control_chart_Format;
    highlightingRules.append(rule);


    control_input_Format.setFontWeight(QFont::Bold);
    control_input_Format.setForeground(QColor("#008B8B"));
    rule.pattern = QRegularExpression("\\binput(\\d+)");
    rule.format = control_input_Format;
    highlightingRules.append(rule);



    control_switchbutton_Format.setFontWeight(QFont::Bold);
    control_switchbutton_Format.setForeground(QColor("#48C9B0"));
    rule.pattern = QRegularExpression("\\bswitchbutton(\\d+)");
    rule.format = control_switchbutton_Format;
    highlightingRules.append(rule);


    control_button_Format.setFontWeight(QFont::Bold);
    control_button_Format.setForeground(QColor("#85C1E9"));
    rule.pattern = QRegularExpression("\\bbutton(\\d+)");
    rule.format = control_button_Format;
    highlightingRules.append(rule);

    control_label_Format.setFontWeight(QFont::Bold);
    control_label_Format.setForeground(QColor("#CD6839"));
    rule.pattern = QRegularExpression("\\blabel(\\d+)");
    rule.format = control_label_Format;
    highlightingRules.append(rule);



    operate_Format.setFontWeight(QFont::Bold);
    operate_Format.setForeground(QColor("#8B008B"));
    rule.pattern = QRegularExpression("[=<>!\\-+*/]");
    rule.format = operate_Format;
    highlightingRules.append(rule);


    singleLineCommentFormat.setForeground(Qt::red);
    rule.pattern = QRegularExpression("#[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);



    quotationFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegularExpression("\".*\"");
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    functionFormat.setFontItalic(true);
    functionFormat.setForeground(Qt::blue);
    rule.pattern = QRegularExpression("\\b[A-Za-z0-9_]+(?=\\()");
    rule.format = functionFormat;
    highlightingRules.append(rule);

    commentStartExpression = QRegularExpression("/\\*");
    commentEndExpression = QRegularExpression("\\*/");
}

void XScriptHighlighter::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegularExpression expression(rule.pattern);
        auto it = expression.globalMatch(text);
        while (it.hasNext()) {
            auto match = it.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }

    setCurrentBlockState(0);
}
